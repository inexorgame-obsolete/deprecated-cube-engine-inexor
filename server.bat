@ECHO OFF
SETLOCAL ENABLEEXTENSIONS

set INEXOR_ARCH=win32

IF /I "%PROCESSOR_ARCHITECTURE%" == "amd64" (
    set INEXOR_ARCH=win64
)
IF /I "%PROCESSOR_ARCHITEW6432%" == "amd64" (
    set INEXOR_ARCH=win64
)

:DATA_VAR
IF NOT DEFINED "%INEXOR_DATA%" GOTO DATA_IN_PROFILE
echo Found data in %INEXOR_DATA%
start bin\windows\%INEXOR_ARCH%\inexor.exe "-q%INEXOR_DATA%" -gserver-log.txt -d %*
GOTO END

:DATA_IN_PROFILE
IF NOT EXIST "%USERPROFILE%\My Games\Inexor" GOTO DATA_LOCAL
echo Found data in %USERPROFILE%\My Games\Inexor
start bin\windows\%INEXOR_ARCH%\inexor.exe "-q%USERPROFILE%\My Games\Inexor" -gserver-log.txt -d %*
GOTO END

:DATA_LOCAL
IF NOT EXIST data GOTO DATA_NOT_FOUND
echo Found data in local directory
start bin\windows\%INEXOR_ARCH%\inexor.exe "-qdata" -gserver-log.txt -d %*
GOTO END

:DATA_NOT_FOUND
echo Could not find the game data. Exiting.

:END
