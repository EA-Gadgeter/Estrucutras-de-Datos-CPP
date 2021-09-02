#include <iostream>
#include <stack>
#include <string>
#include <sstream>

using namespace std;

int main(){
    /*
    stack<double> lStack;

    double lV01, lV02, lV03;

    char* lExp = "12+4*3+", *lp;

    lp = lExp;

    do{
        
        cout << lp[0] << endl;

        if(isdigit(lp[0])){

            lStack.push(lp[0] - 48);

        }else{

            lV02 = lStack.top(); lStack.pop();
            lV01 = lStack.top(); lStack.pop();
            
            switch(lp[0]){

                case '+': lV03 = lV01 + lV02; break;
                case '-': lV03 = lV01 - lV02; break;
                case '*': lV03 = lV01 * lV02; break;
                case '/': lV03 = lV01 / lV02; break;
            }

            lStack.push(lV03);
        }
        lp++;
    }
    while(*lp != '\0');

    cout << "Res: " << lStack.top() << endl;
    */

    /*
    stack<double> lStack;

    double lV01, lV02, lV03;

    string lExp("12+4*3+");
    string::iterator lItr;

    for(lItr = lExp.begin(); lItr < lExp.end(); lItr++){
        
        cout << *lItr << endl;

        if(isdigit(*lItr)){

            lStack.push(*lItr - 48);

        }else{

            lV02 = lStack.top(); lStack.pop();
            lV01 = lStack.top(); lStack.pop();
            
            switch(*lItr){

                case '+': lV03 = lV01 + lV02; break;
                case '-': lV03 = lV01 - lV02; break;
                case '*': lV03 = lV01 * lV02; break;
                case '/': lV03 = lV01 / lV02; break;
            }

            lStack.push(lV03);
        }
    }

    cout << "Res: " << lStack.top() << endl;
    */

    stack<double> lStack;

    double lV01, lV02, lV03;

    istringstream lExp("-10;2.5;+;4;*;3;+");
    string lStr = "";

    //           Fuente, Cachito, Separador(char)
    while(getline(lExp, lStr, ';')){

        cout << lStr << endl;

        if(isdigit(lStr[0])){

            lStack.push(stod(lStr));
        }
        else if((lStr.length() > 1) && (lStr[0] == '-')){

            lStack.push(stod(lStr));
        }
        else{

            lV02 = lStack.top(); lStack.pop();
            lV01 = lStack.top(); lStack.pop();
            
            switch(lStr[0]){

                case '+': lV03 = lV01 + lV02; break;
                case '-': lV03 = lV01 - lV02; break;
                case '*': lV03 = lV01 * lV02; break;
                case '/': lV03 = lV01 / lV02; break;
            }

            lStack.push(lV03);
        }
    }


    cout << "Res: " << lStack.top() << endl;
}