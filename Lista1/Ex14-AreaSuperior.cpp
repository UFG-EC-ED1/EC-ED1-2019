#include <iostream>
#include <iomanip>

using namespace std;

int main(){
	
	char op;
	double sum=0, aux;
	int left=0, right=11;
	cin >> op;
	
	for (int i=0; i<12; i++){
		for (int j=0; j<12; j++){
			cin >> aux;
			if(i<5 && (j>left && j<right))
				sum+=aux;	
		}
		left++;
		right--;
	}

	if(op=='S')
		cout << fixed << setprecision (1) << sum << endl;
	else
		cout << fixed << setprecision (1) << sum/30 << endl;

	return 0;
}