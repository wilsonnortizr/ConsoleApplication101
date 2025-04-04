
#include <iostream>
#include <ctime>  // Usamos esta libreria para el temporizador
#include <algorithm>  // Necesario para usar max y min
#include <thread>     // Para crear hilos de ejecución para los temporizadores
#include <chrono>     // Para controlar los tiempos

using namespace std;
using namespace std::chrono;

// Variables para control de temporizadores
bool tenerHambre = false;
bool necesitaDefecar = false;
bool estaJugando = false;
int energiaGlobal = 50; // Variable global para compartir la energía entre hilos

// Función para el temporizador de hambre (4 segundos)
void temporizadorHambre() {
    while (true) {
        if (tenerHambre) {
            this_thread::sleep_for(seconds(4));
            cout << "\n¡Tu mascota tiene hambre de nuevo!" << endl;
            tenerHambre = false;  // Reiniciar para evitar múltiples mensajes
        }
        this_thread::sleep_for(milliseconds(500));  // Verificar cada medio segundo
    }
}

// Función para el temporizador de necesidades (5 segundos)
void temporizadorNecesidades() {
    while (true) {
        if (necesitaDefecar) {
            this_thread::sleep_for(seconds(5));
            cout << "\n¡Tu mascota necesita defecar otra vez!" << endl;
            necesitaDefecar = false;  // Reiniciar para evitar múltiples mensajes
        }
        this_thread::sleep_for(milliseconds(500));  // Verificar cada medio segundo
    }
}

// Función para la pérdida de energía mientras juega
void perderEnergiaJugando() {
    while (true) {
        if (estaJugando) {
            this_thread::sleep_for(seconds(2));  // Cada 2 segundos pierde energía
            energiaGlobal = max(0, energiaGlobal - 5);  // Pierde 5 puntos de energía
            cout << "\nTu mascota está perdiendo energía mientras juega. Energía actual: " << energiaGlobal << endl;
        }
        this_thread::sleep_for(milliseconds(500));  // Verificar cada medio segundo
    }
}

// Funcion de limpieza de pantalla
void limpiarPantalla() {
    cout << "\033[2J\033[H";
}

// Funcion para agregar retrasos cortos (efectos de animacion basicos)
void esperar(int milisegundos) {
    clock_t startTime = clock();
    while (clock() < startTime + milisegundos * (CLOCKS_PER_SEC / 1000)) {
        // Esperar hasta que haya pasado el tiempo (corregido para usar CLOCKS_PER_SEC)
    }
}

// Funcion para mostrar texto con animacion
void textoAnimado(const string& texto, int velocidad = 30) {
    for (char c : texto) {
        cout << c << flush;
        esperar(velocidad);
    }
    cout << endl;
}

// Funcion para volver al menu principal (faltaba esta definicion)
void volverAlMenu() {
    cout << "\nPresiona Enter para volver al menu principal...";
    cin.ignore();
    cin.get();
}

// Funcion para mostrar el dibujo del perro en la pantalla de inicio
void mostrarPerroInicial() {
    cout << "     / \\ \n";
    cout << "    (    @\\_\n";
    cout << "    /         O\n";
    cout << "   /   (_____ / \n";
    cout << "  /_/    U\n";
    cout << "  /      \\  |   \n";
    cout << " /        \\ |    \n";
    cout << "(          )|     \n";
    cout << " \\/        |   \n";
}

// Funcion para mostrar un dibujo dependiendo de la accion seleccionada
void mostrarDibujo(string estado) {
    if (estado == "comiendo") {
        // Perro comiendo
        cout << "   /\\  /\\\n";
        cout << "  ( o  o )\n";
        cout << "   |  ^  |  <-- Estoy comiendo! \n";
        cout << "   | --- |\n";
        cout << "  /|     |\\\n";
        cout << " / |_| \\\n";
        cout << "   \\_/ \n";
        cout << "    / | \\ \n";
        cout << "   Que rico esta! \n";
    }
    else if (estado == "durmiendo") {
        // Perro durmiendo
        cout << "   /\\  /\\\n";
        cout << "  ( -  - )\n";
        cout << "   | ZZZ |\n";
        cout << "   | --- |\n";
        cout << "  /|     |\\\n";
        cout << " / |_| \\\n";
        cout << "   \\_/ \n";
        cout << "   Zzz... durmiendo! \n";
    }
    else if (estado == "jugando") {
        // Perro jugando (remodelado de lado)
        cout << "    /\\_/\\        \n";
        cout << "   (  o.o )       \n";
        cout << "   |  (_) |        \n";
        cout << "  /        \\       \n";
        cout << " / |     | \\      \n";
        cout << "(/|     | ()     \n";
        cout << "  |  |  |    \n";
        cout << " |         |  \n";
        cout << " \\   ||  /   \n";
        cout << "| \\  |  | / \n";
        cout << "      .    .        < --Estoy jugando!\n";
    }
    else if (estado == "defecando") {
        // Perro defecando
        cout << "   /\\  /\\\n";
        cout << "  ( o  o )\n";
        cout << "   |  X  |  <-- Haciendo mis necesidades! \n";
        cout << "   | --- |\n";
        cout << "  /|     |\\\n";
        cout << " / |_| \\\n";
        cout << "   \\_/\n";
        cout << "   / | | \\ \n";
        cout << "   Mucho mejor ahora! \n";
    }
    else {
        // Perro en estado normal
        cout << "   /\\  /\\\n";
        cout << "  ( o  o )\n";
        cout << "   |  ^  |  <-- Soy un perro feliz! \n";
        cout << "   |-- |\n";
        cout << "  /|     |\\\n";
        cout << " / |_| \\\n";
        cout << "   \\_/ \n";
        cout << "   / | | \\ \n";
        cout << "   Juguemos juntos! \n";
    }
}

// Clase Mascota
class Mascota {
private:
    string nombre;
    int hambre;
    int felicidad;
    string estadoActual;

    const int MAX_ENERGIA = 100;
    const int MAX_FELICIDAD = 100;
    const int MAX_HAMBRE = 100;

public:
    // Constructor
    Mascota(string nombreMascota) {
        nombre = nombreMascota;
        energiaGlobal = 50;  // Usar la variable global
        hambre = 50;
        felicidad = 50;
        estadoActual = "normal";
    }

    // Metodo getter para el nombre
    string getNombre() const {
        return nombre;
    }

    // Metodo para actualizar energía desde la variable global
    void actualizarEnergia() {
        // La energía se lee directamente de la variable global
    }

    // Metodo para comer
    void comer() {
        limpiarPantalla();
        textoAnimado("HORA DE COMER", 50);

        // Mostrar opciones de comida
        int opcionComida;
        cout << "------------------------------------\n";
        cout << "Que comida quieres darle a " << nombre << "?\n";
        cout << "------------------------------------\n";
        cout << "[1] Concentrado\n";
        cout << "[2] Huesos\n";
        cout << "[3] Carne fresca\n";
        cout << "[4] Otros\n";
        cout << "Selecciona una opcion (1-4): ";
        cin >> opcionComida;

        switch (opcionComida) {
        case 1:
            textoAnimado("Yummy! Concentrado delicioso!");
            break;
        case 2:
            textoAnimado("Mmm! Le encantan los huesos!");
            break;
        case 3:
            textoAnimado("Rico! Carne fresca!");
            break;
        case 4:
            textoAnimado("Ups! No tengo idea que es esto, pero lo probare!");
            break;
        default:
            textoAnimado("Opcion no valida. Vamos a darle comida normal.");
            break;
        }

        // Mostrar dibujo del perro comiendo
        mostrarDibujo("comiendo");

        hambre = max(0, hambre - 20);
        energiaGlobal = min(MAX_ENERGIA, energiaGlobal + 15);
        felicidad = min(MAX_FELICIDAD, felicidad + 5);
        estadoActual = "comiendo";

        // Activar el temporizador para tener hambre de nuevo
        tenerHambre = true;

        textoAnimado("\n  Woof! Gracias por alimentarme, humano!");
        volverAlMenu();
    }

    // Metodo para jugar
    void jugar() {
        limpiarPantalla();
        textoAnimado("HORA DE JUGAR", 50);

        // Mostrar opciones de juegos
        int opcionJuego;
        cout << "------------------------------------\n";
        cout << "Que tipo de juego quieres hacer con " << nombre << "?\n";
        cout << "------------------------------------\n";
        cout << "[1] Lanzar la pelota\n";
        cout << "[2] Jugar con el palo\n";
        cout << "[3] Jugar a otros juegos\n";
        cout << "Selecciona una opcion (1-3): ";
        cin >> opcionJuego;

        switch (opcionJuego) {
        case 1:
            textoAnimado("Vamos a lanzar la pelota!");
            break;
        case 2:
            textoAnimado("Juguemos con el palo!");
            break;
        case 3:
            textoAnimado("Vamos a inventar otro juego!");
            break;
        default:
            textoAnimado("Opcion no valida. Vamos a jugar de todos modos.");
            break;
        }

        // Mostrar dibujo del perro jugando
        mostrarDibujo("jugando");

        if (energiaGlobal >= 10) {
            energiaGlobal = max(0, energiaGlobal - 10);
            felicidad = min(MAX_FELICIDAD, felicidad + 20);
            hambre = min(MAX_HAMBRE, hambre + 10);
            estadoActual = "jugando";

            // Activar el temporizador de pérdida de energía mientras juega
            estaJugando = true;

            textoAnimado("\n  Woof! Woof! Esto es muy divertido!");
        }
        else {
            estadoActual = "triste";
            textoAnimado("\n  Woof... Estoy muy cansado. Podriamos descansar un poco?");
        }

        volverAlMenu();
        // Desactivar el juego cuando volvamos al menú
        estaJugando = false;
    }

    // Metodo para dormir
    void dormir() {
        limpiarPantalla();
        cout << "------------------------------------\n";
        textoAnimado("HORA DE DORMIR", 50);
        cout << "------------------------------------\n";

        // Mostrar dibujo del perro durmiendo
        mostrarDibujo("durmiendo");

        energiaGlobal = min(MAX_ENERGIA, energiaGlobal + 30);
        hambre = min(MAX_HAMBRE, hambre + 5);
        estadoActual = "durmiendo";

        textoAnimado("\n  Zzz... Ronquidos adorables de perro!");
        volverAlMenu();
    }

    // Metodo para defecar afuera
    void defecar() {
        limpiarPantalla();
        cout << "------------------------------------\n";
        textoAnimado("HORA DE DEFECAR", 50);
        cout << "------------------------------------\n";

        // Mostrar dibujo del perro defecando
        mostrarDibujo("defecando");

        felicidad = max(0, felicidad - 5);
        hambre = max(0, hambre + 10);
        energiaGlobal = max(0, energiaGlobal - 5);
        estadoActual = "defecando";

        // Activar el temporizador para necesitar defecar de nuevo
        necesitaDefecar = true;

        textoAnimado("\n  Ahh, mucho mejor! Ahora me siento mas ligero.");
        volverAlMenu();
    }

    // Metodo para mostrar estado
    void mostrarEstado() {
        limpiarPantalla();
        cout << "------------------------------------\n";
        textoAnimado("ESTADO DE " + nombre, 50);
        cout << "------------------------------------\n";

        // Mostrar el estado actual con su dibujo
        mostrarDibujo(estadoActual);

        cout << "\n  Estado actual: " << estadoActual << endl;
        cout << "  Nombre: " << nombre << " (El Super Canino)" << endl;
        cout << "  Energia:   " << energiaGlobal << "/100" << endl;
        cout << "  Hambre:    " << hambre << "/100" << endl;
        cout << "  Felicidad: " << felicidad << "/100" << endl;

        if (hambre > 70) {
            textoAnimado("\"Woof! Tengo mucha hambre, me das algo de comer?\"");
        }
        else if (energiaGlobal < 30) {
            textoAnimado("\"Bostezo... Estoy muy cansado, necesito una siesta.\"");
        }
        else if (felicidad < 30) {
            textoAnimado("\"Estoy un poco triste, jugamos un rato?\"");
        }
        else {
            textoAnimado("\"Me siento genial! Que quieres hacer hoy?\"");
        }

        volverAlMenu();
    }
};

// Funcion principal
int main() {
    limpiarPantalla();
    cout << "==================================================\n";
    textoAnimado(" BIENVENIDO A TU MASCOTA VIRTUAL CANINA", 50);
    cout << "==================================================\n";

    // Mostrar el dibujo del perro al inicio
    cout << "\nEste es tu perro:\n\n";
    mostrarPerroInicial();
    cout << "\n";

    textoAnimado("Crea y cuida de tu propio perro virtual!");

    // Pedir nombre para la mascota
    string nombreMascota;
    cout << "Que nombre quieres darle a tu mascota?: ";
    cin >> nombreMascota;

    // Crear la mascota
    Mascota miMascota(nombreMascota);
    textoAnimado(nombreMascota + " ha nacido! Cuidalo bien!");

    // Iniciar los temporizadores en hilos separados
    thread hiloHambre(temporizadorHambre);
    thread hiloNecesidades(temporizadorNecesidades);
    thread hiloJuego(perderEnergiaJugando);

    // Desconectar los hilos para que se ejecuten independientemente
    hiloHambre.detach();
    hiloNecesidades.detach();
    hiloJuego.detach();

    int opcion = 0;
    while (opcion != 6) {
        limpiarPantalla();
        cout << "==================================================\n";
        cout << " MASCOTA VIRTUAL: " << miMascota.getNombre() << "\n";
        cout << "==================================================\n";

        // Mostrar el perro al inicio del menú
        mostrarPerroInicial();
        cout << "\n";

        cout << "[1] Alimentar\n";
        cout << "[2] Jugar\n";
        cout << "[3] Dormir\n";
        cout << "[4] Defecar\n";
        cout << "[5] Ver estado\n";
        cout << "[6] Salir\n";
        cout << "Selecciona una opcion (1-6): ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            miMascota.comer();
            break;
        case 2:
            miMascota.jugar();
            break;
        case 3:
            miMascota.dormir();
            break;
        case 4:
            miMascota.defecar();
            break;
        case 5:
            miMascota.mostrarEstado();
            break;
        case 6:
            limpiarPantalla();
            textoAnimado("Gracias por jugar! Hasta pronto!");
            break;
        default:
            cout << "Opcion no valida. Intentalo de nuevo." << endl;
            esperar(1000);
            break;
        }
    }

    return 0;
}