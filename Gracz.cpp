#include "Biblioteki.h"

Statek& Gracz::operator()(int x, int y) {
	return getMatryca()(y, x);
}

Gracz& Gracz::operator=(const Gracz& data) {
	if (this != &data) {
		typGracza = data.typGracza;
		id = data.id;
		runda = data.runda;
		matrycaGracza = data.matrycaGracza;
	}
	return *this;
}

Gracz::Gracz(const Gracz& data) {
	typGracza = data.typGracza;
	id = data.id;
	runda = data.runda;
	matrycaGracza = data.matrycaGracza;
}

bool Gracz::operator==(const Gracz& data) {
	if ((matrycaGracza != data.matrycaGracza) || (typGracza != data.typGracza) || (id != data.id) || (runda != data.runda)) {
		return false;
	}
	return true;
}

bool Gracz::operator!=(const Gracz& data) {
	return !(*this == data);
}