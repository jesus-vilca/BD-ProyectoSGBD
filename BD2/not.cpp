#include <iostream>
#include <fstream>
#include <string>

class Sector {
private:
    std::string nombreArchivo;  // Nombre del archivo de texto

public:
    Sector(const std::string& archivo) : nombreArchivo(archivo) {}

    void escribirArchivo(const std::string& texto) {
        std::ofstream archivo(nombreArchivo, std::ios::app);
        if (archivo.is_open()) {
            archivo << texto << std::endl;
            archivo.close();
            std::cout << "Texto agregado al archivo." << std::endl;
        } else {
            std::cout << "Error al abrir el archivo: " << nombreArchivo << std::endl;
        }
    }

    void leerArchivo() {
        std::ifstream archivo(nombreArchivo);
        if (archivo.is_open()) {
            std::string linea;
            while (std::getline(archivo, linea)) {
                std::cout << linea << std::endl;
            }
            archivo.close();
        } else {
            std::cout << "Error al abrir el archivo: " << nombreArchivo << std::endl;
        }
    }
};

int main() {
    Sector sector("datos.txt");

    sector.escribirArchivo("Hola, este es un ejemplo.");
    sector.escribirArchivo("Esto es otro texto.");

    sector.leerArchivo();

    return 0;
}
