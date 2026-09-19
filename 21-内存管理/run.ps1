$ErrorActionPreference = 'Stop'

g++ .\main.cpp -o .\main.exe -std=c++20

if ($LASTEXITCODE -eq 0) {
    & .\main.exe
}
