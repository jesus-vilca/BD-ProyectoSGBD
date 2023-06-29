#include <iostream>
using namespace std;

#define ASCENDENTE 1

class Nodo{
    private:
        int hit=0, miss=0,id=0;
        char page=' ';
        Nodo* siguiente=nullptr;
    friend class Lista;
    public:
        Nodo(){}
        Nodo(char a,Nodo* sig):page(a),siguiente(sig){}
        Nodo(char a):page(a){}
};

class Lista {
    private:
        Nodo* list=nullptr;
        int tam;
    public:
        Lista(){}
        ~Lista();
        void Insertar(char a);
        void Borrar(char v);
        bool ListaVacia() { return list == nullptr; }
        void Mostrar(char);
        void Siguiente();
        void Primero();
        void Ultimo();
        bool Actual() { return list != nullptr; }
        void Reemplazar(char,char);
Lista::~Lista() {
    Nodo* aux;
    while(list!= nullptr){
        aux = list;
        list = list->siguiente;
        delete aux;
    }
}
void Lista::Insertar(char v){
    Nodo* nuevo=new Nodo(v);
    if(list==nullptr){
        list=nuevo;
    nuevo->miss=1;
    }else{
        while(list->siguiente && list->siguiente->page <= v) Siguiente();
        list->siguiente = nuevo;
    }    tam++;
}
void Lista::Borrar(char v) {
    Nodo* Nodo;
    Nodo = list;
    while(Nodo && Nodo->page < v) Nodo = Nodo->siguiente;
    if(!Nodo || Nodo->page != v) return;
    delete Nodo;
    tam--;
}
void Lista::Mostrar(char orden) {
    Nodo* Nodo;
    if(orden == ASCENDENTE) {
        Primero();
        Nodo = list;
        while(Nodo) {
            cout << Nodo->page << "-> ";
            Nodo = Nodo->siguiente;
        }
    }
    cout << endl;
}
void Lista::Siguiente() {
   if(list) list = list->siguiente;
}
void Lista::Ultimo() {
   while(list && list->siguiente) list = list->siguiente;
}
void Lista::Reemplazar(char a,char b){

}
};
int main() {
   Lista Lista;

   Lista.Insertar('A');
   Lista.Insertar('B');
   Lista.Insertar('C');
   Lista.Insertar('D');

   Lista.Mostrar(ASCENDENTE);

   Lista.Borrar('A');
   Lista.Borrar('B');
   Lista.Borrar('C');
   Lista.Borrar('D');

   Lista.Mostrar(ASCENDENTE);
 
   return 0;
}