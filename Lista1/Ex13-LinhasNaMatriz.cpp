#include <iostream>
#include <iomanip>

using namespace std;

int main (){

	int n;
	char op;

	float aux, res=0;

	cin >>n >>op;

	for(int i=0; i<12; i++){
		for(int j=0; j<12; j++){
			cin >> aux;
			if(i==n){
				res+=aux;			
			}			
		
		}
	}

	if(op=='S')
		cout << fixed << setprecision (1) <<  res << endl;
	else
		cout << fixed << setprecision (1) << res/12 << endl;

	return 0;
}