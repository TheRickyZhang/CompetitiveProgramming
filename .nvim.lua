-- repo-local DAP + safe run bindings
local dap = require("dap")
local map = vim.keymap.set
local fe = vim.fn.fnameescape
local sh = vim.fn.shellescape

vim.g.autoformat = false
vim.o.autowrite = false
vim.o.autowriteall = false

local function shell_simple(p)
	return p:match("^[%w%./_+,%-]+$") ~= nil
end

-- Related to where this file is located
local ROOT = vim.fs.dirname((debug.getinfo(1, "S").source:gsub("^@", "")))
local INPUT = ROOT .. "/input.txt"
assert(shell_simple(ROOT), "ROOT not shell-simple; use shellescape")
assert(shell_simple(INPUT), "INPUT not shell-simple; use shellescape")

-- codelldb adapter via Mason (assume installed)
do
	local mason = vim.fn.stdpath("data") .. "/mason/packages/codelldb/extension/adapter/codelldb"
	if vim.fn.executable(mason) == 1 then
		dap.adapters.codelldb = {
			type = "server",
			port = "${port}",
			executable = { command = mason, args = { "--port", "${port}" } },
		}
	else
		vim.notify("codelldb not found in Mason. :MasonInstall codelldb", vim.log.levels.ERROR)
	end
end

local function checkRunnable(src)
	if vim.bo.buftype ~= "" then
		vim.notify("Focus a source file.", vim.log.levels.ERROR)
		return false
	end
	vim.cmd("update") -- Saves if the buffer is modified.

	if src == "" or vim.fn.filereadable(src) ~= 1 then
		vim.notify("Current buffer is not a file.", vim.log.levels.ERROR)
		return false
	end
	return true
end

-- local function checkFile()

local function kill_terms()
	for _, b in ipairs(vim.api.nvim_list_bufs()) do
		if vim.bo[b].buftype == "terminal" then
			local jid = vim.b[b].terminal_job_id
			if jid and jid > 0 then
				pcall(vim.fn.jobstop, jid)
			end
			pcall(vim.api.nvim_buf_delete, b, { force = true })
		end
	end
end

local function runProgram(cmd)
	-- Prepare by stopping other processes/windows
	kill_terms()
	-- Open a new window below for running the program
	vim.cmd("silent! only")
	vim.cmd("botright vsplit")
	-- vim.cmd("resize 24")
	vim.cmd("terminal bash -lc " .. vim.fn.shellescape(cmd))
	-- enter Terminal-mode so input is piped in correctly
	vim.cmd("startinsert")
end

---------- START COMMANDS ------------

-- DEBUG: build with -g then launch via DAP (with UI panes if you enabled dap-ui)
-- TODO: Use shell escape instead of fnameescape
map("n", "<leader>dd", function()
	local src = vim.fn.expand("%:p")
	if not checkRunnable(src) then
		return
	end

	local dir = vim.fn.fnamemodify(src, ":h")
	local exe = vim.fn.fnamemodify(src, ":r")

	-- build debug binary
	local build = string.format(
		"g++ -std=gnu++23 -g -O0 -fno-omit-frame-pointer -D_GLIBCXX_ASSERTIONS %s -o %s",
		fe(src),
		fe(exe)
	)
	vim.system({ "bash", "-lc", build }, { text = true }, function(r)
		vim.schedule(function()
			if r.code ~= 0 then
				local msg = (r.stderr and #r.stderr > 0 and r.stderr) or (r.stdout or "build failed")
				return vim.notify(msg, vim.log.levels.ERROR, { title = "build failed" })
			end
			if vim.fn.executable(exe) ~= 1 then
				return vim.notify("Built binary not found: " .. exe, vim.log.levels.ERROR, { title = "dap" })
			end
			dap.run({
				name = "C++ debug (codelldb)",
				type = "codelldb",
				request = "launch",
				program = exe,
				cwd = dir,
				args = {},
				runInTerminal = true, -- stdin works; UI still shows scopes/stacks if dap-ui enabled
				stopOnEntry = false,
			})
		end)
	end)
end, { desc = "debug current file (DAP)" })

map("n", "<leader>r", function()
	local src = vim.fn.expand("%:p")
	if not checkRunnable(src) then
		return
	end

	local cmd = string.format(
		-- Store input to the interactive terminal through tee
		-- Shellescape protects against various things, fnameescape for vim commands
		"cd %s && (tee %s | TIMEOUT=30s ./run.sh %s)",
		ROOT,
		INPUT,
		sh(src)
	)
	runProgram(cmd)
end, { desc = "run current file (terminal, 30s cap)" })

map("n", "<leader>R", function()
	local src = vim.fn.expand("%:p")
	if not checkRunnable(src) then
		return
	end

	local cmd = string.format(
		'RS=%s IS=%s SS=%s; cd "$RS"; ' .. 'touch "$IS"; ' .. 'cat "$IS"; ' .. 'TIMEOUT=30s ./run.sh "$SS" < "$IS"',
		ROOT,
		INPUT,
		sh(src)
	)
	runProgram(cmd)
end, { desc = "run current file with input.txt" })
