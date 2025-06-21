#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
using namespace std;

const int TOTAL_CARTAS = 52;

struct Carta {
    int numero;
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
    for (int i = 0; i < 4; i++) {
        for (int valor = 1; valor <= 13; valor++) {
            mazo[indice].numero = valor;
            mazo[indice].palo = palos[i];
            indice++;
        }
    }
}

void mergeShuffleMitadesAleatorio(Carta mazo[]) {
    Carta copia[TOTAL_CARTAS];
    int mitad = TOTAL_CARTAS / 2;
    int izquierda = 0;
    int derecha = mitad;
    int k = 0;
    while (izquierda < mitad && derecha < TOTAL_CARTAS) {
        if (rand()%2 == 0) {
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

void mostrarCarta(Carta carta){
    cout << nombreCarta(carta.numero) << " de " << carta.palo << endl;
}

int Valordecartas(Carta carta){
    if(carta.numero >= 10) return 10;
    if(carta.numero == 1) return 11;
    return carta.numero;
}

void mostrarMano(Carta mano[], int cantidad, bool ocultarPrimera = false) {
    for (int i = 0; i < cantidad; i++) {
        if (i == 0 && ocultarPrimera) {
            cout << "[Carta Oculta] ";
        } else {
            mostrarCarta(mano[i]);
            cout << " ";
        }
    }
    cout << endl;
}

int calcularPuntaje(Carta mano[], int cantidad) {
    int total = 0;
    int ases = 0;
    for (int i = 0; i < cantidad; i++) {
        int valor = Valordecartas(mano[i]);
        total += valor;
        if (mano[i].numero == 1) ases++;
    }
    while (total > 21 && ases > 0) {
        total -= 10;
        ases--;
    }
    return total;
}   

void agregarCarta(Carta *&mano, int &cantidad, Carta carta){
    Carta *nuevaMano = new Carta[cantidad + 1];
    for (int i = 0; i < cantidad; i++) {
        nuevaMano[i] = mano[i];
    }
    nuevaMano[cantidad] = carta;
    delete[] mano;
    mano = nuevaMano;
    cantidad++;
}

void turnoJugador(Carta *&mano, int &cantidad, Carta mazo[], int &indiceMazo){
    char opcion;
    while (true){
        cout << "Cartas del jugador: ";
        mostrarMano(mano, cantidad);
        cout << "Sus puntos son: " << calcularPuntaje(mano, cantidad) << endl;
        cout << "Si quiere otra carta oprima (h) hit o si se queda con las que tiene oprima (s) stand: ";
        cin >> opcion;
        if (opcion == 'h'){
            agregarCarta(mano, cantidad, mazo[indiceMazo++]);
            if (calcularPuntaje(mano, cantidad) > 21){
                cout << "Usted se pasó de 21." << endl;
                break;
            }
        } else if (opcion == 's'){
            break;
        } else {
            cout << "Opción no válida." << endl;
        }
    }
}

void turnoDealer(Carta *&dealer, int &cantidad, Carta mazo[], int &indiceMazo){
    cout << "Es el turno del dealer" << endl;
    while (calcularPuntaje(dealer, cantidad) < 17){
        agregarCarta(dealer, cantidad, mazo[indiceMazo++]);
    }
    cout << "Las cartas del dealer son: " << endl;
    mostrarMano(dealer, cantidad);
    cout << "El puntaje del dealer es: " << calcularPuntaje(dealer, cantidad) << endl;
}

void quiengana(Carta *jugador, int cantidaddeljugador, Carta *dealer, int cantidaddeldealer){
    int puntajedeljugador = calcularPuntaje(jugador, cantidaddeljugador);
    int puntajedeldealer = calcularPuntaje(dealer, cantidaddeldealer);

    if (puntajedeljugador > 21) {
        cout << "El jugador sacó más de 21, el dealer gana" << endl;
    } else if (puntajedeldealer > 21) {
        cout << "El dealer sacó más de 21, el jugador gana" << endl;
    } else if (puntajedeljugador > puntajedeldealer){
        cout << "El jugador gana" << endl;
    } else if (puntajedeljugador < puntajedeldealer){
        cout << "El dealer gana" << endl;
    } else {
        cout << "Ambos ganan" << endl;
    }
}

int main() {
    srand(time(0));
    SetConsoleOutputCP(CP_UTF8);
    string nombreJugador;

    cout << "Bienvenido al Blackjack ." << endl;
    cout << "Por favor, ingrese su nombre: ";
    cin.ignore();
    getline(cin, nombreJugador);

    char iniciarotrapartida = 's';
    do { 
        Carta mazo[TOTAL_CARTAS];
        generarCartas(mazo);
        mezclarVariasVeces(mazo, 3);
        int indiceMazo = 0;
        
        Carta *jugador = new Carta[0];
        int cantidaddeljugador = 0;        
        Carta *dealer = new Carta[0];
        int cantidaddeldealer = 0;
        
        agregarCarta(jugador, cantidaddeljugador, mazo[indiceMazo++]);
        agregarCarta(jugador, cantidaddeljugador, mazo[indiceMazo++]);
        agregarCarta(dealer, cantidaddeldealer, mazo[indiceMazo++]);
        agregarCarta(dealer, cantidaddeldealer, mazo[indiceMazo++]);
        
        cout << "Cartas del jugador: " << endl;
        mostrarMano(jugador, cantidaddeljugador);
        cout << "Cartas del dealer: " << endl;
        mostrarMano(dealer, cantidaddeldealer, true);

        turnoJugador(jugador, cantidaddeljugador, mazo, indiceMazo);
        if(calcularPuntaje(jugador, cantidaddeljugador) <= 21){
            turnoDealer(dealer, cantidaddeldealer, mazo, indiceMazo);
        }
        quiengana(jugador, cantidaddeljugador, dealer, cantidaddeldealer);
        
        delete[] jugador;
        delete[] dealer;

        cout << "¿Desea jugar una nueva partida? (s/n): ";
        cin >> iniciarotrapartida;
    } while (iniciarotrapartida == 's' || iniciarotrapartida == 'S');
    
    cout << "Gracias por jugar a nuestro 21, que tenga lindo día " << endl;
    return 0;
}