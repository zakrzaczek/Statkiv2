#include <stdio.h>
#include "Biblioteki.h"

Statek::Statek(const Statek& data) {
    numerStatku = data.numerStatku;
    nazwa = data.nazwa;
    rozmiar = data.rozmiar;
    status = data.status;
    naCelowniku = data.naCelowniku;
}

Statek& Statek::operator=(const Statek& data) { //operator przypisania
    if (this != &data) {
        numerStatku = data.numerStatku;
        nazwa = data.nazwa;
        rozmiar = data.rozmiar;
        status = data.status;
        naCelowniku = data.naCelowniku;
    }
    return *this;
}

bool Statek::operator==(const Statek& data) { //operator rownosci
    if ((nazwa != data.nazwa) || (rozmiar != data.rozmiar) || (status != data.status)) {
        return false;
    }
    return true;
}

bool Statek::operator!=(const Statek& data) { //operator nierownosci
    return !(*this == data);
}