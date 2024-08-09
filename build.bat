@echo off
cargo build --release
echo Checking output...
mkdir TEMP_BUILT_MDDR
move target\release\mddr.exe TEMP_BUILT_MDDR\mddr.exe
rmdir /s /q target
echo Successfully built mddr.exe. Copying build script...
xcopy "runbeforeuse.bat" "TEMP_BUILT_MDDR\" /I /H /Y
echo Successfully copied build script. Creating mods folder...
cd TEMP_BUILT_MDDR
mkdir mods
echo Successfully created mods folder. Copying preinstalled mods...
cd mods
mkdir spwn22
mkdir funispwn
cd ../..
xcopy "./preinstalled-mods/spwn22" "./TEMP_BUILT_MDDR/mods/spwn22" /E /I /H /Y
xcopy "./preinstalled-mods/funispwn" "./TEMP_BUILT_MDDR/mods/funispwn" /E /I /H /Y
echo Successfully copied preinstalled mods. Zipping files into zip file...
cd TEMP_BUILT_MDDR
for /f "tokens=3,2,4 delims=/- " %%x in ("%date%") do set d=%%y%%x%%z
set data=%d%
"C:\Program Files\7-Zip\7z.exe" a -tzip "./MDDR.zip" "./"
cd ..
move TEMP_BUILT_MDDR\MDDR.zip ./
rmdir /s /q TEMP_BUILT_MDDR
echo Successfully built mddr. Press any key to exit.
pause >nul