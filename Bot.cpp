#include <iostream>
#include <ctime>

#include "Bot.h"

Bot::Bot(): Gracz::Gracz()
{
	int los;
	srand(time(NULL));
	los = rand() % 3;

	if (los == 0)
		odwaga = 21;
	if (los == 1)
		odwaga = 16;
	if (los == 2)
		odwaga = 12;
}

void Bot::nazwij(int numerBota)
{
	if (numerBota == 0)
		strcpy_s(nazwa, "Bot1");
	if (numerBota == 1)
		strcpy_s(nazwa, "Bot2");
	if (numerBota == 2)
		strcpy_s(nazwa, "Bot3");
}

void Bot::zdecyduj()
{
	if (punkty >= odwaga)
	{
		pas = 1;
		std::cout << jakieImie() << " - spasowa³" << std::endl;
	}
	else
	{
		pas = 0;
		std::cout << jakieImie() << " - dobra³ kartê" << std::endl;
	}
}