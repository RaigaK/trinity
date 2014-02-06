@echo off
echo Checking out project and filters file
p4 edit trinity.vcxproj
p4 edit trinity.vcxproj.filters
p4 edit trinity.orbis.vcxproj
p4 edit trinity.orbis.vcxproj.filters
echo Regenerating
..\..\..\..\..\..\shared_tools\python\27\python.exe ..\..\tools\ProjectFileGenerator\ProjectFileGenerator.py -i trinity.ccpproj
..\..\..\..\..\..\shared_tools\python\27\python.exe ..\..\tools\ProjectFileGenerator\ProjectFileGenerator.py -i trinity.ccpproj --orbis
pause