#include <iostream>
#include <string>
#include <thread>
#include <chrono>
using namespace std;

class Banco {
protected:
    double balance;
    string titularCuenta;

public:
    Banco(double balance, string titularCuenta) {
        this->balance = balance;
        this->titularCuenta = titularCuenta;
    }

    virtual void depositar(double ingreso) {
        balance += ingreso;
    }

    virtual void retirar(double retiro) = 0;

    virtual void mostrarInfo() = 0;
};

class CajaDeAhorro : public Banco {
private:
    int mostrarContador;

public:
    CajaDeAhorro(double balance, string titularCuenta) : Banco(balance, titularCuenta), mostrarContador(0) {}

    void retirar(double retiro) override {
        if (balance < retiro) {
            cout << "El dinero a retirar es mayor a la cantidad disponible." << endl;
            return;
        }
        balance -= retiro;
    }

    void mostrarInfo() override {
        if (mostrarContador >= 3) { // Descuento después de mostrar más de 2 veces
            balance -= 20;
        }
        cout << "Balance: " << balance << "\n";
        cout << "Nombre del titular: " << titularCuenta << "\n";
        cout << "Tipo de cuenta: Caja de Ahorro\n";
        mostrarContador++;
    }

    friend class CuentaCorriente;
};

class CuentaCorriente : public Banco {
private:
    CajaDeAhorro *cajaDeAhorro;

public:
    CuentaCorriente(double balance, string titularCuenta, CajaDeAhorro *cajaDeAhorro) : Banco(balance, titularCuenta) {
        this->cajaDeAhorro = cajaDeAhorro;
    }

    void retirar(double retiro) override {
        if (balance < retiro) {
            cajaDeAhorro->retirar(retiro); // Utiliza el método retirar de CajaDeAhorro
            return;
        }
        balance -= retiro;
    }

    void mostrarInfo() override {
        cout << "Balance: " << balance << "\n";
        cout << "Nombre del titular: " << titularCuenta << "\n";
        cout << "Tipo de cuenta: Cuenta Corriente\n";
    }
};

int main() {
    double balance;
    string titularCuenta;
    int opcion;

    cout << "Ingrese el balance de la cuenta: ";
    cin >> balance;
    cout << "Ingrese el nombre del titular de la cuenta: ";
    cin >> titularCuenta;

    CajaDeAhorro caja_ahorro(balance, titularCuenta);
    CuentaCorriente cuentacorriente(balance, titularCuenta, &caja_ahorro);

    do {
        cout << "\nOpciones:\n";
        cout << "1. Depositar dinero\n";
        cout << "2. Retirar dinero\n";
        cout << "3. Mostrar información de la cuenta de ahorro\n";
        cout << "4. Mostrar información de la cuenta corriente\n";
        cout << "5. Salir\n";
        cout << "Ingrese una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                double ingreso;
                cout << "Ingrese la cantidad de dinero a depositar: ";
                cin >> ingreso;
                caja_ahorro.depositar(ingreso);
                break;
            }
            case 2: {
                double retiro;
                cout << "Ingrese la cantidad de dinero a retirar: ";
                cin >> retiro;
                cuentacorriente.retirar(retiro);
                break;
            }
            case 3: {
                caja_ahorro.mostrarInfo();
                break;
            }
            case 4: {
                cuentacorriente.mostrarInfo();
                break;
            }
            case 5: {
                break;
            }
            default:
                cout << "Opción no válida.\n";
        }

        this_thread::sleep_for(chrono::seconds(2));
    } while (opcion != 5);

    return 0;
}
