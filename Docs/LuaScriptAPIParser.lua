-- Lua script API Parser

luaScriptDir = '../Source/Urho3D/LuaScript/'

-- All enums
enums = {}
-- All classes
classes = {}

-- All global functions
functions = {}
-- All global variables
variables = {}
-- All global constants
constants = {}

-- Parse line then return type and value
function parseLine(line)
    type, value = line:match('// %[(.+)%] (.+)')
    return type, value
end

-- Parse enum
function parseEnum(line)
    if #line == 0 then
        -- End of enum
        current_enum = nil
    else
        item, _ = line:match('lua%[%"(.+)%"%] = (.+);')
        if item ~= nil then
            table.insert(current_enum.items, item)
        end
    end
end

-- Parse class
function parseClass(line)
    if line:find(');') ~= nil or line == '// [ClassEnd]' then
        -- End of class
        current_class = nil
    else
        type, value = parseLine(line)
        if type == 'Constructor' then
            table.insert(current_class.constructors, value)

        elseif type == 'Method' then
            table.insert(current_class.methods, value)

        elseif type == 'Property' then
            table.insert(current_class.properties, value)

        elseif type == 'Property(Readonly)' then
            table.insert(current_class.properties, value .. ' (readonly)')

        elseif type == 'Property(Writeonly)' then
            table.insert(current_class.properties, value .. ' (writeonly)')

        elseif type == 'Field' then
            table.insert(current_class.fields, value)

        elseif type == 'StaticConstant' then
            table.insert(current_class.staticConstants, value)
        end
    end
end

-- Get name of constant and variable
function getName(value)
    local name = ''
    for n in value:gmatch('%S+') do
        name = n
    end
    return name
end

-- Parse binding file
function parseFile(fileName)
    -- print('Parse file ' .. fileName)

    file = io.open(fileName, 'rt')
    for line in file:lines() do
        -- trim
        line = line:match'^%s*(.*%S)' or ''

        if current_enum ~= nil then
            parseEnum(line)

        elseif current_class ~= nil then
            parseClass(line)

        else
            type, value = parseLine(line)
            
            if type == 'Enum' then
                current_enum = {
                    name = value,
                    items = {}
                }
                table.insert(enums, current_enum)

            elseif type == 'Class' then
                name, bases = value:match('(.+) : (.+)')
                if name == nil then
                    name = value
                end

                current_class = {
                    name = name,
                    bases = bases,
                    constructors = {},
                    methods = {},
                    properties = {},
                    fields = {},
                    staticConstants = {}
                }
                table.insert(classes, current_class)

            elseif type == 'Function' then
                local name = ''
                for n in value:gmatch('%S+%(') do
                    name = n
                end
                func = {
                    name = name,
                    signature = value
                }
                table.insert(functions, func)

			elseif type == 'Variable' then
                local name = getName(value)
                variable = {
                    name = name,
                    signature = value
                }
                table.insert(variables, variable)

            elseif type == 'Constant' then
                local name = getName(value)
                constant = {
                    name = name,
                    signature = value
                }
                table.insert(constants, constant)
                                                
            end
        end
    end

    file:close()
end

-- Parse module
function parseModule(moduleName)
    local moduleFileName = luaScriptDir .. moduleName .. 'LuaAPI.cpp'
    -- print('Parse module ' .. moduleFileName)

    moduleFile = io.open(moduleFileName, 'rt')

    local fileNames = {}
    for line in moduleFile:lines() do
        name = line:match('extern void Register(%w+)')
        if name ~= nil then
            local fileName = luaScriptDir .. moduleName .. '/' .. name .. 'Binding.cpp'
            table.insert(fileNames, fileName)
        end
    end
    moduleFile:close()

    for _, fileName in ipairs(fileNames) do
        parseFile(fileName)
    end
end

-- Parser Lua script API
function parseLuaScriptAPI()
    parseModule('Audio')
    parseModule('Core')
    parseModule('Database')
    parseModule('Engine')
    parseModule('Graphics')
    parseModule('Input')
    parseModule('IO')
    parseModule('Math')
    parseModule('Navigation')
    parseModule('Network')
    parseModule('Physics')
    parseModule('Resource')
    parseModule('Scene')
    parseModule('UI')
    parseModule('Urho2D')

    -- LuaScriptLuaAPI.cpp includes some binding code
    parseFile(luaScriptDir .. 'LuaScriptLuaAPI.cpp')

    function compareByName(a, b)
        return a.name < b.name
    end

    -- Sort by name
    table.sort(classes, compareByName)
    table.sort(enums, compareByName)
    table.sort(functions, compareByName)
    table.sort(constants, compareByName)
    table.sort(variables, compareByName)
end
