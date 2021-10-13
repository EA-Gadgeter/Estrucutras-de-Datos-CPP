#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>

#include "DLista.hpp"


using namespace std;

// Definimos la función porque en listas de listas es neceario
void DLista:: write(ofstream& pLFile){ // Pasamos por referencia el ofstream

    PDNODE lTemp = aHead; 

    while(lTemp != NULL){

        pLFile << "\t" << lTemp->sVal << endl;
        lTemp = lTemp->sNext;
        
    }
    // Basicamente la funcion simplmente escribe todo lo que hay en la lista vertical con un tab antes
}

typedef class LNODE* PLNODE;

class LNODE: public DNODE{

    public:
        //string sVal;
        PLNODE sNext;
        PLNODE sPrev;
        //int sFrec; // Frecuencia de un nodo en caso de repetidos
        DLista* sLst;
};

class LLista{

    PLNODE aHead;
    PLNODE aTail;
    bool aChkFrec; // Booleano que permite dublicado en la lista, o contar la frecuencia

    public:
        LLista(bool pChkFrec = false){ 
            aHead = NULL;// La DLista acaba de nacer, por lo que no apunta a ningun lado
            aTail = NULL; // Lo mismo que arriba
            aChkFrec = pChkFrec;
        }

        ~LLista(){
            clear();
        }

        void clear(){
            
            while(aHead){

                PLNODE lTemp = aHead->sNext;

                if(aHead->sLst) delete aHead->sLst; // Borramos la vertical
                    
                delete aHead; // Ahora si podemos borrar el horizontal
                aHead = lTemp;
            }
            aTail = NULL;

        } // Metodo para limpiar la memoria, tirar todos los elementos de la DLista

        void show(){
            
            PLNODE lTemp = aHead;

            cout << "-> ";
            while(lTemp){
                cout << lTemp->sVal << (aChkFrec ? "(" + to_string(lTemp->sFrec) + ")": "");
                if(lTemp->sLst){
                    cout << " [";
                    lTemp->sLst->show();
                    cout << " ] " << endl;
                }
                cout << " -> ";
                lTemp = lTemp->sNext;
            }
            cout << "= " << endl;
            
        } // descr

        void showD(){

            PLNODE lTemp = aTail;

            cout << "-> ";
            while(lTemp){
                cout << lTemp->sVal << (aChkFrec ? "(" + to_string(lTemp->sFrec) + ")": "");
                if(lTemp->sLst){ // Solo si el nodo tiene una lista, lo imprimimos
                    cout << " [";
                    lTemp->sLst->show();
                    cout << " ] ";
                }
                cout << " -> ";
                lTemp = lTemp->sPrev;
            }
            cout << "= " << endl;

        }

        void insertRight(string pVal){

            PLNODE lTemp = pinsertRight(pVal); // la direccion se guarda pero luego se borra
        }

        void insertLeft(string pVal){
            
            PLNODE lTemp = pinsertLeft(pVal);
        }

        void insert(string pVal){ // Inserta un nodo en orde, en el caso de string, por orden alfabetico

            PLNODE lTemp = pinsert(pVal);
        }

        void insert(string pValH, string pValV){

            if(aHead == NULL){ // if si la lista esta vacia
            
                aHead = getNew(pValH);
                aTail = aHead;
                
                // Puede el usuario halla pasado un nulo de string "", un cuyo caso, no instanciamos
                // el objeto
                if(pValV != ""){ 
                
                    aHead->sLst = new DLista(); // Mandamos a llamar el constructor para crear una lista
                    // recordemos sLst solo es un apuntador, no el objeto en si 

                    // Como sLst es una lista doblemente ligada, podemos simplemente usar el insert
                    if(aHead->sLst) aHead->sLst->insert(pValV);
                }
            }
            else{

                PLNODE lN = search(pValH); // Buscamos el valor horizontal
                
                if(lN == NULL){ // Si no lo encuentra..
                
                    lN = pinsert(pValH);

                    if(lN){
                        if(pValV != ""){ 
                    
                            lN->sLst = new DLista(); // Mandamos a llamar el constructor para crear una lista
                            // recordemos sLst solo es un apuntador, no el objeto en si 

                            // Como sLst es una lista doblemente ligada, podemos simplemente usar el insert
                            if(lN->sLst) lN->sLst->insert(pValV);
                        }
                    }
                }
                else{

                    if(pValV != ""){ 
                    
                        if(lN->sLst == NULL) lN->sLst = new DLista(); // Puede que el objeto no exista
                        if(lN->sLst) lN->sLst->insert(pValV); // Si hay memoria, simplemente usamos el insert
                    }
                } 
            }
        }

        void del(string pVal, bool pForce = false){

            PLNODE lNode = search(pVal);

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
                            if(lNode->sLst) delete lNode->sLst; // Solo si existe una lista vertical, la destruimos
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

                                PLNODE lS = lNode->sNext;
                                lNode->sPrev->sNext = lS; // lNode acaba de salir de la lista ascendente
                                lS->sPrev = lNode->sPrev; // Fuera de la lista descendente
                                delete lNode;
                            }
                        }
                    }  
                }
            }
        }//del

        void delV(string pValH, string pValV, bool pForce = false){
            
            PLNODE lNode = search(pValH);

            if(lNode){ // Si existe el nodo
            
                // Puede el usuario halla pasado un nulo de string "", un cuyo caso, no instanciamos
                // el objeto
                if(pValV != ""){ 
                    
                    if(lNode->sLst){ // Si el nodo tiene una lista vertical

                        lNode->sLst->del(pValV); // Simplmente borramos el nodo de la lista vertical
                    }
                }
            }
        }//del
        
        void read(string pPath){ //o


            string lLine, lastLine;
            ifstream lFile(pPath);
            bool isBegin = true;

            if(lFile.is_open()){

                while(getline(lFile, lLine)){

                    if (lLine[0] == '\t' && isBegin){ // Evitar que el principio empieze con un tab
                        continue; // Si es un tab y todavía es el principio, nos saltamos todo el ciclo
                    }
                    else if(lLine[0] != '\t' && isBegin){ // Si es el principio pero ya no es un tab..

                        insert(lLine); // Insertamos nuestra primera linea
                        lastLine = lLine; // Necesitamos guardar registro de la ultima linea, en caso que la siguiente sea vertical
                        isBegin = false; // isBegin es falso, ya no estamos al principio
                        continue; // Nos podemos saltar todo el ciclo
                    }

                    if(lLine[0] == '\t'){ // Si la linea empieza por un tab..
                    
                        insert(lastLine, lLine.substr(1, lLine.length())); // Esta linea va a pertenecer a la lista vertical de la anterior
                        // Hacemos un subtr, para quitar el tab del principio
                    }
                    else{ // Si no, insertamos la linea que no existe, y lastLine ahora va a ser esta linea
                        insert(lLine);
                        lastLine = lLine;
                    }
                    

                }
                lFile.close();
                
            }else cout << "Error de lectura del archivo" << endl;

        } // read 
        
        void write(string pPath) { // a

            ofstream lFile(pPath);
            PLNODE lTemp = aHead;    

            if(lFile.is_open()){

                while(lTemp != NULL){

                    lFile << lTemp->sVal << endl;

                    if(lTemp->sLst){

                        lTemp->sLst->write(lFile);
                    }

                    lTemp = lTemp->sNext;
                }

                lFile.close();

            }else cout << "Error de escritura de archivo";
        } // write 


    protected:
        PLNODE find(string pVal){ // Entrega donde DEBERÍA ir el nodo nuevo en orden

            PLNODE lN = aHead;

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


        PLNODE search(string pVal){

            PLNODE lNode = aHead;

            while(lNode){
                if(lNode->sVal == pVal){
                    break;
                }
                lNode = lNode->sNext;
            }

            return lNode;
        } //Entrega el nodo del valor que se busca

        PLNODE getNew(string pVal){ // Creador de nodos

            PLNODE lTemp = new LNODE;

            if(lTemp != NULL){

                lTemp->sVal = pVal;
                lTemp->sNext = NULL;
                lTemp->sPrev = NULL;
                lTemp->sFrec = 1;
                lTemp->sLst = NULL;
            }

            return lTemp;
        }

        PLNODE pinsertRight(string pVal){


            if(aHead == NULL){ // Por si la lista esta vacia
                
                aHead = getNew(pVal);
                aTail = aHead;
                return aHead;
            }
            else{
                if(aChkFrec){ // A lor largo del programa es una validación, que activa
                            // la frecuencia de los valores de la lista
                    PLNODE lN = search(pVal);

                    if(lN){
                        
                        if(lN->sVal == pVal){
                            lN->sFrec++; 
                        }
                        return lN;
                    }
                    else{
                        PLNODE lTemp = getNew(pVal);  
                        aTail->sNext = lTemp;
                        lTemp->sPrev = aTail;
                        aTail = lTemp;
                        return lTemp;
                    }

                }
                else{

                    PLNODE lTemp = getNew(pVal);    
                    aTail->sNext = lTemp;
                    lTemp->sPrev = aTail;
                    aTail = lTemp;
                    return lTemp;
                }
            }
            
        }

        PLNODE pinsertLeft(string pVal){
            

            if(aHead == NULL){ // Por si la lista esta vacia
            
                aHead = getNew(pVal);
                aTail = aHead;
                return aHead;
            }
            else{

                if(aChkFrec){

                    PLNODE lN = search(pVal);

                    if(lN){
                        
                        if(lN->sVal == pVal){
                            lN->sFrec++;
                        }
                        return lN;
                    }
                    else{
                        PLNODE lTemp = getNew(pVal);
                        aHead->sPrev = lTemp;
                        lTemp->sNext = aHead;
                        aHead = lTemp;
                        return lTemp;
                    }

                }
                else{
                    PLNODE lTemp = getNew(pVal);
                    aHead->sPrev = lTemp;
                    lTemp->sNext = aHead;
                    aHead = lTemp;
                    return lTemp;
                }
            }
        }

        PLNODE pinsert(string pVal){ // Inserta un nodo en orde, en el caso de string, por orden alfabetico

            if(aHead == NULL){ // if si la lista esta vacia
            
                aHead = getNew(pVal);
                aTail = aHead; 
                return aHead;
            }
            else{

                PLNODE lN = find(pVal); // Buscamos donde debería ir el valor

                if(lN == NULL){

                    return pinsertLeft(pVal);
                }
                else{

                    if((lN == aTail) && (pVal > aTail->sVal)){

                        return pinsertRight(pVal);
                    }
                    else{

                        PLNODE lF = lN->sPrev;

                        if((aChkFrec) && ((lF->sVal == pVal) || (lN->sVal == pVal))){ // Verificamos si hay repetecion de valores

                            if(lF->sVal == pVal){
                                lF->sFrec++;
                                return lF;
                            }    
                            else{
                                lN->sFrec++;
                                return lN;
                            }
                                

                            
                        }
                        else{
                            PLNODE lTemp = getNew(pVal);

                            // Entre father y lN va el temp
                            lF->sNext = lTemp;
                            lTemp->sNext = lN;
                            lN->sPrev = lTemp;
                            lTemp->sPrev = lF;
                            return lTemp;
                        }
                    }
                }
            }
        }


};