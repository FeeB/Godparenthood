#include <vector>

class ClPatenschaft;

class ClPerson
{
private:
	char namePate[100];
	int ordnungsnummer;
	char eindeutigeID[100];
	vector<ClPatenschaft*> patenschaften;
	
	static vector<ClPerson*> personen;
	
	
public:
	static int maximaleTiefe;
	static int anzahlPatenschaften;
	
	void setName(char puffer[100]){strcpy(namePate, puffer);}
	char *getName(void){return namePate;}
	void setOrdnungsnummer(char puffer[100]){ordnungsnummer = atoi(puffer);}
	int getOrdnungsnummer(void){return ordnungsnummer;}
	void setEindeutigeID(char puffer[100]){strcpy(eindeutigeID, puffer);}
	char *getEindeutigeID(void){return eindeutigeID;}
	void fuegePatenschaftHinzu(ClPatenschaft *patenschaft);
	int groessePatenschaften(){return patenschaften.size();}
	void ausgabe(int tiefe);
		
	static void lesePerson(ifstream &datei);
	static vector<ClPerson*> suchePersonNachNamensbestandteil(char gesuchterName[100]);
	static ClPerson* suchePersonNachId(char gesuchteID[100]);
	static ClPerson* suchePersonNachOrdnungsnummer(int gesuchteOrdnungsnummer);
	static void leseBeziehungen(ifstream &datei);
};

enum status
{
	ordnumerw, ordnum, nameerw, name, identerw, ident, urlerw, url
};

enum zustand
{
	ordnumPatErw, ordnumPat, ordnumElt, anzahl
};
