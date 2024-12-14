#!/bin/bash

echo "Creating mddr folder..."
mkdir mddr

echo "Moving mods folder..."
mv mods mddr

echo "Moving mddr folder..."
mv mddr /

echo "Deleting this script..."
rm -f "./runbeforeuse.sh"

echo "Done, you can now use MDDR."
