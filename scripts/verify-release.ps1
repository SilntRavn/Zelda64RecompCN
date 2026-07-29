$ErrorActionPreference = "Stop"
$RepoRoot = (Resolve-Path (Join-Path $PSScriptRoot "..")).Path
$ReleaseRoot = Join-Path $RepoRoot "release\Zelda64Recompiled-v1.2.2-CN"
$Expected = @{
    "dxcompiler.dll" = "15304A82C8A61DB615A83961D8967A5C468AE7CE77B86D8E9B3DEC60F7AE2166"
    "dxil.dll" = "2C70D034D38B06C6A1161EFB9246CCE296BE248FF52EFF6C1B587CE150E5F36D"
    "recompcontrollerdb.txt" = "45CD847BE5B2A3C1AD2366A22F59BB6A7B1BA33014103908808A505015AC41F4"
    "SDL2.dll" = "68E36533F0184B533EC79AA01E835641A099880F63EAEFE9425859574A739790"
}

foreach ($Name in $Expected.Keys) {
    $Path = Join-Path $ReleaseRoot $Name
    if (-not (Test-Path $Path)) {
        throw "Missing release file: $Path"
    }
    $Actual = (Get-FileHash -LiteralPath $Path -Algorithm SHA256).Hash
    if ($Actual -ne $Expected[$Name]) {
        throw "SHA-256 mismatch for $Name`nExpected: $($Expected[$Name])`nActual:   $Actual"
    }
    Write-Host "OK  $Name  $Actual"
}

$Executables = @(Get-ChildItem -LiteralPath $ReleaseRoot -Filter "*.exe" -File)
if ($Executables.Count -ne 1) {
    throw "Expected exactly one release executable, found $($Executables.Count)"
}
$ExpectedExeHash = "5881B23739E41C9352000DC0D543173CA1F9BDFB11D537A7E3BC511761C629D3"
$ActualExeHash = (Get-FileHash -LiteralPath $Executables[0].FullName -Algorithm SHA256).Hash
if ($ActualExeHash -ne $ExpectedExeHash) {
    throw "SHA-256 mismatch for release executable`nExpected: $ExpectedExeHash`nActual:   $ActualExeHash"
}
Write-Host "OK  $($Executables[0].Name)  $ActualExeHash"
