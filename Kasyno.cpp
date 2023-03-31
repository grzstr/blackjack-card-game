#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "Kasyno.h"




Kasyno::Kasyno() : //Konstruktor
	Gracze(nullptr),
	GraczKomputerowy(nullptr),
	Karty(new Karta[52]),
	iloscGraczy(0),
	iloscBotow(0)
{

	int i = 0;
	srand(time(NULL));

	for (int kolor = 0; kolor < 4; kolor++)
	{
		for (int wartosc = 0; wartosc < 13; wartosc++)
		{
			Karty[i] = stworzKarte(kolor, wartosc);
			i++;
		}
	}
}


Kasyno::~Kasyno() //Destruktor
{
	delete[] Karty;
	delete[] Gracze;
	delete[] GraczKomputerowy;
}

void Kasyno::nowaGra(int nastepnaRunda)
{
	if (nastepnaRunda == 1)
	{
		for (int i = 0; i < 52; i++)
			wydaneKarty[i] = 0;
		
		delete[] Gracze;
		delete[] GraczKomputerowy;
	}
	tasowanie();

	podajIloscGraczy();
	podajIloscBotow();
	system("cls");

	Gracze = new Gracz[iloscGraczy];
	GraczKomputerowy = new Bot[iloscBotow];

	for (int i = 0; i < iloscGraczy; i++)
		Gracze[i].podajNazwe(i + 1);
	for (int i = 0; i < iloscBotow; i++)
		GraczKomputerowy[i].nazwij(i);

	for (int i = 0; i < iloscGraczy; i++)
	{
		Gracze[i].wezKarte(dajKarte());
		Gracze[i].wezKarte(dajKarte());
	}
	for (int i = 0; i < iloscBotow; i++)
	{
		GraczKomputerowy[i].wezKarte(dajKarte());
		GraczKomputerowy[i].wezKarte(dajKarte());
	}
	dobierzKarte();
}

void Kasyno::podajIloscGraczy()
{
	do
	{
		std::cout << "Podaj ilu graczy ludzkich (1-3) ma graæ: ";
		while (1)	//nieskoñczona pêtla
		{
			std::cin >> iloscGraczy;	//pobranie zmiennej
			if (std::cin.fail() == true)	// wykrycie b³êdu
			{
				std::cout << "Wykryto b³¹d" << std::endl;	// komunikat o b³êdzie
				std::cin.clear();							// resetowanie flag b³êdu
				std::cin.ignore(256, '\n');					// czyszczenie 256 znaków bufora
			}												// lub do napotkania znaku nowej linii
			else break;
		}
		if (iloscGraczy > 3)
			std::cout << "Nie mo¿e byæ tylu graczy!" << std::endl;
		if (iloscGraczy < 1)
			std::cout << "Za ma³o graczy!" << std::endl;
	} while (iloscGraczy>3 || iloscGraczy<1);
}

void Kasyno::podajIloscBotow()
{
	do
	{
		std::cout << "Podaj ilu graczy komputerowych (1-3) ma graæ: ";
		while (1)	//nieskoñczona pêtla
		{
			std::cin >> iloscBotow;	//pobranie zmiennej
			if (std::cin.fail() == true)	// wykrycie b³êdu
			{
				std::cout << "Wykryto b³¹d" << std::endl;	// komunikat o b³êdzie
				std::cin.clear();							// resetowanie flag b³êdu
				std::cin.ignore(256, '\n');					// czyszczenie 256 znaków bufora
			}												// lub do napotkania znaku nowej linii
			else break;
		}
		if (iloscBotow > 3)
			std::cout << "Nie mo¿e byæ tylu graczy!" << std::endl;
		if (iloscBotow < 1)
			std::cout << "Za ma³o graczy!" << std::endl;
	} while (iloscBotow > 3 || iloscBotow < 1);
}


Karta& Kasyno::stworzKarte(int kolor, int wartosc)
{
	Karta nowa(kolor, wartosc);
	return nowa;
}

/*Karta* Kasyno::dajKarte()
{
	int los;

	do
	{
		los = losuj();
	} while (wydaneKarty[los] == 1);
	wydaneKarty[los] = 1;

	return &Karty[los];
}*/

Karta* Kasyno::dajKarte()
{
	int i = 0;

	while (wydaneKarty[i] == 1)
	{
		i++;
	}
	wydaneKarty[i] = 1;

	return &Karty[i];
}

void Kasyno::tasowanie()
{
	int los1, los2;
	Karta wymiana;

	for (int i = 0; i < 100; i++)
	{
		los1 = losuj();
		los2 = losuj();

		wymiana = Karty[los1];
		Karty[los1] = Karty[los2];
		Karty[los2] = wymiana;
	}
}

int Kasyno::losuj()
{
	int los;
	do
	{
		los = std::rand();
	} while (los > 51 || los < 0);

	return los;
}

void Kasyno::dobierzKarte()
{
	int kontynuujGre = 0;
	for (int i = 0; i < iloscGraczy; i++)
	{
		if (Gracze[i].czyPas() == 0)
		{
			system("cls");
			std::cout << Gracze[i].jakieImie() << " " << Gracze[i].ilePunktow() << "pkt" << std::endl << std::endl;
			Gracze[i].pokazKarty();
			Gracze[i].decyzja();
			if (Gracze[i].czyPas() == 0)
			{
				kontynuujGre = 1;
				Gracze[i].wezKarte(dajKarte());
				Gracze[i].pokazKarty();
			}
		}
		else
		{
			system("cls");
			std::cout << Gracze[i].jakieImie() << "- spasowa³" <<std::endl;
		}
		system("pause");
	}
	system("cls");
	for (int i = 0; i < iloscBotow; i++)
	{
		if (GraczKomputerowy[i].czyPas() == 0)
		{
			GraczKomputerowy[i].zdecyduj();
			if (GraczKomputerowy[i].czyPas() == 0)
			{
				kontynuujGre = 1;
				GraczKomputerowy[i].wezKarte(dajKarte());
			}
		}
	}
	system("pause");
	if (kontynuujGre == 0)
	{
		system("cls");
		ktoWygral();
	}
	else
	{
		dobierzKarte();
	}
}

void Kasyno::ktoWygral()
{
	int x = 0, y = 0, najwiekszy, ileGraczy, nieZero = 0;
	int* win, *wyniki;

	pokazWyniki();

	ileGraczy = iloscGraczy + iloscBotow;
	win = new int[ileGraczy];
	win = wypelnijZerami(ileGraczy, win);

	//SPRAWDZENIE ILU GRACZY UZYSKA£O 21 PUNKTÓW
	for (int i = 0; i < iloscGraczy; i++)
	{
		if (Gracze[i].ilePunktow() == 21)
			win[i] = 1;
	}
	for (int i = 0; i < iloscBotow; i++)
	{
		if (GraczKomputerowy[i].ilePunktow() == 21)
			win[i + iloscGraczy - 1] = 1;
	}

	//SPRAWDZENIE CZY WSZYSCY GRACZE UZYSKALI 21 PUNKTÓW
	for (int i = 0; i < ileGraczy; i++)
	{
		if (win[i] == 0)
		{
			x = 1;
			break;
		}
	}
	if (x == 0)
	{
		std::cout << "Wszyscy uzyskali 21 punktów, wszyscy przegrali" << std::endl; // WSZYSCY ZEBRALI 21 PUNKTÓW
	}
	else
	{
		for (int i = 0; i < ileGraczy; i++)
		{
			if (win[i] == 1)
			{
				y = 1;
				break;
			}
		}
		if (y == 0) // NIKT NIE UZYSKA£ 21 PUNKTÓW, DLATEGO TRZEBA PORÓWNAÆ WYNIKI 
		{
			wyniki = new int[ileGraczy];
			for (int i = 0; i < iloscGraczy; i++)
			{
				wyniki[i] = Gracze[i].ilePunktow();
			}
			for (int i = 0; i < iloscBotow; i++)
			{
				wyniki[i + iloscGraczy] = GraczKomputerowy[i].ilePunktow();
			}
			for (int i = 0; i < ileGraczy; i++)
			{
				if (wyniki[i] > 21)
				{
					wyniki[i] = 0; //ZWYCIÊSKI WYNIK NIE MO¯E BYÆ WIÊKSZY OD 21
				}
				if (wyniki[i] != 0) // JE¯ELI WSZYSKIE WYNIKI S¥ WYZEROWANE TO ZNACZY ¯E KA¯DY MA WIÊCEJ NI¯ 21 PUNKTÓW
				{
					nieZero = 1; // 1 -> NIE WSZYSTKIE ZOSTA£Y WYZEROWANE
				}
			}

			najwiekszy = najwiekszyWynik(ileGraczy, wyniki);

			if (nieZero == 0)
			{
				std::cout << "Nikt nie wygra³" << std::endl;
			}
			else
			{
				std::cout << "Wygra³:" << std::endl;
			}
			for (int i = 0; i < iloscGraczy; i++)
			{
				if (najwiekszy == Gracze[i].ilePunktow())
				std::cout << Gracze[i].jakieImie() << " z iloœci¹ punktów: " << Gracze[i].ilePunktow() << std::endl;
			}
			for (int i = 0; i < iloscBotow; i++)
			{
				if (GraczKomputerowy[i].ilePunktow() == najwiekszy)
				std::cout << GraczKomputerowy[i].jakieImie() << " z iloœci¹ punktów: " << GraczKomputerowy[i].ilePunktow() << std::endl;
			}

				
			delete[] wyniki;
		}
		else //PARE OSÓB UZYSKA£O 21 PUNKTÓW ALE NIE WSZYSCY ONI WYGRALI
		{
			std::cout << "Wygra³:" << std::endl;
			for (int i = 0; i < iloscGraczy; i++)
				if (Gracze[i].ilePunktow() == 21)
					std::cout << Gracze[i].jakieImie() << " z iloœci¹ punktów: " << Gracze[i].ilePunktow() << std::endl;
			for (int i = 0; i < iloscBotow; i++)
				if (GraczKomputerowy[i].ilePunktow() == 21)
					std::cout << GraczKomputerowy[i].jakieImie() << " z iloœci¹ punktów: " << GraczKomputerowy[i].ilePunktow() << std::endl;
		}
	}
	delete[] win;

	system("pause");
}

int Kasyno::najwiekszyWynik(int rozmiar, int* tab)
{
	int wynik, loop;
	
	while (1)
	{
		loop = 0;
		for (int i = 0; i < rozmiar; i++)
		{
			if (tab[i] < tab[i + 1])
			{
				wynik = tab[i + 1];
				tab[i + 1] = tab[i];
				tab[i] = wynik;
			}
		}
		for (int i = 0; i < rozmiar; i++)
		{
			if (tab[i] < tab[i + 1])
				loop = 1;
		}
		if (loop == 0)
			break;
	}

	return tab[0];
}

int* Kasyno::wypelnijZerami(int rozmiar, int* tab)
{
	for (int i = 0; i < rozmiar; i++)
		tab[i] = 0;
	return tab;
}

void Kasyno::zapiszDoPliku()
{
	if (iloscGraczy != 0 && iloscBotow != 0)
	{
		std::ofstream plik;
		plik.open("tabela.txt", std::ofstream::out);
		if (plik.is_open() == true) 
		{
			for (int i = 0; i < iloscGraczy; i++)
			{
				plik.setf(std::ios::left, std::ios::adjustfield);
				std::cout.setf(std::ios::showbase);
				plik.width(30);
				plik << Gracze[i].jakieImie();
				for (int m = 0; m < Gracze[i].ileKart(); m++)
				{
					plik << Gracze[i].podajKarty(m).getFigura();

					if (Gracze[i].podajKarty(m).getKolor() == 3)
						plik << " [TREFL],";
					if (Gracze[i].podajKarty(m).getKolor() == 4)
						plik << " [KARO] ,";
					if (Gracze[i].podajKarty(m).getKolor() == 5)
						plik << " [KIER] ,";
					if (Gracze[i].podajKarty(m).getKolor() == 6)
						plik << " [PIK]  ,";
				}
				plik.setf(std::ios::right, std::ios::adjustfield);
				std::cout.setf(std::ios::showbase);

				if (Gracze[i].ileKart() >= 7)
					plik.width(10);
				if (Gracze[i].ileKart() == 6)
					plik.width(20);
				if (Gracze[i].ileKart() == 5)
					plik.width(30);
				if (Gracze[i].ileKart() == 4)
					plik.width(40);
				if (Gracze[i].ileKart() == 3)
					plik.width(50);
				if (Gracze[i].ileKart() == 2)
					plik.width(60);
				if (Gracze[i].ileKart() == 1)
					plik.width(70);

				plik << Gracze[i].ilePunktow() << std::endl;
			}
			for (int i = 0; i < iloscBotow; i++)
			{
				plik.setf(std::ios::left, std::ios::adjustfield);
				std::cout.setf(std::ios::showbase);
				plik.width(30);
				plik << GraczKomputerowy[i].jakieImie();
				for (int m = 0; m < GraczKomputerowy[i].ileKart(); m++)
				{
					plik << GraczKomputerowy[i].podajKarty(m).getFigura();

					if (GraczKomputerowy[i].podajKarty(m).getKolor() == 3)
						plik << " [TREFL],";
					if (GraczKomputerowy[i].podajKarty(m).getKolor() == 4)
						plik << " [KARO] ,";
					if (GraczKomputerowy[i].podajKarty(m).getKolor() == 5)
						plik << " [KIER] ,";
					if (GraczKomputerowy[i].podajKarty(m).getKolor() == 6)
						plik << " [PIK]  ,";
				}
				plik.setf(std::ios::right, std::ios::adjustfield);
				std::cout.setf(std::ios::showbase);

				if (GraczKomputerowy[i].ileKart() >= 7)
					plik.width(10);
				if (GraczKomputerowy[i].ileKart() == 6)
					plik.width(20);
				if (GraczKomputerowy[i].ileKart() == 5)
					plik.width(30);
				if (GraczKomputerowy[i].ileKart() == 4)
					plik.width(40);
				if (GraczKomputerowy[i].ileKart() == 3)
					plik.width(50);
				if (GraczKomputerowy[i].ileKart() == 2)
					plik.width(60);
				if (GraczKomputerowy[i].ileKart() == 1)
					plik.width(70);

				plik << GraczKomputerowy[i].ilePunktow() << std::endl;
			}
			std::cout << "Zapisano stan po grze w pliku tekstowym - tabela.txt" << std::endl;
		}
		else 
		{
			std::cout << "Nie mo¿na otworzyæ pliku!" << std::endl;
		}
		plik.close();
	}
	else
	{
		std::cout << "Brak graczy!" << std::endl;
	}	
	system("pause");
}

void Kasyno::pokazTalie()
{
	for (int i = 0; i < 52; i++)
	{
		std::cout << "Karta [" << i << "]  F = " << Karty[i].getFigura() << " K = " << Karty[i].getKolor() << " W = " << Karty[i].getWartosc() << std::endl;
	}
}

void Kasyno::pokazWyniki()
{
	if (iloscGraczy != 0 && iloscBotow !=0)
	{
		std::cout << "TABELA WYNIKÓW" << std::endl << std::endl;

		for (int i = 0; i < iloscGraczy; i++)
			std::cout << Gracze[i].jakieImie() << " - " << Gracze[i].ilePunktow() << std::endl;
		for (int i = 0; i < iloscBotow; i++)
			std::cout << GraczKomputerowy[i].jakieImie() << " - " << GraczKomputerowy[i].ilePunktow() << std::endl;

		std::cout << std::endl;
	}
	else
	{
		std::cout << "Brak graczy!" << std::endl;
	}
}