-- Pl/Sql Developer Lua Plug-In

local root = plsql.RootPath()


-- Set C-modules placement
do
	local cpath = root:gsub([[^\\%?\]], "") .. "\\clibs\\"

	package.cpath = package.cpath
		.. cpath .. "?52.dll;"
		.. cpath .. "?.dll;"
		.. cpath .. "lua52.dll;"
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


-- Install Addons
local addons = {}
do
	local MAX_ADDONS, MAX_MENUS = ...
	local nfuncs, nmenus = {}, 0
	local naddons = 0

	local function new_addon(funcs)
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

	local function add_menu(func, name)
		nmenus = nmenus + 1
		if nmenus > MAX_MENUS then
			error"Too many menus"
		end
		addons[-nmenus] = name
		addons[-(nmenus + MAX_MENUS)] = func
		return nmenus
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

	-- Install addons
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

		new_addon(addon_info.funcs)
	end

	for i = 1, naddons do
		local name = addons[i]
		if name then
			install_addon(name)
		end
	end
end

return addons
