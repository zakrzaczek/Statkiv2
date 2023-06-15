#pragma once

class Gracz {
public:
	Gracz() { }
	Gracz(int ID) { id = ID; }
	Gracz(string Typ, int ID) { typGracza = Typ; id = ID; }
	Gracz(const Gracz& data);
	
	std::string getTypGracza() { return typGracza; }
	void setTypGracza(std::string Typ) { typGracza = Typ; }
	
	int getID() { return id; }
	void setID(int ID) { id = ID; }
	
	bool getRunda() { return runda; }
	void setRunda(bool Runda) { runda = Runda; }
	
	Matryca& getMatryca() { return matrycaGracza; }
	
	Statek& operator()(int, int);
	Gracz& operator=(const Gracz& g);
	bool operator==(const Gracz& data);
	bool operator!=(const Gracz&);
private:
	Matryca matrycaGracza;
	std::string typGracza = "";
	int id = -1;
	bool runda = false;
};