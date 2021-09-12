/*
- Realice un clase pila (LiFo) con los métodos estándar push, pop, isEmpty y isFull, de enteros. Cada que se haga un push de en la pila, 
verificar si el número es primo, y si lo es añadir 1 a un atributo privado de la clase. Haga el método que pueda entregar el valor del número de primos
que han entrado en la pila.
*/

#include <iostream>

bool esPrimo(int num)
{
    bool res = true;
    if (num != 1 && num != 0 && num != 4){
    for (int i = 2; i <= num/2; i++) {
        if(num % i == 0)
        {
            res = false;
            break;
        }
    }
    return res;
    }
}

template <class T>
class LiFo {
    protected:
        T* aData;
        int aMax;
        int aStep;
        int aCurr;

    public:
        LiFo(int pMax);
        LiFo(int pMax, int pStep); 
        ~LiFo();

        void push(T pVal);
        T pop(void);
        bool isFull(void);
        bool isEmpty(void);

        T get(int pIdx);
        T operator[](int pIdx);
        int search(T pVal);

        void descr(void);
        void primos(void);

    private:
        void resize(void);
        int aContPrimos = 0;
};

template <class T>
LiFo<T>::LiFo(int pMax)
{
    aMax = pMax;
    aStep = pMax;
    aCurr = 0;
    aData = NULL;
    if (aMax > 0) {
        aData = new T [aMax];
    }
} // Constructor

template <class T>
LiFo<T>::LiFo(int pMax, int pStep)
{
    aMax = pMax;
    aStep = pStep;
    aCurr = 0;
    aData = NULL;
    if (aMax > 0) {
        aData = new T [aMax];
    }
} // Constructor 2

template <class T>
LiFo<T>::~LiFo()
{
    if (aData) {
        delete aData;
    }
} // Destructor

template <class T>
void LiFo<T>::push(T pVal)
{
    if (aData) {
        if (!isFull()) {
            aData[aCurr++] = pVal;
            if (esPrimo(pVal) == true)
            {
            aContPrimos++;
            }
        }
        else {
            resize();
            push(pVal);
        }
    }
}
 // push

template <class T>
T LiFo<T>::pop(void)
{
    T lVal;

    if (aData) {
        if (!isEmpty()) {
            lVal = aData[--aCurr];
            return lVal;
        }
    }

    // return lVal;
} // pop

template <class T>
bool LiFo<T>::isFull(void)
{
    return (aCurr == aMax);
} // isFull

template <class T>
bool LiFo<T>::isEmpty(void)
{
    return (aCurr == 0);
} // isEmpty

template <class T>
T LiFo<T>::get(int pIdx)
{
    T lVal;

    if (aData) {
        if (!isEmpty()) {
            // [0, aCurr)
            if ((0 <= pIdx) && (pIdx < aCurr)) {
                lVal = aData[pIdx];
                return lVal;
            }
        }
    }

    // return lVal;
} // get

template <class T>
T LiFo<T>::operator[](int pIdx)
{
    return get(pIdx);
} // operator []

template <class T>
int LiFo<T>::search(T pVal)
{
    int lFIdx = -1;

    if (aData) {
        if (!isEmpty()) {
            for (int lIdx = 0; lIdx < aCurr; lIdx++) {
                if (pVal == aData[lIdx]) {
                    lFIdx = lIdx;
                    break;
                }
            }
        }
    }

    return lFIdx;
} // search

template <class T>
void LiFo<T>::descr(void)
{
    std::cout << aMax << "(" << aStep << ")|";
    std::cout << (isEmpty() == true ? "1" : "0") << "|";
    std::cout << (isFull() == true ? "1" : "0") << "||";
    for (int lIdx = 0; lIdx < aCurr; lIdx++) {
        std::cout << aData[lIdx] << "|";
    }
    std::cout << std::endl;
} // descr

template <class T>
void LiFo<T>::primos(void)
{
    std::cout << "Cantidad de numeros primos en el arreglo: " << aContPrimos << std::endl;
}

template <class T>
void LiFo<T>::resize(void)
{
    if (aData) {
        double* lData = new T [aMax + aStep];
        if (lData) {
            for (int lIdx = 0; lIdx < aCurr; lIdx++) {
                lData[lIdx] = aData[lIdx];
            }
            aMax += aStep;
            delete aData;
            aData = lData;
        }
    }
} // resize

int main()
{
    // LiFo lPila = LiFo(4);
    LiFo<double> lPila = LiFo<double>(4, 2);

    std::cout << "----" << std::endl;

    lPila.push(2);
    lPila.push(3);
    lPila.push(5);
    lPila.push(7);
    lPila.push(11);
    lPila.push(13);
    lPila.primos();
}