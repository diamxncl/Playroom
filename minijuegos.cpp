#include <iostream>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <fstream>
#include <string>

using namespace std;

//! INICIO FUNCIONES LOGIN

int player_score = 0;
int user_id = 0;
string user;

void user_registry() {
    string nombre, contraseña;

    //! ABRIMOS EL ARCHIVO DONDE SE AÑADIRAN LOS CAMPOS USUARIO, CONTRASEÑA

    ofstream writefile("./database/user_database_temp.txt");

    //! DETECCIÓN DE UN POSIBLE ERROR DE CARGA

    if (!writefile) {
        cout << "Error: No ha sido posible abrir la base de datos de los usuarios." << endl;
    }

    system("clear");
    system("figlet Registro");
    cout << endl;

    //! INTRODUCCIÓN DE DATOS

    cout << "Ingrese el nombre de usuario: "; cin >> nombre;
    cout << "Ingrese la contraseña: "; cin >> contraseña;

    writefile << nombre << endl;
    writefile << contraseña << endl;
    writefile << 0 << endl << endl << endl << endl;

    writefile.close();

    //! AÑADIR LOS NUEVOS REGISTROS A LA BASE DE DATOS

    system("cat ./database/user_database_temp.txt >> ./database/user_database.txt");

    cout << "Inicie sesión a continuación..." << endl;
    sleep(1);
}

bool user_login(int ola = 0) {
    int nomb = 1, contras = 1, login_count = 0, punt = 1;
    string nombres[100], contraseñas[100], user_login_var, password_login, puntuacion[100];
    bool loged_in = false;
    bool registrado = false;


    //* CARGAR BASE DE DATOS A USAR
    ifstream readfile("./database/user_database.txt");
    ofstream writefile("./database/user_database_temp.txt");

    if (!readfile || !writefile) {
        cout << "Error: No ha sido posible abrir la base de datos de los usuarios." << endl;
    }

    //- LECTURA DE DATOS DE LA BASE DE DATOS
    for (int i = 1; i == i; i++) {
        if (i % 3 == 0) {
            readfile >> puntuacion[punt];
            if (puntuacion[punt] == "") {
                break;
            }
            i += 3;
            punt++;
        }
        else if (i % 2 == 0) {
            readfile >> contraseñas[contras];
            if (contraseñas[contras] == "" && nombres[nomb] == "") {
                break;
            }
            contras++;
        }
        else {
            readfile >> nombres[nomb];
            if (contraseñas[contras] == "" && nombres[nomb] == "") {
                break;
            }
            nomb++;
        }
        if (contras > 99 || nomb > 99) {
            system("clear");
            system("figlet Error");
            cout << "La base de datos está completa, hay más de " << contras << " registros." << endl << endl << "Vacíe el archivo user_database.txt, o póngase contacto con el desarrolador del programa." << endl;
            sleep(4);
        }
    }

    if (ola == 1) {
        //! CONVERSIÓN NUEVA BASE DE DATOS A LA ANTIGUA
        puntuacion[user_id] = to_string(player_score);

        for (int i = 1; i < nomb; i++) {
            writefile << nombres[i] << endl;
            writefile << contraseñas[i] << endl;
            writefile << puntuacion[i] << endl << endl << endl << endl;
        }

        sleep(1);

        system("cat ./database/user_database_temp.txt > ./database/user_database.txt");
    }

    else if (ola == 2) {
        cout << endl << "------[ Puntuaciones ]------" << endl << endl;
        for (int i = 0; i < 10; i++) {
            if (!nombres[i].empty()) {
                cout << "---> " << nombres[i] << ": " << puntuacion[i] << " puntos." << endl;
            }
        }
    }

    else {
        //! INICIO DE SESIÓN

        for (int r = 0; r == r; r++) {
            system("clear");
            system("figlet Iniciar Sesion");
            if (login_count == 3) {
                cout << "Demasiados intentos introducidos, ¿Desea crear una cuenta? (S/N)" << endl;
                if (getch() == 'S' || getch() == 's') {
                    user_registry();
                    registrado = true;
                }
                else {
                    user_login();
                }
                break;
            }
            if (login_count > 0) { 
                cout << "Usuario o contraseña incorrectos, vuelva a iniciar sesión." << endl << endl;
            }
            cout << "Nombre de usuario: "; cin >> user_login_var;
            cout << "Contraseña: "; cin >> password_login;
            for (int i = 1; i <= contras; i++) {
                if (user_login_var == nombres[i] && password_login == contraseñas[i]) {
                    loged_in = true;
                    cout << endl << "Ha iniciado sesión como " << nombres[i] << endl;
                    user_id = i;
                    user = nombres[i];
                    sleep(1);
                    break;
                }
            }
            if (loged_in) {
                break;
            }
            if (!loged_in) {
                login_count++;
            }
        }
    }

    readfile.close();
    writefile.close();

    player_score = stoi(puntuacion[user_id].c_str());

    if (registrado) {
        return true;
    }
    else if (!registrado) {
        return false;
    }
    else if (loged_in) {
        return false;
    }
    else {
        return false;
    }
}

//! FIN FUNCIONES LOGIN

//! FUNCIONES 4 EN RAYA
void mostrar_tablero_visible_4(string arr[6][7]) {
        for (int i = 0; i < 6; i++) {
        cout << i << " | ";
        for (int j = 0; j < 7; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << "--+---------------\n";
    cout << "  | 0 1 2 3 4 5 6\n";
}

void mostrar_tablero_real_4(int arr2[6][7]) {
    for (int i = 0; i < 6; i++) {
        cout << i << " | ";
        for (int j = 0; j < 7; j++) {
            cout << arr2[i][j] << " ";
        }
        cout << endl;
    }
    cout << "--+---------------\n";
    cout << "  | 0 1 2 3 4 5 6\n";
}

void mostrar_elegir_columna (string arr[7]) {
    cout << "  | ";
    for (int i = 0; i < 7; i++) { 
        cout << arr[i] << " ";
    }
    cout << "\n--+---------------\n";
}
//! FIN FUNCIONES 4 EN RAYA

//! FUNCIONES HUNDIR LA FLOTA
void mostrar_tablero_visible(string arr[6][6]) {
    cout << "\n  | 0 1 2 3 4 5\n";
    cout << "--+-------------\n";
        for (int i = 0; i < 6; i++) {
        cout << i << " | ";
        for (int j = 0; j < 6; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

void mostrar_tablero_real(int arr2[6][6]) {
    cout << "\n  | 0 1 2 3 4 5\n";
    cout << "--+-------------\n";
    for (int i = 0; i < 6; i++) {
        cout << i << " | ";
        for (int j = 0; j < 6; j++) {
            cout << arr2[i][j] << " ";
        }
        cout << endl;
    }
}
//! FIN FUNCIONES HUNDIR LA FLOTA
//! INICIO FUNCIONES WORDLE

void mostrar_tablero_wordle(string arr[6][5]) {
    cout << "\n           +-+-+-+-+-+\n";
    for (int i = 0; i < 6; i++) {
        cout << "           |";
        for (int j = 0; j < 5; j++) {
            cout << arr[i][j] << "|";
        }
        cout << endl;
    }
    cout << "           +-+-+-+-+-+\n";
}

void mostrar_letras_restantes(string arr[26]) {
    cout << "\n\nLetras restantes: " << endl;
    for (int i = 0; i < 26; i++) {
        if (!arr[i].empty()) {
            cout << arr[i] << " ";
        } 
    }
}

//! FIN FUNCIONES WORDLE

//! INICIO FUNCIONES DODGE
void mostrar_dinosaurio(string arr[10][30], int r, int s, int h, int l) {
    system("clear");
    system("figlet Dodge");
    cout << "Hecho por: Álvaro Salas Robledillo" << endl << endl;
    cout << "+------------------------------------------------------------+\n";
    cout << "     Puntuación: "  << r << " - - Vidas: "<< l << " - - Velocidad: " << s << "ms  \n";
    cout << "+------------------------------------------------------------+\n";
    for (int i = 0; i < 62; i++) {
        if (i == 61 || i == 0) 
            cout << "+";
        else {
            cout << "-";
        }
    }
    cout << endl;
    for (int i = 0; i < 10; i++) {
        cout << "|";
        for (int j = 0; j < 30; j++) {
            cout << arr[i][j] << " ";
        }
        cout << "|" << endl;
    }
    for (int i = 0; i < 62; i++) {
        if (i == 61 || i == 0) 
            cout << "+";
        else {
            cout << "-";
        }
    }
    cout << endl;
    cout << "+----------------------------+\n";
    cout << "   Puntuación más alta: "<< h << "\n";
    cout << "+----------------------------+\n";
    cout << endl << endl;
}
//! FIN FUNCIONES DODGE

//! VARIABLES GENERALES (DODGE)

int highscore = -999;
int contador_jugadas = 0;

int main () {
    system("clear");
    srand(time(NULL));

    //! INICIO VARIABLES LOGIN

    int opc_menu = 0;
    string opc_menu_login[4] = {"+-----------------+  +--------------------+\n| [ ] Registrarse |  | [ ] Iniciar sesión |\n+-----------------+  +--------------------+\n\n\n+-----------+\n| [ ] Salir |\n+-----------+", "+-----------------+  +--------------------+\n| [*] Registrarse |  | [ ] Iniciar sesión |\n+-----------------+  +--------------------+\n\n\n+-----------+\n| [ ] Salir |\n+-----------+", "+-----------------+  +--------------------+\n| [ ] Registrarse |  | [*] Iniciar sesión |\n+-----------------+  +--------------------+\n\n\n+-----------+\n| [ ] Salir |\n+-----------+", "+-----------------+  +--------------------+\n| [ ] Registrarse |  | [ ] Iniciar sesión |\n+-----------------+  +--------------------+\n\n\n+-----------+\n| [*] Salir |\n+-----------+"};
    bool registrado = false;

    //! FIN VARIABLES LOGIN

    //! INICIO DECLARACIÓN VARIABLES DE HUNDIR LA FLOTA

    int x1, x2, x3, y1, y2, y3, fil = 0, col = 0, atqx = 0, atqy = 0, barco1 = 2, barco2 = 3, barco3 = 4;
    int tablero_real[6][6]={{0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0}};

    string posant, pos00;
    string tablero_visible[6][6] = {{"-", "-", "-", "-", "-", "-"},
                                    {"-", "-", "-", "-", "-", "-"},
                                    {"-", "-", "-", "-", "-", "-"},
                                    {"-", "-", "-", "-", "-", "-"},
                                    {"-", "-", "-", "-", "-", "-"},
                                    {"-", "-", "-", "-", "-", "-"}};

    //! FIN DECLARACIÓN VARIABLES DE HUNDIR LA FLOTA
    //! INICIO DECLARACIÓN VARIABLES DE 4 EN RAYA

    int mov, col_elegida, contar_0, poner_ficha_cpu, bloqueo = 0, prob_segun_dif = 0;
    int tablero_real_4[6][7] = {{0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0}};

    string elegir_columna[7] = {"-", "-", "-", "-", "-", "-", "-"};
    string tablero_visible_4[6][7]={{"-", "-", "-", "-", "-", "-", "-"},
                                    {"-", "-", "-", "-", "-", "-", "-"},
                                    {"-", "-", "-", "-", "-", "-", "-"},
                                    {"-", "-", "-", "-", "-", "-", "-"},
                                    {"-", "-", "-", "-", "-", "-", "-"},
                                    {"-", "-", "-", "-", "-", "-", "-"}};

    char mov2;

    bool posibilidad_vertical = false, posibilidad_horizontal = false, posibilidad_diagonal_1 = false, posibilidad_diagonal_2 = false, gana_jugador = false, gana_cpu = false;

    //! FIN DECLARACIÓN VARIABLES DE 4 EN RAYA
    //! INICIO VARIABLES WORDLE

    int pos_palabra = 0, contador_letras = 0, dif = 0;

    string palabra_separada[5], palabra_introducida_separada[5];

    string tablero_wordle[6][5] =  {{" ", " ", " ", " ", " "},
                                    {" ", " ", " ", " ", " "},
                                    {" ", " ", " ", " ", " "},
                                    {" ", " ", " ", " ", " "},
                                    {" ", " ", " ", " ", " "},
                                    {" ", " ", " ", " ", " "}};

    string letras[26] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
    string palabra_elegida, palabra_introducida;
    string palabras[170] = {"abeto", "actor", "aguas", "agudo", "alado", "albas", "altar", "acido", "atizo", "antes", "avion", "babas", "bacas", "bache", "bajes", "balas", "bebes", "belen", "berto", "bicho", "bizco", "bueno", "busca", "cabra", "cafes", "cajas", "calar", "calas", "calca", "calla", "calma", "camba", "campo", "canas", "cantos", "capto", "caras", "carlo", "carro", "casas", "catar", "caida", "cejas", "celia", "cenas", "cepas", "cerca", "cerco", "cerdo", "chile", "china", "ciego", "cines", "citas", "clara", "clavo", "colas", "colon", "colon", "coral", "coras", "corea", "corro", "cosas", "costo", "crudo", "curar", "dados", "dagas", "datos", "danos", "dejar", "dejes", "denso", "dices", "divos", "dotes", "dunas", "dures", "duros", "fallo", "falto", "feria", "fetos", "fijos", "filas", "filia", "finca", "gafas", "galas", "golfo", "goles", "ganas", "ganar", "gases", "gasto", "girar", "gordo", "gorro", "grito", "malos", "mania", "marca", "marco", "marti", "maria", "melon", "menos", "meter", "metro", "moler", "monte", "morir", "nacer", "nadar", "narro", "natas", "naves", "necio", "ninos", "notas", "nubes", "obras", "ocios", "ollas", "ondas", "onzas", "opera", "otros", "ovulo", "oirte", "palas", "paris", "pedir", "pelea", "pelos", "peras", "perro", "pesos", "pilas", "pinto", "poder", "sabio", "sacar", "salir", "selva", "sanar", "sopas", "secar", "serio", "sitio", "sobar", "sonar", "subir", "sucio", "siete", "tabla", "tacos", "tania", "tapas", "tazas", "telon", "tener", "tenis", "terco", "terso", "tapon", "tipos", "tiras", "todas"};

    //! FIN VARIABLES WORDLE

    //! INICIO DECLARACION VARIABLES DEL PROGRAMA GENERAL

    string opciones_menu[6] = {"[ ] // 4 En Raya\n[ ] // Hundir La Flota\n[ ] // Wordle\n[ ] // Dodge\n\n[ ] // Salir",
    "\033[1m[*] // 4 En Raya\033[0m\n[ ] // Hundir La Flota\n[ ] // Wordle\n[ ] // Dodge\n\n[ ] // Salir",
    "[ ] // 4 En Raya\n\033[1m[*] // Hundir La Flota\033[0m\n[ ] // Wordle\n[ ] // Dodge\n\n[ ] // Salir",
    "[ ] // 4 En Raya\n[ ] // Hundir La Flota\n\033[1m[*] // Wordle\033[0m\n[ ] // Dodge\n\n[ ] // Salir",
    "[ ] // 4 En Raya\n[ ] // Hundir La Flota\n[ ] // Wordle\n\033[1m[*] // Dodge\033[0m\n\n[ ] // Salir",
    "[ ] // 4 En Raya\n[ ] // Hundir La Flota\n[ ] // Wordle\n[ ] // Dodge\n\n\033[1m[*] // Salir\033[0m"};
    
    int juego = 0, conversion = 1;
    string visible_en_menu = {" ", "x"};
    char opc = '9';

    //! FIN DECLARACION VARIABLES DEL PROGRAMA GENERAL

    //! INICIO DECLARACIÓN DE VARIABLES DODGE

    string tablero_dino[10][30];

    bool playing = true;

    int speed = 250000, hability, contador_dash = 0, nal, contador_agacharse = 0, vidas = 3, save_puntuacion;

    //! FIN DECLARACIÓN DE VARIABLES DODGE

    //- FRONT END - MENÚ LOGIN

    system("clear");
    system("figlet Minijuegos");
    cout << endl << endl;
    cout << opc_menu_login[0];
    getch();
    opc_menu++;

    //! MOVIMIENTO DEL MENÚ

    for (int i = 0; i == i; i++) {
        system("clear");
        system("figlet Minijuegos");
        cout << endl << endl;
        cout << opc_menu_login[opc_menu] << endl;
        do {
            mov = getch();
        } while (mov != 56 && mov != 50 && mov != 10 && mov != 119 && mov != 115 && mov != 32 && mov != 97 && mov != 100);
        if (mov == 56 or mov == 119) { //! ARRIBA 
            if (opc_menu == 3 || opc_menu == 0) {
                if (opc_menu - 1 > 0) {
                    opc_menu = 1;
                }
                else if (opc_menu == 0) {
                    opc_menu++;
                }
            }
        }
        if (mov == 50 or mov == 115) { //! ABAJO 
            if (opc_menu < 3) {
                if (opc_menu + 1 < 4) {
                    opc_menu = 3;
                }
                else if (opc_menu == 0) {
                    opc_menu++;
                }
            }
        }
        if (mov == 97) { //! IZQUIERDA
            if (opc_menu - 1 > 0) {
                opc_menu--;
            }
            else if (opc_menu == 0) {
                opc_menu++;
            }
        }
        if (mov == 100) { //! IZQUIERDA
            if (opc_menu + 1 < 3) {
                opc_menu++;
            }
            else if (opc_menu == 0) {
                opc_menu++;
            }
        }
        if (mov == 10 or mov == 32) { //! ENTER
            break;
        }
    }

    //! OPCIONES MENÚ PRINCIPAL

    switch (opc_menu) {
        case 0:
            cout << endl << "No ha elegido ninguna opción." << endl;
            break;
        case 1:
            user_registry();
            user_login();
            break;
        case 2:
            if (user_login()) {
                user_login();
                break;
            }
            else {
                break;
            }
        case 3:
            cout << endl << "Hasta luego." << endl;
            sleep(1);
            return 0;
    }

    //! MENÚ PRINCIPAL

    cout << endl << "Presione cualquier tecla para continuar...";
    cout << endl;
    getch();
    system("clear");
    system("figlet Minijuegos");
    cout << "Hecho por: Álvaro Salas Robledillo\n\n------[ Participante ]------\n\nNombre de usuario: " << user << "\nPuntuación del jugador: " << player_score << "\n\n-------[ Minijuegos ]-------\n\n";
    cout << opciones_menu[0];
    cout << endl;
    user_login(conversion = 2);

    for (int i = 0; i == i; i++) {
        do {
            mov = getch();
        } while (mov != 56 && mov != 50 && mov != 10 && mov != 119 && mov != 115 && mov != 32);
        if (mov == 56 or mov == 119) { //! ARRIBA 
            if (juego - 1 > 0) {
                juego--;
            }
            else if (juego == 0) {
                juego++;
            }
        }
        if (mov == 50 or mov == 115) { //! ABAJO 
            if (juego + 1 < 6) {
                juego++;
            }
        }
        system("clear");
        system("figlet Minijuegos");
        cout << "Hecho por: Álvaro Salas Robledillo\n\n------[ Participante ]------\n\nNombre de usuario: " << user << "\nPuntuación del jugador: " << player_score << "\n\n-------[ Minijuegos ]-------\n\n";
        cout << opciones_menu[juego];
        cout << endl;
        user_login(conversion = 2);
        if (mov == 10 or mov == 32) { //! ENTER
            break;
        }
    }

    switch (juego) {
        case 1:
            //* 4 EN RAYA

            system("clear");
            system("figlet 4 En Raya");
            cout << "Hecho por: Álvaro Salas Robledillo\n\n";
            cout << "// Instrucciones //\n\n1. El juego de 4 en raya se juega en un tablero vertical con siete columnas y seis filas. Cada columna tiene espacio para seis fichas.\n2. El juego se juega entre dos jugadores, que se turnan para colocar sus fichas en el tablero.\n3. El jugador 1 coloca fichas azules en el tablero, mientras que el jugador 2 (CPU) coloca fichas rojas.\n4. El objetivo del juego es conectar cuatro fichas del mismo color en una fila, columna o diagonal. Cuando un jugador logra esto, gana el juego.\n5. El jugador 1 siempre comienza el juego colocando una ficha en cualquier columna que desee.\n6. Después de que se coloca una ficha en una columna, esta caerá hasta el espacio más bajo disponible en esa columna.\n7. Los jugadores se turnan para colocar sus fichas en el tablero, y cada jugador solo puede colocar una ficha por turno.\n8. Si ningun jugador ha colocado 4 fichas en 28 turnos, se acabará la partida.\n9. ¡Diviértete jugando al 4 en raya!\n\nPresione algún botón para continuar...";
            getch();

            //! ELECCIÓN DE DIFICULTAD

            system("clear");
            system("figlet 4 En Raya");
            cout << "Hecho por: Álvaro Salas Robledillo\n\n";
            cout << "Elija la dificultad:\n\n1 // Facil\n2 // Normal\n3 // Dificil\n4 // 💀 IMPOSIBLE 💀";
            do {
                mov2 = getch();
            } while (mov2 != '1' and mov2 != '2' and mov2 != '3' and mov2 != '4');
            switch (mov2) {
                case '1':
                system("clear");
                system("figlet 4 En Raya");
                cout << "Hecho por: Álvaro Salas Robledillo\n\n";
                    cout << "Te gusta lo fácil eh, bueno la probabilidad de que la CPU pueda bloquear tus movimientos es de un 30%" << endl;
                    prob_segun_dif = 3;
                    dif = 0;
                    break;
                case '2':
                    system("clear");
                    system("figlet 4 En Raya");
                    cout << "Hecho por: Álvaro Salas Robledillo\n\n";
                    cout << "la probabilidad de que la CPU pueda bloquear tus movimientos es de un 50%" << endl;
                    prob_segun_dif = 5;
                    dif = 1;
                    break;
                case '3':
                    system("clear");
                    system("figlet 4 En Raya");
                    cout << "Hecho por: Álvaro Salas Robledillo\n\n";
                    cout << "Espero que te gusten los retos, pues estas delante de uno de los más dificiles de tu vida, la probabilidad de que la CPU pueda bloquear tus movimientos es de un OCHENTA POR CIENTO" << endl;
                    prob_segun_dif = 8;
                    dif = 2;
                    break;
                case '4':
                    system("clear");
                    system("figlet 4 En Raya");
                    cout << "Hecho por: Álvaro Salas Robledillo\n\n";
                    cout << "¿Estas loco?, definitivamente lo estas, la probabilidad de que la CPU pueda bloquear tus movimientos es de un ¡CIEN POR CIEN!\n\n¡DISFRUTA!" << endl;
                    prob_segun_dif = 11;
                    dif = 3;
                    break;
                default:
                    system("clear");
                    system("figlet 4 En Raya");
                    cout << "Hecho por: Álvaro Salas Robledillo\n\n";
                    cout << "Muy bien, no has elegido bien la dificultad...\nTe lo vamos a poner facilito...\n";
                    prob_segun_dif = 3;
                    break;
            }

            //! BUCLE PRINCIPAL CON CONTADOR DE RONDAS

            for (int i = 0; i < 28; i++) {
                pos00 = elegir_columna[0];
                elegir_columna[0] = "+";
                col = 0;
                contar_0 = 0;
                posibilidad_vertical = false;
                posibilidad_horizontal = false;
                posibilidad_diagonal_1 = false;
                posibilidad_diagonal_2 = false;
                poner_ficha_cpu = 0;

                //! MOVIMIENTO DEL JUGADOR + ALGORITMO DE BLOQUEO + CONVERSIÓN DE VALORES DE TABLERO REAL A VISIBLE

                for (int j = 0; j == j; j++) {
                    cout << "\nMuévase con el teclado númerico o con WASD." << endl;
                    do {
                        mov = getch();
                    } while (mov != 54 && mov != 52 && mov != 10 && mov != 100 && mov != 97 && mov != 32);
                    system("clear");
                    system("figlet 4 En Raya");
                    cout << "\nRonda " << i + 1 << endl << "Tu turno" << endl << endl;
                    if (mov == 52 or mov == 97) { //! IZQUIERDA 
                        if (col - 1 >= 0) {
                            elegir_columna[0] = pos00;
                            posant = elegir_columna[col-1];
                            elegir_columna[col - 1] = "\033[34mo\033[0m";
                            mostrar_elegir_columna(elegir_columna);
                            mostrar_tablero_visible_4(tablero_visible_4);
                            elegir_columna[col - 1] = posant;
                            col--;
                        }
                        else {
                            posant = elegir_columna[col];
                            elegir_columna[col] = "\033[34mo\033[0m";
                            mostrar_elegir_columna(elegir_columna);
                            mostrar_tablero_visible_4(tablero_visible_4);
                            elegir_columna[col] = posant;
                        }
                    }
                    if (mov == 54 or mov == 100) { //! DERECHA 
                        if (col + 1 <= 6) {
                            elegir_columna[0] = pos00;
                            posant = elegir_columna[col + 1];
                            elegir_columna[col + 1] = "\033[34mo\033[0m";
                            mostrar_elegir_columna(elegir_columna);
                            mostrar_tablero_visible_4(tablero_visible_4);
                            elegir_columna[col + 1] = posant;
                            col++;
                        }
                        else {
                            posant = elegir_columna[col];
                            elegir_columna[col] = "\033[34mo\033[0m";
                            mostrar_elegir_columna(elegir_columna);
                            mostrar_tablero_visible_4(tablero_visible_4);
                            elegir_columna[col] = posant;
                        }
                    }
                    if (mov == 10 or mov == 32) { //! ENTER
                        col_elegida = col;

                        //! BUCLE PARA COMPROBAR SI LA COLUMNA ESTA LLENA

                        for (int k = 5; k >= 0; k--) {
                            if (tablero_real_4[k][col_elegida] == 0) {
                                contar_0++;
                            }
                        }

                        //! SI LA FILA ESTA INCOMPLETA...

                        if (contar_0 != 0) {
                            for (int k = 5; k >= 0; k--) {
                                if (tablero_real_4[k][col_elegida] == 0) {
                                    tablero_real_4[k][col_elegida] = 1;
                                    break;
                                }
                            }
                        }
                        else {
                            cout << "La fila esta completa, repite posición." << endl;
                            i--;
                            break;
                        }

                        //! ALGORITMO DETECCIÓN DE POSIBLE VICTORIA DEL JUGADOR

                        //! COMPROBACIÓN HORIZONTAL
                        for (int fila = 0; fila < 6; fila++) {
                            for (int columna = 0; columna < 4; columna++) {
                                if (tablero_real_4[fila][columna] + tablero_real_4[fila][columna + 1] + tablero_real_4[fila][columna + 2] + tablero_real_4[fila][columna + 3] == 3) {
                                    posibilidad_horizontal = true;
                                    for (int p = 0; p < 4; p++) {
                                        if (tablero_real_4[fila][p] == 0) {
                                            poner_ficha_cpu = p;
                                        }
                                    }
                                }
                            }
                        }

                        //! COMPROBACIÓN DIAGONAL 1
                        for (int columna = 0; columna < 4; columna++) {
                            for (int fila = 2; fila >= 0; fila--) {
                                if (tablero_real_4[fila][columna] + tablero_real_4[fila+1][columna+1] + tablero_real_4[fila+2][columna+2] + tablero_real_4[fila+3][columna+3] == 3) {
                                    posibilidad_diagonal_1 = true;
                                    if (tablero_real_4[fila][columna] == 0) {
                                        poner_ficha_cpu = columna;
                                    }
                                    if (tablero_real_4[fila + 1][columna + 1] == 0) {
                                        poner_ficha_cpu = columna + 1;
                                    }
                                    if (tablero_real_4[fila + 2][columna + 2] == 0) {
                                        poner_ficha_cpu = columna + 2;
                                    }
                                    if (tablero_real_4[fila + 3][columna + 3] == 0) {
                                        poner_ficha_cpu = columna + 3;
                                    }
                                }
                            }
                        }

                        //! COMPROBACIÓN DIAGONAL 2
                        for (int columna = 6; columna > 2; columna--) {
                            for (int fila = 0; fila <= 2; fila++) {
                                if (tablero_real_4[fila][columna] + tablero_real_4[fila+1][columna-1] + tablero_real_4[fila+2][columna-2] + tablero_real_4[fila+3][columna-3] == 3) {
                                    posibilidad_diagonal_2 = true;
                                    if (tablero_real_4[fila][columna] == 0) {
                                        poner_ficha_cpu = columna;
                                    }
                                    if (tablero_real_4[fila + 1][columna - 1] == 0) {
                                        poner_ficha_cpu = columna - 1;
                                    }
                                    if (tablero_real_4[fila + 2][columna - 2] == 0) {
                                        poner_ficha_cpu = columna - 2;
                                    }
                                    if (tablero_real_4[fila + 3][columna - 3] == 0) {
                                        poner_ficha_cpu = columna - 3;
                                    }
                                }
                            }
                        }

                        //! COMPROBACIÓN VERTICAL
                        for (int columna = 0; columna < 7; columna++) {
                            for (int fila = 0; fila < 3; fila++) {
                                if (tablero_real_4[fila][columna] + tablero_real_4[fila + 1][columna] + tablero_real_4[fila + 2][columna] + tablero_real_4[fila + 3][columna] == 3) {
                                    posibilidad_vertical = true;
                                    poner_ficha_cpu = columna;
                                }
                            }
                        }

                        //* GENERAR PROBABILIDAD DE BLOQUEO O FICHA RANDOM

                        bloqueo = rand() % 10;

                        if (bloqueo > prob_segun_dif) {
                            do{
                                poner_ficha_cpu = rand() % 7;
                            } while (tablero_real_4[0][poner_ficha_cpu] == 1 || tablero_real_4[0][poner_ficha_cpu] == -1);
                        }
                        else { 
                            if (posibilidad_vertical == false && posibilidad_horizontal == false && posibilidad_diagonal_1 == false && posibilidad_diagonal_2 == false) {
                                do{
                                    poner_ficha_cpu = rand() % 7;
                                } while (tablero_real_4[0][poner_ficha_cpu] == 1 || tablero_real_4[0][poner_ficha_cpu] == -1);
                            }
                        }

                        //! AÑADIR FICHA DELANTE DEL JUGADOR
                        //! BUCLE PARA COMPROBAR SI LA COLUMNA ESTA LLENA

                        for (int k = 5; k >= 0; k--) {
                            if (tablero_real_4[k][poner_ficha_cpu] == 0) {
                                contar_0++;
                            }
                        }

                        //! SI LA FILA ESTA INCOMPLETA...

                        if (contar_0 != 0) {
                            for (int k = 5; k >= 0; k--) {
                                if (tablero_real_4[k][poner_ficha_cpu] == 0) {
                                    tablero_real_4[k][poner_ficha_cpu] = -1;
                                    break;
                                }
                            }
                        }
                        else {
                            cout << "La fila esta completa, repite posición." << endl;
                            i--;
                            break;
                        }

                        //! Movimiento ficticio de la IA.

                        col = 0;
                        for (int movimiento = 0; movimiento <= poner_ficha_cpu; movimiento++) {
                            system("clear");
                            system("figlet 4 En Raya");
                            cout << "\nRonda " << i + 1 << endl << "Turno CPU" << endl << endl;
                            if (movimiento == 0) {
                                elegir_columna[0] = "\033[31mo\033[0m";
                                mostrar_elegir_columna(elegir_columna);
                                mostrar_tablero_visible_4(tablero_visible_4);
                            }
                            else {
                                posant = elegir_columna[col + 1];
                                elegir_columna[col + 1] = "\033[31mo\033[0m";
                                mostrar_elegir_columna(elegir_columna);
                                mostrar_tablero_visible_4(tablero_visible_4);
                                elegir_columna[col + 1] = posant;
                                col++;
                            }
                            elegir_columna[0] = pos00;
                            usleep(500000);
                        }

                        //* COMPROBACIÓN VICTORIA

                        //! COMPROBACIÓN VERTICAL
                        for (int columna = 0; columna < 7;  columna++) {
                            for (int fila = 0; fila < 3; fila++) {
                                if (tablero_real_4[fila][columna] + tablero_real_4[fila + 1][columna] + tablero_real_4[fila + 2][columna] + tablero_real_4[fila + 3][columna] == 4) {
                                    gana_jugador = true;
                                    tablero_real_4[fila][columna] = -9;
                                    tablero_real_4[fila + 1][columna] = -9;
                                    tablero_real_4[fila + 2][columna] = -9;
                                    tablero_real_4[fila + 3][columna] = -9;
                                    break;
                                }
                                if (tablero_real_4[fila][columna] + tablero_real_4[fila + 1][columna] + tablero_real_4[fila + 2][columna] + tablero_real_4[fila + 3][columna] == -4) {
                                    gana_cpu = true;
                                    tablero_real_4[fila][columna] = -9;
                                    tablero_real_4[fila + 1][columna] = -9;
                                    tablero_real_4[fila + 2][columna] = -9;
                                    tablero_real_4[fila + 3][columna] = -9;
                                    break;
                                }
                            }
                        }

                        //! COMPROBACIÓN HORIZONTAL
                        for (int fila = 0; fila < 6;  fila++) {
                            for (int columna = 0; columna < 4; columna++) {
                                if (tablero_real_4[fila][columna] + tablero_real_4[fila][columna + 1] + tablero_real_4[fila][columna + 2] + tablero_real_4[fila][columna + 3] == 4) {
                                    gana_jugador = true;
                                    tablero_real_4[fila][columna] = -9;
                                    tablero_real_4[fila][columna + 1] = -9;
                                    tablero_real_4[fila][columna + 2] = -9;
                                    tablero_real_4[fila][columna + 3] = -9;
                                    break;
                                }
                                if (tablero_real_4[fila][columna] + tablero_real_4[fila][columna + 1] + tablero_real_4[fila][columna + 2] + tablero_real_4[fila][columna + 3] == -4) {
                                    gana_cpu = true;
                                    tablero_real_4[fila][columna] = -9;
                                    tablero_real_4[fila][columna + 1] = -9;
                                    tablero_real_4[fila][columna + 2] = -9;
                                    tablero_real_4[fila][columna + 3] = -9;
                                    break;
                                }
                            }
                        }

                        //! COMPROBACIÓN DIAGONAL 1
                        for (int columna = 0; columna < 4; columna++) {
                            for (int fila = 2; fila >= 0; fila--) {
                                if (tablero_real_4[fila][columna] + tablero_real_4[fila+1][columna+1] + tablero_real_4[fila+2][columna+2] + tablero_real_4[fila+3][columna+3] == 4) {
                                    gana_jugador = true;
                                    tablero_real_4[fila][columna] = -9;
                                    tablero_real_4[fila + 1][columna + 1] = -9;
                                    tablero_real_4[fila + 2][columna + 2] = -9;
                                    tablero_real_4[fila + 3][columna + 3] = -9;
                                    break;
                                }
                                if (tablero_real_4[fila][columna] + tablero_real_4[fila+1][columna+1] + tablero_real_4[fila+2][columna+2] + tablero_real_4[fila+3][columna+3] == -4) {
                                    gana_cpu = true;
                                    tablero_real_4[fila][columna] = -9;
                                    tablero_real_4[fila + 1][columna + 1] = -9;
                                    tablero_real_4[fila + 2][columna + 2] = -9;
                                    tablero_real_4[fila + 3][columna + 3] = -9;
                                    break;
                                }
                            }
                        }

                        //! COMPROBACIÓN DIAGONAL 2
                        for (int columna = 6; columna > 2; columna--) {
                            for (int fila = 0; fila <= 2; fila++) {
                                if (tablero_real_4[fila][columna] + tablero_real_4[fila+1][columna-1] + tablero_real_4[fila+2][columna-2] + tablero_real_4[fila+3][columna-3] == 4) {
                                    gana_jugador = true;
                                    tablero_real_4[fila][columna] = -9;
                                    tablero_real_4[fila + 1][columna - 1] = -9;
                                    tablero_real_4[fila + 2][columna - 2] = -9;
                                    tablero_real_4[fila + 3][columna - 3] = -9;
                                    break;
                                }
                                if (tablero_real_4[fila][columna] + tablero_real_4[fila+1][columna-1] + tablero_real_4[fila+2][columna-2] + tablero_real_4[fila+3][columna-3] == -4) {
                                    gana_cpu = true;
                                    tablero_real_4[fila][columna] = -9;
                                    tablero_real_4[fila + 1][columna - 1] = -9;
                                    tablero_real_4[fila + 2][columna - 2] = -9;
                                    tablero_real_4[fila + 3][columna - 3] = -9;
                                    break;
                                }
                            }
                        }

                        //! CONVERSOR DE POSICIONES DE TABLERO REAL A TABLERO VISIBLE

                        for (int fila = 0; fila < 6;  fila++) {
                            for (int columna = 0; columna < 7; columna++) {
                                if (tablero_real_4[fila][columna] == 1) {
                                    tablero_visible_4[fila][columna] = "\033[34mo\033[0m";
                                }
                                if (tablero_real_4[fila][columna] == -1) {
                                    tablero_visible_4[fila][columna] = "\033[31mo\033[0m";
                                }
                                if (tablero_real_4[fila][columna] == -9) {
                                    tablero_visible_4[fila][columna] = "\033[1mo\033[0m";
                                }
                            }
                        }
                        break;
                    }
                }

                if (gana_jugador == true) {
                    system("clear");
                    system("figlet 4 En Raya");
                    cout << "¡Enhorabuena has ganado!" << endl << endl;
                    mostrar_tablero_visible_4(tablero_visible_4);
                    cout << "\nEspere...";
                    cout << endl;
                    switch(dif) {
                        case 0:
                            player_score += 10;
                            break;
                        case 1:
                            player_score += 25;
                            break;
                        case 2:
                            player_score += 50;
                            break;
                        case 3:
                            player_score += 150;
                            break;
                    }
                    sleep(4);
                    break;
                }
                if (gana_cpu == true) {
                    system("clear");
                    system("figlet 4 En Raya");
                    cout << "Perdiste..." << endl << endl;
                    mostrar_tablero_visible_4(tablero_visible_4);
                    cout << "\nEspere...";
                    cout << endl;
                    switch(dif) {
                        case 0:
                            if (player_score != 0) {
                                player_score -= 0;
                            }
                            break;
                        case 1:
                            if (player_score != 0) {
                                player_score -= 10;
                            }
                            break;
                        case 2:
                            if (player_score != 0) {
                                player_score -= 25;
                            }
                            break;
                        case 3:
                            if (player_score != 0) {
                                player_score -= 50;
                            }
                            break;
                    }
                    sleep(4);
                    break;
                }
            }

            break;
        
        case 2:
            //* HUNDIR LA FLOTA

            system("clear");
            system("figlet Hundir La Flota");
            cout << "Hecho por: Álvaro Salas Robledillo\n\n";
            cout << "// Instrucciones //\n\n1. El juego genera aleatoriamente los barcos que se colocan en la cuadrícula del jugador.\n2. Cada barco se coloca horizontal o verticalmente en la cuadrícula, y puede ocupar entre 2 y 4 espacios.\n3. Los barcos no se pueden superponer entre sí.\n4. El objetivo del juego es hundir todos los barcos generados aleatoriamente antes de que se agoten los intentos del jugador.\n5. El jugador lanza un disparo a la cuadrícula, indicando una coordenada en la cuadrícula moviendose con el teclado.\n6. Si el disparo impacta en un barco, el juego indicará 'tocado'. Si el disparo no impacta en un barco, el juego indicará 'agua'.\n7. Si el jugador logra impactar en todas las partes de un barco generado aleatoriamente, el juego indicará 'hundido'.\n8. El jugador tiene un número limitado de intentos para hundir todos los barcos generados aleatoriamente.\n9. Si el jugador logra hundir todos los barcos antes de que se agoten los intentos, el jugador gana. De lo contrario, pierde.\n10. ¡Diviértete jugando Hundir la Flota!";

            //! GENERAR BARCO 1

            x1 = rand()%6;
            y1 = rand()%6;
            tablero_real[x1][y1] = 1;

            do {
            nal = rand()%4;
                switch (nal) {
                    case 0: //! ARRIBA
                        if (x1 - 1 < 0 or x1 - 1 > 5){
                            nal = 1;
                        }
                        else {
                            tablero_real[x1-1][y1] = 1;
                            break;
                        }
                    case 1: //! ABAJO
                        if(x1 + 1 < 0 or x1 + 1 > 5) {
                            nal = 2;
                        }
                        else {
                            tablero_real[x1+1][y1] = 1;
                            break;
                        }
                    case 2: //! IZQUIERDA
                        if(y1 - 1 < 0 or y1 - 1 > 5) {
                            nal = 3;
                        }
                        else {
                            tablero_real[x1][y1-1] = 1;
                            break;
                        }
                    case 3: //! DERECHA
                        if(y1 + 1 < 0 or y1 + 1 > 5) {
                            nal = 4;
                            usleep(50000);
                        }
                        else {
                            tablero_real[x1][y1+1] = 1;
                            break;
                        }
                    }
            } while (nal == 4);

            //! GENERAR BARCO 2

            do {
                do { // Generar primera posición del barco
                    x2 = rand()%6;
                    y2 = rand()%6;
                    usleep(50000);
                } while (tablero_real[x2 - 2][y2] == 1 && tablero_real[x2 + 2][y2] == 1 && tablero_real[x2][y2 + 2] == 1 && tablero_real[x2][y2 - 2] == 1 && tablero_real[x2 - 1][y2] == 1 && tablero_real[x2 + 1][y2] == 1 && tablero_real[x2][y2 + 1] == 1 && tablero_real[x2][y2 - 1] == 1);
            } while (x2 == x1 and y2 == y1 or tablero_real[x2][y2] == 1);

            tablero_real[x2][y2] = 2;

            do {
                nal = rand()%4;
                switch (nal) {
                    case 0: //!ARRIBA
                    if (x2 - 2 < 0 or x2 - 2 > 5 or y2 < 0 or y2 > 5) {
                        nal = 1;
                    }
                    else {
                        if (tablero_real[x2 - 1][y2] != 1 and tablero_real[x2 - 2][y2] != 1) {
                            tablero_real[x2 - 1][y2] = 2;
                            tablero_real[x2 - 2][y2] = 2;
                            break;
                        }
                        else {
                            nal = 1;
                        }
                    }
                    case 1: //!ABAJO
                    if (x2 + 2 < 0 or x2 + 2 > 5 or y2 < 0 or y2 > 5) {
                        nal = 2;
                    }
                    else {
                        if (tablero_real[x2+1][y2] !=  1 and tablero_real[x2+2][y2] != 1) {
                            tablero_real[x2+1][y2] = 2;
                            tablero_real[x2+2][y2] = 2;
                            break;
                        }
                        else {
                            nal = 2;
                        }
                    }
                    case 2: //!IZQUIERDA
                    if (x2 < 0 or x2 > 5 or y2 - 2 < 0 or y2 - 2 > 5) {
                        nal = 3;
                    }
                    else {
                        if (tablero_real[x2][y2-1] != 1 and tablero_real[x2][y2-2] != 1) {
                            tablero_real[x2][y2-1] = 2;
                            tablero_real[x2][y2-2] = 2;
                            break;
                        }
                        else {
                            nal = 3;
                        }
                    }
                    case 3: //!DERECHA
                    if (x2 < 0 or x2 > 5 or y2 + 2 < 0 or y2 + 2 > 5) {
                        nal = 4;
                    }
                    else {
                        if (tablero_real[x2][y2+1] != 1 and tablero_real[x2][y2+2] != 1) {
                            tablero_real[x2][y2+1] = 2;
                            tablero_real[x2][y2+2] = 2;
                            break;
                        }
                        else {
                            nal = 4;
                        }
                    }
                }
            } while (nal == 4);

            //! GENERAR BARCO 3

            do {
                do { // Generar primera posición del barco
                    x3 = rand()%6;
                    y3 = rand()%6;
                    usleep(50000);
                } while (tablero_real[x3 - 3][y3] == 1 && tablero_real[x3 + 3][y3] == 1 && tablero_real[x3][y3 - 3] == 1 && tablero_real[x3][y3 + 3] == 1 && tablero_real[x3 - 2][y3] == 1 && tablero_real[x3 + 2][y3] == 1 && tablero_real[x3][y3 + 2] == 1 && tablero_real[x3][y3 - 2] == 1 && tablero_real[x3 - 1][y3] == 1 && tablero_real[x3 + 1][y3] == 1 && tablero_real[x3][y3 + 1] == 1 && tablero_real[x3][y3 - 1] == 1);
            } while (x3 == x2 and y3 == y2 and x3 == x1 and y3 == y1 or tablero_real[x3][y3] == 1 or tablero_real[x3][y3] == 2);

            tablero_real[x3][y3] = 3;

            do {
                nal = rand()%4;
                switch (nal) {
                    case 0: //!ARRIBA
                    if (x3 - 3 < 0 or x3 - 3 > 5 or y3 < 0 or y3 > 5) {
                        nal = 1;
                    }
                    else {
                        if (tablero_real[x3 - 1][y3] == 0 and tablero_real[x3 - 2][y3] == 0 and tablero_real[x3 - 3][y3] == 0) {
                            tablero_real[x3 - 1][y3] = 3;
                            tablero_real[x3 - 2][y3] = 3;
                            tablero_real[x3 - 3][y3] = 3;
                            break;
                        }
                        else {
                            nal = 1;
                        }
                    }
                    case 1: //!ABAJO
                    if (x3 + 3 < 0 or x3 + 3 > 5 or y3 < 0 or y3 > 5) {
                        nal = 2;
                    }
                    else {
                        if (tablero_real[x3 + 1][y3] == 0 and tablero_real[x3 + 2][y3] == 0 and tablero_real[x3 + 3][y3] == 0) {
                            tablero_real[x3+1][y3] = 3;
                            tablero_real[x3+2][y3] = 3;
                            tablero_real[x3+3][y3] = 3;
                            break;
                        }
                        else {
                            nal = 2;
                        }
                    }
                    case 2: //!IZQUIERDA
                    if (x3 < 0 or x3 > 5 or y3 - 3 < 0 or y3 - 3 > 5) {
                        nal = 3;
                    }
                    else {
                        if (tablero_real[x3][y3 - 1] == 0 and tablero_real[x3][y3 - 2] == 0 and tablero_real[x3][y3 - 3] == 0) {
                            tablero_real[x3][y3-1] = 3;
                            tablero_real[x3][y3-2] = 3;
                            tablero_real[x3][y3-3] = 3;
                            break;
                        }
                        else {
                            nal = 3;
                        }
                    }
                    case 3: //!DERECHA
                    if (x3 < 0 or x3 > 5 or y3 + 3 < 0 or y3 + 3 > 5) {
                        nal = 4;
                    }
                    else {
                        if (tablero_real[x3][y3 + 1] == 0 and tablero_real[x3][y3 + 2] == 0 and tablero_real[x3][y3 + 3] == 0) {
                            tablero_real[x3][y3+1] = 3;
                            tablero_real[x3][y3+2] = 3;
                            tablero_real[x3][y3+3] = 3;
                            break;
                        }
                        else {
                            nal = 4;
                        }
                    }
                }
            } while (nal == 4);

            //! FRONT-END

            for (int b = 0; b < 20; b++) { //! BUCLE DE TURNOS
                fil = 0;
                col = 0;
                pos00 = tablero_visible[0][0];
                tablero_visible[0][0] = "*";
                for (int c = 0; c == c; c++) {

                    //! MOVIMIENTO DEL JUGADOR EN EL TABLERO + COMPROBACIÓN DE CASILLA

                    cout << "\n\nMuévase con el teclado númerico o con WASD." << endl;
                    do {
                        mov = getch();
                    } while (mov != 56 && mov != 54 && mov != 50 && mov != 52 && mov != 10 && mov != 119 && mov != 100 && mov != 115 && mov != 97 && mov != 32);
                    system("clear");
                    system("figlet Hundir La Flota");
                    cout << "\nRonda " << b + 1 << endl;
                    if (mov == 56 or mov == 119) { //! ARRIBA 
                        if (fil - 1 >= 0) {
                            tablero_visible[0][0] = pos00;
                            posant = tablero_visible[fil - 1][col];
                            tablero_visible[fil - 1][col] = "*";
                            mostrar_tablero_visible(tablero_visible);
                            tablero_visible[fil - 1][col] = posant;
                            fil--;
                        }
                        else {
                            posant = tablero_visible[fil][col];
                            tablero_visible[fil][col] = "*";
                            mostrar_tablero_visible(tablero_visible);
                            tablero_visible[fil][col] = posant;
                        }
                    }
                    if (mov == 54 or mov == 100) { //! DERECHA 
                        if (col + 1 <= 5) {
                            tablero_visible[0][0] = pos00;
                            posant = tablero_visible[fil][col + 1];
                            tablero_visible[fil][col + 1] = "*";
                            mostrar_tablero_visible(tablero_visible);
                            tablero_visible[fil][col + 1] = posant;
                            col++;
                        }
                        else {
                            posant = tablero_visible[fil][col];
                            tablero_visible[fil][col] = "*";
                            mostrar_tablero_visible(tablero_visible);
                            tablero_visible[fil][col] = posant;
                        }
                    }
                    if (mov == 50 or mov == 115) { //! ABAJO 
                        if (fil + 1 <= 5) {
                            tablero_visible[0][0] = pos00;
                            posant = tablero_visible[fil + 1][col];
                            tablero_visible[fil + 1][col] = "*";
                            mostrar_tablero_visible(tablero_visible);
                            tablero_visible[fil + 1][col] = posant;
                            fil++;
                        }
                        else {
                            posant = tablero_visible[fil][col];
                            tablero_visible[fil][col] = "*";
                            mostrar_tablero_visible(tablero_visible);
                            tablero_visible[fil][col] = posant;
                        }
                    }
                    if (mov == 52 or mov == 97) { //! IZQUIERDA 
                        if (col - 1 >= 0) {
                            tablero_visible[0][0] = pos00;
                            posant = tablero_visible[fil][col - 1];
                            tablero_visible[fil][col - 1] = "*";
                            mostrar_tablero_visible(tablero_visible);
                            tablero_visible[fil][col - 1] = posant;
                            col--;
                        }
                        else {
                            posant = tablero_visible[fil][col];
                            tablero_visible[fil][col] = "*";
                            mostrar_tablero_visible(tablero_visible);
                            tablero_visible[fil][col] = posant;
                        }
                    }
                    //! ENTRADA DE CASILLA - COMPROBACIONES
                    if (mov == 10 or mov == 32) {
                        atqx = fil;
                        atqy = col;
                        if (tablero_real[atqx][atqy] == 7 || tablero_real[atqx][atqy] == 11 || tablero_real[atqx][atqy] == 12 || tablero_real[atqx][atqy] == 13) {
                            cout << "¡Esta posición ya ha sido elegida anteriormente!" << endl;
                            b--;
                            break;
                        }
                        if (tablero_real[atqx][atqy] == 1 || tablero_real[atqx][atqy] == 2 || tablero_real[atqx][atqy] == 3) {
                            cout << "¡Tocado!" << endl;
                            tablero_visible[atqx][atqy] = "x";
                            if (tablero_real[atqx][atqy] == 1) {
                                tablero_real[atqx][atqy] = 11;
                                barco1--;
                                if (barco1 == 0) {
                                    for (int i = 0; i < 6; i++) {
                                        for (int j = 0; j < 6; j++) {
                                            if (tablero_real[i][j] == 11) {
                                                tablero_visible[i][j] = "\033[1mo\033[0m";
                                            }
                                        }
                                    }
                                    cout << "¡Barco hundido!" << endl;
                                    mostrar_tablero_visible(tablero_visible);
                                }
                                usleep(500000);
                            }
                            if (tablero_real[atqx][atqy] == 2) {
                                tablero_real[atqx][atqy] = 12;
                                barco2--;
                                if (barco2 == 0) {
                                    for (int i = 0; i < 6; i++) {
                                        for (int j = 0; j < 6; j++) {
                                            if (tablero_real[i][j] == 12) {
                                                tablero_visible[i][j] = "\033[1mo\033[0m";
                                            }
                                        }
                                    }
                                    cout << "¡Barco hundido!" << endl;
                                    mostrar_tablero_visible(tablero_visible);
                                }
                                usleep(500000);
                            }
                            if (tablero_real[atqx][atqy] == 3) {
                                tablero_real[atqx][atqy] = 13;
                                barco3--;
                                if (barco3 == 0) {
                                    for (int i = 0; i < 6; i++) {
                                        for (int j = 0; j < 6; j++) {
                                            if (tablero_real[i][j] == 13) {
                                                tablero_visible[i][j] = "\033[1mo\033[0m";
                                            }
                                        }
                                    }
                                    cout << "¡Barco hundido!" << endl;
                                    mostrar_tablero_visible(tablero_visible);
                                }
                                usleep(500000);
                            }
                        }
                        else {
                            cout << "¡Agua!" << endl;
                            tablero_visible[fil][col] = " ";
                            tablero_real[atqx][atqy] = 7; 
                        }
                        break;
                    }
                }
                //! COMPROBACIÓN GANAR
                if (barco1 == 0 and barco2 == 0 and barco3 == 0) {
                    system ("clear");
                    cout << "\n¡Ganaste!" << endl;
                    mostrar_tablero_visible(tablero_visible);
                    cout << "\nEspere...";
                    cout << endl;
                    player_score += 150;
                    sleep(4);
                    break;
                }
            }

            //! CASO PERDER
            if (barco1 != 0 or barco2 != 0 or barco3 != 0) {
                system ("clear");
                cout << "Perdiste..." << endl << endl;
                cout << "Tablero real: " << endl;
                for (int i = 0; i < 6; i++) {
                    for (int j = 0; j < 6; j++) {
                        if (tablero_real[i][j] == 1) {
                            tablero_visible[i][j] = "1";
                        }
                        if (tablero_real[i][j] == 2) {
                            tablero_visible[i][j] = "2";
                        }
                        if (tablero_real[i][j] == 3) {
                            tablero_visible[i][j] = "3";
                        }
                    }
                }
                mostrar_tablero_visible(tablero_visible);
                cout << "\nEspere...";
                cout << endl;
                if (player_score != 0) {
                    player_score -= 50;
                }
                sleep(4);
            }
            break;
        
        case 3: 
            //* WORDLE

            system("clear");
            system("figlet Wordle");
            cout << "Hecho por: Álvaro Salas Robledillo\n\n";
            cout << "// Instrucciones //\n\n1. El juego se compone de una palabra de cinco letras que debes adivinar en seis intentos.\n2. Cada vez que hagas un intento, el juego te mostrará cuántas letras has acertado (amarillas) y cuántas de esas letras están en la posición correcta (verde).\n3. Utiliza esta información para deducir la palabra secreta. Por ejemplo, si en tu primer intento escribes 'avion' y el juego te muestra que has acertado dos letras pero ninguna de ellas está en la posición correcta, podrías deducir que la palabra secreta no tiene ninguna de esas dos letras.\n5. Usa la lógica y la deducción para reducir las posibilidades y adivinar la palabra secreta antes de que se te acaben los seis intentos.\n6. Una vez que adivines la palabra, puedes jugar de nuevo para intentar mejorar tu puntuación.\n7. ¡Diviértete intentando adivinar la palabra secreta!\n\nPresione cualquier botón para continuar...";
            getch();

            //! ELECCIÓN PALABRA ALEATORIA
            pos_palabra = rand() % 170;
            palabra_elegida = palabras[pos_palabra];

            //! SEPARAR LA PALABRA INTRODUCIDA
            for (int i = 0; i < 5; i++) {
                palabra_separada[i] = palabra_elegida[i];
            }

            for (int b = 0; b < 6; b++) {
                system("clear");
                system("figlet Wordle");
                mostrar_tablero_wordle(tablero_wordle);
                mostrar_letras_restantes(letras);
                cout << "\n\nIntroduzca una palabra: ";

                //! INTRODUCIR LA PALABRA
                do {
                    cin >> palabra_introducida;
                    if (palabra_introducida.length() != 5) {
                        cout << "Introduce una palabra de 5 letras\n";
                        cout << "Introduzca una palabra: ";
                        cout << endl;
                    }
                } while (palabra_introducida.length() != 5);

                //! SEPARAR CARACTERES DE LA PALABRA INTRODUCIDA
                for (int j = 0; j < 5; j++) {
                    palabra_introducida_separada[j] = palabra_introducida[j];
                    tablero_wordle[b][j] = palabra_introducida_separada[j];
                }

                //* COMPROBACIONES

                //! COMPROBAR SI LA LETRA SE ENCUENTRA EN LA PALABRA INTRODUCIDA - COLOR AMARILLO.
                for (int i = 0; i < 5; i++) {
                    for (int j = 0; j < 5; j++) {
                        if (palabra_introducida_separada[i] == palabra_separada[j]) {
                            tablero_wordle[b][i] = "\033[33m" + palabra_introducida_separada[i] + "\033[0m";
                        }
                    }
                }

                //! COMPROBAR SI LA LETRA SE ENCUENTRA EN LA MISMA POSICIÓN - COLOR VERDE.
                contador_letras = 0;
                for (int i = 0; i < 5; i++) {
                    if (palabra_introducida_separada[i] == palabra_separada[i]) {
                        tablero_wordle[b][i] = "\033[32m" + palabra_introducida_separada[i] + "\033[0m";
                    }
                }

                //! COMPROBAR LETRA USADA, Y QUITARLA DE LA LISTA DEL ABECEDARIO
                for (int i = 0; i < 5; i++) {
                    for (int j = 0; j < 26; j++) {
                        if (palabra_introducida_separada[i] == letras[j])
                            letras[j].clear();
                    }
                }

                //! CASO GANAR
                if (palabra_introducida == palabra_elegida) {
                    system("clear");
                    system("figlet Wordle");
                    mostrar_tablero_wordle(tablero_wordle);
                    cout << "\n\n¡Enhorabuena!" << endl << endl << "La palabra era: " << palabra_elegida << endl;
                    sleep(4);
                    switch(b) {
                        case 0:
                            player_score += 1000;
                            break;
                        case 1:
                            player_score += 200;
                            break;
                        case 2:
                            player_score += 150;
                            break;
                        case 3:
                            player_score += 75;
                            break;
                        case 4:
                            player_score += 75;
                            break;
                        case 5:
                            player_score += 75;
                            break;
                    }
                    break;
                }
            }

            //! CASO PERDER
            if (palabra_elegida != palabra_introducida) {
                system("clear");
                system("figlet Wordle");
                mostrar_tablero_wordle(tablero_wordle);
                cout << "\n\nPerdiste..." << endl << endl << "La palabra era: " << palabra_elegida << endl;
                if (player_score != 0) {
                    player_score -= 50;
                }
                sleep(4);
            }

            break;

            case 4: 
                //* DODGE

                if (contador_jugadas == 0) {
                    system("clear");
                    system("figlet Dodge");
                    cout << "Hecho por: Álvaro Salas Robledillo \n\n";
                    cout << "// Instrucciones //\n\n1 Tu personaje comenzará a correr automáticamente. Tu objetivo es mantenerlo vivo y hacer la mayor cantidad de puntos posible.\n2 Presiona la tecla de espacio para hacer que tu personaje salte en el espacio-tiempo y evite los obstáculos que aparecen en el camino como cactus (*).\n3 Presiona la tecla de s o S para hacer que tu personaje sea más pequeño y evite los obstáculos que aparecen en el camino como pájaros (^).\n4 A medida que avances en el juego, la velocidad aumentará y los obstáculos se volverán más difíciles de evitar.\n5 Si tocas un obstáculo, el juego terminará y tendrás la opción de volver a jugarlo.\n6 Diviértete jugando y trata de superar tu puntaje anterior en cada intento.\n";
                    cout << "\nPresione cualquier botón para empezar...";
                    getch();
                }

                for (int i = 0; i < 10; i++) {
                    for (int j = 0; j < 30; j++) {
                        tablero_dino[i][j] = " ";
                    }
                }

                for (int puntuacion = 0; puntuacion == puntuacion; puntuacion++) { 
                    //! VELOCIDAD DEL PROGRAMA

                    if (puntuacion > 300) {
                        speed = 70000;
                    }
                    else if (puntuacion > 200) {
                        speed = 90000;
                    }
                    else if (puntuacion > 100) {
                        speed = 150000;
                    }
                    else if (puntuacion > 50) {
                        speed = 200000;
                    }

                    //! GENERACIÓN ESCENARIO

                    if (puntuacion % 4 == 0 && puntuacion > 3) {
                        nal = rand() % 4;
                        switch (nal) {
                            case 0:
                                tablero_dino[2][29] = "^";
                                tablero_dino[4][27] = "^";
                            break;
                            case 1:
                                tablero_dino[2][29] = "^";
                                tablero_dino[0][29] = "^";
                                tablero_dino[1][27] = "^";
                                tablero_dino[3][29] = "^";
                            break;
                            case 2:
                                tablero_dino[0][29] = "^";
                                tablero_dino[3][27] = "^";
                            break;
                            case 3:
                                tablero_dino[1][27] = "^";
                                tablero_dino[2][29] = "^";
                            break;
                        }
                    }

                    //! GENERACIÓN OBJETOS

                    if (puntuacion % 8 == 0 && puntuacion > 3) {
                        nal = rand() % 3;
                        switch (nal) {
                            case 0: //! CACTUS 2
                                tablero_dino[9][29] = "\033[32m*\033[0m";
                                tablero_dino[8][29] = "\033[32m*\033[0m";
                                break;
                            case 1: //! CACTUS 3
                                tablero_dino[9][29] = "\033[32m*\033[0m";
                                tablero_dino[8][29] = "\033[32m*\033[0m";
                                tablero_dino[7][29] = "\033[32m*\033[0m";
                                break;
                            case 2: //! PAJAROS
                                tablero_dino[8][29] = "^";
                                tablero_dino[8][27] = "^";
                                break;
                        }
                    }
                    else {
                        tablero_dino[9][29] = " ";
                        tablero_dino[8][29] = " ";
                    }

                    //! DETECTAR TECLADO

                    if (kbhit()) {
                        hability = getch();
                        if (hability == 10 || hability == 32) { //! DASH
                            if (contador_dash == 0)
                                contador_dash = 5;
                        } 
                        if (hability == 115 || hability == 83) {
                            if (contador_agacharse == 0) {
                                tablero_dino[8][6] = "\033[1m>\033[0m";
                                contador_agacharse = 6;
                            }
                        }
                    }

                    //! TRANSLADO DE COLUMNAS

                    if (puntuacion % 2 == 0) {
                        for (int y = 29; y > 0; y--) {
                            for (int x = 0; x < 10; x++) {
                                if (tablero_dino[x][y] == "\033[1m>\033[0m" && tablero_dino[x][y + 1] == "\033[32m*\033[0m" || tablero_dino[x][y] == "\033[1m>\033[0m" && tablero_dino[x][y + 1] == "^") {
                                    vidas--;
                                    break;
                                }
                                if (tablero_dino[x][y] == "\033[1m>\033[0m") {
                                    tablero_dino[x][y] = " ";
                                }
                                tablero_dino[x][y - 1] = tablero_dino[x][y];
                                tablero_dino[x][y] = " ";
                            }
                            if (vidas == 0) {
                                break;
                            }
                            if (y - 1 > 0) {
                                y--;
                            }
                        }
                    }
                    else {
                        for (int y = 28; y > 0; y--) {
                            for (int x = 0; x < 10; x++) {
                                if (tablero_dino[x][y] == "\033[1m>\033[0m" && tablero_dino[x][y + 1] == "\033[32m*\033[0m" || tablero_dino[x][y] == "\033[1m>\033[0m" && tablero_dino[x][y + 1] == "^") {
                                    vidas--;
                                    break;
                                }
                                if (tablero_dino[x][y] == "\033[1m>\033[0m") {
                                    tablero_dino[x][y] = " ";
                                }
                                tablero_dino[x][y - 1] = tablero_dino[x][y];
                                tablero_dino[x][y] = " ";
                            }
                            if (vidas == 0) {
                                break;
                            }
                            if (y - 1 > 0) {
                                y--;
                            }
                        }
                    }

                    //! MUERTO?

                    if (vidas == 0) {
                        playing = false;
                    }

                    if (!kbhit()) {
                        if (contador_dash == 0 && contador_agacharse == 0) {
                            tablero_dino[9][6] = "\033[1m>\033[0m";
                            tablero_dino[8][6] = "\033[1m>\033[0m";
                        }
                    }

                    //! CONTADOR HABILIDADES

                    if (contador_dash > 0) {
                        contador_dash--;
                    }

                    if (contador_agacharse > 0) {
                        contador_agacharse--;
                        tablero_dino[9][6] = "\033[1m>\033[0m";
                    }

                    //! COMPROBACIÓN DE CHOQUE

                    if (contador_dash == 0 && contador_agacharse == 0) {
                        if (tablero_dino[8][6] == "\033[32m*\033[0m" || tablero_dino[9][6] == "\033[32m*\033[0m" || tablero_dino[8][6] == "^") {
                            vidas--;
                        }
                    }

                    //! ASIGNACION DE PUNTUACION MAS ALTA

                    if (puntuacion > highscore) {
                        highscore = puntuacion;
                    }

                    if (!playing) {
                        tablero_dino[9][6] = "\033[1m>\033[0m";
                        tablero_dino[8][6] = "\033[1m>\033[0m";
                    }

                    mostrar_dinosaurio(tablero_dino, puntuacion, speed, highscore, vidas);
                    usleep(speed);

                    save_puntuacion = puntuacion;

                    if (!playing) {
                        break;
                    }
                }
            cout << "Perdiste..." << endl << endl;
            cout << "Espere..." << endl;
            contador_jugadas = 1;
            player_score += save_puntuacion;
            sleep(2);

            break;

        default:
            cout << "\n¡Hasta luego!" << endl;
            sleep(1);
            return 0;
    }

    user_login(conversion = 1);
    system("clear");
    system("figlet Minijuegos");
    cout << endl << "¿Desea volver a jugar? (S/N)";
    cout << endl;
    sleep(1);
    do {
        opc = getch();
    } while (opc != 'S' && opc != 's' && opc != 'N' && opc != 'n');

    if (opc == 'S' or opc == 's') {
        main();
    }

    return 0;
}