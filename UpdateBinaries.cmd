
ECHO OFF

IF "%SKIPPOSTSTEP%" == "1" (EXIT)
IF EXIST ..\..\..\eve\updateBinaries.cmd ( START /D ..\..\..\eve /WAIT updateBinaries.cmd )
IF EXIST ..\..\..\wod\updateBinaries.cmd ( START /D ..\..\..\wod /WAIT updateBinaries.cmd )

EXIT