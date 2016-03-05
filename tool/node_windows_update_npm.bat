@echo off
:: Install any needed files if necessary.
:: We just call our generic node environment setting batch with the additional commands it shall execute.
setlocal DisableDelayedExpansion

call %~dp0node_windows_generic_handler.bat call !NPM_EXECUTEABLE! update
