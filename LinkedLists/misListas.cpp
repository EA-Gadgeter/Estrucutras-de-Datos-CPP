#include <iostream>
#include "Lista.hpp"

using namespace std;

int main(){


    Lista lLst = Lista();

    lLst.insertLeft("Moscu");
    lLst.insertLeft("Rusia");
    lLst.insert("Tlacotepec");
    lLst.show();
    lLst.del("Moscu");
    lLst.show();
    
}