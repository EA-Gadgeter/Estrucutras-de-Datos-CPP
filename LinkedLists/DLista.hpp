#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

typedef class DNODE* PDNODE;

class DNODE{

    public:
        string sVal;
        PDNODE sNext;
        PDNODE sPrev;
        int sFrec; // Frecuencia de un nodo en caso de repetidos
};

class DLista{

    PDNODE aHead;
    PDNODE aTail;
    bool aChkFrec; // Booleano que permite dublicado en la lista, o contar la frecuencia

    public:
        DLista(bool pChkFrec = false){ 
            aHead = NULL;// La DLista acaba de nacer, por lo que no apunta a ningun lado
            aTail = NULL; // Lo mismo que arriba
            aChkFrec = pChkFrec;
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
                cout << lTemp->sVal << (aChkFrec ? "(" + to_string(lTemp->sFrec) + ")": "") << " ->";
                lTemp = lTemp->sNext;
            }
            cout << " -> =" << endl; 
        } // descr

        void showD(){

            PDNODE lTemp = aTail;

            cout << "-> ";
            while(lTemp){
                cout << lTemp->sVal << (aChkFrec ? "(" + to_string(lTemp->sFrec) + ")": "") << " ->";
                lTemp = lTemp->sPrev;
            }
            cout << " -> =" << endl;

        }

        void insertRight(string pVal){

            PDNODE lTemp = getNew(pVal);

            if(aHead == NULL){ // Por si la lista esta vacia
                
                aHead = lTemp;
                aTail = lTemp;
            }
            else{
                if(aChkFrec){ // A lor largo del programa es una validación, que activa
                            // la frecuencia de los valores de la lista
                    PDNODE lN = search(pVal);

                    if(lN){
                        
                        if(lN->sVal == pVal){
                            lN->sFrec++;
                        }
                    }
                    else{

                        aTail->sNext = lTemp;
                        lTemp->sPrev = aTail;
                        aTail = lTemp;
                    }

                }
                else{

                    aTail->sNext = lTemp;
                    lTemp->sPrev = aTail;
                    aTail = lTemp;
                }
            }
        }

        void insertLeft(string pVal){
            
            PDNODE lTemp = getNew(pVal);

            if(aTail == NULL){ // Por si la lista esta vacia
            
                aHead = lTemp;
                aTail = lTemp;
            }
            else{

                if(aChkFrec){

                    PDNODE lN = search(pVal);

                    if(lN){
                        
                        if(lN->sVal == pVal){
                            lN->sFrec++;
                        }
                    }
                    else{

                        aHead->sPrev = lTemp;
                        lTemp->sNext = aHead;
                        aHead = lTemp;
                    }

                }
                else{

                    aHead->sPrev = lTemp;
                    lTemp->sNext = aHead;
                    aHead = lTemp;
                }
            }
        }

        void insert(string pVal){ // Inserta un nodo en orde, en el caso de string, por orden alfabetico

            if(aHead == NULL){ // if si la lista esta vacia
            
                aHead = getNew(pVal);
                aTail = aHead; 
            }
            else{

                PDNODE lN = find(pVal); // Buscamos donde debería ir el valor

                if(lN == NULL){

                    insertLeft(pVal);
                }
                else{

                    if((lN == aTail) && (pVal > aTail->sVal)){

                        insertRight(pVal);
                    }
                    else{

                        PDNODE lF = lN->sPrev;

                        if((aChkFrec) && ((lF->sVal == pVal) || (lN->sVal == pVal))){ // Verificamos si hay repetecion de valores

                            if(lF->sVal == pVal)
                                lF->sFrec++;
                            else
                                lN->sFrec++;

                            
                        }
                        else{
                            PDNODE lTemp = getNew(pVal);

                            // Entre father y lN va el temp
                            lF->sNext = lTemp;
                            lTemp->sNext = lN;
                            lN->sPrev = lTemp;
                            lTemp->sPrev = lF;
                        }

                        
                    }
                }
            }
        }

        void del(string pVal, bool pForce = false){

            PDNODE lNode = search(pVal);

            if(lNode){
                if(lNode->sVal == pVal){

                    if(pForce)lNode->sFrec = 1; // Si esta activada la frecuencia, en lugar de sacar, solo le restamos uno
                    
                    if(aChkFrec && (lNode->sFrec > 1)){

                        lNode->sFrec--;
                    }
                    else{
                        /* Se validan 3 casos, que se quiera eliminar el head
                            , el tail, y hasta el final, un nodo de en medio
                        */
                        if(lNode == aHead){
                        
                            if(lNode->sNext){

                                lNode->sNext->sPrev = NULL;
                            }
                            if (aHead == aTail){

                                aTail = NULL;
                            }

                            aHead = lNode->sNext;
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
            }
        }//del

        void read(string pPath, char pMethod){ // r, l, o

            auto lStart = chrono::high_resolution_clock::now();
            string lLine;
            ifstream lFile(pPath);

            while(getline(lFile, lLine)){

                switch(pMethod){
                    case 'r': insertRight(lLine); break;
                    case 'l': insertLeft(lLine); break;
                    case 'o': insert(lLine); break;
                }
            }
            lFile.close();

            auto lElapsed = chrono::high_resolution_clock::now() - lStart;
            long long lMicroseconds = chrono::duration_cast<std::chrono::microseconds>(lElapsed).count();
            cout << lMicroseconds << "ms" << endl;
        } // read 

        void write(string pPath, char pMethod) { // a, d

            auto lStart = chrono::high_resolution_clock::now();
            ofstream lFile(pPath);
            PDNODE lTemp = NULL;    

            if(pMethod == 'a')
                lTemp = aHead;
            else
                lTemp = aTail;    

            if(lFile.is_open()){

                while(lTemp != NULL){

                    if(aChkFrec){
                        
                        for(int i = 0; i < lTemp->sFrec; i++){
                            lFile << lTemp->sVal << endl;
                        }
                    }
                    else{
                        lFile << lTemp->sVal << endl;
                    }

                    if(pMethod == 'a')
                        lTemp = lTemp->sNext;
                    else if(pMethod == 'd')
                        lTemp = lTemp->sPrev;    
                }

                lFile.close();
                auto lElapsed = chrono::high_resolution_clock::now() - lStart;
                long long lMicroseconds = chrono::duration_cast<std::chrono::microseconds>(lElapsed).count();
                cout << lMicroseconds << "ms" << endl;

            }else cout << "Error de escritura de archivo";
        } // write

        void write(ofstream& pLFile); // Funcion necesaria para que write de listas de listas funcione, por ahora solo esta declarada

    protected:
        PDNODE find(string pVal){ // Entrega donde DEBERÍA ir el nodo nuevo en orden

            PDNODE lN = aHead;

            if(lN){

                if(pVal < aHead->sVal){

                    lN = NULL;
                }
                else{

                    if(pVal >= aTail->sVal){

                        lN = aTail;
                    }
                    else{

                        while(lN){

                            if(pVal < lN->sVal)
                                break;
                            
                            lN = lN->sNext;
                        }
                    }
                }
            }

            return lN;
        } //find


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

        PDNODE getNew(string pVal){ // Creador de nodos

            PDNODE lTemp = new DNODE;

            if(lTemp != NULL){

                lTemp->sVal = pVal;
                lTemp->sNext = NULL;
                lTemp->sPrev = NULL;
                lTemp->sFrec = 1;
            }

            return lTemp;
        }
};