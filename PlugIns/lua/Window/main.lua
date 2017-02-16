-- Pl/Sql Developer Lua Plug-In Addon: Window


-- Variables

local AddMenu = ...

local plsql = plsql
local SYS, IDE, SQL = plsql.sys, plsql.ide, plsql.sql

local ShowMessage = plsql.ShowMessage


-- Reload File
do
	AddMenu(IDE.ReloadFile, "Lua / Window / Reload File")
end


-- Close All Quietly
do
	local function CloseAllQuietly()
		local windowCount = IDE.GetWindowCount()
		if windowCount == 0 or plsql.MessageBox(
			"Do you really want to close all windows without save?",
			"Close All Quietly", "YesNo", "Question") == "No"
		then return end

		for i = 0, windowCount - 1 do
			IDE.SelectWindow(i)
			IDE.CloseFile(plsql.WindowClose.Quiet)
		end
	end

	AddMenu(CloseAllQuietly, "Lua / Window / Close All Quietly")
end


-- Read-Only Mode
do
	local function ToggleReadOnly()
		IDE.SetReadOnly(not IDE.GetReadOnly())
	end  

	AddMenu(ToggleReadOnly, "Lua / Window / Read-Only")
end 


-- Fullscreen Mode [Experimental]
do
	local isFullscreen

	local function ToggleFullscreen()
		local windowHandle = IDE.GetWindowHandle()
		local clientHandle = IDE.GetClientHandle()

		isFullscreen = not isFullscreen
		if isFullscreen then
			local w, h = plsql.GetWindowArea(windowHandle)
			plsql.SetWindowPos(clientHandle, 0, 0, w, h)
		else
			plsql.ShowWindow(windowHandle, "restore")
			plsql.ShowWindow(windowHandle, "maximize")
		end
	end

	AddMenu(ToggleFullscreen, "Lua / Window / Fullscreen")
end


-- Addon description
local function About()
	return "Window Utilities"
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
	OnWindowConnectionChange,
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

