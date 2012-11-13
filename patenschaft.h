#include <fstream>

using namespace std;
class ClPerson;

class ClPatenschaft
{
private:
	ClPerson *eltern;
	//int ordnungsnummerPate;
	int anzahlKinder;
	
public:
	//void setOrdnungsnummerPate(char puffer[100]){ordnungsnummerPate = atoi(puffer);}
	//int getOrdnungsnummerPate(void){return ordnungsnummerPate;}
	void setEltern(ClPerson *neueEltern){eltern = neueEltern;}
	ClPerson *getEltern(void){return eltern;}
	void setAnzahlKinder(char puffer[100]){anzahlKinder = atoi(puffer);}
	int getAnzahlKinder(void){return anzahlKinder;}
	void ausgabe(int tiefe);
};