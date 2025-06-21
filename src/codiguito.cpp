#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>
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

void mezclarCartas(Carta mazo[]) {
    random_device rd;
    mt19937 g(rd());
    shuffle(mazo, mazo + TOTAL_CARTAS, g);
}

Carta robarCarta(Carta mazo[], int &cartasRestantes) {
    if (cartasRestantes == 0) {
        cout << "No quedan cartas en el mazo." << endl;
        exit(0);
    }
    return mazo[--cartasRestantes];
}

int main() {
    srand(time(0));
    Carta mazo[TOTAL_CARTAS];
    generarCartas(mazo);
    mezclarCartas(mazo);

    int cartasRestantes = TOTAL_CARTAS;
    int opcion;

    do {
        cout << "\nMenú:\n1. Robar carta\n2. Salir\nOpción: ";
        cin >> opcion;

        if (opcion == 1) {
            if (cartasRestantes > 0) {
                Carta robada = robarCarta(mazo, cartasRestantes);
                cout << "Robaste: " << nombreCarta(robada.valor.numero) << " de " << robada.palo << endl;
            } else {
                cout << "No quedan cartas en el mazo." << endl;
            }
        }
    } while (opcion != 2);

    cout << "Programa finalizado." << endl;
    return 0;
}
