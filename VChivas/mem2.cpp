#include <iostream>

using namespace std;

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

    private:
        void resize(void);
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
    // cout << "Bye!" << endl;
} // Destructor

template <class T>
void LiFo<T>::push(T pVal)
{
    if (aData) {
        if (!isFull()) {
            aData[aCurr++] = pVal;
        }
        else {
            resize();
            push(pVal);
        }
    }
} // push

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
    cout << aMax << "(" << aStep << ")|";
    cout << (isEmpty() == true ? "1" : "0") << "|";
    cout << (isFull() == true ? "1" : "0") << "||";
    for (int lIdx = 0; lIdx < aCurr; lIdx++) {
        cout << aData[lIdx] << "|";
    }
    cout << endl;
} // descr

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

    lPila.descr();
    lPila.push(2.1);
    lPila.push(-2.2);
    lPila.push(4.3);
    lPila.descr();
    lPila.push(10.4);
    lPila.descr();
    lPila.push(10);
    lPila.descr();

    cout << "----" << endl;

    cout << lPila.get(-1) << endl;
    cout << lPila.get(1) << endl;
    cout << lPila[2] << endl;

    int lIdx = lPila.search(10.4);
    if (lIdx > -1) {
        cout << lIdx << ", " << lPila[lIdx] << endl;
    }

    cout << "----" << endl;

    cout << lPila.pop() << endl;
    cout << lPila.pop() << endl;
    cout << lPila.pop() << endl;
    lPila.descr();
    cout << lPila.pop() << endl;
    lPila.descr();
    cout << lPila.pop() << endl;
    lPila.descr();
}