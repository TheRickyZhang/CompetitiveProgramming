<#
.SYNOPSIS
  Organize or move your .cpp files exactly like before, plus:
    • 6-digit+letter ⇒ Codeforces\Gym
    • “OI” in first 4 chars ⇒ Other\OI_Problems
.PARAMETER Prefix
  (Optional) If provided, only moves all files matching “<Prefix>*.cpp”
  into the Codeforces subfolder grouped by 50-range.  If omitted, it
  processes *all* .cpp files with your USACO/CF/CSES/OI/Gym logic.
#>

param(
    [string] $Prefix
)

Set-Location $PSScriptRoot

# —— 0) Clean out any stray executables ——
Remove-Item "*.exe"                   -Force -ErrorAction SilentlyContinue
Remove-Item "cmake-build-debug\*.exe" -Force -ErrorAction SilentlyContinue
Remove-Item "*.out"                   -Force -ErrorAction SilentlyContinue

# —— 1) Exclusions ——
$Exclude = @('Template.cpp')

# ——— No args = move everything by your USACO/CF/CSES/OI/Gym logic ———
$files = Get-ChildItem -Path . -Filter '*.cpp' -File |
        Where-Object { $Exclude -notcontains $_.Name }

Write-Host "Found $($files.Count) .cpp files:"
$files | ForEach-Object { Write-Host "  $($_.Name)" }

# —— ONE-ARG MODE: move <Prefix>*.cpp into Codeforces\<range>\<prefix> ——
if($Prefix -and $Prefix -match '^\d+$') {
    Write-Host "Activating with [$Prefix]"
    $p = [int]$Prefix
    $start = [math]::Floor($p/50)*50
    $end   = $start + 49
    $range = "$start-$end"
    $targetDir = Join-Path "Codeforces" (Join-Path $range $Prefix)

    if (-not (Test-Path $targetDir)) {
        New-Item -ItemType Directory -Path $targetDir | Out-Null
    }

    foreach ($f in $files) {
        Move-Item $f.FullName -Destination $targetDir -Force
        Write-Host "[CF] Moved $($f.Name) → $targetDir"
    }
    return;
}

# —— No args = every .cpp ——
$files = Get-ChildItem -Filter '*.cpp'
foreach ($f in $files) {
    if ($Exclude -contains $f.Name) {
        Write-Host "[skip] $($f.Name)"
        continue
    }
#    Write-Host "trying $($f.Name)"

    $base = $f.BaseName
    $dest = $null

    # Match OI
    if ($base.Substring(0,[Math]::Min(4,$base.Length)) -match 'OI') {
        $dest = 'Other\OI_Problems'
    }
    switch -Regex ($base) {
        # Match USACO
        '^Bronze'   { $dest = "USACO";      break }
        '^Silver'   { $dest = "USACO";      break }
        '^Gold'     { $dest = "USACO";      break }
        '^Platinum' { $dest = "USACO";      break }

        # Match Codeforces
        '^[0-9]{6}[A-Za-z]' {
            $dest = 'Codeforces\Gym'
            break
        }
        '^(?<num>[0-9]{1,6})([A-Z])' {
            $cid   = [int]$Matches['num']
            $start = [math]::Floor($cid/50)*50
            $end   = $start + 49
            $dest  = "Codeforces\$($start)-$($end)\$($cid)"
            break
        }

        # Match other
        '-' { $dest = "CSES"; break }
        default { break }
    }

    # perform the move if we set $dest
    if ($dest) {
        if (-not (Test-Path $dest)) {
            New-Item -ItemType Directory -Path $dest | Out-Null
        }
        Move-Item $f.FullName -Destination $dest -Force
        Write-Host "[$dest] Moved $($f.Name) → $dest"
    }
    else {
        Write-Host "[$($f.BaseName)] Doesn't match any"
    }
}
