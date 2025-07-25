param([string]$src)
if (-not (Test-Path $src)) { Write-Error "File not found: $src"; exit 1 }

$full = Resolve-Path $src
$dir  = Split-Path  $full
$name = [IO.Path]::GetFileNameWithoutExtension($full)
$ext  = [IO.Path]::GetExtension($full).ToLower()

# init
$compile = $null
$run     = $null
$kill    = ''
$cleanup = $null

switch ($ext) {
    '.cpp' {
        $compile = { g++ $full -O2 -std=c++23 -o "$dir\$name.exe" }
        $run     = { & "$dir\$name.exe" }
        $kill    = $name
        $cleanup = { Remove-Item "$dir\$name.exe" -Force -ErrorAction SilentlyContinue }
    }
    '.java' {
        $compile = { javac $full }
        $run     = { & java -cp $dir $name }
        $kill    = 'java'
        $cleanup = { Get-ChildItem $dir "$name*.class" | Remove-Item -Force -ErrorAction SilentlyContinue }
    }
    '.py' {
        # no compile step
        $run     = { & python $full }
        $kill    = ''
        $cleanup = $null
    }
    '.rs' {
        # compile with optimization, output to the same name.exe
        $compile = { rustc $full -C opt-level=3 --edition=2021 -o "$dir\$name.exe" }
        $run     = { & "$dir\$name.exe" }
        # Rust binary will be named the same as $name
        $kill    = $name
        $cleanup = { Remove-Item "$dir\$name.exe" -Force -ErrorAction SilentlyContinue }
    }
    default {
        Write-Error "Unsupported extension: $ext"
        exit 1
    }
}

try {
  if ($compile) {
    & $compile
    if ($LASTEXITCODE -ne 0) { throw "compile-failed" }
  }

  if ($kill) {
    Stop-Process -Name $kill -ErrorAction SilentlyContinue -Force
  }

  & $run
}
finally {
  if ($cleanup) { & $cleanup }
}
