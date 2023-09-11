#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <cstdlib> // para system()

namespace fs = std::filesystem;

// Aquí estás embebido tu 'fit', pero lo pondré como string constante como ejemplo.
const std::string fit = "Tu contenido embebido aquí";

int main(int argc, char *argv[]) {
    std::string outputFile = "firmware.img";
    std::string inputFile = "";

    // Parsea argumentos del command line, no es como 'flag' en Go pero hace el jale
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-o") {
            if (i + 1 < argc) {
                outputFile = argv[++i];
            }
        } else if (arg == "-i") {
            if (i + 1 < argc) {
                inputFile = argv[++i];
            }
        }
    }

    if (inputFile.empty()) {
        std::cerr << "no input, ándale con la que te rayaste perri" << std::endl;
        return 1;
    }

    auto absPath = fs::absolute(inputFile);

    // Creamos un archivo temporal
    auto tempPath = fs::temp_directory_path() / "vf2-fit";
    {
        std::ofstream tempFile(tempPath);
        std::string replacedFit = fit; // Aquí deberías de reemplazar '$firmware' por 'absPath'
        tempFile << replacedFit;
    }

    // Ahora ejecutamos el comando, estilo perriláctico
    std::ostringstream cmd;
    cmd << "mkimage -f " << tempPath << " -A riscv -O u-boot -T firmware " << outputFile;
    int status = std::system(cmd.str().c_str());

    if (status != 0) {
        std::cerr << "Ocurrió un error, no fluyó como se esperaba perri" << std::endl;
        return 1;
    }

    return 0;
}
