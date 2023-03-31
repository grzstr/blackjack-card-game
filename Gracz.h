#pragma once
class Karta;
class Kasyno;

class Gracz
{
protected:
	Karta *mojekarty;
	int ilekart;
	int punkty;
	int pas;
	char nazwa[20];

public:
	Gracz();
	~Gracz();
	Gracz(const Gracz& poprzedni);
	Gracz& operator=(const Gracz& doprzypisania);
	void wezKarte(Karta* _karta);
	void pokazKarty();
	void decyzja();
	void podajNazwe(int numerGracza);
	//akcesory
	int czyPas() { return pas; };
	int ilePunktow() { return punkty;}
	int ileKart() { return ilekart; }
	char* jakieImie() { return nazwa; }

	Karta& podajKarty(int i);
};