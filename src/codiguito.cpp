#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>
#include <vector>
using namespace std;

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

vector<Carta> generarCartas() {
    vector<Carta> mazo;
    string palos[] = {"Picas", "Treboles", "Corazones", "Diamantes"};
    for (int i = 0; i < 4; i++) {
        for (int valor = 1; valor <= 13; valor++) {
            Carta c;
            c.valor.numero = valor;
            c.palo = palos[i];
            mazo.push_back(c);
        }
    }
    return mazo;
}

void mezclarCartas(vector<Carta> &mazo) {
    random_device rd;
    mt19937 g(rd());
    shuffle(mazo.begin(), mazo.end(), g);
}

Carta robarCarta(vector<Carta> &mazo) {
    Carta robada = mazo.back();
    mazo.pop_back();
    return robada;
}

int main() {
    srand(time(0));
    vector<Carta> mazo = generarCartas();
    mezclarCartas(mazo);
    int opcion;

    do {
        cout << "\nMenú:\n1. Robar carta\n2. Salir\nOpción: ";
        cin >> opcion;

        if (opcion == 1) {
            if (!mazo.empty()) {
                Carta robada = robarCarta(mazo);
                cout << "Robaste: " << nombreCarta(robada.valor.numero) << " de " << robada.palo << endl;
            } else {
                cout << "No quedan cartas en el mazo." << endl;
            }
        }
    } while (opcion != 2);

    cout << "Programa finalizado." << endl;
    return 0;
}
