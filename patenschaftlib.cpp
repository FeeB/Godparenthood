#include "patenschaft.h"
#include "person.h"

#include <iostream>

using namespace std;
//int anzahlPatenschaften=0;

void ClPatenschaft::ausgabe(int tiefe) {
	
	for (int i = 0; i < tiefe; i++) {
		cout << "| ";
	}
	cout << anzahlKinder << " von " << eltern->getName() << endl;
	eltern->ausgabe(tiefe + 1);
	
	/*for (int i = 0; i < tiefe; i++) {
		anzahlPatenschaften=(anzahlPatenschaften+anzahlKinder);
		if (pate->groessePatenschaften==i) {
			cout << "Anzahl Patenschaften: " << anzahlPatenschaften << endl;
		}
		
	}
	anzahlPatenschaften=(anzahlPatenschaften+anzahlKinder);*/

	
}