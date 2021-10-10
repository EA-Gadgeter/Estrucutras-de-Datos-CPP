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
    lLst.insert("Lisboa"); lLst.show();
    lLst.insert("Berlin"); lLst.show();
    lLst.insert("Helsinki"); lLst.show();
    lLst.insert("Chernobyl"); lLst.show();
    lLst.insert("Tetelcingo"); lLst.show();
    lLst.show();
    // Berlin(1) ->Chernobyl(1) ->Helsinki(1) ->Tokyo(2) ->Lisboa(3) ->Tetelcingo(1)

    cout << endl << "----" << endl << endl;

    lLst.write("miarchivo.txt", 'a');

    lLst.clear();

    
    // gutemberg.org
    lLst.read("C:\\Users\\Chino\\Downloads\\timemachine.txt", 'o');
    
    // Tiempo por insertRight: 55001ms
    // Tiempo por ordenacion: 76994ms
    
    
}