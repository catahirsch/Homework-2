// 3. Escriba una interfaz llamada “Numero” que indique la implementación de las
// operaciones suma, resta y multiplicación de números (si desea, puede también agregar
// la división), así como también un método denominado “toString” que muestra el
// número en formato string.
// a. De esta interfaz, se deben implementar las siguientes tres clases:
// • Clase “Entero”,
// • Clase “Real”,
// • Clase “Complejo”
// b. Verifique el funcionamiento de cada uno de estas clases mediante la
// implementación de cada una de las operaciones con los números que desee e
// imprima el resultado utilizando el método “toString”.

#include <iostream>
#include <complex>

using namespace std;

class Numero{
    public:

    virtual int suma(Numero numero) = 0;
    virtual int resta(Numero numero) = 0;
    virtual int multiplicacion(Numero numero) = 0;
    virtual int division(Numero numero) = 0;
    virtual string toString() = 0;
}

class Entero{
    public:

    int numero;
    Entero(int numero){
        this->numero = numero;
    }

    int suma(Entero numero){
        return this->numero + entero->numero;
    }
    int resta(Entero numero){
        return this->numero - entero->numero;
    }
    int multiplicacion(Entero numero){
        return this->numero * entero->numero;
    }
    int division(Entero numero){
        return this->numero / entero->numero;
    }
}

class Real{
    public:
    float numero;
    Real(float numero){
        this->numero = numero;
    }
    float suma(Real numero){
        return this->numero + real->numero;
    }
    float resta(Real numero){
        return this->numero - real->numero;
    }
    float multiplicacion(Real numero){
        return this->numero * real->numero;
    }
    float division(Real numero){
        return this->numero / real->numero;
    }
}

class Complejo{
    public:
    complex<float>c;

    Complejo(complex<float>c){
        this->c = c;
    }

    complex<float> suma(Complejo numero){
        return this->c + complejo->c;
    }
    complex<float> resta(Complejo numero){
        return this->c - complejo->c;
    }
    complex<float> multiplicacion(Complejo numero){
        return this->c1 * complejo->c;
    }
    complex<float> division(Complejo numero){
        return this->c1 / complejo->c;
    }
}
