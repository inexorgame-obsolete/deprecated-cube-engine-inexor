@ECHO OFF

set INEXOR_BIN=bin

IF /I "%PROCESSOR_ARCHITECTURE%" == "amd64" (
    set INEXOR_BIN=bin64
)
IF /I "%PROCESSOR_ARCHITEW6432%" == "amd64" (
    set INEXOR_BIN=bin64
)

start %INEXOR_BIN%\inexor.exe "-q$HOME\My Games\Inexor" -gserver-log.txt -d %*
