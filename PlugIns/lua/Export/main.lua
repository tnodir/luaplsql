-- Pl/Sql Developer Lua Plug-In Addon: Exports


local sys = require("sys")


-- Variables

local AddMenu, rootPath, dirName = ...

local plsql = plsql
local SYS, IDE, SQL = plsql.sys, plsql.ide, plsql.sql

local exports = {}

local CurExportInit, CurExportFinished, CurExportPrepare, CurExportData

local buffer = sys.mem.pointer()

local filename


-- Addon description
local function About()
	return "Exports"
end


local function RegisterExport()

	-- Export filters
	local n, filter = 1, ""

	-- Traverse export directory
	local root = rootPath .. "\\" .. dirName .. "\\"

	for name, is_dir in sys.dir(root) do
		if is_dir then
			local chunk, err = loadfile(root .. name .. "\\main.lua")
			if not chunk then
				plsql.ShowMessage(err)
			else
				local title, ext, funcs = chunk(root, name)
				if title then
					exports[n], n = funcs, n + 1

					filter = filter	.. title
						.. " files (*." .. ext .. ")\0"
						.. "*." .. ext .. "\0"
				end
			end
		end
	end

	exports.filter = filter .. "\0\0"
end


local function ExportInit()

	-- Get export filename
	local index
	filename, index = plsql.GetSaveFileName(nil, exports.filter)
	if not (filename and buffer:alloc()) then
		return false
	end

	local funcs = exports[index]

	CurExportInit = funcs[1]
	CurExportFinished = funcs[2]
	CurExportPrepare = funcs[3]
	CurExportData = funcs[4]

	if CurExportInit then
		return CurExportInit(buffer)
	end
end


local function ExportFinished()
	if CurExportFinished then
		CurExportFinished()
	end

	-- Write file
	local fd = sys.handle()
	if not (fd:create(filename)
		and fd:write(buffer:getstring()))
	then
		plsql.ShowMessage(errorMessage)
	end
	fd:close()

	buffer:close()

	collectgarbage("collect")
	collectgarbage("collect")
end


local function ExportPrepare()
	if CurExportPrepare then
		return CurExportPrepare()
	end
end


local function ExportData(value)
	if CurExportData then
		return CurExportData(value)
	end
end


return {
	OnActivate,
	OnDeactivate,
	CanClose,
	AfterStart,
	AfterReload,
	OnBrowserChange,
	OnWindowChange,
	OnWindowCreate,
	OnWindowCreated,
	OnWindowClose,
	BeforeExecuteWindow,
	AfterExecuteWindow,
	OnConnectionChange,
	OnPopup,
	OnMainMenu,
	OnTemplate,
	OnFileLoaded,
	OnFileSaved,
	About,
	CommandLine,
	RegisterExport,
	ExportInit,
	ExportFinished,
	ExportPrepare,
	ExportData
}

