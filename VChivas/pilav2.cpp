#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <math.h>
#define PI 3.14159265358979323846

double trigParse(std::string eq){
    double res;
    std::string tipoTrigo = eq.substr(0,3);
    unsigned pOpen = eq.find("(")+1;
    unsigned pClose = eq.find(")")-4;
    std::string valTrigoS = eq.substr(pOpen, pClose);
    double valTrigo = std::stod(valTrigoS);
    std::cout << valTrigo << ";" << tipoTrigo << std::endl;

    if (tipoTrigo == "cos")
    {
        double res = cos(valTrigo * PI /180);
        return res;
    }
    else if (tipoTrigo == "sen")
    {
        double res = sin(valTrigo * PI /180);
        return res;
    }
    else if (tipoTrigo == "tan")
    {
        double res = tan(valTrigo * PI /180);
        return res;
    }
    
}

int main()
{
    std::stack<double> lStack;
    double lV01, lV02, lV03;
    std::istringstream lExp("-10;0;+;sen(90);*;3;+");
    std::string lStr = "";

    while(getline(lExp, lStr, ';'))
    {
        std::cout << lStr << std::endl;
        if (isdigit(lStr[0]))
        {
            lStack.push(stod(lStr));
        }
        else if ((lStr.length() > 1) && (lStr[0] == '-'))
        {
            lStack.push(stod(lStr));
        }
        else 
        {
            lV02 = lStack.top(); lStack.pop();
            lV01 = lStack.top(); lStack.pop();
            if (lStr[0] == '+')
            {
                lV03 = lV01 + lV02;
            }
            else if (lStr[0] == '-')
            {
                lV03 = lV01 - lV02;
            }
            else if (lStr[0] == '*')
            {
                lV03 = lV01 * lV02;
            }
            else if (lStr[0] == '/')
            {
                lV03 = lV01 / lV02;
            }
            lStack.push(lV03);
        }
    }

    lV03 = lStack.top();
    std::cout << "Resultado = " << lV03 << std::endl;
}