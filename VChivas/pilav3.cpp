#include <iostream>
#include <stack>
#include <string>

std::string trigParse(std::string eq){
    std::string tipoTrigo = eq.substr(0,3);
    unsigned pOpen = eq.find("(")+1;
    unsigned pClose = eq.find(")")-1;
    std::string valTrigoS = eq.substr(pOpen, pClose);
    std::cout << valTrigoS << std::endl;
    return tipoTrigo;
}

int main()
{
    std::cout << trigParse("sen(90)")<< std::endl;
}