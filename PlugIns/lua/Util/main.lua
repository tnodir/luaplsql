-- Pl/Sql Developer Lua Plug-In Addon: Utilities


-- Variables

local AddMenu = ...

local plsql = plsql
local SYS, IDE, SQL = plsql.sys, plsql.ide, plsql.sql

local ShowMessage = plsql.ShowMessage


-- Wrap program unit
do
	-- Wrappable object types
	local wrapObjectTypes = {
		["FUNCTION"] = true,
		["PROCEDURE"] = true,
		["PACKAGE"] = true,
		["PACKAGE BODY"] = true,
	}

	local wrapSQL = [[
		Declare
		  v_Array Dbms_SQL.Varchar2A;
		Begin
		  v_Array(1) := 'Create Or Replace ';
		  For x In (
		    Select t.Line, t.Text
		      From User_Source t
		      Where t.Name = Upper(:Name)
		        And t.Type = :Type
		      Order By t.Line
		  ) Loop
		    v_Array(1 + x.Line) := x.Text;
		  End Loop;
		  Dbms_Ddl.Create_Wrapped(v_Array, 1, v_Array.Count);
		End;
	]]

	local function Wrap(objectType, objectName)
		SQL.SetVariable("Name", objectName)
		SQL.SetVariable("Type", objectType)
		if SQL.Execute(wrapSQL) ~= 0 then
			ShowMessage(SQL.ErrorMessage())
		end
		SQL.ClearVariables()
	end

	local function BackupAndWrap(objectType, objectOwner, objectName)

		-- Get source text
		local source = IDE.GetObjectSource(objectType, objectOwner, objectName)

		-- Already wrapped?
		if source:match(" wrapped [\r]\na0") then return end

		-- Get backup filename
		local filename = plsql.GetSaveFileName(objectName .. '.'
			.. IDE.GetProcEditExtension(objectType),
			nil, "Backup")
		if not filename then return end

		-- Backup file
		do
			errorMessage = nil
			local fd = sys.handle()
			if fd:create(filename) then
				fd:write(source)
				fd:close()
			end
			if errorMessage then
				return ShowMessage(errorMessage)
			end
		end

		Wrap(objectType, objectName)
	end

	-- Wrap program units currently selected in the Browser
	local function WrapUnits()

		-- Loop over selected objects in the Browser
		local objectType, objectOwner, objectName = IDE.FirstSelectedObject()

		if not wrapObjectTypes[objectType] then
			return ShowMessage("Select wrappable objects.")
		end

		while objectType do
			BackupAndWrap(objectType, objectOwner, objectName)

			objectType, objectOwner, objectName = IDE.NextSelectedObject()
		end
	end

	AddMenu(WrapUnits, "&Lua / Utilities / Wrap Program Units")
end


-- Export Packages
do
	local Find, Gsub, Lower, Rep =
		string.find, string.gsub, string.lower, string.rep

	local function Rtrim(str)
		return (Gsub(str, "[ \t\r\n]+$", ""))
	end

	local function LoopSelectedItems(fd, directory)
		local nexported = 0
		local installText = ""

		-- Loop over selected objects in the Browser
		local objectType, objectOwner, objectName = IDE.FirstSelectedObject()

		while objectType == "PACKAGE" do
			local filename = Lower(objectName) .. ".pck"

			installText = installText
				.. "\nprompt\n"
				.. "prompt Creating package "
				.. objectName
				.. "\nprompt ================="
				.. Rep('=', #objectName)
				.. "\nprompt\n"
				.. "@@Packages\\" .. filename .. "\n"

			-- Get source text
			local source = Rtrim(IDE.GetObjectSource("PACKAGE BODY", objectOwner, objectName))
			if Find(source, "^/%*") then
				source = ''  -- Skip empty package body
			else
				source = source .. "\r\n/\r\n"
			end
			source = Rtrim(IDE.GetObjectSource("PACKAGE", objectOwner, objectName))
				.. "\r\n/\r\n" .. source

			-- Write source to file
			local success = fd:create(directory .. filename)
				and fd:write(source)
			fd:close()

			-- Error?
			if not success then break end

			nexported = nexported + 1

			objectType, objectOwner, objectName = IDE.NextSelectedObject()
		end
		return nexported, installText
	end

	local function ExportPackages()

		-- Get the main filename to export
		local filename = plsql.GetSaveFileName("Install.sql")
		if not filename then return end

		errorMessage = nil

		local fd = sys.handle()

		-- Loop over selected packages in the Browser
		local directory = Gsub(filename, "[^\\/]+$", "")
		local nexported, installText = LoopSelectedItems(fd, directory)

		if nexported > 0 then
			if fd:create(filename) and fd:write(installText) then
				errorMessage = nexported .. " packages exported."
			end
			fd:close()
		else
			errorMessage = "Select packages."
		end

		if errorMessage then
			ShowMessage(errorMessage)
		end
	end

	AddMenu(ExportPackages, "&Lua / Utilities / Export Packages")
end


-- Open TNS File
do
	local function OpenTNSFile()
		IDE.OpenFile(plsql.WindowType.SQL, SYS.TNSNAMES())
	end

	AddMenu(OpenTNSFile, "&Lua / Utilities / Open TNS File")
end


-- Table: Truncate
local truncMenuItem
do
	local function Truncate()
		local _, _, objectName = IDE.GetPopupObject()
		local sql = "Truncate Table " .. objectName

		if plsql.MessageBox("Do you really want to delete rows?",
			sql, "YesNo", "Question") == "No"
		then return end

		if SQL.Execute(sql) ~= 0 then
			ShowMessage(SQL.ErrorMessage())
		end
	end

	truncMenuItem = AddMenu(Truncate)
end


-- Table: Foreign Key References
local refsMenuItem
do
	local Sub = string.sub

	local sql = [[
		Select t.Constraint_Name, t.Table_Name,
		    c.Column_Name, c2.Column_Name Ref_Column_Name
		  From User_Constraints t
		    Join User_Indexes ui On ui.Index_Name = t.r_Constraint_Name
		      And ui.Uniqueness = 'UNIQUE'
		      And ui.Table_Name = :Name
		    Join User_Cons_Columns c On c.Constraint_Name = t.Constraint_Name
		    Join User_Cons_Columns c2 On c2.Constraint_Name = t.r_Constraint_Name
		      And c2.Position = c.Position
		  Order By t.Constraint_Name, c.Position
	]]

	local function LoopReferences(refTableName)
		local s = ""
		local prevConstraintName, tableName, columnNames, refColumnNames

		while true do
			local constraintName = SQL.Field(1)
			if prevConstraintName ~= constraintName then
				if prevConstraintName then
					s = s .. 'Alter Table ' .. tableName
						.. ' Add Constraint '
						.. prevConstraintName
						.. ' Foreign Key ('
						.. Sub(columnNames, 3)
						.. ') References '
						.. refTableName .. ' ('
						.. Sub(refColumnNames, 3) .. ');\r\n'
				end
				prevConstraintName = constraintName
				tableName = SQL.Field(2)
				columnNames, refColumnNames = "", ""
			end
			if SQL.Eof() then break end
			columnNames = columnNames .. ', ' .. SQL.Field(3)
			refColumnNames = refColumnNames .. ', ' .. SQL.Field(4)
			SQL.Next()
		end
		plsql.SetClipboardText(s)
	end

	local function CopyReferences()
		local _, _, objectName = IDE.GetPopupObject()

		SQL.SetVariable("Name", objectName)
		if SQL.Execute(sql) ~= 0 then
			ShowMessage(SQL.ErrorMessage())
		else
			LoopReferences(objectName)
		end
		SQL.ClearVariables()
	end

	refsMenuItem = AddMenu(CopyReferences)
end


-- Initialization
local function OnActivate()

	-- Add items to context menu
	IDE.CreatePopupItem(truncMenuItem, "Truncate", "TABLE")
	IDE.CreatePopupItem(refsMenuItem, "Copy References", "TABLE")
end


-- Destruction
local function OnDeactivate()

	-- Workaround: Close the IUP module
	if iup then
		iup.Close()
	end
end


-- After Plug-In Reloaded
local function AfterReload()

	-- Workaround: Refresh Key Configuration
	do
		local oldWindow = plsql.GetForegroundWindow()

		local function OnTimer(timerId)
			local currentWindow = plsql.GetForegroundWindow()
			if currentWindow ~= oldWindow then
				plsql.KillTimer(timerId)
				plsql.KeyDown(currentWindow, 13)  -- Press OK button
			end
		end

		plsql.SetTimer(100, OnTimer)
		IDE.ShowDialog("PREFERENCES")
	end
end


-- Addon description
local function About()
	return "Utilities"
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
-- Dependences: uncomment one of the following lines.
--, {"Session", "Window"}  -- Activate after these modules
--, "Session"  -- Activate before this module

