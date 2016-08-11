-- Script use to generate LuaScriptAPI.dox file

doxFileName = 'LuaScriptAPI_New.dox'

require('LuaScriptAPIParser')


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

parseFile(luaScriptDir .. 'LuaScriptLuaAPI.cpp')

function compareByName(a, b)
	return a.name < b.name
end

table.sort(classes, compareByName)
table.sort(enums, compareByName)
table.sort(functions, compareByName)
table.sort(constants, compareByName)
table.sort(variables, compareByName)

function writeClassList(output)
	output:write('\n')
	output:write('\\section LuaScriptAPI_ClassList Class list')
	output:write('\n')

	for _, class in ipairs(classes) do
		output:write('<a href="#Class_' .. class.name .. '"><b>' .. class.name .. '</b></a>')
		output:write('\n')
	end
end

function writeClasses(output)
	output:write('\n')
	output:write('\\section LuaScriptAPI_Classes Classes')
	output:write('\n')

	for _, class in ipairs(classes) do
		-- output:write('<a href="#Class_' .. class.name .. '"><b>' .. class.name .. '</b></a>')
		output:write('<a name="Class_' .. class.name .. '"></a>')

		output:write('\n')
		if class.bases == nil then
			output:write('### ' .. class.name)
		else
			output:write('### ' .. class.name .. ' : ' .. class.bases)
		end

		if #class.constructors > 0 then
			output:write('\n')
			for _, item in ipairs(class.constructors) do
				output:write('- ' .. item)
				output:write('\n')
			end
		end

		if #class.methods > 0 then
			output:write('\n')
			output:write('Methods:')
			output:write('\n')
			output:write('\n')
			for _, item in ipairs(class.methods) do
				output:write('- ' .. item)
				output:write('\n')
			end
		end

		if #class.properties > 0 then
			output:write('\n')
			output:write('Properties:')
			output:write('\n')
			output:write('\n')
			for _, item in ipairs(class.properties) do
				output:write('- ' .. item)
				output:write('\n')
			end
		end

		if #class.fields > 0 then
			output:write('\n')
			output:write('Fields:')
			output:write('\n')
			output:write('\n')
			for _, item in ipairs(class.fields) do
				output:write('- ' .. item)
				output:write('\n')
			end
		end

		if #class.staticConstants > 0 then
			output:write('\n')
			output:write('StaticConstants:')
			output:write('\n')
			output:write('\n')
			for _, item in ipairs(class.staticConstants) do
				output:write('- ' .. item)
				output:write('\n')
			end
		end


		output:write('\n')
	end
end

function writeEnums(output)
	output:write('\n')
	output:write('\\section LuaScriptAPI_Enums Enumerations')
	output:write('\n')
	output:write('\n')

	for _, enum in ipairs(enums) do
		output:write('\n')
		output:write('### ' .. enum.name)
		output:write('\n')
		output:write('\n')
		for _, item in ipairs(enum.items) do
			output:write('- int ' .. item)
			output:write('\n')
		end
	end
end

function writeGlobalFunctons(output)
	output:write('\n')
	output:write('\\section LuaScriptAPI_GlobalFunctions Global functions')
	output:write('\n')
	output:write('\n')

	for _, func in ipairs(functions) do
		output:write('- ' .. func.signature)
		output:write('\n')
	end
end

function writeGlobalProperties(output)
	output:write('\n')
	output:write('\\section LuaScriptAPI_GlobalProperties Global properties')
	output:write('\n')
	output:write('\n')
	
	for _, variable in ipairs(variables) do
		output:write('- ' .. variable.signature)
		output:write('\n')
	end

	for _, constant in ipairs(constants) do
		output:write('- ' .. constant.signature .. ' (readonly)')
		output:write('\n')
	end
end

function writeDocumentation()
	output = io.open(doxFileName, 'wt')

	output:write('namespace Urho3D\n')
	output:write('{\n')
	output:write('/**\n')
	output:write('\\page LuaScriptAPI Lua scripting API\n')
	output:write('\n')
	output:write('\\section LuaScriptAPI_TableOfContents Table of contents\n')
	output:write('\n')
	output:write('\\ref LuaScriptAPI_ClassList "Class list"<br>\n')
	output:write('\\ref LuaScriptAPI_Classes "Classes"<br>\n')
	output:write('\\ref LuaScriptAPI_Enums "Enumerations"<br>\n')
	output:write('\\ref LuaScriptAPI_toluaFunctions "tolua functions"<br>\n')
	output:write('\\ref LuaScriptAPI_GlobalFunctions "Global functions"<br>\n')
	output:write('\\ref LuaScriptAPI_GlobalProperties "Global properties"<br>\n')
	output:write('\\ref LuaScriptAPI_GlobalConstants "Global constants"<br>\n')


	writeClassList(output)
	writeClasses(output)
	writeEnums(output)
	writeGlobalFunctons(output)
	writeGlobalProperties(output)

	output:write('*/\n\n}\n')

	output:close()
end

writeDocumentation()