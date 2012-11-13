#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#include "person.h"

int main() {
	char dateiPerson[100];
	char dateiBeziehung[100];
	char gesuchteID[100];
	char gesuchterNamensbestandteil[200];
	char aktion=' ';
	int maximaleTiefe;
	
	cout << endl << "Bitte geben Sie die Datei ein, in der die Personen abgespeichert sind: ";
	cin >> dateiPerson;
	cout << endl;
	
	ifstream personenDatei;
	personenDatei.open (dateiPerson);
	if (!personenDatei)
	{
		cout << "Die Datei " << dateiPerson << " konnte nicht geöffnet werden." << endl;
		return 1;
	}
	
	cout << endl << "Bitte geben Sie die Datei ein, in der die Beziehungen abgespeichert sind: ";
	cin >> dateiBeziehung;
	cout << endl;
	
	ifstream patenschaftDatei;
	patenschaftDatei.open (dateiBeziehung);
	if (!patenschaftDatei)
	{
		cout << "Die Datei " << dateiBeziehung << " konnte nicht geöffnet werden." << endl;
		return 1;
	}
	
	cout << "Bitte geben Sie die maximale Tiefe ein, in der das Dokument durchsucht werden soll, um eine Endlosschleife zu verhindern: ";
	cin >> maximaleTiefe;
	
	ClPerson::maximaleTiefe = maximaleTiefe;
	
	ClPerson::lesePerson(personenDatei);
	ClPerson::leseBeziehungen(patenschaftDatei);
	
	while (aktion != '*') {
		cout << endl << "MENUE:" << endl << "Wenn Sie nach der eindeutigen Identifikation suchen wollen, geben Sie ein 'I' ein," << endl << " wollen Sie nach einem Namensbestandteil suchen, geben Sie ein 'N' ein," << endl << " das Programm beenden Sie mit einem '*': ";
		cin >> aktion;
		
		aktion = tolower(aktion);
		
		switch (aktion) {
			case 'i':{
				cout << endl << "Bitte geben Sie die eindeutige Identifikation der gesuchten Person ein: ";
				cin >> gesuchteID;
				ClPerson *person = ClPerson::suchePersonNachId(gesuchteID);
				if(person!=NULL){
					person->ausgabe(0);
					cout << person->getName() << "hat insgesamt " << ClPerson::anzahlPatenschaften << " Patenschaften übernommen" << endl;
				}
				break;
			}
			case 'n':{
				cout << endl << "Bitte geben Sie einen Namensbestandteil der gesuchten Person ein: ";
				cin >> gesuchterNamensbestandteil;
				vector<ClPerson*> personen = ClPerson::suchePersonNachNamensbestandteil(gesuchterNamensbestandteil);
				for (int i = 0; i < personen.size(); i++) {
					cout <<  endl << "######################## Gefundene Person ###########################" << endl;
					ClPerson::anzahlPatenschaften=0;
					personen[i]->ausgabe(0);
					cout << personen[i]->getName() << "hat insgesamt " << ClPerson::anzahlPatenschaften << " Patenschaften übernommen" << endl;
				}
				break;
			}
		}
	}
}
