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
        CajaDeAhorro(double balanceInicial, string titularCuenta)
            : Banco(balanceInicial, titularCuenta), mostrarContador(0) {}

        void retirar(double retiro) override {
            if (balance < retiro) { // Si el retiro es mayor al balance disponible se muestra un mensaje y se retorna sin hacer nada
                cout << "El dinero a retirar es mayor a la cantidad disponible." << endl;
                return;
            }
            balance -= retiro;
        }

        void mostrarInfo() override {
            if (balance < 0) {
                cout << "El balance no puede ser negativo.\n";
                return;
            }
            mostrarContador++; // Se incrementa el contador
            if (mostrarContador >= 3) { // Si se ha mostrado 3 veces el balance se descuenta $20
                balance -= 20;
            }
            cout << "Balance: " << balance << "\n";
            cout << "Nombre del titular: " << titularCuenta << "\n";
            cout << "Tipo de cuenta: Caja de Ahorro\n";
        }

        friend class CuentaCorriente;
};


class CuentaCorriente : public Banco {
    private:
        CajaDeAhorro& cajaDeAhorro; // Referencia a la cuenta de ahorro
        double balanceCorriente;

    public:
        CuentaCorriente(double balanceCorriente, string titularCuenta, CajaDeAhorro& cajaDeAhorro)
            : Banco(balanceCorriente, titularCuenta),
            cajaDeAhorro(cajaDeAhorro),
            balanceCorriente(balanceCorriente) {} 

        void retirar(double retiro) override {
            if (balanceCorriente < retiro) {
                double retiroAhorro = retiro - balanceCorriente; // Retiro de la cuenta de ahorro
                balanceCorriente = 0; // Se vacía la cuenta corriente
                cajaDeAhorro.retirar(retiroAhorro); // Se retira de la cuenta de ahorro
            }else{
                balanceCorriente -= retiro; // Se retira de la cuenta corriente
            }
        }

        void mostrarInfo() override {
            cout << "Balance: " << balanceCorriente << "\n";
            cout << "Nombre del titular: " << titularCuenta << "\n";
            cout << "Tipo de cuenta: Cuenta Corriente\n";
        }
};

int main() {
    double balanceAhorro;
    double balanceCorriente;
    string titularCuenta;
    int opcion;

    cout << "Ingrese el nombre del titular de la cuenta: ";
    getline(cin, titularCuenta);

    cout << "Ingrese el balance de la cuenta de ahorro: ";
    cin >> balanceAhorro;

    cout << "Ingrese el balance de la cuenta corriente: ";
    cin >> balanceCorriente;

    CajaDeAhorro caja_ahorro(balanceAhorro, titularCuenta);
    CuentaCorriente cuentacorriente(balanceCorriente, titularCuenta, caja_ahorro);

    do {
        cout << "\nOpciones:\n";
        cout << "1. Depositar dinero a la cuenta de ahorro\n";
        cout << "2. Depositar dinero a la cuenta corriente\n";
        cout << "3. Retirar dinero de la cuenta de ahorro\n";
        cout << "4. Retirar dinero de la cuenta corriente\n";
        cout << "5. Mostrar información de la cuenta de ahorro\n";
        cout << "6. Mostrar información de la cuenta corriente\n";
        cout << "7. Salir\n";
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
                double ingreso;
                cout << "Ingrese la cantidad de dinero a depositar: ";
                cin >> ingreso;
                cuentacorriente.depositar(ingreso);
                break;
            }
            case 3: {
                double retiro;
                cout << "Ingrese la cantidad de dinero a retirar: ";
                cin >> retiro;
                caja_ahorro.retirar(retiro);
                break;
            }
            case 4: {
                double retiro;
                cout << "Ingrese la cantidad de dinero a retirar: ";
                cin >> retiro;
                cuentacorriente.retirar(retiro);
                break;
            }
            case 5: {
                caja_ahorro.mostrarInfo();
                break;
            }
            case 6: {
                cuentacorriente.mostrarInfo();
                break;
            }
            case 7: {
                cout << "Saliendo...\n";
                break;
            }
            default:
                cout << "Opción no válida.\n";
        }
        this_thread::sleep_for(chrono::seconds(2));
    } while (opcion != 7);

    return 0;
}
