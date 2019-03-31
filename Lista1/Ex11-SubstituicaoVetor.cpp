#include <iostream>

using namespace std;

int main (){
	
	int n;

	for(int i=0; i<10; i++){
		cin>>n;
		if(n<=0) n=1;
		cout << "X[" << i <<"] = " << n <<endl;
	}

	return 0;
}