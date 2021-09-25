#include <iostream>
#include "DLista.hpp"

using namespace std;

int main(){


    DLista lLst = DLista();

    lLst.insertRight("Moscu"); lLst.show();
    lLst.insertRight("Tokyo"); lLst.show();
    lLst.insertRight("Denver"); lLst.show();
    lLst.insertRight("Berlin"); lLst.show();

    cout << endl << "----" << endl << endl;

    lLst.showD();
    
    cout << endl << "----" << endl << endl;
    lLst.clear();

    lLst.insertRight("Tokyo"); lLst.show();
    lLst.insertRight("Denver"); lLst.show();
    lLst.insertLeft("Lisboa"); lLst.show();
}