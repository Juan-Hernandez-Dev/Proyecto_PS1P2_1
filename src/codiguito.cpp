#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>  // para shuffle
#include <random>     // para random_device y mt19937
using namespace std;

const int TOTAL_CARTAS = 52;

union ValorCarta {
    int numero;
    char simbolo;
};

struct Carta {
    ValorCarta valor;
    string palo;
};

string nombreCarta(int valor) {
    switch (valor) {
        case 1: return "As";
        case 11: return "J";
        case 12: return "Q";
        case 13: return "K";
        default: return to_string(valor);
    }
}

void generarCartas(Carta mazo[]) {
    string palos[] = {"Picas", "Treboles", "Corazones", "Diamantes"};
    int indice = 0;
    for (int i = 0; i < 4; i++) {
        for (int valor = 1; valor <= 13; valor++) {
            mazo[indice].valor.numero = valor;
            mazo[indice].palo = palos[i];
            indice++;
        }
    }
}

void mostrarCartas(Carta mazo[]) {
    for (int i = 0; i < TOTAL_CARTAS; i++) {
        cout << "Carta " << i + 1 << ": ";
        cout << nombreCarta(mazo[i].valor.numero) << " de " << mazo[i].palo << endl;
    }
}

void mezclarCartas(Carta mazo[]) {
    random_device rd;
    mt19937 g(rd());
    shuffle(mazo, mazo + TOTAL_CARTAS, g);
}

int main() {
    srand(time(0));
    Carta mazo[TOTAL_CARTAS];
    generarCartas(mazo);
    mezclarCartas(mazo);
    mostrarCartas(mazo);
    return 0;
}
