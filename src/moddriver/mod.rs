use std::fs::{self, File};
use std::io::Read;
use std::path::Path;

pub fn launchmod(modid: &str) {
    let modfolderpath = Path::new("/mddr/mods");
    let mut foundmod = false;

    match fs::read_dir(modfolderpath) {
        Ok(entries) => {
            for entry in entries {
                match entry {
                    Ok(entry) => {
                        if entry.path().is_dir() {
                            if let Some(name) = entry.file_name().to_str() {
                                if read_mddri_file(format!("/mddr/mods/{}/info.mddri", name))[0] == modid {
                                    foundmod = true;
                                }
                            }
                        }
                    }
                    Err(e) => eprintln!("Error reading entry: {}", e),
                }
            }
        }
        Err(e) => eprintln!("Error reading directory: {}", e),
    }
    if foundmod == false {
        println!("Error: Mod Not Found");
    }
}

pub fn mods() -> Vec<[String; 2]> {
    let mut modlist = Vec::new();
    let modfolderpath = Path::new("/mddr/mods");

    match fs::read_dir(modfolderpath) {
        Ok(entries) => {
            for entry in entries {
                match entry {
                    Ok(entry) => {
                        if entry.path().is_dir() {
                            if let Some(name) = entry.file_name().to_str() {
                                modlist.push(read_mddri_file(format!("/mddr/mods/{}/info.mddri", name)));
                            }
                        }
                    }
                    Err(e) => eprintln!("Error reading entry: {}", e),
                }
            }
        }
        Err(e) => eprintln!("Error reading directory: {}", e),
    }

    modlist
}
fn read_mddri_file(path: String) -> [String; 2] {
    let mut file = match File::open(&path) {
        Ok(file) => file,
        Err(_) => return [String::from("oh no"), String::from("something went wrong")],
    };
    let mut mddri_file_content = String::new();
    match file.read_to_string(&mut mddri_file_content) {
        Ok(_) => (),
        Err(_) => return [String::from("oh no"), String::from("something went wrong")],
    };

    // this is to turn the file content into the return value
    let mut lines = mddri_file_content.lines();
    let info = [
        lines.next().unwrap_or("").strip_prefix("modname: ").unwrap_or("").to_string(),
        lines.next().unwrap_or("").strip_prefix("moddescription: ").unwrap_or("").to_owned()
    ];
    
    info
}