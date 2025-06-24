#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <fstream>
#include <chrono>
#include <iomanip>
#include "json.hpp" //para usar el archivo JSON
#include "include/utils.h"

using namespace std;
using json = nlohmann::json; // Para manejar JSON

const int TOTAL_CARTAS = 52;

struct Carta {
    int numero;
    string palo;
};

string nombreCarta(int valor) {
    switch (valor) {
        case 1: return "A";
        case 11: return "J";
        case 12: return "Q";
        case 13: return "K";
        default: return to_string(valor);
    }
}

string obtenerSimboloPalo(const string& palo) {
    if (palo == "Picas") return "♠";
    if (palo == "Treboles") return "♣";
    if (palo == "Corazones") return "♥";
    if (palo == "Diamantes") return "♦";
    return palo;
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

void mostrarCarta(Carta carta) {
    string simbolo = obtenerSimboloPalo(carta.palo);
    string color = (carta.palo == "Corazones" || carta.palo == "Diamantes") ? RED : WHITE;
    
    cout << "[" << nombreCarta(carta.numero) << " " << color << simbolo << RESET << "]";
}

int Valordecartas(Carta carta){
    if(carta.numero >= 10) return 10;
    if(carta.numero == 1) return 11;
    return carta.numero;
}

void mostrarMano(Carta mano[], int cantidad, bool ocultarPrimera = false) {
    for (int i = 0; i < cantidad; i++) {
        if (i > 0) cout << " ";
        if (ocultarPrimera && i == 0) {
            cout << "[?]";
        } else {
            mostrarCarta(mano[i]);
        }
    }
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

char mostrarMenuAcciones() {
    char opcion;
    do {
        askForInput("Actions: (h)it, (s)tand, (e)xit: ");
        cin >> opcion;
        opcion = tolower(opcion);
        if (opcion == 'h' || opcion == 's' || opcion == 'e') {
            return opcion;
        }
        printError("Invalid option. Please try again.");
    } while (true);
}

void mostrarEstadoJuego(Carta *dealer, int cantDealer, Carta *jugador, int cantJugador, bool ocultarPrimeraDealer = true) {
    clearScreen();
    printTitle("BLACKJACK");
    
    printSubTitle("\nDealer's hand:");
    mostrarMano(dealer, cantDealer, ocultarPrimeraDealer);
    if (!ocultarPrimeraDealer) {
        cout << "  (" << calcularPuntaje(dealer, cantDealer) << " points)" << endl;
    } else {
        cout << "  (?? points)" << endl;
    }
    
    printSubTitle("Your hand:");
    mostrarMano(jugador, cantJugador);
    cout << "  (" << calcularPuntaje(jugador, cantJugador) << " points)" << "\n" << endl;
}

void turnoJugador(Carta *&mano, int &cantidad, Carta mazo[], int &indiceMazo, Carta *dealer, int cantDealer, bool &juegoActivo) {
    char opcion;
    int puntaje;
    
    do {
        mostrarEstadoJuego(dealer, cantDealer, mano, cantidad);
        opcion = mostrarMenuAcciones();
        
        if (opcion == 'e') {
            juegoActivo = false;
            return;
        }

        if (opcion == 'h' || opcion == 'H') {
            agregarCarta(mano, cantidad, mazo[indiceMazo++]);
            puntaje = calcularPuntaje(mano, cantidad);
            
            if (puntaje > 21) {
                mostrarEstadoJuego(dealer, cantDealer, mano, cantidad);
                printError("BUSTED! You went over 21.");
                Sleep(1500);
                return;
            } else if (puntaje == 21) {
                mostrarEstadoJuego(dealer, cantDealer, mano, cantidad);
                printSuccess("BLACKJACK!");
                Sleep(1500);
                return;
            }
        }
    } while ((opcion == 'h' || opcion == 'H') && calcularPuntaje(mano, cantidad) < 21);
    
    mostrarEstadoJuego(dealer, cantDealer, mano, cantidad);
    if (opcion == 's' || opcion == 'S') {
        printInfo("You stand with your current hand.");
        Sleep(1000);
    }
}

void turnoDealer(Carta *&dealer, int &cantidad, Carta mazo[], int &indiceMazo, Carta *jugador, int cantJugador) {
    printInfo("Dealer's turn...");
    Sleep(1500);
    
    mostrarEstadoJuego(dealer, cantidad, jugador, cantJugador, false);
    
    while (calcularPuntaje(dealer, cantidad) < 17) {
        printInfo("Dealer hits...");
        Sleep(1500);
        
        agregarCarta(dealer, cantidad, mazo[indiceMazo++]);
        mostrarEstadoJuego(dealer, cantidad, jugador, cantJugador, false);
        
        if (calcularPuntaje(dealer, cantidad) > 21) {
            printError("Dealer BUSTED!");
            Sleep(1500);
            return;
        }
        
        if (calcularPuntaje(dealer, cantidad) >= 17) {
            printInfo("Dealer stands.");
            Sleep(1500);
            return;
        }
    }
}

void quiengana(Carta *jugador, int cantidaddeljugador, Carta *dealer, int cantidaddeldealer) {
    int puntajeJugador = calcularPuntaje(jugador, cantidaddeljugador);
    int puntajeDealer = calcularPuntaje(dealer, cantidaddeldealer);

    printTitle("FINAL RESULT");
    cout << "Your score: " << BOLD << puntajeJugador << RESET << endl;
    cout << "Dealer's score: " << BOLD << puntajeDealer << RESET << endl << endl;

    if (puntajeJugador > 21) {
        printError("You lose! You busted.");
    } else if (puntajeDealer > 21) {
        printSuccess("You win! Dealer busted.");
    } else if (puntajeJugador > puntajeDealer) {
        printSuccess("You win! You beat the dealer's hand.");
    } else if (puntajeJugador < puntajeDealer) {
        printError("You lose! Dealer has a better hand.");
    } else {
        printWarning("Push! It's a tie, your bet is returned.");
    }
}

// ------------ JSON PART STARTS HERE ------------------

string getCurrentDateTime() {
    auto now = chrono::system_clock::now();
    time_t timeNow = chrono::system_clock::to_time_t(now);
    tm localTime;
#ifdef _WIN32
    localtime_s(&localTime, &timeNow);
#else
    localtime_r(&timeNow, &localTime);
#endif
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &localTime);
    return string(buffer);
}

string cardToString(Carta carta) {
    return nombreCarta(carta.numero) + " " + obtenerSimboloPalo(carta.palo);
}

void saveGame(string playerName, Carta* player, int playerCount, Carta* dealer, int dealerCount, string result) {
    json game;

    game["date"] = getCurrentDateTime();
    game["player"]["name"] = playerName;

    for (int i = 0; i < playerCount; i++) {
        game["player"]["cards"].push_back(cardToString(player[i]));
    }

    for (int i = 0; i < dealerCount; i++) {
        game["dealer"]["cards"].push_back(cardToString(dealer[i]));
    }

    game["result"] = result;

    json history;
    ifstream inputFile("games.json");
    if (inputFile.is_open()) {
        try {
            inputFile >> history;
        } catch (...) {
            history = json::array();
        }
        inputFile.close();
    } else {
        history = json::array();
    }

    history.push_back(game);

    ofstream outputFile("games.json");
    outputFile << setw(4) << history;
    outputFile.close();
}

// ------------ JSON PART ENDS HERE ------------------

bool playGame(string playerName) {
    Carta mazo[TOTAL_CARTAS];
    generarCartas(mazo);
    mezclarVariasVeces(mazo, 5);
    
    Carta *jugador = new Carta[10];
    Carta *dealer = new Carta[10];
    int cantidadJugador = 0;
    int cantidadDealer = 0;
    int indiceMazo = 0;
    bool continuarJugando = true;
    
    for (int i = 0; i < 2; i++) {
        agregarCarta(jugador, cantidadJugador, mazo[indiceMazo++]);
        agregarCarta(dealer, cantidadDealer, mazo[indiceMazo++]);
    }
    
    mostrarEstadoJuego(dealer, cantidadDealer, jugador, cantidadJugador);
    
    turnoJugador(jugador, cantidadJugador, mazo, indiceMazo, dealer, cantidadDealer, continuarJugando);
    
    if (continuarJugando && calcularPuntaje(jugador, cantidadJugador) <= 21) {
        mostrarEstadoJuego(dealer, cantidadDealer, jugador, cantidadJugador, false);
        turnoDealer(dealer, cantidadDealer, mazo, indiceMazo, jugador, cantidadJugador);
        mostrarEstadoJuego(dealer, cantidadDealer, jugador, cantidadJugador, false);
        quiengana(jugador, cantidadJugador, dealer, cantidadDealer);
        Sleep(2000);
    }

    // Save game result
    string finalResult;
    int playerScore = calcularPuntaje(jugador, cantidadJugador);
    int dealerScore = calcularPuntaje(dealer, cantidadDealer);

    if (playerScore > 21) finalResult = "Player busted";
    else if (dealerScore > 21) finalResult = "Dealer busted - Player wins";
    else if (playerScore > dealerScore) finalResult = "Player wins";
    else if (playerScore < dealerScore) finalResult = "Dealer wins";
    else finalResult = "Draw";

    saveGame(playerName, jugador, cantidadJugador, dealer, cantidadDealer, finalResult);

    delete[] jugador;
    delete[] dealer;

    return continuarJugando;
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    
    srand(time(0));

    string playerName;
    printTitle("Welcome to Blackjack!");
    askForInput("Please enter your name: ");
    getline(cin, playerName);

    bool keepPlaying = true;
    
    while (keepPlaying) {
        clearScreen();
        printTitle("Starting game...");
        Sleep(1500);
        clearScreen();
        keepPlaying = playGame(playerName);
        
        if (keepPlaying) {
            printInfo("Starting a new game...");
            Sleep(1500);
        }
    }

    printInfo("Thanks for playing!");
    return 0;
}