#pragma once
using namespace std;
enum Stan { na_powierzchni = true, zatopiony = false };

class Statek {
public:
    Statek() { }
    Statek(string Nazwa, int Rozmiar, Stan Status, int NumerStatku) { nazwa = Nazwa; rozmiar = Rozmiar; status = Status; numerStatku = NumerStatku; }
    Statek(const Statek& data);
    ~Statek() { }
    
    int getRozmiar() { return rozmiar; }
    void setRozmiar(int Rozmiar) { rozmiar = Rozmiar; }
   
    string getNazwa() { return nazwa; }
    void setNazwa(string Nazwa) { nazwa = Nazwa; }
    
    bool getStatus() { return status; }
    void setStatus(Stan Status) { status = Status; }
    
    bool getNaCelowniku() { return naCelowniku; }
    void setNaCelowniku(bool c) { naCelowniku = c; }
    
    int getNumerStatku() { return numerStatku; }
    void setNumerStatku(int n) { numerStatku = n; }
    
    Statek& operator=(const Statek&);
    bool operator==(const Statek&);
    bool operator!=(const Statek&);

private:
    int numerStatku = -1;
    string nazwa = "";
    int rozmiar = 0;
    //true = zatopiony, false = na powierzchni
    Stan status = zatopiony;
    bool naCelowniku = false;
};
