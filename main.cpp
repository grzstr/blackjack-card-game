#include <iostream>

#include "Kasyno.h"

int main()
{

	Kasyno Vegas;
	setlocale(LC_ALL, "pl_PL");
	int wybor, czyZakonczyc = 0;
	do
	{
		std::cout << "||-----|| GRA W OCZKO ||-----||" << std::endl << std::endl
			<< "1 - Nowa gra" << std::endl
			<< "2 - Zapis tablicy wynik�w do pliku .txt" << std::endl
			<< "3 - Tabela wynik�w" << std::endl
			<< "4 - Wyj�cie z gry" << std::endl << std::endl << "-> ";
		while (1)	//niesko�czona p�tla
		{
			std::cin >> wybor;	//pobranie zmiennej
			if (std::cin.fail() == true)	// wykrycie b��du
			{
				std::cout << "Wykryto b��d" << std::endl;	// komunikat o b��dzie
				std::cin.clear();							// resetowanie flag b��du
				std::cin.ignore(256, '\n');					// czyszczenie 256 znak�w bufora
			}												// lub do napotkania znaku nowej linii
			else break;
		}
		switch (wybor)
		{
		case 1:
			system("cls");
			Vegas.nowaGra(1);
			system("cls");
			break;

		case 2:
			system("cls");
			Vegas.zapiszDoPliku();
			system("cls");
			break;

		case 3:
			system("cls");
			Vegas.pokazWyniki();
			system("pause");
			system("cls");
			break;

		case 4:
			czyZakonczyc = 1;
			break;

		default:
			system("cls");
			std::cout << "Nie ma takiej opcji!" << std::endl;
			break;
		}
		if (czyZakonczyc == 1)
			break;
	} while (1);
	return 0;
}