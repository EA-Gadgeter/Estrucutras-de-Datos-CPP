#include <iostream>

class LiFo {
protected:
    float *aData;
    int aMax;
    int aCurr;

public:
    LiFo(int pMax);
    ~LiFo();

    void push(float pVal);
    float pop(void);
    bool isFull(void);
    bool isEmpty(void);

    void descr(void);


};
LiFo::LiFo(int pMax)
{
    aMax = pMax;
    aCurr = 0;
    aData = NULL;
    if (aMax > 0){
        aData = new float[aMax];
    }

} // Constructor

LiFo::~LiFo()
{
    if(aData)
    {
        delete aData;
    }
} // Destructor

void LiFo::push(float pVal)
{
    if(aData) {
        if(!isFull()){
            aData[aCurr] = pVal;
            aCurr++;
        }
    }
} // push

float LiFo::pop(void)
{
    float lVal = 0;
    if(aData) {
        if(!isEmpty()){
            lVal = aData[--aCurr];
        }
    }
    return lVal;
} // pop

bool LiFo::isFull(void)
{
    return (aCurr == aMax);
} // isFull

bool LiFo::isEmpty(void)
{
    return (aCurr == 0);
} // isEmpty

void LiFo::descr(void)
{

    std::cout << aMax << "|";
    std::cout << (isEmpty() == true ? "1" : "0") << "|";
    std::cout << (isFull() == true ? "1" : "0") << "||";
    for (int lIdx = 0; lIdx < aCurr; lIdx++)
    {
        std::cout << aData[lIdx] << "|";
    }
    std::cout << std::endl;

} // descr

int main()
{
    LiFo lPila = LiFo(4);
    lPila.descr();
    lPila.push(99.74);
    lPila.push(78.24);
    lPila.push(8.89);
    lPila.descr();
    lPila.push(1000.2);
    lPila.descr();
    lPila.push(9.67);
    lPila.descr();
    
    std::cout << "--------------------------------" << std::endl;
    
    std::cout << lPila.pop() << std::endl;
    std::cout << lPila.pop() << std::endl;
    std::cout << lPila.pop() << std::endl;
    lPila.descr();
    std::cout << lPila.pop() << std::endl;
    lPila.descr();
    std::cout << lPila.pop() << std::endl;
    lPila.descr();
}
