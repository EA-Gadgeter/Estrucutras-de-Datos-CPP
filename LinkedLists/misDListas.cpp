#include <iostream>
#include "DLista.hpp"

using namespace std;

int main(){


    DLista lLst = DLista(true);

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

    cout << endl << "----" << endl << endl;

    lLst.clear();
    lLst.insert("Tokyo"); lLst.show();
    lLst.insert("Berlin"); lLst.show();
    lLst.insert("Denver"); lLst.show();
    lLst.insert("Oslo"); lLst.show();
    lLst.insert("Lisboa"); lLst.show();
    lLst.insert("Berlin"); lLst.show();
    lLst.insert("Lisboa"); lLst.show();
    lLst.insert("Tokyo"); lLst.show();

    cout << endl << "----" << endl << endl;

    lLst.del("Tokyo"); lLst.show();
    lLst.del("Tokyo"); lLst.show();
    lLst.del("Tokyo"); lLst.show();

    lLst.del("Lisboa", true); lLst.show();

    lLst.clear();

    cout << endl << "----" << endl << endl;

    lLst.insertLeft("Tokyo"); lLst.show();
    lLst.insertLeft("Tokyo"); lLst.show();
    lLst.insertRight("Lisboa"); lLst.show();
    lLst.insertRight("Lisboa"); lLst.show();

    cout << endl << "----" << endl << endl;

    lLst.clear();

    // gutemberg.org
    //lLst.read("dsadsa", 'r');

    
}