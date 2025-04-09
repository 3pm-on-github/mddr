#!/bin/bash

set -e

# compiling part

echo "Building project..."
gcc src/main.c -o MDDR

echo "Checking output..."
mkdir -p TEMP_BUILT_MDDR
mv MDDR TEMP_BUILT_MDDR/mddr
rm -rf target

# end of compiling part

echo "Successfully built mddr. Copying build script..."
cp runbeforeuse.sh TEMP_BUILT_MDDR/

echo "Successfully copied build script. Creating mods folder..."
cd TEMP_BUILT_MDDR
mkdir -p mods/spwn22 mods/funispwn
cd ..

echo "Successfully created mods folder. Copying preinstalled mods..."
cp -r ./preinstalled-mods/spwn22 ./TEMP_BUILT_MDDR/mods/spwn22
cp -r ./preinstalled-mods/funispwn ./TEMP_BUILT_MDDR/mods/funispwn

echo "Successfully copied preinstalled mods. Zipping files into zip file..."
cd TEMP_BUILT_MDDR
current_date=$(date +%Y%m%d)
zip -r MDDR.zip .
cd ..
mv TEMP_BUILT_MDDR/MDDR.zip ./
rm -rf TEMP_BUILT_MDDR

echo "Successfully built mddr. Press any key to exit."
read -n 1 -s