#pragma once
#include "Gracz.h"

class Bot: public Gracz
{
private:
	int odwaga;

public:
	Bot();
	void nazwij(int numerBota);
	void zdecyduj();
};