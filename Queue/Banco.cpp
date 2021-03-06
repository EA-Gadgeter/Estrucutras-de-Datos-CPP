#include <iostream>

using namespace std;

template <class T>
class FiFo{

protected:

    T* aData;
    int aMax;
    int aStep;
    int aCurr;

public:

    FiFo(int pMax){

        aMax = pMax;
        aStep = pMax;
        aCurr = 0;
        aData = NULL;

        if(aMax > 0){

            aData = new T[aMax];
        }
    }// Constructor

    FiFo(int pMax, int pStep){

        aMax = pMax;
        aStep = pStep;
        aCurr = 0;
        aData = NULL;

        if(aMax > 0){

            aData = new T[aMax];
        }
    }

    ~FiFo(){

        if(aData){ // Pregunto si me dieron memoria

            delete aData;
        }

    }// Destructor

    void push(T pVal){

        if(aData){

            if(!isFull()){

                aData[aCurr++] = pVal;
            }/*
				else {

					resize();
					push(pVal);
				}*/
        }
    }// push

    T pop(){

        T lVal;

        if(aData){

            if(!isEmpty()){

                lVal = aData[0];

                /* La unica diferencia entre una pila y una cola
                    es el metodo pop, en lugar de salir de arriba los datos
                    salen de abajo, como entregamos algo de abajo, todo lo de abajo se
                    recorre, como cayera todo para abajo en uno
                */
                for(int i = 0; i < aCurr - 1; i++){
                    // Recorremos todos los datos
                    aData[i] = aData[i + 1];
                }
                // Recorremos el aCurr
                aCurr--;

                return lVal;
            }
        }

        //return lVal;
    }// pop

    bool isFull(){

        return (aCurr == aMax);
    }

    bool isEmpty(){

        return (aCurr == 0);
    }

    void descr(){

        cout << aMax << "(" << aStep << ")" << "|";
        cout << (isEmpty() == true ? true : false) << "|";
        cout << (isFull() == true ? true : false) << "|";

        for(int i = 0; i < aCurr; i++){

            cout << aData[i] << "|";
        }

        cout << endl;
    }

    T get(int indice){

        T lVal;

        if(aData){

            if(!isEmpty()){

                if ((indice >= 0) && (indice < aCurr)){

                    lVal = aData[indice];
                    return lVal;
                }

            }
        }

        //return lVal;
    }

    T operator[](int indice){

        return get(indice);
    }// Esta funcion sirve para poder usar nuestra pila como un arreglo normal,
    // haciendo mas entendible la sintaxis.

    int search(T valor){

        int indice = -1;

        if(aData){

            if(!isEmpty()){

                for(int i = 0; i < aCurr; i++){

                    if(aData[i] == valor){

                        indice = i;
                        break;
                    }
                }

            }
        }

        return indice;
    }// busca la primera ocurrencia de un valor dado, regresa el indice

private:

    void resize(){

        if(aData){

            T* lData = new T[aMax + aStep];

            if(lData){

                // Ahora mismo aData y aCurr valen lo mismo, ya que resize()
                // solo se manda a llamar cuando la pila llego al tope
                for(int i = 0; i < aCurr; i++){

                    lData[i] = aData[i];
                }

                aMax += aStep;
                delete aData;
                // Cambiamos la direcci??n de memoria, para que aData ahora
                // tenga la direcci??n de memoria de lData, que es el nuevo vector m??s
                // grande
                aData = lData;
            }
        }

    }//resize

};

int fnRnd(int pMin, int pMax){

    // Genera aleatorios, incluyendo los extremos
    return (rand() % (pMax - pMin + 1)) + pMin;
}

#define K_MAX_CAJAS 3
#define K_MAX_PERSONAS 100
#define K_MAX_FILA 10

int main(){

    int lCajas[K_MAX_CAJAS];
    int lCont = 0;
    int lMaxPers = K_MAX_PERSONAS;
    int lNumPers = 0;
    int lNOpers = 0;
    FiFo<int> lFiFo = FiFo<int>(K_MAX_FILA);
    FiFo<int> lFiFoOne = FiFo<int>(K_MAX_FILA);
    int lRebotes = 0;
    int lTermino = 0;
    bool lFin = false;
    int lVolado = 0;

    for (int i = 0; i < K_MAX_CAJAS; i++){

        lCajas[i] = 0;
    }

    do{

        lCont++;

        if(lNumPers < lMaxPers){

            lNumPers++;
            
            // Para probar que la fila especial funciona
            // Forzamos para que haya un 50% de probabilidad de salga un 1
            lNOpers = fnRnd(1, 10); //Tiramos un "dado" de 10 caras
            if(lNOpers % 2 == 0){ // Si sale un par, la operacion va de 2 a 5

                lNOpers = fnRnd(2, 5);
            }
            else lNOpers = 1; // Si es impar, lo cual tiene un 50% de probabilidad, la operacion es 1

            if(lNOpers == 1){
                
                if(lFiFoOne.isFull()){

                    if(lFiFo.isFull()){

                        lRebotes++;
                    }
                    else{

                        lVolado = fnRnd(1, 2);
                        if(lVolado == 1){

                            lFiFo.push(lNOpers);
                        }
                        else lRebotes++;

                    }
                }
                else{

                    lFiFoOne.push(lNOpers);
                }
            }
            else{

                if(!lFiFo.isFull()){

                    lFiFo.push(lNOpers);
                }
                else lRebotes++;
            }
            

        }

        cout << lCont << ": ";
        lFiFo.descr();
        cout << lCont << " Especial: ";
        lFiFoOne.descr();

        lTermino = 0;

        for (int i = 1; i < K_MAX_CAJAS; i++){

            cout << lCont << ": " << "Caja " << (i+1) << ": " << lCajas[i];

            if(lCajas[i] == 0){

                if(!lFiFo.isEmpty()){

                    lCajas[i] = lFiFo.pop();
                }
                else lTermino++;
            }
            else lCajas[i]--;

            cout << " -> " << lCajas[i] << endl;
        }

        cout << lCont << ": " << "Caja Especial" << ": " << lCajas[0];

        if(lCajas[0] == 0){

            if(!lFiFoOne.isEmpty()){

                lCajas[0] = lFiFoOne.pop();
            }
            else{

                if(!lFiFo.isEmpty()){

                    lCajas[0] = lFiFo.pop();
                }
                else lTermino++;
            }
        }else lCajas[0]--;

        cout << " -> " << lCajas[0] << endl;

        cout << lCont << ": ";
        lFiFo.descr();
        cout << lCont << " Especial: ";
        lFiFoOne.descr();


        // Como lFin es un bool, podemos hacer operaciones logicas
        // solo si se cumplen las 3, osea todas dan True, lFin pasara a tomar
        // ese valor
        lFin = (
                (lNumPers >= lMaxPers) &&
                (lFiFo.isEmpty()) &&
                (lFiFoOne.isEmpty()) &&
                (lTermino == K_MAX_CAJAS)
        );

    }while(!lFin);

    cout << "Cajas: " << K_MAX_CAJAS << endl;
    cout << "Fila: " << K_MAX_FILA << endl;
    cout << "Pers: " << K_MAX_PERSONAS << endl;
    cout << "Rebotes: " << lRebotes << endl; // Mientras m??s rebotes, peor banco
    cout << "Ciclos: " << lCont << endl;

    return 0;
}