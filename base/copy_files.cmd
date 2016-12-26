@echo off
setlocal
REM -- language file
call ..\env_cfg.bat

SET DEST=..\bin
SET THIRDPARTY=..\..\3rdParty

rem (mkdir is recursive) if not exist "%DEST%" mkdir "%DEST%">nul
if not exist "%DEST%\lang" mkdir "%DEST%\lang">nul
"%QTDIR%\lrelease" -compress -silent ..\i18n\de.ts -qm ..\i18n\de.qm
"%QTDIR%\lrelease" -compress -silent ..\i18n\nl.ts -qm ..\i18n\nl.qm
copy /Y "..\i18n\core_??.qm" "%DEST%\lang">nul
copy /Y "..\i18n\??.qm" "%DEST%\lang">nul

REM -- sounds
if not exist "%DEST%\sounds" mkdir "%DEST%\sounds">nul
copy /Y "..\base\sounds\buzzer.wav" "%DEST%\sounds">nul
copy /Y "%THIRDPARTY%\sounds\*.wav" "%DEST%\sounds">nul

REM -- binaries
copy /Y "%QTDIR%\QtCore*.dll" "%DEST%">nul
copy /Y "%QTDIR%\QtGui*.dll" "%DEST%">nul
copy /Y "%QTDIR%\QtNetwork*.dll" "%DEST%">nul
copy /Y "%QTDIR%\QtXmlPatterns*.dll" "%DEST%">nul
copy /Y "%THIRDPARTY%\msvc120\*.dll" "%DEST%">nul

REM -- doc
rem copy /Y "%DEST%\doc\Anleitung.pdf" "%DEST%">nul
rem copy /Y "%DEST%\doc\manual.pdf" "%DEST%">nul

REM -- categories
copy /Y "..\base\categories.json" "%DEST%">nul
REM -- clubs
if not exist "%DEST%\clubs" mkdir "%DEST%\clubs">nul
copy /Y "clubs.json" "%DEST%">nul
copy /Y "clubs\*.png" "%DEST%\clubs">nul

REM -- templates
if not exist "%DEST%\templates" mkdir "%DEST%\templates">nul
copy /Y "templates\*.*" "%DEST%\templates">nul

REM -- modes
copy /Y TournamentModes.ini "%DEST%">nul

REM -- programme
REM if not exist "%DEST%\Ipponboard.exe" (
	REM echo ERROR: Ipponboard.exe not found
	REM pause
	REM exit 1
REM )

copy /Y "..\CHANGELOG.txt" "%DEST%">nul