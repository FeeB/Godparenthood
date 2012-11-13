#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "person.h"
#include "patenschaft.h"
 
vector<ClPerson*> ClPerson::personen; 
int ClPerson::maximaleTiefe=0;
int ClPerson::anzahlPatenschaften=0;


/* Objektmethoden */

void ClPerson::fuegePatenschaftHinzu(ClPatenschaft *patenschaft){
	patenschaften.push_back(patenschaft);
}

void ClPerson::ausgabe(int tiefe) {
	if(tiefe >= ClPerson::maximaleTiefe) {
		return;
	};
	
	if (patenschaften.size() == 0) {
		for (int i = 0; i < tiefe; i++) {
			cout << "| ";
		}
		if(tiefe==0){
			cout << this->getName() << "hat keine Patenschaften übernommen" << endl;
			return;
		}
		else{
			cout << "Hat selbst keine Patenschaften übernommen" << endl;
			return;
		}
	}
	
	if (tiefe == 0) {
		cout << this->getName() << "hat folgende Patenschaften übernommem: " << endl;		
	} else {
		for (int i = 0; i < tiefe; i++) {
			cout << "| ";
		}
		cout << "Dieser hat selbst folgende Patenschaften übernommen:" << endl;			
	}
	for (int i = 0; i < patenschaften.size(); i++) {
		patenschaften[i]->ausgabe(tiefe);
		if (tiefe==0) {
			anzahlPatenschaften=(anzahlPatenschaften+patenschaften[i]->getAnzahlKinder());
		}
	}	
}
	

/* Statische Methoden (zugehörigkeit Klasse) */

void ClPerson::lesePerson(ifstream &datei){
	
	char puffer[100];
	char zeichen;
	int zaehler;
	enum status status;
	ClPerson *aktuellePerson = new ClPerson;
	
	status=ordnumerw;
	zaehler=0;
	for(;;) {
		datei.get(zeichen);
		if (datei.eof()){
			ClPerson::personen.push_back(aktuellePerson);
			//cout << "abbruch"<<endl;
			break;
		}
		
		switch(zeichen) {
			case ' ':
				if (status==ordnumerw) {
					if (zaehler!=0){
						status=ordnum;
						puffer[zaehler]='\0';
						zaehler=0;
						//cout << puffer << endl;
						aktuellePerson->setOrdnungsnummer(puffer);
						//cout << "ordnum"<<endl;
					}
					else {
						status=ordnumerw;
						zaehler=0;
						//cout << "ordnumerw"<<endl;
					}
				}
				else if (status=nameerw) {
					puffer[zaehler]=zeichen;
					zaehler++;
				}
				break;
			case '"':
				if (status==ordnum){
					status=nameerw;
					zaehler=0;
					//cout << "nameerw"<<endl;
				}
				else if (status==ident){
					status=urlerw;
					zaehler=0;
					//cout << "urlerw"<<endl;
				}
				else if (status==urlerw){
					status=url;
					zaehler=0;
					//cout << "url"<<endl;
				}
				else if (status==nameerw){
					status=name;
					zaehler=0;
				}
				break;
			case '(':
				status=identerw;
				puffer[zaehler]='\0';
				zaehler=0;
				aktuellePerson->setName(puffer);
				//cout << "ordnum"<<endl;
				//cout << aktuellePerson->getName();
				//cout << "name"<<endl;
				//cout << puffer<<endl;
				break;
			case ')':
				status=ident;
				puffer[zaehler]='\0';
				zaehler=0;
				aktuellePerson->setEindeutigeID(puffer);
				//cout << "ident"<<endl;
				break;
			case '\n':
				//cout << "ordnumerw" << endl;
				status=ordnumerw;
				zaehler=0;
				ClPerson::personen.push_back(aktuellePerson);
				aktuellePerson = new ClPerson;
				break; 
			default:
				puffer[zaehler]=zeichen;
				zaehler++;
				break;
		}
	}
}

void ClPerson::leseBeziehungen(ifstream &datei){
	
	char puffer[100];
	char zeichen;
	int zaehler;
	enum zustand zustand;
	int ordnungsnummerAktuellerPate = 0;
	//vector<ClPatenschaft*> beziehungen; 
	ClPatenschaft *aktuellePatenschaft = new ClPatenschaft;
	
	zustand=ordnumPatErw;
	zaehler=0;

	for(;;) {
		datei.get(zeichen);
		if (datei.eof()){
			ClPerson *pate = ClPerson::suchePersonNachOrdnungsnummer(ordnungsnummerAktuellerPate);
			pate->fuegePatenschaftHinzu(aktuellePatenschaft);
			break;
		}
		//cout << "aktuelles zeichen '" << zeichen << "' ARSCH" << endl;
		
		switch(zeichen) {
			case ' ': {
				if (zustand==ordnumPatErw) {
					if (zaehler!=0){
						zustand=ordnumPat;
						puffer[zaehler]='\0';
						zaehler=0;
						//cout << puffer << endl;
						//aktuellePatenschaft->setOrdnungsnummerPate(puffer);
						ordnungsnummerAktuellerPate = atoi(puffer);
						//cout << "ordnum"<<endl;
					}
					else {
						zustand=ordnumPatErw;
					}
				}
				
				else if (zustand=ordnumPat) {
					zustand=ordnumElt;
					puffer[zaehler]='\0';
					zaehler=0;
					//cout << puffer << endl;
					ClPerson *eltern = ClPerson::suchePersonNachOrdnungsnummer(atoi(puffer));
					aktuellePatenschaft->setEltern(eltern);
					//cout << "ordnum"<<endl;
				}
				else if (zustand=ordnumElt) {
					zustand=anzahl;
					puffer[zaehler]='\0';
					zaehler=0;
					//cout << puffer << endl;
					aktuellePatenschaft->setAnzahlKinder(puffer);
					//cout << "ordnum"<<endl;
				}
				break;
			}
			case '\n': {
				if (zustand=ordnumElt) {
					puffer[zaehler]='\0';
					zaehler=0;
					aktuellePatenschaft->setAnzahlKinder(puffer);
					zustand=ordnumPatErw;
				}
				ClPerson *pate = ClPerson::suchePersonNachOrdnungsnummer(ordnungsnummerAktuellerPate);
				pate->fuegePatenschaftHinzu(aktuellePatenschaft);
				aktuellePatenschaft = new ClPatenschaft;
				break; 
			}
			default: {
				puffer[zaehler]=zeichen;
				zaehler++;
				break;
			}
		}
	}
}

vector<ClPerson*> ClPerson::suchePersonNachNamensbestandteil(char gesuchterName[100]){
	vector<ClPerson*> gefundenePersonen;
	for (int i = 0; i < ClPerson::personen.size(); i++) {
		if (strstr(ClPerson::personen[i]->getName(), gesuchterName) != NULL) {
			gefundenePersonen.push_back(ClPerson::personen[i]);
		}
	}
	if (gefundenePersonen.size()!=0) {
		return gefundenePersonen;
	}
	else {
		cout << "Der Name konnte nicht gefunden werden." << endl;
	}
	return gefundenePersonen;
}


ClPerson* ClPerson::suchePersonNachOrdnungsnummer(int gesuchteOrdnungsnummer) {
	for (int i = 0; i < ClPerson::personen.size(); i++) {
		if (ClPerson::personen[i]->getOrdnungsnummer() == gesuchteOrdnungsnummer) {
			return ClPerson::personen[i];
		}
	}
	return NULL;
}

ClPerson* ClPerson::suchePersonNachId(char gesuchteID[100]){
	for (int i = 0; i < ClPerson::personen.size(); i++) {
		if (strcmp(ClPerson::personen[i]->getEindeutigeID(), gesuchteID) == 0) {
			return ClPerson::personen[i];
		}
	}
	return NULL;
}
