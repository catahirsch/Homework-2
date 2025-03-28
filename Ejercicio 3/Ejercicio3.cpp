#include <iostream>
#include <complex>

using namespace std;

class Numero {
public:
    virtual Numero* suma(Numero* numero) = 0;
    virtual Numero* resta(Numero* numero) = 0;
    virtual Numero* multiplicacion(Numero* numero) = 0;
    virtual Numero* division(Numero* numero) = 0;
    virtual string toString() = 0;
    virtual ~Numero() {}
};

class Entero;  // Declaración adelantada

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

    double getValor() { return valor; }
};

class Entero : public Numero {
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

class Complejo : public Numero {
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
    Numero* e1 = new Entero(5);
    Numero* e2 = new Entero(3);
    Numero* resultado = e1->suma(e2);
    if (resultado) {
        cout << "Suma Entero: " << resultado->toString() << endl;
        delete resultado;
    }

    delete e1;
    delete e2;

    Numero* r1 = new Real(5.5);
    Numero* r2 = new Real(3.3);
    resultado = r1->resta(r2);
    if (resultado) {
        cout << "Resta Real: " << resultado->toString() << endl;
        delete resultado;
    }

    delete r1;
    delete r2;

    Numero* c1 = new Complejo(1, 2);
    Numero* c2 = new Complejo(3, 4);
    resultado = c1->multiplicacion(c2);
    if (resultado) {
        cout << "Multiplicación Complejo: " << resultado->toString() << endl;
        delete resultado;
    }

    delete c1;
    delete c2;

    return 0;
}
