@echo off

:: Start the nodejs app as the Inexor scripting backend.
:: We just call our generic node environment setting batch, setting the booleans what it should do beforehand.
:: The generic handler sets the PATHs for us.

:: we set those to enable those commands in the generic handler
set "inexor_update_npm=true"
set "inexor_start_nodeapp=true"

call %~dp0tool\node_windows_generic_handler.bat
