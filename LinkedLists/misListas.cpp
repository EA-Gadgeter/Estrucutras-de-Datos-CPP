#include <iostream>
#include "Lista.hpp"

using namespace std;

int main(){


    Lista lLst = Lista();

    lLst.insert("Moscu");
    lLst.show();
    lLst.insert("Cd.Mex"); lLst.show();
    lLst.insert("Cairo"); lLst.show();
    lLst.clear();
    lLst.show();
    lLst.insert("Moscu");
    lLst.show();
    lLst.insert("Cd.Mex"); lLst.show();
    lLst.insert("Cairo"); lLst.show();
    lLst.del("Moscu");
    lLst.show();
}