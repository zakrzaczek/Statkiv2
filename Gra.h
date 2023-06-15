#pragma once


class Gra{
public:
	Gra();
	Gracz& getGracz(int id);
	void strzelaj(Gracz&, int, int); //atakuj statek przeciwnika
private:
	Gracz g1;
	Gracz g2;
};