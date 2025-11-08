#!/bin/bash

set -e

mkdir -p TEMP_BUILT_MDDR

echo "Copying MDDR script..."
rm -rf src/moddriver/__pycache__
cp -r ./src/moddriver ./TEMP_BUILT_MDDR/
cp ./src/mddr.py ./TEMP_BUILT_MDDR/
cp runbeforeuse.sh ./TEMP_BUILT_MDDR/
cp run.sh ./TEMP_BUILT_MDDR/

echo "Copying preinstalled patches..."
cd TEMP_BUILT_MDDR
mkdir -p patches
cd ..
cp ./preinstalled-patches/funistr.ips ./TEMP_BUILT_MDDR/patches/

echo "Zipping files into zip file..."
cd TEMP_BUILT_MDDR
current_date=$(date +%Y%m%d)
zip -r MDDR.zip .
cd ..
mv TEMP_BUILT_MDDR/MDDR.zip ./
rm -rf TEMP_BUILT_MDDR

echo "Successfully built MDDR. Press any key to exit."
read -n 1 -s