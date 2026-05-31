if ($args.Count -ne 1) {
    Write-Host "Usage: .\build.ps1 <output_name>" -ForegroundColor Red
    exit 1
}

$exe_name = $args[0]
clang *.c -o "$exe_name.exe"