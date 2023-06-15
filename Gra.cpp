#include "Biblioteki.h"

Gracz preGracz(-1);

Gracz& Gra::getGracz(int id) {
	if (id == 1) { return g1; }
	else if (id == 2) { return g2; }
	else {
		std::cout << "B³ad podczas pobierania gracza\n";
		return preGracz;
	}
}

void Gra::strzelaj(Gracz& atakowanyGracz, int xAtaku, int yAtaku) {

    //czesto uzywane referencje
	Statek* atakowaneMiejsce = &atakowanyGracz(yAtaku, xAtaku);
	Statek* statekPrzechowywanyWTabeli = &atakowanyGracz.getMatryca().getStatki(atakowanyGracz(yAtaku, xAtaku).getNumerStatku());
	
    std::cout << krawedz;
    //sprawdzenie poprawnego celu
	if (xAtaku >= 0 && xAtaku < ROZMIAR_TABLICY && yAtaku >= 0 && yAtaku < ROZMIAR_TABLICY) {
		//jeœli ju¿ zaatakowane, zwróæ b³¹d
		if (atakowaneMiejsce->getNaCelowniku()) {
			std::cout << "Blad, juz zaatakowane\n";
			return;
		}
		//w przeciwnym razie, atakuj
		else {
			atakowaneMiejsce->setNaCelowniku(true);
			//zatop statek, zmniejsz liczbê statków w tablicy
			if (atakowaneMiejsce->getStatus() == na_powierzchni) {
				atakowaneMiejsce->setStatus(zatopiony);
				//zmniejsz liczbê statków w tablicy
				statekPrzechowywanyWTabeli->setRozmiar(statekPrzechowywanyWTabeli->getRozmiar() - 1);
				std::cout << "\033[;33mTRAFIONY!\033[0m\n";
				//zatop tablicê statków, jeœli wszystkie obiekty statków zosta³y zatopione
				if (statekPrzechowywanyWTabeli->getRozmiar() == 0) {
					statekPrzechowywanyWTabeli->setStatus(zatopiony);
					std::cout << "Statek " << statekPrzechowywanyWTabeli->getNazwa() << " gracza " << atakowanyGracz.getID() << " ZATOPIONY!\n";
				}
			}
			else {
				std::cout << "\033[;31mPUDLO!\033[0m\n";
			}
		}
	}
	else {
		std::cout << "Nieprawidlowa wspolrzedna ataku\n";
	}
}

//dwa tryby gry
//1 = gracz vs. cpu
//2 = cpu vs. cpu
Gra::Gra() {

    cout << R"(
        		      ~ ~				   
                         __/___            	       
                   _____/______|           	         
           _______/_____\_______\_____     	   
           \              < < <       |)" << endl;
    cout << "\033[;34m~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\033[0m" << endl;

    g1.setID(1); g1.setTypGracza("human");
    g2.setID(2); g2.setTypGracza("cpu");
    g1.setRunda(true);
    g2.getMatryca().losowoUstawFlote();

    std::cout << "---------------------------------------------------------\nROZPOCZECIE GRY\n";
    std::string poczatek, koniec;
    int x1, y1, x2, y2, numerStatku;
    char wybor;

    //umieœæ statki
    std::cout << "Prosze umiescic statki.\n";
    std::cout << krawedz;
    //dopóki nie umieszczone wszystkie statki
    //daj opcjê losowego rozmieszczenia
    std::cout << "Chcesz sam umiescic flote czy ustawic losowo (s/l)?\n: ";
    std::cin >> wybor;
    std::cout << krawedz;
    if (wybor == 's' || wybor == 'S') {
        while (!g1.getMatryca().czyWszystkieStUmieszczone()) {
            //wyœwietl pozosta³e statki
            //wyœwietl planszê
            std::cout << "aktualna plansza p1:\n";
            g1.getMatryca().wyswietlMatryce();
            g1.getMatryca().wyswietlPozostaleStatki();

            std::cout << "Prosze podac numer statku do umieszczenia:\nNumer statku: ";
            std::cin >> numerStatku;
            std::cout << "Prosze podac zakres umieszczenia statku:\nPoczatkowe miejsce (np. a3): ";
            std::cin >> poczatek;
            std::cout << "Koncowe miejsce (np. a6): ";
            std::cin >> koniec;

            x1 = toupper(poczatek[0]) - 'A';
            y1 = poczatek[1] - '0';
            x2 = toupper(koniec[0]) - 'A';
            y2 = koniec[1] - '0';

            //umieœæ statek
            g1.getMatryca().setStatek(numerStatku, x1, y1, x2, y2);
            system("cls");
        }
    }
    else if (wybor == 'l' || wybor == 'L') { g1.getMatryca().losowoUstawFlote(); }
    else { std::cout << "Nieprawidlowa opcja\n"; return; }

    getchar(); getchar();
    system("cls");

    Gracz aktualnyGracz = g1;
    Gracz nastepnyGracz = g2;
    Gracz tmpGracz;
    int opcja;
    std::string koordynataAtaku;

    while (!(aktualnyGracz.getMatryca().czyWszystkieStZatopione() || nastepnyGracz.getMatryca().czyWszystkieStZatopione())) {
        
        cout << R"(
        		      ~ ~				   
                         __/___            	       
                   _____/______|           	         
           _______/_____\_______\_____     	   
           \              < < <       |)" << endl;
        cout << "\033[;34m~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\033[0m" << endl;

        if (aktualnyGracz.getTypGracza() == "human") {

            std::cout << "Tura gracza " << aktualnyGracz.getID() << ":\n";
            std::cout << "Prosze wybrac polecenie.......\n";
            std::cout << "\033[;34m1. Wyswietl moja plansze\n2. Atakuj przeciwnika\n3. Wyswietl plansze przeciwnika\n \033[0m";
            std::cin >> opcja;

            if (opcja == 1) {
                std::cout << "Plansza gracza " << aktualnyGracz.getID() << "\n";
                aktualnyGracz.getMatryca().wyswietlMatryce();
            }
            else if (opcja == 2) {
                std::cout << krawedz;
                std::cout << "Wprowadz koordynaty ataku (np. a3)\n: ";
                std::cin >> koordynataAtaku;
                x1 = (int)koordynataAtaku[0] - 97;
                y1 = (int)koordynataAtaku[1] - 48;
                if (x1 >= 0 && y1 >= 0 && x1 < ROZMIAR_TABLICY && y1 < ROZMIAR_TABLICY && !nastepnyGracz.getMatryca()(x1, y1).getNaCelowniku()) {
                    strzelaj(nastepnyGracz, x1, y1);
                    std::cout << krawedz;
                    //zamiana graczy po udanym strzale
                    tmpGracz = aktualnyGracz;
                    aktualnyGracz = nastepnyGracz;
                    nastepnyGracz = tmpGracz;
                }
                else {
                    std::cout << krawedz;
                    std::cout << "Nieprawidlowy cel, sprobuj ponownie\n";
                    std::cout << krawedz;
                }
            }
            else if (opcja == 3) {
                std::cout << krawedz;
                std::cout << "Plansza gracza " << nastepnyGracz.getID() << "\n";
                nastepnyGracz.getMatryca().wyswietlMatryce(2);
            }
            else {
                std::cout << krawedz;
                std::cout << "Nieprawidlowa opcja, sprobuj ponownie.\n";
                std::cout << krawedz;
            }
        }
        else {

            //initialize array of random numbers 0-99 to attack ships randomly
            int g1LosKoord[ROZMIAR_TABLICY * ROZMIAR_TABLICY];
            int g2LosKoord[ROZMIAR_TABLICY * ROZMIAR_TABLICY];
            int tmpLosNum1, tmpLosNum2, tmpNumer;

            for (int i = 0; i < ROZMIAR_TABLICY * ROZMIAR_TABLICY; i++) {
                g1LosKoord[i] = i;
                g2LosKoord[i] = i;
            }

            srand(static_cast<unsigned int>(time(NULL)));

            for (int k = 0; k < ROZMIAR_TABLICY * ROZMIAR_TABLICY * ROZMIAR_TABLICY; k++) {
                tmpLosNum1 = rand() % 100;
                tmpNumer = g1LosKoord[tmpLosNum1];
                g1LosKoord[tmpLosNum1] = g1LosKoord[ROZMIAR_TABLICY * ROZMIAR_TABLICY - 1];
                g1LosKoord[ROZMIAR_TABLICY * ROZMIAR_TABLICY - 1] = tmpNumer;

                tmpLosNum2 = rand() % 100;
                tmpNumer = g2LosKoord[tmpLosNum2];
                g2LosKoord[tmpLosNum2] = g2LosKoord[ROZMIAR_TABLICY * ROZMIAR_TABLICY - 1];
                g2LosKoord[ROZMIAR_TABLICY * ROZMIAR_TABLICY - 1] = tmpNumer;
            }

            int atakX, atakY;
            atakX = rand() % ROZMIAR_TABLICY;
            atakY = rand() % ROZMIAR_TABLICY;

            int i = 0;
            int k = 0;

            //generate random attack that hasn't already been guessed
            //pick from random numbers p1
            if (aktualnyGracz.getID() == 1) {
                atakX = g1LosKoord[i] / 10;
                atakY = g1LosKoord[i] % 10;
                i++;
            }
            else {
                atakX = g2LosKoord[i] / 10;
                atakY = g2LosKoord[i] % 10;
                k++;
            }
            //take turns
            std::cout << "Runda gracza nr " << aktualnyGracz.getID();
            std::cout <<  "\nStrzela w punkt: (" << atakX << ',' << atakY << ")\n";

            strzelaj(nastepnyGracz, atakX, atakY);
            std::cout << krawedz;

            tmpGracz = aktualnyGracz;
            aktualnyGracz = nastepnyGracz;
            nastepnyGracz = tmpGracz;

        }
        getchar(); getchar();

        system("cls");
    };

        //ostatni gracz, który zgadnie, wygra i zostanie przypisany do nastepnegoGracza
        std::cout << "\033[;92mGRACZ " << nastepnyGracz.getID() << " WYGRAL!!!!\nGRATULACJE!!!\033[0m\n";
        std::cout << "Czy chcesz zagrac ponownie (t/n)?\n: ";
        char ponownie = 'p';
        std::cin >> ponownie;
        do {
            std::cout << krawedz;
            if (ponownie == 't' || ponownie == 'T') { Gra(); }
            else if (ponownie == 'n' || ponownie == 'N') { return; }
            else {
                std::cout << "Nieprawid³owy wybor, sprobuj ponownie.\nZagraj ponownie (t/n)?\n: ";
                std::cin >> ponownie;
            }
        } while (ponownie != 't' || ponownie == 'T' || ponownie != 'n' || ponownie == 'N');
 
}