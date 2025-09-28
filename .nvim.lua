-- repo-local DAP for stdin
local map = vim.keymap.set
local fe = vim.fn.fnameescape
local dap = require("dap")

-- adapter
local mason = vim.fn.stdpath("data") .. "/mason/packages/codelldb/extension/adapter/codelldb"
dap.adapters.codelldb = {
	type = "server",
	port = "${port}",
	executable = {
		command = (vim.fn.executable(mason) == 1) and mason or "codelldb",
		args = { "--port", "${port}" },
	},
}

-- make nvim-dap open a real terminal split for runInTerminal
dap.defaults.fallback.terminal_win_cmd = function()
	vim.cmd("belowright 12split | enew")
	return vim.api.nvim_get_current_buf()
end

-- build with debug flags then run in terminal
map("n", "<leader>R", function()
	if vim.bo.buftype ~= "" then
		return vim.notify("Focus a source file.", vim.log.levels.ERROR)
	end
	vim.cmd("update")
	local src = vim.fn.expand("%:p")
	if src == "" or vim.fn.filereadable(src) ~= 1 then
		return vim.notify("Current buffer is not a file.", vim.log.levels.ERROR)
	end

	vim.system({ "bash", "-lc", "./run.sh --debug " .. fe(src) }, { text = true }, function(r)
		vim.schedule(function()
			if r.code ~= 0 then
				local msg = (r.stderr and #r.stderr > 0 and r.stderr) or (r.stdout or "build failed")
				return vim.notify(msg, vim.log.levels.ERROR, { title = "build failed" })
			end
			local exe = vim.fn.fnamemodify(src, ":r") -- basename without extension
			if vim.fn.executable(exe) ~= 1 then
				return vim.notify("Built binary not found: " .. exe, vim.log.levels.ERROR, { title = "dap" })
			end
			dap.run({
				name = "codelldb",
				type = "codelldb",
				request = "launch",
				program = exe,
				cwd = vim.fn.getcwd(),
				args = {},
				stopOnEntry = false,
				runInTerminal = true, -- key: create real terminal, not the debug console
			})
		end)
	end)
end, { desc = "repo: debug current file in terminal with stdin" })

-- optional plain run
map("n", "<leader>r", function()
	if vim.bo.buftype ~= "" then
		return vim.notify("Focus a source file.", vim.log.levels.ERROR)
	end
	vim.cmd("update | botright split")
	local src = vim.fn.expand("%:p")
	vim.cmd("terminal bash -lc " .. vim.fn.shellescape("./run.sh " .. fe(src)))
	vim.cmd("startinsert")
end, { desc = "repo: run current file" })
