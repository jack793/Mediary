#ifndef CONTAINER_H
#define CONTAINER_H

template<class T>
class Container{
    friend class Iterator;
private:
    unsigned int  items;  //conta il numero di elementi nel contenitore (molto utile)
    class Nodo; //dich. incompleta

    class Smartp{
    public:
        Nodo* punt; //unico campo dati di smartp
        
        //Costruttore
        Smartp(Nodo* p=0): punt(p) { if(punt!=0) punt->riferimenti++; }
        
        //Construttore di copia
        Smartp(const Smartp& c): punt(c.punt) { if(punt!=0) punt->riferimenti++;}
        
        //Distruttore
        ~Smartp(){
            if(punt!=0){
                punt->riferimenti--;
                if(punt->riferimenti==0) delete punt;
            }
        }
        
        //Assegnazione ridefinita
        Smartp& operator= (const Smartp& smp){
            if(this != &smp){   //se non puntano alla stessa area di memoria ha senso fare assegnazi. prof.
                Nodo* aux=punt;
                punt=smp.punt;
                if(punt!=0) punt->riferimenti++;
                if(aux){
                    aux->riferimenti--;
                    if(aux->riferimenti==0) delete aux;
                }
            }
            return *this;
        }
        
        //RIDEF. OPERATORI

        bool operator==(const Smartp& smp) const { return punt==smp.punt; } //Uguaglianza

        bool operator!=(const Smartp& smp) const { return punt!=smp.punt; } //Disuguaglianza

        Nodo& operator*() const {return *punt;} //Dereferenziazione

        Nodo* operator->() const {return punt;} //Accesso a membro

    };  //fine classe Smartp

    class Nodo{
    public:
        Nodo(T t, const Smartp& smp=0) : info(t), next(smp), riferimenti(0) {}
        T info;
        Smartp next;
        int riferimenti;
    };  //fine classe Nodo

    Smartp first;   //unico campo dati privato del contenitore

public:
    class Iterator{
        friend class Container;
    private:
        Container::Smartp punt;
    public:
        //ITERATOR FORNISCE:
        
        //Prefisso
        Iterator& operator++(){
            if(punt!=0) punt=punt->next;
            return *this;
        }
        
        //Postfisso
        Iterator operator++(int){
            Iterator aux=*this;
            if(punt!=0) punt=punt->next;
            return aux;
        }
        
        //Dereferenziazione
        T* operator*() const{ return punt->info; }
        
        //Uguaglianza e disuguaglianza
        bool operator==(const Iterator& cit) const{ return punt==cit.punt; }
        bool operator!=(const Iterator& cit) const{ return punt!=cit.punt; }
    };  //fine classe Iterator
    
    //CONTAINER:
    
    //Costruttore
    Container() :  items(0) first(0) {}

    //Costruttore di copia
    Container(const Container& c) :  items(c. items), first(c.first) {}

    //Assegnazione
    Container& operator=(const Container& c){
        if(this != &c){
            first=c.first;
        }
        return *this;
    }
    
    //Metodi
    unsigned int size() const {return items;}
    
    bool isEmpty() const { return first==0; }

    void push_front(T& t){
        first=new Nodo(t,first);
         items++;
    }

    void push_back(T& t){
        if(first==0) first=new Nodo(t,0);   //non c'era alcun elemento nel contenitore
        else{
            Smartp aux=first;
            while(aux->next != 0) aux=aux->next; //scorro fino all'ultimo
            aux->next=new Nodo(t,0); //collego un nodo dopo l'ultimo
        }
         items++;
    }

    void pop_front(){
        if(first!=0){
            first=first->next;
             items--;
        }
    }

    void pop_element(T element){
            Smartp p=first, 
            Smartp prec, q;
            Smartp aux=first;
            first=0;
            while(p!=0 && !(p->info==element))
            {
                q=new Nodo(p->info,p->next);
                if(prec==0) first=q;
                else prec->next=q;
                prec=q;
                p=p->next;
            }
            if(p!=0 && p->info==element) items--;
            if(p==0) first=aux;
            else if(prec==0) first=p->next;
                 else prec->next=p->next;
        }


    void pop_back(){
        if(first!=0){
            if(first->next!=0){
                Smartp prec=first;
                Smartp aux=first->next;
                while(aux->next != 0) {prec=prec->next; aux=aux->next;}
                prec->next=0;
            }
            else 
                first=0;
            items--;
        }
    }
    
    //Metodi che usano iteratore

    Iterator begin() const{
        Iterator inizio;
        inizio.punt=first;
        return inizio;
    }

    Iterator end() const{
        Iterator fine;
        fine.punt=0;
        return fine;
    }

    T& operator[](const Iterator& cit) const{
        return (cit.punt)->info;
    }
 
};  //FINE TEMPLATE DI CLASSE Container


#endif //CONTAINER_H

