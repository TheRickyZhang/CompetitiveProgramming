-- repo-local DAP + safe run bindings
local map = vim.keymap.set
local fe = vim.fn.fnameescape
local dap = require("dap")

vim.g.autoformat = false
vim.o.autowrite = false
vim.o.autowriteall = false

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

-- dap.defaults.fallback.terminal_win_cmd = function()
-- 	vim.cmd("belowright 12split | enew")
-- 	return vim.api.nvim_get_current_buf()
-- end

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

-- DEBUG: build with -g then launch via DAP (with UI panes if you enabled dap-ui)
map("n", "<leader>R", function()
	if vim.bo.buftype ~= "" then
		return vim.notify("Focus a source file.", vim.log.levels.ERROR)
	end
	vim.cmd("update")
	local src = vim.fn.expand("%:p")
	if src == "" or vim.fn.filereadable(src) ~= 1 then
		return vim.notify("Current buffer is not a file.", vim.log.levels.ERROR)
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
	if vim.bo.buftype ~= "" then
		return vim.notify("Focus a source file.", vim.log.levels.ERROR)
	end
	vim.cmd("update")
	local src = vim.fn.expand("%:p")
	if src == "" or vim.fn.filereadable(src) ~= 1 then
		return vim.notify("Current buffer is not a file.", vim.log.levels.ERROR)
	end
	local dir = vim.fn.fnamemodify(src, ":h")
	local cmd = string.format("cd %s && TIMEOUT=30s ./run.sh %s", vim.fn.shellescape(dir), vim.fn.fnameescape(src))

	-- Prepare by stopping other processes/windows
	kill_terms()
	vim.cmd("silent! only")

	-- Open a new window below for running the program
	vim.cmd("botright 12split")
	vim.cmd("terminal bash -lc " .. vim.fn.shellescape(cmd))
	-- enter Terminal-mode so input flows to the program
	vim.cmd("startinsert")
end, { desc = "run current file (terminal, 30s cap)" })
