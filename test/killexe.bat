@echo off

setlocal enabledelayedexpansion

set "script_path=%~dp0"
echo Deleting .exe files...

for /r %%i in (*.exe) do (
    set "relative_path=%%i"
    set "relative_path=!relative_path:%script_path%=!"
    echo Relative Path: !relative_path!
    del /q "%%i"
)

echo Deletion complete

pause