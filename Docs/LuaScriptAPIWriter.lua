-- LuaScriptAPI.dox Generator

require('LuaScriptAPIParser')

-- Write class list section
function writeClassList(output)
    output:write('\n\\section LuaScriptAPI_ClassList Class list\n\n')
    for _, class in ipairs(classes) do
        output:write('<a href="#Class_' .. class.name .. '"><b>' .. class.name .. '</b></a>\n')
    end
end

-- Write classes section
function writeClasses(output)
    output:write('\n\\section LuaScriptAPI_Classes Classes\n\n')

    for _, class in ipairs(classes) do      
        output:write('<a name="Class_' .. class.name .. '"></a>\n')

        if class.bases == nil then
            output:write('### ' .. class.name)
        else
            output:write('### ' .. class.name .. ' : ' .. class.bases)
        end

        if #class.constructors > 0 then
            output:write('\n')
            for _, item in ipairs(class.constructors) do
                output:write('- ' .. item .. '\n')
            end
        end

        if #class.methods > 0 then
            output:write('\nMethods:\n\n')
            for _, item in ipairs(class.methods) do
                output:write('- ' .. item .. '\n')
            end
        end

        if #class.properties > 0 then
            output:write('\nProperties:\n\n')
            for _, item in ipairs(class.properties) do
                output:write('- ' .. item .. '\n')
            end
        end

        if #class.fields > 0 then
            output:write('\nFields:\n\n')
            for _, item in ipairs(class.fields) do
                output:write('- ' .. item .. '\n')
            end
        end

        if #class.staticConstants > 0 then
            output:write('\nStaticConstants:\n\n')
            for _, item in ipairs(class.staticConstants) do
                output:write('- ' .. item .. '\n')
            end
        end
        
        output:write('\n')
    end
end

-- Write enums section
function writeEnums(output)
    output:write('\n\\section LuaScriptAPI_Enums Enumerations\n\n')

    for _, enum in ipairs(enums) do
        output:write('\n### ' .. enum.name .. '\n\n')
        for _, item in ipairs(enum.items) do
            output:write('- int ' .. item .. '\n')
        end
    end
end

-- Write global functions section
function writeGlobalFunctons(output)
    output:write('\n\\section LuaScriptAPI_GlobalFunctions Global functions\n\n')

    for _, func in ipairs(functions) do
        output:write('- ' .. func.signature .. '\n')
    end
end

-- Write global properties section
function writeGlobalProperties(output)
    output:write('\n\\section LuaScriptAPI_GlobalProperties Global properties\n\n')
    
    for _, variable in ipairs(variables) do
        output:write('- ' .. variable.signature .. '\n')
    end

    for _, constant in ipairs(constants) do
        output:write('- ' .. constant.signature .. ' (readonly)\n')
    end
end

-- Write dox file
function writeDoxFile(doxFileName)
    output = io.open(doxFileName, 'wt')

    output:write(
[[
namespace Urho3D
{

/**
\page LuaScriptAPI Lua scripting API

\section LuaScriptAPI_TableOfContents Table of contents

\ref LuaScriptAPI_ClassList "Class list"<br>
\ref LuaScriptAPI_Classes "Classes"<br>
\ref LuaScriptAPI_Enums "Enumerations"<br>
\ref LuaScriptAPI_toluaFunctions "tolua functions"<br>
\ref LuaScriptAPI_GlobalFunctions "Global functions"<br>
\ref LuaScriptAPI_GlobalProperties "Global properties"<br>
\ref LuaScriptAPI_GlobalConstants "Global constants"<br>
]])

    writeClassList(output)
    writeClasses(output)
    writeEnums(output)
    writeGlobalFunctons(output)
    writeGlobalProperties(output)

    output:write(
[[*/

}
]])

    output:close()
end

-- Parse Lua script API
parseLuaScriptAPI()

-- Write dox file
writeDoxFile('LuaScriptAPI.dox')
