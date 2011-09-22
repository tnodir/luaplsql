-- Pl/Sql Developer Lua Plug-In Addon: Session


-- Variables

local AddMenu = ...

local plsql = plsql
local SYS, IDE, SQL = plsql.sys, plsql.ide, plsql.sql

local ShowMessage = plsql.ShowMessage


-- Re-Connect To Database
local OnConnectionChange
do
	local username, password, database

	OnConnectionChange = function()
		if IDE.Connected() then
			username, password, database = IDE.GetConnectionInfo()
		end
	end

	local function ReConnect()
		if username then
			IDE.SetConnection(username, password, database)
		end
	end

	AddMenu(ReConnect, "&Lua / Session / Re-Connect")
end


-- Initialization
local function OnActivate()

	-- Plugin called after connection established
	OnConnectionChange()
end


-- Addon description
local function About()
	return "Session Utilities"
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

