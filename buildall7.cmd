call "C:\Program Files\Microsoft Visual Studio .NET 2003\Common7\Tools\vsvars32.bat"
start devenv trinity.sln /build release
start devenv trinity.sln /build debug
start devenv trinity.sln /build dev9
start devenv trinity.sln /build dev10

