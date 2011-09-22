-- Pl/Sql Developer Lua Plug-In Addon: Exports: RTF

-- See "PLSQL Developer\PlugInDoc\Delphi\rtf export\RTFExportUnit.pas"


local sys = require("sys")


-- Variables

local plsql = plsql
local SYS, IDE, SQL = plsql.sys, plsql.ide, plsql.sql

local Gsub, Floor = string.gsub, math.floor

local out, colCount, curCol, prepared, header


-- RTF Related functions


-- Add new line
local function AddNewLine()
	out:write("\r\n")
end


-- Start a group with a {
local function StartGroup(controlWord)
	out:write('{')
	if controlWord then
		out:write('\\', controlWord)
	end
end

-- End a group with a }
local function EndGroup()
	-- Trailing space?
	local len = out:seek() - 1
	if out[len] == 32 then
		out:seek(len)
	end
	out:write('}')
	AddNewLine()
end

-- Start a control word with a /
local function AddControlWord(title, value, group)
	if group then
		StartGroup(title)
	else
		out:write('\\', title)
	end
	if value ~= '' then
		if type(value) ~= "number" then
			out:write(' ')
		end
		out:write(value)
	end
	if group then EndGroup() end
end

-- Convert special characters
local function RTFString(str)
	return (Gsub(str, "[}{\\\n]", {
		['}'] = '\\}',
		['{'] = '\\{',
		['\\'] = '\\\\',
		['\n'] = '\n\\par ',
	}))
end

-- Create the RTF header with some general info
local function RTFStart(title, author, company)
	local now = sys.date({})

	StartGroup('rtf')
	StartGroup('info')
	AddControlWord('title', RTFString(title), true)
	AddControlWord('author', RTFString(author), true)
	StartGroup('creatim')
	AddControlWord('yr', now.year)
	AddControlWord('mo', now.month)
	AddControlWord('dy', now.day)
	AddControlWord('hr', now.hour)
	AddControlWord('min', now.min)
	EndGroup()
	AddControlWord('company', RTFString(company), true)
	EndGroup()
end

-- Some formating for the rows
local function RTFFormat1()
	AddControlWord([[pard \nowidctlpar\widctlpar\intbl\adjustright]], '')
	AddNewLine()
end

-- Some formating, used at the end of the file
local function RTFFormat2()
	AddControlWord([[pard \nowidctlpar\widctlpar\adjustright]], '')
	AddNewLine()
end

-- Close the RTF
local function RTFEnd()
	RTFFormat2()
	AddControlWord('par', '', true)
	EndGroup()
end

-- Start a RTF row
local function RTFStartRow()
	AddControlWord('trowd', '')
	AddNewLine()
	for i = 1, colCount do
		AddControlWord('cellx', Floor(9000 * i / colCount))
	end
	AddNewLine()
	RTFFormat1()
	StartGroup()
end

-- Add one cell
local function RTFAddCell(value)
	out:write(RTFString(value))
	AddControlWord('cell ', '')
end

-- End the row
local function RTFEndRow()
	EndGroup()
	AddControlWord('row', '', true)
end


-- Export related functions


--
-- First call after an export request
-- You can ask the user for a filename or initialize stuff.
-- Return False if you want to cancel the export.
--
local function ExportInit(buffer)
	out = buffer
	colCount = 0
	curCol = 0
	prepared = false
	header = {}
end


--
-- Done, everything is exported.
--
local function ExportFinished()
	RTFEnd()
	out = nil
end


--
-- This function allows you to prepare for the actual data
-- All values received with Exportdata before this function is called are column headers,
-- and all values received after ExportPrepare is data.
--
local function ExportPrepare()
	RTFStart('PL/SQL Developer Export', '', 'Lua')
	RTFFormat1()
	-- First add the buffered header
	RTFStartRow()
	for i = 1, colCount do
		RTFAddCell(header[i])
	end
	RTFEndRow()
	prepared = true
	header = nil
end


--
-- One cell of data, this can be the column description or the actual data.
--
local function ExportData(value)
	if not prepared then
		colCount = colCount + 1
		header[colCount] = value
	else
		if curCol == 0 then RTFStartRow() end
		RTFAddCell(value)
		curCol = curCol + 1
		if curCol == colCount then
			curCol = 0
			RTFEndRow()
		end
	end
end


return "RTF", "rtf", {
	ExportInit,
	ExportFinished,
	ExportPrepare,
	ExportData
}

