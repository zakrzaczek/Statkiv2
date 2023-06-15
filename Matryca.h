#pragma once
#include "Biblioteki.h"


const int ROZMIAR_TABLICY = 10;
const int liczbaStatkow = 3;

class Matryca {
public:
	Matryca();
	Matryca(const Matryca& data);
	~Matryca() {}
	
	void wyswietlMatryce();
	void wyswietlMatryce(int IdGracza);
	void setStatek(int numerStatku, int x1, int y1, int x2, int y2);
	bool czyDobryKierunek(int x1, int y1, int x2, int y2);
	bool czyZajete(int x1, int y1, int x2, int y2);
	bool czySieZmiesci(int x1, int y1, int x2, int y2);
	bool czyZatonal(int numerStatku);
	void losowoUstawFlote();
	bool czyWszystkieStUmieszczone();
	bool czyWszystkieStZatopione();
	void wyswietlPozostaleStatki();

	Statek& getStatki(int n) { return Statki[n]; }
	
	Statek& operator()(int, int);
	Matryca& operator=(const Matryca& rhs);
	bool operator==(const Matryca&);
	bool operator!=(const Matryca&);

private:
	Statek planszaGry[ROZMIAR_TABLICY][ROZMIAR_TABLICY];
	Statek Statki[liczbaStatkow];
};