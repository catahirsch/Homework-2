// 4. Se tiene una clase abstracta que representa una cuenta de banco genérica. Esta clase
// tiene los siguiente atributos y métodos:
// i. balance: el total de la cuenta (tipo double).
// ii. titularCuenta: nombre del dueño de la cuenta (string).
// iii. depositar(): deposita una cantidad de dinero en la cuenta.
// iv. retirar(): retira una cantidad de dinero de la cuenta (método virtual puro).
// v. mostrarInfo(): muestra la información de la cuenta (método virtual puro) que
// consta del balance, el tipo de cuenta y el nombre del titular.
// De esta clase se derivan dos subclases:
// CajaDeAhorro:
// • El método retirar() impide retirar más dinero del que existe en el balance.
// • Se realizará un descuento de $20 del balance luego de mostrar más de 2 veces
// la información de la cuenta.
// CuentaCorriente:
// • El método retirar() permite retirar dinero de la caja de ahorro si no existen
// suficientes fondos en este tipo de cuenta.
// • En caso de que la caja de ahorro tampoco tenga dinero, se imprimirá un aviso
// de que la cuenta no posee dinero. Utilizar friend para esto.
// Se pide:
// a. Establecer los especificadores de acceso (public, private y private) en los atributos y
// métodos de todas las clases, explicando su elección en función de la seguridad y la la
// flexibilidad para futuros requerimientos de cambio.
// b. Escriba el código para implementar todas clases.
// c. Escriba el código que permita probar los puntos mencionados para CajaDeAhorro y
// CuentaCorriente.

#include <iostream>
#include <string>
#include <thread>
#include <chrono> 
using namespace std;

class Banco{
    protected:
        double balance;
        string titularCuenta;

    public:

        Banco(double balance, string titularCuenta){
            this->balance = balance;
            this->titularCuenta = titularCuenta;
        }

        virtual void depositar(double ingreso){
            balance = balance + ingreso;
        }

        virtual void retirar(double retiro) = 0;

        virtual void mostrarInfo() = 0;
};

class CajaDeAhorro: public Banco{
    private:
        int mostrarContador;

    public:
        CajaDeAhorro(double balance, string titularCuenta): Banco(balance, titularCuenta), mostrarContador(0){}

        void retirar(double retiro) override{
            if(balance < retiro){
                cout << "El dinero a retirar es mayor a la cantidad disponible" << endl;
                return;
            }else{
                balance -= retiro;
            }
        }

        void mostrarInfo() override{
            if (mostrarContador > 2){
                balance -= 20;
            }
            cout << "Balance: " << balance << "\n" << endl;
            cout << "Nombre del titular: " << titularCuenta << "\n" << endl;
            cout << "Tipo de cuenta: Caja de Ahorro\n" << endl;
            mostrarContador += 1;
        }
        friend class CuentaCorriente;
};

class CuentaCorriente: public Banco{
    private:
        class CajaDeAhorro *cajaDeAhorro;

    public:
        CuentaCorriente(double balance, string titularCuenta, CajaDeAhorro *cajaDeAhorro) : Banco(balance, titularCuenta){
            this->cajaDeAhorro = cajaDeAhorro;
        }

        void retirar(double retiro) override{
            if(balance < retiro){
                cajaDeAhorro->retirar(retiro);
                return;
            } else if(cajaDeAhorro->balance < retiro){
                cout << "La cuenta no posee dinero" << endl;
                return;
            }
            balance -= retiro;
        }

        void mostrarInfo() override{
            cout << "Balance: " << balance << "\n" << endl;
            cout << "Nombre del titular: " << titularCuenta << "\n" << endl;
            cout << "Tipo de cuenta: Cuenta Corriente\n" << endl;
        }
};

int main(){
    double balance;
    string titularCuenta;
    int opcion;

    cout << "Ingrese el balance de la cuenta: ";
    cin >> balance;
    cout << "Ingrese el nombre del titular de la cuenta: ";
    cin >> titularCuenta;

    CajaDeAhorro caja_ahorro(balance, titularCuenta);
    CuentaCorriente cuentacorriente(balance, titularCuenta, &caja_ahorro);

    do{
        cout << "Opciones: \n" << endl;
        cout << "1. Depositar dinero\n" << endl;
        cout << "2. Retirar dinero\n" << endl;
        cout << "3. Mostrar información de la cuenta de ahorro\n" << endl;
        cout << "4. Mostrar información de la cuenta corriente\n" << endl;
        cout << "5. Salir\n" << endl;
        cout << "Ingrese una opción: ";
        cin >> opcion;

        switch(opcion){
            case 1:{
                double ingreso;
                cout << "Ingrese la cantidad de dinero a depositar: ";
                cin >> ingreso;
                caja_ahorro.depositar(ingreso);
                break;
            }
            case 2:{
                double retiro;
                cout << "Ingrese la cantidad de dinero a retirar: ";
                cin >> retiro;
            }

            case 3:{
                caja_ahorro.mostrarInfo();
                break;
            }

            case 4:{
                cuentacorriente.mostrarInfo();
                break;
            }

            case 5:{
                break;
            }
        } 
        this_thread::sleep_for(chrono::seconds(2));
    } while(opcion != 5);
    return 0;
}