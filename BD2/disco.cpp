#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <ctime>
#include <random>

using namespace std;
class Bloque{
    int capacidad;
    vector<Sector*>* sectors=new vector<Sector*>;
    public:
        Bloque(int n){
            capacidad=n;
        }
};

class Sector{
    int bytes;
    vector<short> PassengerId;  //2 bytes
    vector<bool> Survived;      //1 byte
    vector<char> Pclass;        //1 byte
    vector<string> Name;        //81 bytes
    vector<char> Sex;           //1 byte
    vector<short> Age;          //2 bytes
    vector<short> SibSp;        //2 bytes
    vector<short> Parch;        //2 bytes
    vector<string> Ticket;      //19 bytes
    vector<float> Fare;         //4 bytes
    vector<string> Cabin;       //16 bytes
    vector<char> Embarked;      //1 byte
    const int bits=132*8;
    public:
        Sector(int n){bytes=n;}
        void llenar_sector(string,int&);
        void print_sector();
        bool Svoid(){
            if(PassengerId.empty()) return true;
            return false;
        }
        void PinS(int);
        int BpS(){
            int aux=bits*PassengerId.size();
            return aux;
        }
        bool space(){
            if(bytes>132) return true;
            return false;
        }
        friend class Pista;
        friend class Plato;
        friend class Bloque;
        friend class Disco;
};
void Sector::llenar_sector(string nombreArchivo,int& n) {
    ofstream arch;
    arch.open(nombreArchivo+".txt",ios::app);
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo: " << nombreArchivo << endl;
        return;
    }
    string linea;
    for(int i=0;i<n+1;i++){
        getline(archivo,linea);
    }
    while (getline(archivo, linea) && bytes>132) {
        istringstream iss(linea);
        string dato;

        getline(iss, dato, ',');
        PassengerId.push_back(stoi(dato));
        bytes-=2;

        getline(iss, dato, ',');
        Survived.push_back(dato == "1");
        bytes-=1;

        getline(iss, dato, ',');
        Pclass.push_back(dato[0]);
        bytes-=1;

        getline(iss, dato, '"');
        getline(iss, dato, '"');
        Name.push_back(dato);
        bytes-=81;

        getline(iss, dato, ',');
        getline(iss, dato, ',');
        Sex.push_back(dato[0]);
        bytes-=1;

        getline(iss, dato, ',');
        Age.push_back(stof(dato));
        bytes-=2;

        getline(iss, dato, ',');
        SibSp.push_back(stoi(dato));
        bytes-=2;

        getline(iss, dato, ',');
        Parch.push_back(stoi(dato));
        bytes-=2;

        getline(iss, dato, ',');
        Ticket.push_back(dato);
        bytes-=19;

        getline(iss, dato, ',');
        Fare.push_back(stof(dato));
        bytes-=4;

        getline(iss, dato, ',');
        Cabin.push_back(dato);
        bytes-=16;

        getline(iss, dato, ',');        
        Embarked.push_back(dato[0]);
        bytes-=1;

        n++;
    }
    archivo.close();
}
void Sector::print_sector(){
    if(!Svoid()){
        cout<<"PassengerId\tSurvivedPclass\tName\tSex\tAge\tSibSp\tParch\tTicket\tFare\tCabin\tEmbarked"<<endl;
        for(size_t i=0;i<PassengerId.size();i++){
            cout<<PassengerId[i]<<"\t\t"<<Survived[i]<<"\t "<<Pclass[i]<<"\t"<<Name[i]<<"\t"<<Sex[i]<<"\t"<<Age[i]<<"\t"<<SibSp[i]<<"\t"<<Parch[i]<<"\t"<<Ticket[i]<<"\t"<<Fare[i]<<"\t"<<Cabin[i]<<"\t"<<Embarked[i]<<endl;
        }
    }
}
void Sector::PinS(int n){
    if(!Svoid()){
        for(size_t i=0;i<PassengerId.size();i++){
            if(PassengerId[i]==n){
                cout<<PassengerId[i]<<"\t"<<Survived[i]<<"\t "<<Pclass[i]<<"\t"<<Name[i]<<"\t"<<Sex[i]<<"\t"<<Age[i]<<"\t"<<SibSp[i]<<"\t"<<Parch[i]<<"\t"<<Ticket[i]<<"\t"<<Fare[i]<<"\t"<<Cabin[i]<<"\t"<<Embarked[i]<<endl;
            }
        }
    }
}
//4 sectores en cada pista
class Pista{
    int sectores;
    vector<Sector*> s;
    public:
        Pista(int sector,int byte){
            sectores=sector;
            for(int i=0;i<sector;i++){
                Sector* sec=new Sector(byte);
                s.push_back(sec);
            }
        }
        void llenar_pista(string,int&);
        void print_pista();
        bool Pvoid(){
            if(s[0]->Svoid()) return true;
            return false;
        }
        void PinP(int n){
            if(!Pvoid()){
                for(int i=0;i<sectores;i++) if(!s[i]->Svoid()) s[i]->PinS(n);
            }
        }
        int BpP(){
            if(!Pvoid()){
                int aux=0;
                for(int i=0;i<sectores;i++) if(!s[i]->Svoid()) aux+=s[i]->BpS();
                return aux;
            }
            return 0;
        }
        void PSinP(int& a,int n, int j){
            if(!Pvoid()){
                for(int i=0;i<sectores;i++) 
                    if(!s[i]->Svoid()){
                        if(a==1){
                            if(n%2==0){
                                cout<<"Plato "<<n/2
                                <<" , superficie A"
                                <<" - Pista "<<j
                                <<" - Sector "<<i<<endl;
                                s[i]->print_sector();
                                a=-1;
                                return;
                            }else if(n%2!=0){
                                cout<<"Plato "<<n/2
                                <<" , superficie B"
                                <<" - Pista "<<j
                                <<" - Sector "<<i<<endl;
                                s[i]->print_sector();
                                a=-1;
                                return;
                            }
                            
                        }else a--;
                    }
            }
        }
        bool spaceP(){
            for(int i=0;i<sectores;i++){
                if(s[i]->space()) return true;
            }
            return false;
        }
        Sector* RPtoSinP(int& n){
            for(int i=0;i<sectores;i++){
                if(n>sectores){
                    n-=sectores;    
                }else{
            
                }
            }
        }
        friend class Plato;
        friend class Bloque;
        friend class Disco;
};
void Pista::llenar_pista(string nombreArchivo,int& n){
    for(size_t i=0;i<s.size();i++){
        if(s[i]->space()){
            s[i]->llenar_sector(nombreArchivo,n);
        }
    }
}
void Pista::print_pista(){
    if(!Pvoid()){
        for(size_t i=0;i<s.size();i++){
            cout<<"Sector"<<i<<endl;
            s[i]->print_sector();
            cout<<endl;
        }
    }
}
//2 pistas en cada plato
class Plato{
    int pistas;
    vector<Pista*> p;
    public:
        Plato(int pista,int sector, int byte){
            pistas=pista;
            for(int i=0;i<pista;i++){
                Pista* pist=new Pista(sector,byte);
                p.push_back(pist);
            }
        }
        void llenar_plato(string,int&);
        void print_plato();
        bool PLvoid(){
            if(p[0]->Pvoid()) return true;
            return false;
        }
        void PinPL(int n){
            if(!PLvoid()){
                for(int i=0;i<pistas;i++) if(!p[i]->Pvoid()) p[i]->PinP(n);
            }
        }
        int BpPL(){
            if(!PLvoid()){
                int aux=0;
                for(int i=0;i<pistas;i++) if(!p[i]->Pvoid()) aux+=p[i]->BpP();
                return aux;
            }
            return 0;
        }
        void PSinPL(int& a,int j){
            if(!PLvoid()){
                for(int i=0;i<pistas;i++) 
                    if(!p[i]->Pvoid()){
                        p[i]->PSinP(a,j,i);
                    }   
                
            }
        }
        bool spacePL(){
            for(int i=0;i<pistas;i++){
                if(p[i]->spaceP()) return true;
            }
            return false;
        }
        friend class Bloque;
        friend class Disco;
};
void Plato::llenar_plato(string nombreArchivo,int& n){
    for(size_t i=0;i<p.size();i++){
        if(p[i]->spaceP()){
            p[i]->llenar_pista(nombreArchivo,n);
        }
    }
}
void Plato::print_plato(){
    if(!PLvoid()){
        for(size_t i=0;i<p.size();i++){
            cout<<"Pista"<<i<<endl;
            p[i]->print_pista();
            cout<<endl;
        }
    }
}

class Disco{
    int platos;
    vector<Plato*> pl;
    public:
        Disco(int plato,int pista,int sector ,int byte){
            platos=plato;
            for(int i=0;i<plato;i++){
                Plato* platA=new Plato(pista,sector,byte);
                Plato* platB=new Plato(pista,sector,byte);
                pl.push_back(platA);
                pl.push_back(platB);
            }
        }
        void capacidad();
        int getdat(){return platos;}
        void llenar_disco(string,int&);
        void print_disco();
        int bitXRegistro(){
            return pl[0]->p[0]->s[0]->bits;
        }
        bool Dvoid(){
            if(pl[0]->PLvoid()) return true;
            return false;
        }
        void PinD(int a){
            if(!Dvoid()){
                for(int i=0;i<platos;i++) if(!pl[i]->PLvoid()) pl[i]->PinPL(a);
            }
        }
        int BpF(){
            if(!Dvoid()){
                int aux=0;
                for(int i=0;i<platos;i++) if(!pl[i]->PLvoid()) aux+=pl[i]->BpPL();
                return aux;
            }
            return 0;
        }
        void PSinD(int a){
            if(!Dvoid()){
                for(int i=0;i<2*platos;i++)  
                    if(!pl[i]->PLvoid()){
                        pl[i]->PSinPL(a,i);
                    }
            }
        }
        bool spaceD(){
            for(int i=0;i<platos;i++){
                if(pl[i]->spacePL()) return true;
            }
            return false;
        }
};
void Disco::capacidad(){
    int cnt=0,cap=platos*2*(pl[0]->pistas)*(pl[0]->p[0]->sectores);
    while(cap/1024!=0){
        cnt++;
        cap/=1024;
    }
    cap*=(pl[0]->p[0]->s[0]->bytes);
    while(cap/1024!=0){
        cnt++;
        cap/=1024;
    }
    if(cnt==0) cout<<cap<<"bytes"<<endl;
    else if(cnt==1) cout<<cap<<"Kb"<<endl;
    else if(cnt==2) cout<<cap<<"Mb"<<endl;
    else if(cnt==3) cout<<cap<<"Gb"<<endl;
    else if(cnt==4) cout<<cap<<"Tb"<<endl;
}
void Disco::llenar_disco(string nombreArchivo,int& n){
    if(!spaceD()){
        cout<<"No hay más espacio en el disco."<<endl;
        return;
    }
    for(size_t i=0;i<pl.size();i++){
        if(pl[i]->spacePL()){
            pl[i]->llenar_plato(nombreArchivo,n);
        }
    }
}
void Disco::print_disco(){
    if(!Dvoid()){
        for(size_t i=0;i<pl.size();i++){
            if(i%2==0){
                cout<<"Plato "<<i/2<<" - superficie A"<<endl;
                pl[i]->print_plato();
                cout<<endl;
            }else{
                cout<<"Plato "<<i/2<<" - superficie B"<<endl;
                pl[i]->print_plato();
                cout<<endl;
            }
        }
    }
}

int main(){
    //(cantidad de platos, pistas por plato, sectores por pista, bytes por sector)
    /*
    Megatron->print_disco();
    *//*
    Disco* Megatron=nullptr;
    int in;
    cin>>in;
    while(in!=-1){
        cout<<"0. crear disco"<<endl;
        cout<<"1. capacidad del disco"<<endl;
        cout<<"2. llenar disco"<<endl;
        cout<<"3. bits por registro"<<endl;
        cout<<"4. bit por file"<<endl;
        cout<<"5. imprimir contenido disco"<<endl;
        cout<<"6. imprimir registro"<<endl;
        cout<<"7. imprimir sector"<<endl;
        if(in==0){
            int a,b,c,d;
            cout<<"Ingrese cantidad de platos: "<<endl;
            cin>>a;
            cout<<"Ingrese cantidad de pistas por plato: "<<endl;
            cin>>b;
            cout<<"Ingrese cantidad de sectores por pista: "<<endl;
            cin>>c;
            cout<<"Ingrese cantidad de bytes por sector: "<<endl;
            cin>>d;
            Disco* disco=new Disco(a,b,c,d);
            Megatron=disco;
        } 
        if(in==1){
            if(Megatron==nullptr) cout<<"NO se ha creado un disco."<<endl;
            Megatron->capacidad();
        } 
        if(in==2){
            if(Megatron==nullptr) cout<<"NO se ha creado un disco."<<endl;
            string file;
            cout<<"ingrese su file: "<<endl;
            getline(cin,file);
            int cant_registros=0;
            Megatron->llenar_disco(file,cant_registros);
            cout<<"Se agregaron correctamente "<<cant_registros<<" registros."<<endl;
        }
        if(in==3){
            if(Megatron==nullptr) cout<<"NO se ha creado un disco."<<endl;
            cout<<Megatron->bitXRegistro()<<endl;
        }
        if(in==4){
            if(Megatron==nullptr) cout<<"NO se ha creado un disco."<<endl;
            cout<<Megatron->BpF()<<endl;
        }
        if(in==5){
            if(Megatron==nullptr) cout<<"NO se ha creado un disco."<<endl;
            Megatron->print_disco();
        }
        if(in==6){
            if(Megatron==nullptr) cout<<"NO se ha creado un disco."<<endl;
            cout<<"digite su registro: "<<endl;
            int a=0;
            cin>>a;
            Megatron->PinD(a);
        }
        if(in==7){
            if(Megatron==nullptr) cout<<"NO se ha creado un disco."<<endl;
            cout<<"digite su registro: "<<endl;
            int a=0;
            cin>>a;
            Megatron->PSinD();
        }
        if(in==4);
        if(in==4);
        if(in==4);
        if(in==4);
        cin>>in;
    }
    */
    //cout<<Megatron->print_Registro(257)<<endl;
    srand(time(NULL));
    Disco* Megatron=new Disco(4,2,4,4096);
    int a=0;
    Megatron->llenar_disco("titanic.csv",a);
    a=29;
    //cout<<"imprimir el sector "<<a<<endl;
    //Megatron->PSinD(a);
}