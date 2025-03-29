#include <iostream>
#include <complex>

using namespace std;

class Numero { // Clase abstracta
public:
    virtual Numero* suma(Numero* numero) = 0; // Método virtual puro
    virtual Numero* resta(Numero* numero) = 0;
    virtual Numero* multiplicacion(Numero* numero) = 0;
    virtual Numero* division(Numero* numero) = 0;
    virtual string toString() = 0;
    virtual ~Numero() {}
};

class Entero; // Declaración adelantada de la clase Entero para poder usarla en la clase Real

class Real : public Numero {
private:
    double valor;

public:
    Real(double valor) : valor(valor) {}

    Numero* suma(Numero* numero) override;
    Numero* resta(Numero* numero) override;
    Numero* multiplicacion(Numero* numero) override;
    Numero* division(Numero* numero) override;

    string toString() override {
        return to_string(valor);
    }

    double getValor() { 
        return valor; 
    }
};

class Entero : public Numero { // Clase Entero que hereda de Numero
private:
    int valor;

public:
    Entero(int valor) : valor(valor) {}

    Numero* suma(Numero* numero) override {
        if (Entero* e = dynamic_cast<Entero*>(numero)) {
            return new Entero(valor + e->valor);
        } else if (Real* r = dynamic_cast<Real*>(numero)) {
            return new Real(valor + r->getValor());
        }
        cout << "No se puede sumar Entero con otro tipo" << endl;
        return nullptr;
    }

    Numero* resta(Numero* numero) override {
        if (Entero* e = dynamic_cast<Entero*>(numero)) {
            return new Entero(valor - e->valor);
        } else if (Real* r = dynamic_cast<Real*>(numero)) {
            return new Real(valor - r->getValor());
        }
        cout << "No se puede restar Entero con otro tipo" << endl;
        return nullptr;
    }

    Numero* multiplicacion(Numero* numero) override {
        if (Entero* e = dynamic_cast<Entero*>(numero)) {
            return new Entero(valor * e->valor);
        } else if (Real* r = dynamic_cast<Real*>(numero)) {
            return new Real(valor * r->getValor());
        }
        cout << "No se puede multiplicar Entero con otro tipo" << endl;
        return nullptr;
    }

    Numero* division(Numero* numero) override {
        if (Entero* e = dynamic_cast<Entero*>(numero)) {
            if (e->valor == 0) {
                cout << "Error: División por cero" << endl;
                return nullptr;
            }
            return new Entero(valor / e->valor);
        } else if (Real* r = dynamic_cast<Real*>(numero)) {
            if (r->getValor() == 0) {
                cout << "Error: División por cero" << endl;
                return nullptr;
            }
            return new Real(valor / r->getValor());
        }
        cout << "No se puede dividir Entero con otro tipo" << endl;
        return nullptr;
    }

    string toString() override {
        return to_string(valor);
    }

    int getValor() { return valor; }
};

// Implementación de los métodos de la clase Real
Numero* Real::suma(Numero* numero) {
    if (Real* r = dynamic_cast<Real*>(numero)) {
        return new Real(valor + r->valor);
    } else if (Entero* e = dynamic_cast<Entero*>(numero)) {
        return new Real(valor + e->getValor());
    }
    cout << "No se puede sumar Real con otro tipo" << endl;
    return nullptr;
}

Numero* Real::resta(Numero* numero) {
    if (Real* r = dynamic_cast<Real*>(numero)) {
        return new Real(valor - r->valor);
    } else if (Entero* e = dynamic_cast<Entero*>(numero)) {
        return new Real(valor - e->getValor());
    }
    cout << "No se puede restar Real con otro tipo" << endl;
    return nullptr;
}

Numero* Real::multiplicacion(Numero* numero) {
    if (Real* r = dynamic_cast<Real*>(numero)) {
        return new Real(valor * r->valor);
    } else if (Entero* e = dynamic_cast<Entero*>(numero)) {
        return new Real(valor * e->getValor());
    }
    cout << "No se puede multiplicar Real con otro tipo" << endl;
    return nullptr;
}

Numero* Real::division(Numero* numero) {
    if (Real* r = dynamic_cast<Real*>(numero)) {
        if (r->valor == 0) {
            cout << "Error: División por cero" << endl;
            return nullptr;
        }
        return new Real(valor / r->valor);
    }
    cout << "No se puede dividir Real con otro tipo" << endl;
    return nullptr;
}

class Complejo : public Numero { // Clase Complejo que hereda de Numero
private:
    complex<double> valor;

public:
    Complejo(double real, double imaginario) : valor(real, imaginario) {}

    Numero* suma(Numero* numero) override {
        if (Complejo* c = dynamic_cast<Complejo*>(numero)) {
            return new Complejo(valor.real() + c->valor.real(), valor.imag() + c->valor.imag());
        }
        cout << "No se puede sumar Complejo con otro tipo" << endl;
        return nullptr;
    }

    Numero* resta(Numero* numero) override {
        if (Complejo* c = dynamic_cast<Complejo*>(numero)) {
            return new Complejo(valor.real() - c->valor.real(), valor.imag() - c->valor.imag());
        }
        cout << "No se puede restar Complejo con otro tipo" << endl;
        return nullptr;
    }

    Numero* multiplicacion(Numero* numero) override {
        if (Complejo* c = dynamic_cast<Complejo*>(numero)) {
            complex<double> resultado = valor * c->valor;
            return new Complejo(resultado.real(), resultado.imag());
        }
        cout << "No se puede multiplicar Complejo con otro tipo" << endl;
        return nullptr;
    }

    Numero* division(Numero* numero) override {
        if (Complejo* c = dynamic_cast<Complejo*>(numero)) {
            if (c->valor == complex<double>(0, 0)) {
                cout << "Error: División por cero" << endl;
                return nullptr;
            }
            complex<double> resultado = valor / c->valor;
            return new Complejo(resultado.real(), resultado.imag());
        }
        cout << "No se puede dividir Complejo con otro tipo" << endl;
        return nullptr;
    }

    string toString() override {
        return to_string(valor.real()) + " + " + to_string(valor.imag()) + "i";
    }
};

int main() {
    Numero* e1 = new Entero(5); // Creación de un objeto Entero
    Numero* e2 = new Entero(3); // Creación de otro objeto Entero

    cout << "Entero 1: " << e1->toString() << endl;
    cout << "Entero 2: " << e2->toString() << "\n" << endl;

    Numero* resultado = e1->suma(e2);  // Suma de los dos objetos Entero
    if (resultado) {
        cout << "Suma Entero: " << resultado->toString() << endl;
        delete resultado;
    }
    resultado = e1->resta(e2); // Resta de los dos objetos Entero
    if (resultado) {
        cout << "Resta Entero: " << resultado->toString() << endl;
        delete resultado;
    }
    resultado = e1->multiplicacion(e2); // Multiplicación de los dos objetos Entero
    if (resultado) {
        cout << "Multiplicación Entero: " << resultado->toString() << endl;
        delete resultado;
    }
    resultado = e1->division(e2); // División de los dos objetos Entero
    if (resultado) {
        cout << "División Entero: " << resultado->toString() << "\n" << endl;
        delete resultado;
    }

    delete e1;
    delete e2;

    Numero* r1 = new Real(5.5); // Creación de un objeto Real
    Numero* r2 = new Real(3.3); // Creación de otro objeto Real

    cout << "Real 1: " << r1->toString() << endl;
    cout << "Real 2: " << r2->toString() << "\n" << endl;

    resultado = r1->suma(r2); // Suma de los dos objetos Real
    if (resultado) {
        cout << "Suma Real: " << resultado->toString() << endl;
        delete resultado;
    }
    resultado = r1->resta(r2); // Resta de los dos objetos Real
    if (resultado) {
        cout << "Resta Real: " << resultado->toString() << endl;
        delete resultado;
    }
    resultado = r1->multiplicacion(r2); // Multiplicación de los dos objetos Real
    if (resultado) {
        cout << "Multiplicación Real: " << resultado->toString() << endl;
        delete resultado;
    }
    resultado = r1->division(r2); // División de los dos objetos Real
    if (resultado) {
        cout << "División Real: " << resultado->toString() << "\n" << endl;
        delete resultado;
    }

    delete r1;
    delete r2;

    Numero* c1 = new Complejo(1, 2); // Creación de un objeto Complejo
    Numero* c2 = new Complejo(3, 4); // Creación de otro objeto Complejo

    cout << "Complejo 1: " << c1->toString() << endl;
    cout << "Complejo 2: " << c2->toString() << "\n" << endl;

    resultado = c1->suma(c2); // Suma de los dos objetos Complejo
    if (resultado) {
        cout << "Suma Complejo: " << resultado->toString() << endl;
        delete resultado;
    }
    resultado = c1->resta(c2); // Resta de los dos objetos Complejo
    if (resultado) {
        cout << "Resta Complejo: " << resultado->toString() << endl;
        delete resultado;
    }
    resultado = c1->multiplicacion(c2); // Multiplicación de los dos objetos Complejo
    if (resultado) {
        cout << "Multiplicación Complejo: " << resultado->toString() << endl;
        delete resultado;
    }
    resultado = c1->division(c2); // División de los dos objetos Complejo
    if (resultado) {
        cout << "División Complejo: " << resultado->toString() << "\n" << endl;
        delete resultado;
    }

    delete c1;
    delete c2;

    return 0;
}
