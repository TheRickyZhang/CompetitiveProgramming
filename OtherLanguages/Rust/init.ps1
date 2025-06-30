<#
.SYNOPSIS
  Create six files from Template.rs named <prefix>A.rs … <prefix>F.rs.

.PARAMETER Prefix
  The base name to prepend (e.g. “Problem” → ProblemA.rs, …, ProblemF.rs).
#>
param(
    [Parameter(Mandatory=$true)]
    [string] $Prefix
)

# Ensure Template.rs exists
if (-not (Test-Path 'Template.rs')) {
    Write-Error 'Template.rs not found in current directory.'
    exit 1
}

# Letters to append
$letters = 'A','B','C','D','E','F'

foreach ($l in $letters) {
    $out = "$Prefix$l.rs"
    Copy-Item -Path 'Template.rs' -Destination $out -Force
    Write-Host "Created $out"
}
