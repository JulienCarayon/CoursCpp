Rem | Ce script permet de copier tous les fichiers src/dll/*/release/*.dll
Rem | dans bin/release et les fichiers src/dll/*/debug/*.dll dans bin/debug.
echo Copy DLL files in bin/release and bin/debug directories.
FOR /D %%D IN (..\src\dll\*) DO (
XCOPY  /Y /C /F  "%%D\qt5\release\*.dll" "..\bin\release"
XCOPY  /Y /C /F  "%%D\qt5\debug\*.dll" "..\bin\debug"
)
