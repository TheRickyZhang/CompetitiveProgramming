# run.ps1 — compile & run a .cpp, then delete the exe

if ($args.Count -lt 1) {
  Write-Error "Usage: run.ps1 <source.cpp>"
  exit 1
}
$cpp = $args[0]

if (-not $cpp.EndsWith('.cpp')) {
  Write-Error "I only compile .cpp files, got: $cpp"
  exit 1
}

$FullPath = Resolve-Path $cpp
$Dir      = Split-Path $FullPath
$Name     = [IO.Path]::GetFileNameWithoutExtension($FullPath)
$Exe      = Join-Path $Dir "$Name.exe"

# 4) compile
g++ $FullPath -O2 -std=c++23 -o $Exe
if ($LASTEXITCODE -ne 0) {
  Write-Error "Compilation failed."
  exit 1 # Any way to still have this goto 5 THEN exit 1 so that we stil clearn up oldinstances regardless?
}

# 5) kill old instances, run, then clean up
Stop-Process -Name $Name -ErrorAction SilentlyContinue -Force
& $Exe
if (Test-Path $Exe) { Remove-Item $Exe -Force }
