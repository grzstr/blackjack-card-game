#include "Karta.h"
#include "Gracz.h"
#include "Bot.h"

class Karta;
class Gracz;
class Bot;

class Kasyno
{
private:
	Karta* Karty;
	int wydaneKarty[52];
	Gracz* Gracze;
	Bot* GraczKomputerowy;
	int iloscGraczy;
	int iloscBotow;

public:
	Kasyno();
	~Kasyno();
	void nowaGra(int nastepnaRunda);
	void podajIloscGraczy();
	void podajIloscBotow();
	Karta& stworzKarte(int kolor, int wartosc);
	Karta* dajKarte();
	void tasowanie();
	int losuj();
	void dobierzKarte();
	void ktoWygral();
	int najwiekszyWynik(int rozmiar, int* tab);
	int* wypelnijZerami(int rozmiar, int* tab);
	void zapiszDoPliku();
	void pokazTalie();
	void pokazWyniki();
};