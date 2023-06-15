#include <stdio.h>
#include "Biblioteki.h"


Matryca::Matryca(const Matryca& data) {
    for (int i = 0; i < ROZMIAR_TABLICY; i++) {
        for (int k = 0; k < ROZMIAR_TABLICY; k++) {
            planszaGry[i][k] = data.planszaGry[i][k];
        }
    }
    for (int i = 0; i < liczbaStatkow; i++) {
        Statki[i] = data.Statki[i];
    }
}

void Matryca::wyswietlMatryce() {
    std::cout << "x = trafiony statek\no = statek na planszy\n~ = puste miejsce\n";
    std::cout << krawedz;
    std::cout << "\t  ";
        for (int i = 0; i < ROZMIAR_TABLICY; i++) {
            std::cout << alfabet[i];
            if (i != ROZMIAR_TABLICY - 1) { std::cout << ' '; }
        }
        std::cout << "\n";
        for (int j = 0; j < ROZMIAR_TABLICY; j++) {
            std::cout << "\t" << j << "\033[34;46m \033[0m";
            for (int k = 0; k < ROZMIAR_TABLICY; k++) {
                if (planszaGry[j][k].getNumerStatku() != -1 && planszaGry[j][k].getNaCelowniku()) {
                    std::cout << "\033[31;46mx\033[0m";
                }
                else if (!planszaGry[j][k].getStatus()) { std::cout << "\033[34;46m~\033[0m"; } //puste miejsca
                else { std::cout << "\033[93;46mo\033[0m"; } //statki na wodzie
                if (k != ROZMIAR_TABLICY - 1) { std::cout << "\033[34;46m \033[0m"; }
            }
            std::cout << "\n";
        }
        std::cout << krawedz;

}

void Matryca::wyswietlMatryce(int IdGracza) {
    std::cout << "x = trafiony statek\no = statek na planszy\n~ = puste miejsce\n";
    std::cout << krawedz;

    if (IdGracza == 1) {
        std::cout << "\t  ";
        for (int i = 0; i < ROZMIAR_TABLICY; i++) {
            std::cout << alfabet[i];
            if (i != ROZMIAR_TABLICY - 1) { std::cout << ' '; }
        }
        std::cout << "\n";
        for (int j = 0; j < ROZMIAR_TABLICY; j++) {
            std::cout << "\t" << j << "\033[34;46m \033[0m";
            for (int k = 0; k < ROZMIAR_TABLICY; k++) {
                if (planszaGry[j][k].getNumerStatku() != -1 && planszaGry[j][k].getNaCelowniku()) {
                    std::cout << "\033[31;46mx\033[0m";
                }
                else if (!planszaGry[j][k].getStatus()) { std::cout << "\033[34;46m~\033[0m"; } //puste miejsca
                else { std::cout << "\033[93;46mo\033[0m"; } //statki na wodzie
                if (k != ROZMIAR_TABLICY - 1) { std::cout << "\033[34;46m \033[0m"; }
            }
            std::cout << "\n";
        }
        std::cout << krawedz;
    }
    else {
        std::cout << "\t  ";
        for (int i = 0; i < ROZMIAR_TABLICY; i++) {
            std::cout << alfabet[i];
            if (i != ROZMIAR_TABLICY - 1) { std::cout << ' '; }
        }
        std::cout << "\n";
        for (int j = 0; j < ROZMIAR_TABLICY; j++) {
            std::cout << "\t" << j << "\033[34;46m \033[0m";
            for (int k = 0; k < ROZMIAR_TABLICY; k++) {
                if (planszaGry[j][k].getNumerStatku() != -1 && planszaGry[j][k].getNaCelowniku()) {
                    std::cout << "\033[31;46mx\033[0m";
                }
                else { std::cout << "\033[34;46m~\033[0m"; } //puste miejsca
                if (k != ROZMIAR_TABLICY - 1) { std::cout << "\033[34;46m \033[0m"; }
            }
            std::cout << "\n";
        }
        std::cout << krawedz;
    }
}

Matryca::Matryca() {
    Statki[0] = Statek("Czteromasztowiec", 4, zatopiony, 0);
    Statki[1] = Statek("Trzymasztowiec", 3, zatopiony, 1);
    Statki[2] = Statek("Dwumasztowiec", 2, zatopiony, 2);
}

Statek& Matryca::operator()(int x, int y) {
    return planszaGry[y][x];
}

//zwraca prawdê, jeœli wspó³rzêdne s¹ prawid³owym kierunkiem
bool Matryca::czyDobryKierunek(int x1, int y1, int x2, int y2) {
    if (x1 == x2 || y1 == y2) { return true; }
    return false;
}

//zwraca prawdê, jeœli zakres jest zajêty
bool Matryca::czyZajete(int x1, int y1, int x2, int y2) {
    //jeœli poziomo
    if (y1 == y2) {
        while (x1 != x2) {
            if (planszaGry[y1][x1].getStatus()) {
                return true;
            }
            if (x1 > x2) {
                x1--;
            }
            else {
                x1++;
            }
        }
        if (planszaGry[y1][x1].getStatus()) {
            return true;
        }
    }

    //jeœli pionowo
    else {
        while (y1 != y2) {
            if (planszaGry[y1][x1].getStatus()) {
                return true;
            }
            if (y1 > y2) {
                y1--;
            }
            else {
                y1++;
            }
        }
        if (planszaGry[y1][x1].getStatus()) {
            return true;
        }

    }
    return false;
}

bool Matryca::czySieZmiesci(int x1, int y1, int x2, int y2) {
    if ((x1 >= 0 && x1 < ROZMIAR_TABLICY) && (x2 >= 0 && x2 < ROZMIAR_TABLICY) && (y1 >= 0 && y1 < ROZMIAR_TABLICY) && (y2 >= 0 && y2 < ROZMIAR_TABLICY)) { return true; }
    return false;
}

bool Matryca::czyZatonal(int numerStatku) {
    return !Statki[numerStatku].getStatus();
}

bool Matryca::czyWszystkieStUmieszczone() {
    for (int i = 0; i < liczbaStatkow; i++) {
        if (!Statki[i].getStatus()) {
            return false;
        }
    }
    return true;
}

bool Matryca::czyWszystkieStZatopione() {
    for (int i = 0; i < ROZMIAR_TABLICY; i++) {
        for (int k = 0; k < ROZMIAR_TABLICY; k++) {
            if (planszaGry[i][k].getStatus()) {
                return false;
            }
        }
    }
    return true;
}

bool Matryca::operator==(const Matryca& data) {
    for (int i = 0; i < ROZMIAR_TABLICY; i++) {
        for (int k = 0; k < ROZMIAR_TABLICY; k++) {
            if (planszaGry[i][k] != data.planszaGry[i][k]) {
                return false;
            }
        }
    }
    for (int r = 0; r < liczbaStatkow; r++) {
        if (Statki[r] != data.Statki[r]) {
            return false;
        }
    }
    return true;
}

bool Matryca::operator!=(const Matryca& data) {
    return !(*this == data);
}

Matryca& Matryca::operator=(const Matryca& data) {
    if (this != &data) {
        for (int i = 0; i < ROZMIAR_TABLICY; i++) {
            for (int k = 0; k < ROZMIAR_TABLICY; k++) {
                planszaGry[i][k] = data.planszaGry[i][k];
            }
        }
        for (int i = 0; i < liczbaStatkow; i++) {
            Statki[i] = data.Statki[i];
        }
    }
    return *this;
}

void Matryca::setStatek(int numerStatku, int x1, int y1, int x2, int y2) {
    //sprawdŸ najpierw, czy jest poprawne umieszczenie
    if (!czyZajete(x1, y1, x2, y2) && czySieZmiesci(x1, y1, x2, y2) && czyDobryKierunek(x1, y1, x2, y2)) {
        Statek statekDoUmieszczenia = Statek(Statki[numerStatku].getNazwa(), Statki[numerStatku].getRozmiar(), na_powierzchni, numerStatku);
        //umieœæ statek
        while ((x1 != x2 || y1 != y2)) {
            planszaGry[y1][x1] = statekDoUmieszczenia;
            planszaGry[y1][x1].setNumerStatku(numerStatku);
            if (x1 > x2) {
                x1--;
            }
            else if (x2 > x1) {
                x1++;
            }
            else if (y1 > y2) {
                y1--;
            }
            else if (y2 > y1) {
                y1++;
            }
        }
        planszaGry[y1][x1] = statekDoUmieszczenia;
        Statki[numerStatku].setStatus(na_powierzchni);
    }
    else {
        return;
    }
}

void Matryca::losowoUstawFlote() {
    srand(static_cast<unsigned int>(time(NULL)));
    for (int i = 0; i < liczbaStatkow; i++) {
        int startX = rand() % ROZMIAR_TABLICY;
        int startY = rand() % ROZMIAR_TABLICY;
        int endX = startX;
        int endY = startY;

        //w pionie
            if (rand() % 2 == 0) {
                //w górê
                if (rand() % 2 == 0) {
                    endX -= (Statki[i].getRozmiar() - 1);
                }
                //w dó³
                else {
                    endX += (Statki[i].getRozmiar() - 1);
                }
            }
        //w poziomie
            else {
                //w lewo
                if (rand() % 2 == 0) {
                    endY -= (Statki[i].getRozmiar() - 1);
                }
                //w prawo
                else {
                    endY += (Statki[i].getRozmiar() - 1);
                }
            }
        setStatek(i, startX, startY, endX, endY);
        //nie zwiêkszaj i, jeœli statek nie jest umieszczony
        if (!Statki[i].getStatus()) {
            i--;
        }
    }
}

void Matryca::wyswietlPozostaleStatki() {
    for (int i = 0; i < liczbaStatkow; i++) {
        if (!Statki[i].getStatus()) {
            std::cout << "Numer: " << i << "\tNazwa: " << Statki[i].getNazwa() << "\tRozmiar: " << Statki[i].getRozmiar() << "\n";
        }
    }
}
