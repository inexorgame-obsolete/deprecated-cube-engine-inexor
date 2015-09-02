if "%platform%"=="Win32" set "inexor_platform_name=win32"
if "%platform%"=="x64"   set "inexor_platform_name=win64"
bin\windows\%inexor_platform_name%\unit_tests.exe
exit /b 0