-- Pl/Sql Developer Lua Plug-In

local MAX_ADDONS, MAX_MENUS = ...

local plsql = plsql
local SYS, IDE, SQL = plsql.sys, plsql.ide, plsql.sql

local root = plsql.RootPath()


-- Set C-modules placement
do
	local cpath = root:gsub("^\\\\%?\\", "") .. "\\clibs\\"
	local version = (_VERSION == "Lua 5.2") and "52" or "51"

	package.cpath = package.cpath
		.. ";" .. cpath .. "?" .. version .. ".dll"
		.. ";" .. cpath .. "?.dll"
		.. ";" .. cpath .. "lua" .. version .. ".dll"
end


-- Global 'sys' library
sys = require("sys")


-- Window Types
plsql.WindowType = {
	None = 0,	[0] = "None";
	SQL = 1,	[1] = "SQL";
	Test = 2,	[2] = "Test";
	Procedure = 3,	[3] = "Procedure";
	Command = 4,	[4] = "Command";
	Plan = 5,	[5] = "Plan";
	Report = 6,	[6] = "Report";
	HTML = 7,	[7] = "HTML";
	Diagram = 10,	[10] = "Diagram";
}

-- Window Close Actions
plsql.WindowClose = {
	Default = 0,
	Confirm = 1,
	Quiet = 2
}

-- Window Execute Result
plsql.WindowExecute = {
	Error = 0,
	Continue = 1,
	Success = 2
}

-- Perfom Commands
plsql.PerformCommand = {
	Execute = 1,	[1] = "Execute";
	Break = 2,	[2] = "Break";
	Kill = 3,	[3] = "Kill";
	Commit = 4,	[4] = "Commit";
	Rollback = 5,	[5] = "Rollback";
	Print = 6,	[6] = "Print";
}

-- Object Actions
plsql.ObjectAction = {
	Created = 1,	[1] = "Created";
	Modified = 2,	[2] = "Modified";
	Deleted = 3,	[3] = "Deleted";
}

-- Key Shifts
plsql.KeyShift = {
	Shift = 1,
	Alt = 2,
	Ctrl = 3
}

-- Beautifier Options
plsql.BeautifierOption = {
	AfterCreating = 1,
	AfterLoading = 2,
	BeforeCompiling = 4,
	BeforeSaving = 8
}

-- Field Types
plsql.FieldType = {
	Integer = 3,	[3] = "Integer";
	Float = 4,	[4] = "Float";
	String = 5,	[5] = "String";
	Long = 8,	[8] = "Long";
	Date = 12,	[12] = "Date";
	LongRaw = 24,	[24] = "LongRaw";
}

-- Keyword Styles
plsql.KeywordStyle = {
	Custom = 10,	[10] = "Custom";
	Keywords = 11,	[11] = "Keywords";
	Comment = 12,	[12] = "Comment";
	Strings = 13,	[13] = "Strings";
	Numbers = 14,	[14] = "Numbers";
	Symbols = 15,	[15] = "Symbols";
}


-- Menu
local add_menu, get_menu_indexes
local CreateMenuItem, OnMenuClick, OnActivate
do
	local menu_names, menu_nnames = {}, 0
	local menu_funcs, menu_icons = {}, {}

	local is_ribbon = false
	local ribbon_names, ribbon_nnames

	local ribbon_indexes  -- ribbon index -> menu index
	local menu_indexes  -- menu index -> ribbon index

	add_menu = function(func, name, icon)
		menu_nnames = menu_nnames + 1
		if menu_nnames > MAX_MENUS then
			error"Too many menus"
		end
		menu_names[menu_nnames] = name
		menu_funcs[menu_nnames] = func
		menu_icons[menu_nnames] = icon
		return menu_nnames
	end

	ribbon_menu = function()
		is_ribbon = true
		ribbon_names, ribbon_nnames = {}, 0

		ribbon_indexes = {}
		menu_indexes = {}

		local tabs = {}  -- menu items tree

		local GMatch, GSub, SSub = string.gmatch, string.gsub, string.sub

		function build_tree(index, name)
			local t = tabs
			for s in GMatch(name, "%s*([^/]+)%s*/?") do
				s = GSub(s, "%s*$", "")  -- trim trailing spaces
				local sub = t[s]
				if not sub then
					sub = {}
					local i = #t + 1
					t[s], t[i] = sub, s
				end
				t = sub
			end
			t[0] = index  -- menu_index
		end

		function build_names(t, depth)
			local n = #t
			if n == 0 then return end

			local level
			local opt = ""
			if depth == 1 then
				level, opt = "TAB", " [tabindex=7]"
			elseif depth == 2 then
				level = "GROUP"
			elseif depth == 3 then
				level = "MENUITEM"
			elseif depth == 4 then
				level = "SUBITEM"
			else return end

			for i = 1, n do
				local name = t[i]
				local sub = t[name]
				local findpat = ""
        
				-- don't overwrite custom indexes
				if depth == 1 then
					findpat = "%s%[tabindex="
				elseif depth == 2 then
					findpat = "%s%[groupindex="
				end
				if findpat ~= "" then
					local sstart, send = string.find(name, findpat)
					if sstart ~= nil then
						opt = " "
					end
				end
        
				if depth == 3 then
					level = #sub > 0 and "MENUITEM" or "ITEM"
				end

				-- don't override custom options
				if SSub(name, -1) == ']' then
					opt = ""
				end

				ribbon_nnames = ribbon_nnames + 1

				local ribbon_name = level .. "=" .. name .. opt
				ribbon_names[ribbon_nnames] = ribbon_name

				local index = sub[0]  -- menu_index
				if index then
					ribbon_indexes[ribbon_nnames] = index
					menu_indexes[index] = ribbon_nnames
				end

				build_names(sub, depth + 1)
			end
		end

		-- parse menus into tab:group:menuitem:subitem tree
		for i = 1, menu_nnames do
			local name = menu_names[i]
			if name then
				build_tree(i, name)
			end
		end

		-- build ribbon names
		build_names(tabs, 1)
	end

	get_menu_indexes = function()
		local indexes, nindexes = {}, menu_nnames
		local src, src_nindexes

		-- Use Ribbon Menu with Pl/Sql Developer v12+
		if SYS.Version() >= 1200 then
			ribbon_menu()
			src, src_nindexes = menu_indexes, ribbon_nnames
		else
			src_nindexes = menu_nnames
		end

		indexes[0] = src_nindexes
		for i = 1, nindexes do
			indexes[i] = src and src[i] or i
		end

		return indexes
	end

	CreateMenuItem = function(index)
		local t = is_ribbon and ribbon_names or menu_names
		return t[index]
	end

	OnMenuClick = function(index)
		if is_ribbon then
			index = ribbon_indexes[index]
		end

		local func = menu_funcs[index]
		if func then
			func(index)
		end
	end

	OnActivate = function()
		for i = 1, menu_nnames do
			local icon = menu_icons[i]
			if icon then
				local name = menu_names[i]
				IDE.CreateToolButton(i, name, root .. "\\" .. icon)
			end
		end
	end
end


-- Process Addons
local addons = {}
do
	local nfuncs, naddons = {}, 0

	local function add_funcs(funcs)
		for i, func in pairs(funcs) do
			local n = nfuncs[i]
			if not n then
				nfuncs[i], n = 0, 0
			else
				n = n + 1
				nfuncs[i] = n
			end
			addons[i * MAX_ADDONS + n] = func
		end
	end

	local function add_addon(name, funcs, dep)
		naddons = naddons + 1
		local addon_info = {
			index = naddons,
			funcs = funcs
		}
		addons[naddons] = name
		addons[name] = addon_info

		-- Dependences
		if type(dep) == "string" then  -- Activate before this addon
			local info = addons[dep]
			if info then
				if not info.dep then
					info.dep = {}
				end
				info.dep[#info.dep + 1] = name
			end
		else  -- Activate after these addons
			addon_info.dep = dep
		end
	end

	local function install_addon(name)
		local addon_info = addons[name]
		if not addon_info then return end

		-- Addon installed
		addons[name], addons[addon_info.index] = nil, nil

		-- Install dependency addons
		if addon_info.dep then
			for _, dep_name in ipairs(addon_info.dep) do
				install_addon(dep_name)
			end
		end

		add_funcs(addon_info.funcs)
	end

	-- Traverse plugin directory
	local fd = sys.handle()

	for name, is_dir in sys.dir(root) do
		if is_dir and fd:open(root .. "\\" .. name .. "\\" .. "main.lua", 'r') then
			-- Load addon
			local chunk, err = loadfile(root .. "\\" .. name .. "\\" .. "main.lua")
			if not chunk then
				plsql.ShowMessage(err)
			else
				local funcs, dep = chunk(add_menu, root, name)
				if funcs then
					add_addon(name, funcs, dep)
				end
			end
		end
		fd:close()
	end

	-- Install base funcs
	add_funcs{
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
		ExportData,

		CreateMenuItem,
		OnMenuClick
	}

	-- Install addons
	for i = 1, naddons do
		local name = addons[i]
		if name then
			install_addon(name)
		end
	end
end

return addons, get_menu_indexes()
