@ECHO OFF

set INEXOR_ARCH=win32

IF /I "%PROCESSOR_ARCHITECTURE%" == "amd64" (
    set INEXOR_ARCH=win64
)
IF /I "%PROCESSOR_ARCHITEW6432%" == "amd64" (
    set INEXOR_ARCH=win64
)

start bin\windows\%INEXOR_ARCH%\inexor.exe "-q$HOME\My Games\Inexor" -glog.txt %*
