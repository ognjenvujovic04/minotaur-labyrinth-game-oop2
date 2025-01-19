#include <iostream>

using namespace std;

int main(){
	cout << "Dobrodosli u igricu bjeg iz lavirinta u Knososu!" << endl << endl;
	int n, m, k;
	cout << "Unesite broj kolona: ";
	cin >> n;
	cout << "Unesite broj redova: ";
	cin >> m;
	while (true){	
		cout << "Unesite broj predmeta: ";
		cin >> k;
		if (k > (n * m)/2){
			cout << "Broj predmeta ne moze biti veci od broja slobodnih polja lavirinta!" << endl;
		}
		else if(k<4) {
			cout << "Broj predmeta mora biti veci od 3!" << endl;
		}
		else {
			break;
		}
	}
	cout << n << " " << m << " " << k << endl;


	
}