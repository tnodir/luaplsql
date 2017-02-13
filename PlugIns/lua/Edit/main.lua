-- Pl/Sql Developer Lua Plug-In Addon: Edit


-- Variables

local AddMenu = ...

local plsql = plsql
local SYS, IDE, SQL = plsql.sys, plsql.ide, plsql.sql

local ShowMessage = plsql.ShowMessage

local Gsub, Sub, Upper, Lower = string.gsub, string.sub, string.upper, string.lower


-- Scroll Up/Down
do
	local upMenuItem

	local function Scroll(menuItem)
		local step = (menuItem == upMenuItem) and -1 or 1
		IDE.LineScroll(0, step)
		IDE.SetCursor(0, IDE.GetCursorY() + step)
	end
	
	AddMenu(nil, "TAB=LuaPLSQL")
	AddMenu(nil, "GROUP=Edit")
	upMenuItem = AddMenu(Scroll, "ITEM=Scroll Up")
	AddMenu(Scroll, "ITEM=Scroll Down")
end


-- Duplicate selected text
do
	local function ToSqlWindow()
		local text = IDE.GetSelectedText()

		IDE.SetCursor(0, 0)
		IDE.InsertText(text)
	end
	
	AddMenu(nil, "MENUITEM=Selection")
	AddMenu(ToSqlWindow, "SUBITEM=Duplicate")
end

-- Inverse Special Copy (Java, C++)
do
	local function InverseSpecial()
		local text = IDE.GetSelectedText()

		text = Gsub(text, "^[^\"]*\"", '')  -- Text head
		text = Gsub(text, "\"[^\"]*$", '')  -- Text tail
		text = Gsub(text, "\n[^\"]*\"", '\n')  -- Line head
		text = Gsub(text, "[ \t]*\"[^\"\r\n]*([\r\n])", '%1')  -- Line tail
		text = Gsub(text, "\"[^\"\n]+\"", '1')  -- Line middles
		IDE.InsertText(Gsub(text, "\\n", ''))
	end

	AddMenu(InverseSpecial, "SUBITEM=Inverse Special")
end


-- Init Caps
do
	local function Capitalize(s)
		if #s == 1 then
			return Lower(s)
		end
		return Upper(Sub(s, 1, 1)) .. Lower(Sub(s, 2))
	end

	local function InitCaps()
		local text = IDE.GetSelectedText()

		IDE.InsertText(Gsub(text, "%w+", Capitalize))
	end

	AddMenu(InitCaps, "SUBITEM=Init Caps")
end


-- Strip trailing spaces of the lines
do
	local function ClearBlanks()
		local text = IDE.GetSelectedText()

		text = Gsub(text, "[ \t]+$", "")
		IDE.InsertText(Gsub(text, "[ \t]+([\r\n])", "%1"))
	end

	AddMenu(ClearBlanks, "SUBITEM=Clear Blanks")
end


-- Copy selected text to new SQL window
do
	local function ToSqlWindow()
		local text = IDE.GetSelectedText()

		IDE.CreateWindow(plsql.WindowType.SQL, text)
	end

	AddMenu(ToSqlWindow, "SUBITEM=SQL Window")
end

-- Copy selected text to new SQL window
do
	local function ToSqlWindow()
		local text = IDE.GetSelectedText()

		IDE.CreateWindow(plsql.WindowType.SQL, text)
	end

	AddMenu(ToSqlWindow, "SUBITEM=to SQL Win")
end


-- Copy selected text to new SQL window and execute it
do
	local function ToSqlWindowExecute()
		local text = IDE.GetSelectedText()
	
		IDE.CreateWindow(plsql.WindowType.SQL, text)
		
		-- execute
		IDE.Perform(1)
	end
	
	AddMenu(ToSqlWindowExecute, "SUBITEM=to SQL Win execute")
end

-- Copy selected text to new Command window
do
	local function ToCommandWindow()
		local text = IDE.GetSelectedText()

		IDE.CreateWindow(plsql.WindowType.Command, text)
	end

	AddMenu(ToCommandWindow, "SUBITEM=to Command Win")
end

-- Copy selected text to new Command window and execute it
do
	local function ToCommandWindowExecute()
		local text = IDE.GetSelectedText()
	
		IDE.CreateWindow(plsql.WindowType.Command, text)
		
		-- execute
		IDE.Perform(1)
	end
	
	AddMenu(ToCommandWindowExecute, "SUBITEM=to Command Win execute")
end

-- Addon description
local function About()
	return "Edit Utilities"
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

