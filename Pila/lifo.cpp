#include <iostream>

using namespace std;

template <class T>
class LiFo{

	protected:

		T* aData;
		int aMax;
		int aStep;
		int aCurr;

	public:
		
		LiFo(int pMax){

			aMax = pMax;
			aStep = pMax;
			aCurr = 0;
			aData = NULL;

			if(aMax > 0){

				aData = new T[aMax];
			}
		}// Constructor

		LiFo(int pMax, int pStep){

			aMax = pMax;
			aStep = pStep;
			aCurr = 0;
			aData = NULL;

			if(aMax > 0){

				aData = new T[aMax];
			}
		}

		~LiFo(){

			if(aData){ // Pregunto si me dieron memoria

				delete aData;
			}

			cout << "Bye" << endl;
		}// Destructor

		void push(T pVal){

			if(aData){

				if(!isFull()){

					aData[aCurr++] = pVal;
				}
				else {

					resize();
					push(pVal);
				}
			}	
		}// push

		T pop(){

			T lVal;

			if(aData){

				if(!isEmpty()){

					lVal = aData[--aCurr];
					return lVal;
				}
			}

			//return lVal;
		}// pop

		bool isFull(){

			return (aCurr == aMax);
		}

		bool isEmpty(){

			return (aCurr == 0);
		}

		void descr(){

			cout << aMax << "(" << aStep << ")" << "|";
			cout << (isEmpty() == true ? true : false) << "|";
			cout << (isFull() == true ? true : false) << "|";

			for(int i = 0; i < aCurr; i++){

				cout << aData[i] << "|";
			}

			cout << endl;git
		}

		T get(int indice){

			T lVal;

			if(aData){

				if(!isEmpty()){

					if ((indice >= 0) && (indice < aCurr)){

						lVal = aData[indice];
						return lVal;
					}
					
				}
			}

			//return lVal;
		}

		T operator[](int indice){
			
			return get(indice);
		}// Esta funcion sirve para poder usar nuestra pila como un arreglo normal,
		// haciendo mas entendible la sintaxis.

		int search(T valor){

			int indice = -1;

			if(aData){

				if(!isEmpty()){

					for(int i = 0; i < aCurr; i++){

						if(aData[i] == valor){

							indice = i;
							break;
						} 
					}
					
				}
			}

			return indice;
		}// busca la primera ocurrencia de un valor dado, regresa el indice

	private:
		
		void resize(){

			if(aData){

				T* lData = new T[aMax + aStep];

				if(lData){

					// Ahora mismo aData y aCurr valen lo mismo, ya que resize()
					// solo se manda a llamar cuando la pila llego al tope 
					for(int i = 0; i < aCurr; i++){
						
						lData[i] = aData[i];
					}

					aMax += aStep;
					delete aData;
					// Cambiamos la direcci??n de memoria, para que aData ahora
					// tenga la direcci??n de memoria de lData, que es el nuevo vector m??s
					// grande
					aData = lData;
				}
			}

		}//resize

};

int main(){

	LiFo<float> lPila = LiFo<float>(3, 1);

	lPila.descr();
	lPila.push(-2.5);
	lPila.descr();
	lPila.push(20.5);
	lPila.descr();
	lPila.push(10.5);
	lPila.descr();
	lPila.push(10);
	lPila.descr();
	
	cout << "-----" << endl;

	cout << lPila.get(1) << endl;
	cout << lPila.get(-1) << endl;
	cout << lPila[2] << endl;
	int lIndx = lPila.search(10);
	if(lIndx != -1){

		cout << lIndx << ", " << lPila[lIndx] << endl;
	}

	cout << "-----" << endl;
	
	for(int i=0; i < 4;i++){

		cout << lPila.pop() << endl;
		lPila.descr();
	}
	
	// 
	return 0;
}