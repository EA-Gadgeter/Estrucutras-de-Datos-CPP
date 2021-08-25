#include <iostream>

using namespace std;

class LiFo{

	protected:

		int* aData;
		int aMax;
		int aCurr;

	public:
		
		LiFo(int pMax){

			aMax = pMax;
			aCurr = 0;
			aData = NULL;

			if(aMax > 0){

				aData = new int[aMax];
			}
		}// Constructor

		~LiFo(){

			if(aData){ // Pregunto si me dieron memoria

				delete aData;
			}

			cout << "Bye" << endl;
		}// Destructor

		void push(int pVal){

			if(aData){

				if(!isFull()){

					aData[aCurr++] = pVal;
				}
			}	
		}// push

		int pop(){

			int lVal = 0;

			if(aData){

				if(!isEmpty()){

					lVal = aData[--aCurr];
				}
			}

			return lVal;
		}// pop

		bool isFull(){

			return (aCurr == aMax);
		}

		bool isEmpty(){

			return (aCurr == 0);
		}

		void descr(){

			cout << aMax << "|";
			cout << (isEmpty() == true ? true : false) << "|";
			cout << (isFull() == true ? true : false) << "|";

			for(int i = 0; i < aCurr; i++){

				cout << aData[i] << "|";
			}

			cout << endl;
		}
};

int main(){

	LiFo lPila = LiFo(3);

	lPila.descr();
	lPila.push(-2);
	lPila.descr();
	lPila.push(20);
	lPila.descr();
	lPila.push(10);
	lPila.descr();
	lPila.push(10);
	lPila.descr();
	
	for(int i=0; i < 4;i++){

		cout << lPila.pop() << endl;
		lPila.descr();
	}
	
	
	
	return 0;
}