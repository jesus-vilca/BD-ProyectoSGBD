#ifndef BUFFER_MANAGER_H
#define BUFFER_MANAGER_H
#include <iostream>
using namespace std;

template<typename T> class Page;
template<typename T> class Frame;
template<typename T> class Bufferpool;
int change_bit(int);

template<typename T> class Page{
    T PageID;
    bool DirtyBit;
    int pincount;
    friend class Frame<T>;
    friend class Bufferpool<T>;
    public:
        Page();
};

template<typename T> Page<T>::Page(){
    this->DirtyBit=0;
    this->pincount=0;
}

template<typename T> class Frame{
    int FrameID;
    bool residentbit;
    bool refbit;
    int lru;
    Page<T>* Pag=nullptr;
    Frame<T>* next=nullptr;
    Frame<T>* prev=nullptr;
    friend class Bufferpool<T>;
    public:
        Frame();
};

template<typename T> Frame<T>::Frame(){
    this->FrameID=0;
    this->residentbit=0;
    this->refbit=0;
}

template<typename T> class Bufferpool{
    Frame<T>* beg=nullptr;
    Frame<T>* end=nullptr;
    Frame<T>* clock=end;
    int maxsize=0;
    public:
        Bufferpool(int x);
        void cant_frames(int n);
        bool is_in_memory(T dat);
        void _CLOCK(T dat);
        void _LRU(T dat);
        void imprimir();
};

template<typename T> Bufferpool<T>::Bufferpool(int x){
    this->beg=nullptr;
    this->end=nullptr;
    cant_frames(x);
}

template<typename T>
void Bufferpool<T>::cant_frames(int n){
    for(int i=0;i<n;i++){
        if(beg==nullptr){
            Frame<T>* auxP = new Frame<T>();
            auxP->lru=i;
            auxP->FrameID=i;
            auxP->next=nullptr;
            auxP->prev=nullptr;
            beg=end=auxP;
            maxsize++;
        }else if(maxsize==1){
            Frame<T>* auxP = new Frame<T>();
            auxP->lru=i;
            auxP->FrameID=i;
            auxP->next=auxP->prev=beg;
            beg->prev=end->next=auxP;
            end=auxP;
            maxsize++;
        }else{
            Frame<T>* auxP = new Frame<T>();
            auxP->lru=i;
            auxP->FrameID=i;
            auxP->next=beg;
            auxP->prev=end;
            beg->prev=end->next=auxP;
            end=auxP;
            maxsize++;
        }
    }
}

template<typename T>
bool Bufferpool<T>::is_in_memory(T dat){
    Frame<T>* aux = new Frame<T>();
    aux=beg;
    if(aux->Pag!=nullptr && aux->Pag->PageID==dat) return 1;
    aux=aux->next;
    while(aux->next==beg){
        if(aux->Pag!=nullptr && aux->Pag->PageID==dat) return 1;
        aux=aux->next;
    }
    return 0;
}

template<typename T>
void Bufferpool<T>::_CLOCK(T dat){
    if(!is_in_memory(dat)){
        clock=clock->next;
        if(clock->residentbit==0 && clock->refbit==0){
            Page<T>* aux = new Page<T>();
            aux->PageID=dat;
            aux->pincount=1;
            clock->Pag=aux;
            clock->refbit=change_bit(clock->refbit);
            clock->residentbit=change_bit(clock->residentbit);
        }else if(clock->residentbit==1 && clock->refbit==1){
            clock->refbit=change_bit(clock->refbit);
            _CLOCK(dat);
        }else if(clock->residentbit==1 && clock->refbit==0){
            if(clock->Pag->PageID==dat){}else{
                Page<T>* aux = new Page<T>();
                aux->PageID=dat;
                aux->pincount=1;
                clock->Pag=aux;
                clock->refbit=change_bit(clock->refbit);
            }
        }
    }
}

template<typename T>
void _LRU(T dat){
    if(!is_in_memory(dat)){
        Frame<T>* ax = new Frame<T>();
        ax=beg;
        while(ax->Pag!=nullptr && ax->next!=beg){
            ax->lru++;
            if(ax->lru==maxsize){
                ax->lru=0;
            }
            ax=ax->next;
        } 
        if(ax==end) ax=ax->next;
        Page<T>* aux = new Page<T>();
        aux->PageID=dat;
        aux->pincount=1;
        ax->Pag=aux;
        ax->residentbit=change_bit(ax->residentbit);
    }else if(is_in_memory(dat)){

    }
}

template<typename T>
void Bufferpool<T>::imprimir(){
    Frame<T>* aux = new Frame<T>();
    aux=beg;
    while(aux->next!=beg){
        if(aux->Pag!=nullptr) cout<<"Frame "<<aux->FrameID<<": "<<aux->Pag->PageID<<endl;
        else cout<<"Frame "<<aux->FrameID<<": "<<endl;
        aux=aux->next;
    }
    if(aux->Pag!=nullptr) cout<<"Frame "<<aux->FrameID<<": "<<aux->Pag->PageID<<endl;
    else cout<<"Frame "<<aux->FrameID<<": "<<endl;
}

int change_bit(int n){
    if(n==0){
        return 1;
    }else return 0;
}

#endif