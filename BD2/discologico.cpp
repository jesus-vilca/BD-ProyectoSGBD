#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class DiscoLogico {
    private:
        vector<Plato> platos;
    public:
        void agregarPlato(const Plato& plato) {
            platos.push_back(plato);
        }
        void guardarEnDisco(const string& nombreArchivo) {
            ofstream archivo(nombreArchivo, ios::binary);

            for (const auto& plato : platos) {
                plato.guardarEnDisco(archivo);
            }

            archivo.close();
        }
        void leerDesdeDisco(const string& nombreArchivo) {
            ifstream archivo(nombreArchivo, ios::binary);

            if (!archivo) {
                cout << "Error al abrir el archivo: " << nombreArchivo << endl;
                return;
            }

            // Leer los platos desde el archivo
            // ...

            archivo.close();
        }
};

class Plato {
private:
    vector<Superficie> superficies;

public:
    void agregarSuperficie(const Superficie& superficie) {
        superficies.push_back(superficie);
    }

    void guardarEnDisco(ofstream& archivo) const {
        for (const auto& superficie : superficies) {
            superficie.guardarEnDisco(archivo);
        }
    }

    // Resto de métodos de Plato
};

class Superficie {
private:
    vector<Pista> pistas;

public:
    void agregarPista(const Pista& pista) {
        pistas.push_back(pista);
    }

    void guardarEnDisco(ofstream& archivo) const {
        for (const auto& pista : pistas) {
            pista.guardarEnDisco(archivo);
        }
    }

    // Resto de métodos de Superficie
};

class Pista {
private:
    vector<Sector> sectores;

public:
    void agregarSector(const Sector& sector) {
        sectores.push_back(sector);
    }

    void guardarEnDisco(ofstream& archivo) const {
        for (const auto& sector : sectores) {
            sector.guardarEnDisco(archivo);
        }
    }

    // Resto de métodos de Pista
};

class Sector {
private:
    vector<Registro> registros;

public:
    void agregarRegistro(const Registro& registro) {
        registros.push_back(registro);
    }

    void guardarEnDisco(ofstream& archivo) const {
        for (const auto& registro : registros) {
            registro.guardarEnDisco(archivo);
        }
    }

    // Resto de métodos de Sector
};

class Registro {
private:
    int offset;
    string datos;

public:
    void agregarDato(char dato) {
        datos.push_back(dato);
    }

    void guardarEnDisco(ofstream& archivo) const {
        // Guardar offset y datos en el archivo
        // ...
    }

    // Resto de métodos de Registro
};

// Ejemplo de uso
int main() {
    DiscoLogico disco;

    Plato plato1;
    // Agregar superficies, pistas, sectores y registros a plato1
    disco.agregarPlato(plato1);

    Plato plato2;
    // Agregar superficies, pistas, sectores y registros a plato2
    disco.agregarPlato(plato2);

    // Guardar en disco
    disco.guardarEnDisco("disco.dat");

    // Leer desde disco
    DiscoLogico disco2;
    disco2.leerDesdeDisco("disco.dat");

    return 0;
}
