#include <iostream>

void dameMemoria(int ***pMat, int pS)
{
    int lNum = 0;
    *pMat = (int **)malloc(pS *sizeof(int *));
    if(*pMat){
        for(int lRow = 0; lRow < pS; lRow++)
        {
            (*pMat)[lRow] = (int*)malloc((pS-lRow) * sizeof(int));
            if((*pMat)[lRow])
            {
                for(int lCol = 0; lCol < (pS-lRow); lCol++)
                {
                    (*pMat)[lRow][lCol] = ++lNum;
                }
            }
            
        }
    }

}

int main()
{
    int **lMat = NULL;
    int ls = 3;
    dameMemoria(&lMat, ls);

    if(lMat){
        for(int lRow = 0; lRow < ls; lRow++)
        {
                for(int lCol = 0; lCol < (ls-lRow); lCol++)
                {
                    std::cout << (lMat)[lRow][lCol] << '\t';
                }
                std::cout << "\n";
        }
        // free
    }
}