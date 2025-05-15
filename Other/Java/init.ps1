param(
    [Parameter(Mandatory=$true)]
    [string] $Prefix
)

if (-not (Test-Path 'Template.java')) {
    Write-Error 'Template.java not found in current directory.'
    exit 1
}

# If $Prefix is all digits, we’ll append A–F; otherwise just one “letter” (empty)
if ($Prefix -match '^\d+$') {
    $letters = 'A','B','C','D','E','F'
} else {
    $letters = ''
}

foreach ($l in $letters) {
    if ($Prefix -match '^\d+$') {
        $name = "_${Prefix}${l}"
    } else {
        $name = $Prefix
    }
    $out = "$name.java"

    Get-Content Template.java |
            ForEach-Object { $_ -replace 'class\s+Template\b', "class $name" } |
            Set-Content $out

    Write-Host "Created $out"
}
