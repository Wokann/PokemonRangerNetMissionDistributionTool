@echo off
@echo *-------------------------------------------------------------*
@echo ^| 宝可梦巡护员网络任务配信器 v0.1            ——卧看微尘制作 ^| 
@echo ^| PokemonRangerNetMissionDistributionTool v0.1 made by wokann ^|
@echo ^|                                                  2023.12.10 ^|
@echo *-------------------------------------------------------------*
@echo.

%~d0
cd "%~dp0"
::@echo 您拖放的文件是："%~1"
if "%~1" == "" (
    @echo 请将需要配信巡护员网络任务的sav存档文件，拖到本bat文件上。
    @echo Please drag the ranger sav file needed to be distributed onto this bat file.
    @echo.
pause
goto :eof
)

set filePath=%1
for %%F in ("%filePath%") do (
    set "originalFileName=%%~nxF"
)
set "distributedfile=Distributed_%originalFileName%"

@echo 请输入游戏版本 [-r1/-r2/-r3]
@echo Please enter game version [-r1/-r2/-r3]
set /p gameversion=: 
@echo.
@echo 请输入游戏语言 [-jp/-oversea]
@echo Please enter game language [-jp/-oversea]
set /p gamelanguage=: 
@echo.

@echo 正在配信中...
@echo.
".\PRNMDTool.exe" "%gameversion%" "%gamelanguage%" "%~1" "%distributedfile%" 
@echo.
@echo.
pause
