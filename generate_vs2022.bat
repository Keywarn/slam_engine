@echo off

SET RootPath=%~dp0
SET BuildPath=%RootPath%\generated\vs2022\
SET CMakeExePath="C:\Program Files\CMake\bin\cmake.exe"

echo Generating %RootPath%
echo %CMakeExePath% -S %RootPath% -B %BuildPath%

%CMakeExePath% -S %RootPath% -B %BuildPath% -G "Visual Studio 17 2022"