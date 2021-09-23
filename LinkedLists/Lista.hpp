#pragma once // Para que se lo cargue una vez el codigo de este , y no de error de definición

#include <iostream>
#include <string>

using namespace std;

typedef class NODE* PNODE; // Creamos una excepcion, basicamente creo mi propio tipo de dato
// que es un puntero PNODE

class NODE{

    public:
        string sVal;
        PNODE sNext;
};

class Lista{
    PNODE aHead;
    PNODE aTail;

    public:
        Lista(){
            aHead = NULL;// La lista acaba de nacer, por lo que no apunta a ningun lado
            aTail = NULL;
        }

        ~Lista(){
            clear();
        }

        void clear(){
            
            while(aHead){

                PNODE lTemp = aHead->sNext;
                delete aHead;
                aHead = lTemp;
            }
            aTail = NULL;

        } // Metodo para limpiar la memoria, tirar todos los elementos de la lista

        void show(){
            
            PNODE lTemp = aHead;

            cout << "->";
            while(lTemp){
                cout << lTemp->sVal;
                if(lTemp != aTail) cout << "->";
                lTemp = lTemp->sNext;
            }
            cout << " -> =" << endl; 
        } // descr

        void insert(string pVal){

            PNODE lTemp = getNew(pVal);

            if(aHead == NULL){
                
                aHead = lTemp;
                aTail = lTemp;
            }
            else{

                aTail->sNext = lTemp;
                aTail = lTemp;
            }
        }

        void del(string pVal){

            PNODE lF = search(pVal);
            PNODE lS = NULL;

            if(lF){
                if(lF->sNext != NULL){

                    if(lF->sNext->sVal == pVal){ // Verificacion
                    
                        lS = lF->sNext;
                        lF->sNext = lS->sNext; // Sacarlo de la lista, es lS->next, porque lS
                        // se va a borrar

                        if(lS == aTail){
                            aTail = lF;
                        }
                        delete lS;
                    }
                }
            }else{

                if(aHead){

                    if(aHead->sVal == pVal){

                        lS = aHead->sNext;

                        if(aHead == aTail){
                            aTail = NULL;
                        }
                        delete aHead;
                        aHead = NULL;
                    }
                }
            }

            
        }//del

    protected:
        PNODE search(string pVal){

            PNODE lF = NULL;
            PNODE lS = aHead;

            while(lS){
                if(lS->sVal == pVal){
                    break;
                }

                lF = lS;
                lS = lS->sNext;
            }

            return lF;
        } //Entrega el nodo anterior al que se busca

        PNODE getNew(string pVal){

            PNODE lTemp = new NODE;

            if(lTemp != NULL){

                lTemp->sVal = pVal;
                lTemp->sNext = NULL;
            }

            return lTemp;
        }
};