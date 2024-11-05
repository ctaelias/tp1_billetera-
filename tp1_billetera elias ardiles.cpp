#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void mostrarMenu() {
    cout << "\nBilletera Electronica\n";
    cout << "D - Deposito\n";
    cout << "E - Extraccion\n";
    cout << "T - Transferencia\n";
    cout << "Seleccione una opcion (D/E/T): ";
}

float obtenerSaldo() {
    ifstream archivo("billetera.txt");
    float saldo = 0.0;
    if (archivo.is_open()) {
        archivo >> saldo;
    } else {
        cout << "No se pudo abrir el archivo billetera.txt" << endl;
    }
    archivo.close();
    return saldo;
}

void guardarSaldo(float saldo) {
    ofstream archivo("billetera.txt");
    if (archivo.is_open()) {
        archivo << saldo;
    } else {
        cout << "No se pudo guardar el archivo billetera.txt" << endl;
    }
    archivo.close();
}

void realizarDeposito() {
    float deposito;
    cout << "Ingrese el monto a depositar: ";
    cin >> deposito;
    if (deposito <= 0) {
        cout << "El monto debe ser positivo." << endl;
        return;
    }

    float saldo = obtenerSaldo();
    saldo += deposito;
    guardarSaldo(saldo);
    cout << "Deposito realizado con exito. Nuevo saldo: " << saldo << endl;
}

void realizarExtraccion() {
    float extraccion;
    cout << "Ingrese el monto a extraer: ";
    cin >> extraccion;

    float saldo = obtenerSaldo();
    if (extraccion > saldo) {
        cout << "Saldo insuficiente. Operacion no realizada." << endl;
    } else if (extraccion <= 0) {
        cout << "El monto a extraer debe ser positivo." << endl;
    } else {
        saldo -= extraccion;
        guardarSaldo(saldo);
        cout << "Extraccion realizada con exito. Nuevo saldo: " << saldo << endl;
    }
}

void realizarTransferencia() {
    float transferencia;
    string numeroCelular;
    cout << "Ingrese el monto a transferir: ";
    cin >> transferencia;

    if (transferencia <= 0) {
        cout << "El monto debe ser positivo." << endl;
        return;
    }

    cout << "Ingrese el numero de celular del destinatario: ";
    cin >> numeroCelular;

    float saldo = obtenerSaldo();
    if (transferencia > saldo) {
        cout << "Saldo insuficiente. Operacion no realizada." << endl;
    } else {
        saldo -= transferencia;
        guardarSaldo(saldo);
        cout << "Transferencia realizada con exito a " << numeroCelular << ". Nuevo saldo: " << saldo << endl;
    }
}

int main() {
    // Verificar si el archivo existe; si no, crearlo con saldo inicial 0.
    ifstream archivo("billetera.txt");
    if (!archivo.is_open()) {
        ofstream nuevoArchivo("billetera.txt");
        nuevoArchivo << 0.0; // saldo inicial 0
        nuevoArchivo.close();
    }

    char opcion;
    bool salir = false;

    while (!salir) {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case 'D':
            case 'd':
                realizarDeposito();
                break;
            case 'E':
            case 'e':
                realizarExtraccion();
                break;
            case 'T':
            case 't':
                realizarTransferencia();
                break;
            default:
                cout << "Opcion invalida. Por favor ingrese D, E o T." << endl;
        }

        cout << "\nDesea realizar otra operacion? (s/n): ";
        char respuesta;
        cin >> respuesta;
        if (respuesta == 'n' || respuesta == 'N') {
            salir = true;
        }
    }

    cout << "Gracias por usar la billetera electronica." << endl;
    return 0;
}
