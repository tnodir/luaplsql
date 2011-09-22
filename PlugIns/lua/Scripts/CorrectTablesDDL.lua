-- Correct Tables DDL


-- Name of the index tablespace
local INDEX_TBS = "CORE_IDX_TBS"


-- Get the input filename
local in_filename = plsql.GetOpenFileName("In_Tables.sql",
	"SQL (*.sql)\0*.sql\0All files\0*.*\0\0\0")
if not in_filename then return end

-- Create file
local out_file
do
	-- Get the output filename
	local out_filename = plsql.GetSaveFileName("Out_Tables.sql")
	if not out_filename then return end

	out_file = io.open(out_filename, "w")
	if not out_file then return end
end

-- Cut tablespace parameters
do
	local Find, Sub = string.find, string.sub

	local is_tablespace

	for line in io.lines(in_filename) do
		if is_tablespace then
			local i = Find(line, ')', 1, true)
			if i then
				is_tablespace = false
				out_file:write(Sub(line, i + 1), '\n')
			end
		else
			if Find(line, '^%-%-') then
				line = ''  -- Skip commentaries
			elseif Find(line, "tablespace", 1, true) then
				is_tablespace = true
			elseif line == "organization index;" then
				line = "organization index tablespace "
					.. INDEX_TBS .. " overflow tablespace "
					.. INDEX_TBS .. ";"
			end
			out_file:write(line, is_tablespace and '' or '\n')
		end
	end
end

-- Close the output file
out_file:close()

print"OK"
