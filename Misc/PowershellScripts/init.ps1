<#
.SYNOPSIS
  Create six files from Template.cpp named <prefix>A.cpp … <prefix>F.cpp.

.PARAMETER Prefix
  The base name to prepend (e.g. “Problem” → ProblemA.cpp, …, ProblemF.cpp).
#>
param(
    [Parameter(Mandatory=$true)]
    [string] $Prefix
)

# Ensure Template.cpp exists
if (-not (Test-Path 'Template.cpp')) {
    Write-Error 'Template.cpp not found in current directory.'
    exit 1
}

# Letters to append
$letters = 'A','B','C','D','E','F'

foreach ($l in $letters) {
    $out = "$Prefix$l.cpp"
    Copy-Item -Path 'Template.cpp' -Destination $out -Force
    Write-Host "Created $out"
}
