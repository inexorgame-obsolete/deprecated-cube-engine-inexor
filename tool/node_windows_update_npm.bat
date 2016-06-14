@echo off
:: Install any needed files if necessary.

:: we set those to enable those commands in the generic handler
set "inexor_update_npm=true"
set "inexor_start_nodeapp=false"

call %~dp0node_windows_generic_handler.bat
