import os
import moddriver.patcher

def runpatch(filename, spwnexepath):
    moddriver.patcher.patch(f"{os.getenv("HOME")}/mddr/patches/"+filename, spwnexepath)

def listPatches():
    moddirpath = f"{os.getenv("HOME")}/mddr/patches/"
    mods = []
    for item in os.listdir(moddirpath):
        mods.append(moddriver.patcher.getPatchName(moddirpath+item))
    return mods