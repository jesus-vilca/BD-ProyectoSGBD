#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>
using namespace std;

void procesarArchivoCSV(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo: " << nombreArchivo << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        istringstream iss(linea);
        string valor;
        while (getline(iss, valor, ',')) {
            if (valor.empty()) {
                cout << "Tipo: vacío" << endl;
            } else if (valor[0] == '"' && valor.back() == '"') {
                cout << "Tipo: string entre comillas" << endl;
            } else if (isdigit(valor[0])) {
                char* p;
                strtod(valor.c_str(), &p);
                if (*p == 0){}
                //    cout << "Tipo: número" << endl;
                else{}
                //    cout << "Tipo: otro string" << endl;
            } else {
                cout << "Tipo: otro string" << endl;
            }
        }
    }

    archivo.close();
}

int main() {
    string nombreArchivo = "titanic.csv";
    procesarArchivoCSV(nombreArchivo);

    return 0;
}
