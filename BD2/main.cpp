#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>
#include <bitset>

using namespace std;

class Sector {
public:
    int bytes=4096;
    string file;
    public:
        Sector(){}
        void cargarDatosDeFormaFija(string,int&);
        void cargarDatosDeFormaVariable(string,int&);
};

void Sector::cargarDatosDeFormaFija(string nombreArchivo,int& n) {
    ifstream archivo(nombreArchivo);
    ofstream database(file,ios::app);
    string linea;
    getline(archivo,linea);
    for(int i=0;i<n;i++){
        getline(archivo,linea);
    }
    while (getline(archivo, linea)) {
        istringstream iss(linea);
        string dato, reg;
        while(getline(iss, dato, ',')){
            if (dato.front() == '"') {
                string aux=dato+',';
                while(dato.back() != '"'){
                    getline(iss, dato, ',');
                    aux+=dato;
                }
                aux = aux.substr(1, aux.length() - 2);
                reg+=stringABits(reserva_de_memoria(aux.size(),aux));
            } else if (!dato.empty() && all_of(dato.begin(), dato.end(), [](unsigned char c) { return isdigit(c); })) {
                int entero = stoi(dato);
                reg+=enteroABits(entero);
            } else if (isdigit(dato[0])) {
                double flotante = stod(dato);
                reg+=flotanteABits(flotante);
            } else if (dato.empty()) {
                reg+=enteroABits(0);
            } else {
            }
        }
        char ultimoCaracter = linea.back();
        if(ultimoCaracter==','){
            reg+=enteroABits(0).substr(16);
        }
        database<<reg<<endl;
        n++;
    }
    archivo.close();
}

string enteroABits(int numero) {
    bitset<sizeof(int) * 8> bits(numero);
    string resultado = bits.to_string();
    return resultado;
}
int bitsAEntero(const std::string& bits) {
    int numero = std::bitset<32>(bits).to_ulong();
    return numero;
}
string flotanteABits(float numero) {
    unsigned int bits = *reinterpret_cast<unsigned int*>(&numero);
    string resultado = bitset<sizeof(float) * 8>(bits).to_string();
    return resultado;
}
float bitsAFlotante(const std::string& bits) {
    // Obtener la representación en entero de los bits
    int numeroEntero = std::bitset<32>(bits).to_ulong();

    // Interpretar el entero como un flotante
    float numeroFlotante = *reinterpret_cast<float*>(&numeroEntero);

    return numeroFlotante;
}
string stringABits(const string& text) {
    string binary;
    for (char c : text) {
        binary += bitset<8>(c).to_string();
    }
    return binary;
}
string bitsAString(const string& bits) {
    string resultado;
    for (size_t i = 0; i < bits.length(); i += 8) {
        string grupoBits = bits.substr(i, 8);
        unsigned char caracter = bitset<8>(grupoBits).to_ulong();
        resultado.push_back(static_cast<char>(caracter));
    }
    return resultado;
}
string reserva_de_memoria(int numero, const string bitmap) {
    string aux;
    int multiplo = ((numero + 7) / 8) * 8;
    for (int i = 0; i < multiplo; i++) aux += '0';
        int bitmapIndex = bitmap.length() - 1;
    for (int i = aux.length() - 1; i >= 0; i--) {
        if (bitmapIndex >= 0) {
            aux[i] = bitmap[bitmapIndex];
            bitmapIndex--;
        } else break;
        }
    return aux;
}

void Sector::cargarDatosDeFormaVariable(string nombreArchivo,int& n) {
    ifstream archivo(nombreArchivo);
    ofstream database(file,ios::app);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo: " << nombreArchivo << endl;
        return;
    }
    int cantdat=0;
    string linea,dit;
    getline(archivo,linea);
    istringstream isini(linea);
    while(getline(isini,dit,',')){ cantdat++; }
    for(int i=0;i<n;i++){
        getline(archivo,linea);
    }
    while (getline(archivo, linea)) {
        istringstream iss(linea);
        string dato, bitmap, reg, regvar, offset;
        while(getline(iss, dato, ',')){
            if (dato.front() == '"') {
                string aux=dato+',';
                while(dato.back() != '"'){
                    getline(iss, dato, ',');
                    aux+=dato;
                }
                aux = aux.substr(1, aux.length() - 2);
                offset=enteroABits(cantdat*4+regvar.size()/8).substr(16);
                offset+=enteroABits(aux.size()).substr(16);
                reg+=offset;
                regvar+=stringABits(aux);
                bitmap+="0";
            } else if (!dato.empty() && all_of(dato.begin(), dato.end(), [](unsigned char c) { return isdigit(c); })) {
                int entero = stoi(dato);
                reg+=enteroABits(entero);
                bitmap+="0";
            } else if (isdigit(dato[0])) {
                double flotante = stod(dato);
                reg+=flotanteABits(flotante);
                bitmap+="0";
            } else if (dato.empty()) {
                reg+=enteroABits(0);
                bitmap+="1";
            } else {
                offset=enteroABits(cantdat*4+regvar.size()/8).substr(16);
                offset+=enteroABits(dato.size()).substr(16);
                reg+=offset;
                regvar+=stringABits(dato);
                bitmap+="0";
            }
        }
        char ultimoCaracter = linea.back();
        if(ultimoCaracter==','){
            reg+=enteroABits(0);
            bitmap+="1";
        }
        reg+=reserva_de_memoria(cantdat,bitmap);
        reg+=regvar;
        database<<reg<<endl;
        n++;
    }
    archivo.close();
}

int main(){
    
    Sector sector;
    string nombreArchivo = "titanic.csv";
    int iter=0;
    sector.cargarDatosDeFormaVariable(nombreArchivo,iter);
}

