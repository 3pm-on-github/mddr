import os, sys, platform
import moddriver

VERSION = "v0.1.0"
spwnexepath = f"{os.getenv("HOME")}/Desktop/spwn/spwn"

def clearcmd():
    os.system('cls' if os.name == 'nt' else 'clear')

def menu():
    print(f"MDDR {VERSION} by 3pm\n")
    print("NOTE: To run mods, you need to run MDDR with Administrator Privileges.")
    print("1. Exit")
    print("2. Patches")
    print("3. Scripts")
    print("4. Set SPWN Information")
    print("5. About")
    choice = input(">>> ").strip()
    if choice == "1":
        clearcmd()
        sys.exit(0)
    elif choice == "2":
        clearcmd()
        print("Patches:\n0. Exit")
        i=0
        for patchname in moddriver.listPatches():
            i+=1
            print(str(i)+". "+patchname)
        modid = input("Enter the patch you want to run.\n>>> ").strip()
        if modid == "0":
            clearcmd()
            menu()
        else:
            clearcmd()
            moddriver.runpatch(os.listdir(f"{os.getenv("HOME")}/mddr/patches")[int(modid)-1], spwnexepath)
            print("Press enter to go back to the menu", end="\r")
            input()
            clearcmd()
            menu()
    elif choice == "3":
        clearcmd()
        print("Coming Soon")
        menu()
    elif choice == "4":
        clearcmd()
        print("Please enter the path to your SPWN executable.")
        spwnexe = input(">>> ")
        print("Please enter the version of your copy of SPWN.")
        spwnver = input(">>> ")
        operatingsystem = ""
        # this looks bad, really bad.
        if platform.system().lower() == "windows":
            operatingsystem = "win"
        elif platform.system().lower() == "darwin":
            operatingsystem = "macOS"
        elif platform.system().lower() == "linux":
            operatingsystem = "linux"
        else:
            operatingsystem = "unknown"
        print(f"This information will be set:\nSPWN Executable Path: {spwnexe}\nSPWN Version: {spwnver}\nOperating System: {operatingsystem}\nPress enter to go back to the menu", end="\r")
        input()
        clearcmd()
        menu()
    elif choice == "5":
        clearcmd()
        print(f"MDDR {VERSION}")
        print("© 2024 - 2025")
        print("Credits:")
        print("Developer: 3pm")
        print("\nnote from 3pm: do not use this tool while drunk\n")
        print("█████████████████")
        print("██             ██")
        print("██   ██   ██   ██")
        print("██             ██")
        print("██  █████████  ██")
        print("██             ██")
        print("█████████████████")
        print("                  [mddr]\n")
        print("Press enter to go back to the menu", end="\r")
        input()
        clearcmd()
        menu()

def main():
    clearcmd()
    print("Welcome to MDDR!")
    menu()

if __name__ == "__main__":
    main()