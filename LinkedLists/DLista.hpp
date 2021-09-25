#pragma once
#include <string>
#include <iostream>

using namespace std;

typedef class DNODE* PDNODE;

class DNODE{

    public:
        string sVal;
        PDNODE sNext;
        PDNODE sPrev;
};

class DLista{

    PDNODE aHead;
    PDNODE aTail;

    public:
        DLista(){
            aHead = NULL;// La DLista acaba de nacer, por lo que no apunta a ningun lado
            aTail = NULL;
        }

        ~DLista(){
            clear();
        }

        void clear(){
            
            while(aHead){

                PDNODE lTemp = aHead->sNext;
                delete aHead;
                aHead = lTemp;
            }
            aTail = NULL;

        } // Metodo para limpiar la memoria, tirar todos los elementos de la DLista

        void show(){
            
            PDNODE lTemp = aHead;

            cout << "-> ";
            while(lTemp){
                cout << lTemp->sVal << " -> ";
                lTemp = lTemp->sNext;
            }
            cout << " -> =" << endl; 
        } // descr

        void showD(){

            PDNODE lTemp = aTail;

            cout << "-> ";
            while(lTemp){
                cout << lTemp->sVal << " -> ";
                lTemp = lTemp->sPrev;
            }
            cout << " -> =" << endl;

        }

        void insertRight(string pVal){

            PDNODE lTemp = getNew(pVal);

            if(aHead == NULL){
                
                aHead = lTemp;
                aTail = lTemp;
            }
            else{

                aTail->sNext = lTemp;
                lTemp->sPrev = aTail;
                aTail = lTemp;
            }
        }

        void insertLeft(string pVal){
            
            PDNODE lTemp = getNew(pVal);

            if(aTail == NULL){
            
                aHead = lTemp;
                aTail = lTemp;
            }
            else{

                aHead->sPrev = lTemp;
                lTemp->sNext = aHead;
                aHead = lTemp;
            }
        }

        void del(string pVal){

            PDNODE lNode = search(pVal);

            if(lNode){
                if(lNode->sVal == pVal){
                    
                    if(lNode == aHead){
                        
                        if(lNode->sNext){

                            lNode->sNext->sPrev = NULL;
                        }
                        if (aHead == aTail){

                            aTail = NULL;
                        }

                        aHead = lNode->sPrev;
                        delete lNode; 
                    }
                    else{

                        if(lNode == aTail){

                            if(lNode->sPrev){

                                lNode->sPrev->sNext = NULL;
                            }
                            
                            aTail = lNode->sPrev;
                            delete lNode;
                        }
                        else{

                            PDNODE lS = lNode->sNext;
                            lNode->sPrev->sNext = lS; // lNode acaba de salir de la lista ascendente
                            lS->sPrev = lNode->sPrev; // Fuera de la lista descendente
                            delete lNode;
                        }
                    }
                    
                }
            }
        }//del

    protected:
        PDNODE search(string pVal){

            PDNODE lNode = aHead;

            while(lNode){
                if(lNode->sVal == pVal){
                    break;
                }
                lNode = lNode->sNext;
            }

            return lNode;
        } //Entrega el nodo del valor que se busca

        PDNODE getNew(string pVal){

            PDNODE lTemp = new DNODE;

            if(lTemp != NULL){

                lTemp->sVal = pVal;
                lTemp->sNext = NULL;
                lTemp->sPrev = NULL;
            }

            return lTemp;
        }
};