use std::env;
use std::fs::{self, File};
use std::io::{self, Read, Write};
use std::path::{Path, PathBuf};
use std::process::{self, Command};

const VF2_FIT_ITS: &[u8] = include_bytes!("vf2-fit.its");

fn main() -> io::Result<()> {
    let args: Vec<String> = env::args().collect();
    let mut output_file = "firmware.img".to_string();
    let mut input_file = String::new();

    for i in 1..args.len() {
        if args[i] == "-o" && i + 1 < args.len() {
            output_file = args[i + 1].clone();
        } else if args[i] == "-i" && i + 1 < args.len() {
            input_file = args[i + 1].clone();
        }
    }

    if input_file.is_empty() {
        eprintln!("No input");
        process::exit(1);
    }

    let path = Path::new(&input_file);
    if !path.exists() {
        eprintln!("Error: Input file does not exist");
        process::exit(1);
    }

    let mut temp_file = tempfile::NamedTempFile::new()?;
    temp_file.write_all(VF2_FIT_ITS)?;

    let mut temp_content = String::new();
    temp_file.as_file_mut().read_to_string(&mut temp_content)?;

    if let Some(pos) = temp_content.find("$firmware") {
        temp_content.replace_range(pos..pos + 9, &path.to_string_lossy());
    }

    temp_file.as_file_mut().set_len(0)?;
    temp_file.write_all(temp_content.as_bytes())?;

    let cmd = format!(
        "mkimage -f {} -A riscv -O u-boot -T firmware {}",
        temp_file.path().display(),
        output_file
    );

    let status = Command::new("sh")
        .arg("-c")
        .arg(&cmd)
        .status()
        .expect("Failed to run mkimage command");

    if !status.success() {
        eprintln!("Error: Failed to run mkimage command");
        process::exit(1);
    }

    Ok(())
}
