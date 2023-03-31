#include <iostream>

#include "Gracz.h"
#include "Karta.h"
#include "Kasyno.h"




Gracz::Gracz(): // Konstruktor
	mojekarty(nullptr),
	ilekart(0),
	punkty(0),
	pas(0)
{}

Gracz::~Gracz() // Destruktor
{
	delete[] mojekarty;
}

Gracz::Gracz(const Gracz& poprzedni) // Konstruktor kopiuj¹cy
{
	ilekart = poprzedni.ilekart;
	mojekarty = new Karta[ilekart];
	punkty = poprzedni.punkty;
	pas = poprzedni.pas;
	strcpy_s(nazwa, poprzedni.nazwa);

	for (int i = 0; i < ilekart; i++)
	{
		*(mojekarty + i) = *(poprzedni.mojekarty + i);
	}
}

Gracz& Gracz::operator=(const Gracz& doprzypisania) // Operator przypisania
{
	if (&doprzypisania == this) return *this;
	delete[] mojekarty;

	ilekart = doprzypisania.ilekart;
	punkty = doprzypisania.punkty;
	pas = doprzypisania.pas;
	strcpy_s(nazwa, doprzypisania.nazwa);

	for (int i = 0; i < ilekart; i++)
	{
		*(mojekarty + i) = *(doprzypisania.mojekarty + i);
	}

	return *this;
}

void Gracz::wezKarte(Karta* _karta)
{
	Karta* nowe_mojekarty;
	if (ilekart < 10)
	{
		ilekart++;
		punkty += _karta->getWartosc();
		nowe_mojekarty = new Karta[ilekart];

		for (int i = 0; i < ilekart - 1; i++)
		{
			*(nowe_mojekarty + i) = *(mojekarty + i);
		}

		*(nowe_mojekarty + (ilekart - 1)) = *_karta;

		delete[] mojekarty;

		mojekarty = nowe_mojekarty;
	}
}

void Gracz::pokazKarty()
{
	for (int i = 0; i < ilekart; i++)
	{
		mojekarty[i].wypisz();
		std::cout << "  ";
	}
	std::cout << std::endl;
}

void Gracz::decyzja()
{
	int wybor;

	if (punkty >= 21)
	{
		std::cout << "Masz ju¿ 21 punktów lub wiêcej, pasujesz"<< std::endl;
		pas = 1;
	}
	else
	{
		do
		{
			std::cout << std::endl << "0 - Dobierz karte" << std::endl << "1 - Pas" << std::endl << "-> ";

			while (1)	//nieskoñczona pêtla
			{
				std::cin >> wybor;	//pobranie zmienne
				if (std::cin.fail() == true)	// wykrycie b³êdu
				{
					std::cout << "Wykryto b³¹d" << std::endl;	// komunikat o b³êdzie
					std::cin.clear();							// resetowanie flag b³êdu
					std::cin.ignore(256, '\n');					// czyszczenie 256 znaków bufora
				}												// lub do napotkania znaku nowej linii
				else break;
			}

			switch (wybor)
			{
			case 0:
				pas = 0;
				break;

			case 1:
				pas = 1;
				break;

			default:
				std::cout << "Nie ma takiej opcji!" << std::endl;
				break;
			}
		} while (wybor != 0 && wybor != 1);
	}
}

void Gracz::podajNazwe(int numerGracza)
{
	std::cout << "Podaj nazwê gracza (" << numerGracza << "):" << std::endl;
	while (1)	//nieskoñczona pêtla
	{
		std::cin >> nazwa;	//pobranie zmiennej
		std::cin.get();
		if (std::cin.fail() == true)	// wykrycie b³êdu
		{
			std::cout << "Wykryto b³¹d" << std::endl;	// komunikat o b³êdzie
			std::cin.clear();							// resetowanie flag b³êdu
			std::cin.ignore(256, '\n');					// czyszczenie 256 znaków bufora
		}												// lub do napotkania znaku nowej linii
		else break;
	}
	system("cls");
}

Karta& Gracz::podajKarty(int i)
{
	return mojekarty[i];
}