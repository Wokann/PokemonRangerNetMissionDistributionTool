@echo off
@echo *-------------------------------------------------------------*
@echo ^| ������Ѳ��Ա�������������� v0.1            �����Կ�΢������ ^| 
@echo ^| PokemonRangerNetMissionDistributionTool v0.1 made by wokann ^|
@echo ^|                                                  2023.12.10 ^|
@echo *-------------------------------------------------------------*
@echo.

%~d0
cd "%~dp0"
::@echo ���Ϸŵ��ļ��ǣ�"%~1"
if "%~1" == "" (
    @echo �뽫��Ҫ����Ѳ��Ա���������sav�浵�ļ����ϵ���bat�ļ��ϡ�
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

@echo ��������Ϸ�汾 [-r1/-r2/-r3]
@echo Please enter game version [-r1/-r2/-r3]
set /p gameversion=: 
@echo.
@echo ��������Ϸ���� [-jp/-oversea]
@echo Please enter game language [-jp/-oversea]
set /p gamelanguage=: 
@echo.

@echo ����������...
@echo.
".\PRNMDTool.exe" "%gameversion%" "%gamelanguage%" "%~1" "%distributedfile%" 
@echo.
@echo.
pause
