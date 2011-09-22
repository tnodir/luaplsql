-- Get static methods of selected type
-- TODO: Integrate with Code Assistent

require("iuplua")

local plsql = plsql
local SYS, IDE, SQL = plsql.sys, plsql.ide, plsql.sql

local ShowMessage = plsql.ShowMessage


local function RefreshList(list, objectName)
	local sql = [[
		Select Distinct Lower(t.Method_Name)
		  From Dba_Type_Methods t
		  Where t.Type_Name = Upper(:Name)
		  Order By Lower(t.Method_Name)
	]]
	SQL.SetVariable("Name", objectName)
	if SQL.Execute(sql) ~= 0 then
		ShowMessage(SQL.ErrorMessage())
	else
		local i = 0
		while not SQL.Eof() do
			i = i + 1
			list[i] = SQL.Field(1)
			SQL.Next()
		end
	end
	SQL.ClearVariables()
end

local function GetTypeMethods()
	local objectType, objectOwner, objectName = IDE.GetBrowserInfo()

	if objectType ~= 'TYPE' then
		return ShowMessage("Select 'type' object.")
	end

	-- Create a list and sets its items, dropdown and amount of visible items
	local list = iup.list{
		dropdown = "NO", visible_items = 10, size = "300x200y",
		EDITBOX = "YES", VISIBLELINES = 10, SCROLLBAR = "YES"
	}

	-- Create frame with dropdown list and sets its title
	local frm_list = iup.frame{list; title = "Api"}

	-- Create a dialog with the the frames with three lists and sets its title
	local dlg = iup.dialog{iup.hbox{frm_list}; title = "Select item"}

	-- Set key handler of list
	function list:k_any(k)
		if k == 13 then
			dlg:hide()
			plsql.SetClipboardText(list["VALUE"])
		elseif k == 27 then
			dlg:hide()
		end
		return k
	end

	RefreshList(list, objectName)

	-- Show dialog in the center of the screen
	dlg:showxy(iup.CENTER, iup.CENTER)
	iup.MainLoop()
	dlg:destroy()

	--AddMenu(GetTypeMethods, "&Lua / Edit / Get Type Methods")
end

GetTypeMethods()

return true
