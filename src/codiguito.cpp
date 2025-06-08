#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

const int TOTAL_CARTAS = 56;

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
    int indice = 0;
    string palos[] = {"Picas", "Treboles", "Corazones", "Diamantes"};

    for (int m = 0; m < 4; m++) {
        for (int i = 0; i < 4; i++) {
            for (int valor = 1; valor <= 13; valor++) {
                if (indice < TOTAL_CARTAS) {
                    mazo[indice].valor.numero = valor;
                    mazo[indice].palo = palos[i];
                    indice++;
                }
            }
        }
    }

    while (indice < TOTAL_CARTAS) {
        mazo[indice].valor.numero = 1;
        mazo[indice].palo = palos[indice % 4];
        indice++;
    }
}

void mostrarCartas(Carta mazo[]) {
    for (int i = 0; i < TOTAL_CARTAS; i++) {
        cout << "Carta " << i + 1 << ": ";
        cout << nombreCarta(mazo[i].valor.numero) << " de " << mazo[i].palo << endl;
    }
}
void mergeShuffleMitadesAleatorio(Carta mazo[]) {
    Carta copia[TOTAL_CARTAS];
    int mitad = TOTAL_CARTAS / 2;
    int izquierda = 0;
    int derecha = mitad;
    int k = 0;

    while (izquierda < mitad && derecha < TOTAL_CARTAS) {
        if (rand() % 2 == 0) {
            copia[k++] = mazo[izquierda++];
        } else {
            copia[k++] = mazo[derecha++];
        }
    }

    while (izquierda < mitad) copia[k++] = mazo[izquierda++];
    while (derecha < TOTAL_CARTAS) copia[k++] = mazo[derecha++];

    for (int i = 0; i < TOTAL_CARTAS; i++) {
        mazo[i] = copia[i];
    }
}
void mezclarVariasVeces(Carta mazo[], int repeticiones) {
    for (int i = 0; i < repeticiones; i++) {
        mergeShuffleMitadesAleatorio(mazo);
    }
}
int main() {
    srand(time(0));
    Carta mazo[TOTAL_CARTAS];
    generarCartas(mazo);
    mezclarVariasVeces(mazo, 3);
    mostrarCartas(mazo);
    return 0;
}