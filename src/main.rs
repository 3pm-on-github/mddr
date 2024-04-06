use core::time;
use std::thread::sleep;
use colored::Colorize;
use std::io::Write;
use std::io;
use std::process::Command;
mod mods {
    pub mod spwn22;
}

fn clearcmd(){if cfg!(target_os = "windows"){let _=Command::new("cmd").args(&["/c","cls"]).status();}else{let _=Command::new("clear").status();}}
fn error(error:&str){println!("{}",error.red().bold())}
fn rainbow(text:&str, secs:u64){let rts=[text.red(),text.yellow(),text.green(),text.blue(),text.purple()];for _ in 0..secs {for i in 0..5{print!("\r{}",rts[i]);let _=io::stdout().flush();sleep(time::Duration::from_millis(200));}}}

fn run() {
    const VERSION: &str = "v0.0.01A";
    let modslist = [
        ["spwn22", "A spwn mod to implement some 2.2 features in SPWN!"]
    ];
    print!("\rMDDR {} by GachaYTB3", VERSION);
    println!();
    println!("NOTE: to run mods, you need to run mddr as administrator.");
    println!("1. Exit");
    println!("2. Run a mod");
    println!("3. Mod list");
    let mut input = String::new();
    print!(">>> ");
    let _ = io::stdout().flush();
    io::stdin().read_line(&mut input).expect("Failed to read line");
    input = input.trim().to_string();
    match input.as_str() {
        "1" => {
            clearcmd();
            std::process::exit(0);
        }
        "2" => {
            clearcmd();
            println!("What's the mod id?");
            print!(">>> ");
            let _ = io::stdout().flush();
            let mut modid = String::new();
            io::stdin().read_line(&mut modid).expect("Failed to read line");
            let modid = modid.trim();
            clearcmd();
            match modid {
                "spwn22" => {
                    let _ = mods::spwn22::init();
                }
                _ => {
                    error("Error: Invalid mod id");
                    run();
                }
            }
        }
        "3" => {
            clearcmd();
            println!("Mods:");
            for item in modslist.iter() {
                println!("{}: {}", item[0], item[1])
            }
            run();
        }
        _ => {
            error("Error: Invalid option");
            run();
        }
    }
}

fn main() {
    clearcmd();
    rainbow("Welcome to MDDR!", 2);
    run()
}