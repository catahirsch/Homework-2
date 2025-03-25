// 2. Escribir una clase denominada Curso que contiene un vector (std::vector) con
// punteros a objetos estudiantes. 
// a. El objeto estudiante simplemente cuenta con el nombre completo, su legajo
// (que es único por alumno), una lista de cursos con su nota final y los métodos
// que crea necesarios para obtener los datos del alumno: nombre completo,
// legajo y su promedio general. En función de esto, califique todos los atributos
// correctamente.
// b. Como se mencionó anteriormente, un objeto de la clase Curso contendrá la lista
// de estudiantes del curso (el vector conteniendo objetos tipo estudiante). La
// clase Curso permite:
// i. Inscribir y desinscribir estudiantes al curso.
// ii. Ver si un estudiante se encuentra inscripto o no en el curso buscándolo por
// su legajo.
// iii. Indicar si el curso está completo o no, teniendo en cuenta que el curso tiene
// una capacidad de 20 alumnos.
// iv. Imprimir la lista de estudiantes en orden alfabético. Para ello, utilice el
// algoritmo std::sort() en <algorithm>, el cual requerirá sobreescribir el
// operador “<”, y sobreescriba el operador “<<” (del método y clase que
// correspondan) para presentar los datos por pantalla.
// v. Dado que algunos cursos comparten la mayor parte de los estudiantes, se
// desea poder hacer una copia del objeto curso. Justifique su respuesta con
// un comentario en el código (esta puede llevar varias líneas), indicando de
// que tipo de copia se trata y como la hizo.
// c. ¿Qué tipo de relación existe entre los objetos curso y estudiante?
// d. Proporcione un menú que permita evaluar lo pedido en este ejercicio. 

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Estudiante{
    private:
        string nombreCompleto;
        int legajo;
        vector<pair<string, float>> cursos;
    
    public:
        Estudiante(string nombreCompleto, int legajo){
            this->nombreCompleto = nombreCompleto;
            this->legajo = legajo;
        }

        string getNombreCompleto(){
            return nombreCompleto;
        }

        int getLegajo(){
            return legajo;
        }

        void agregarCurso(string nombreCurso, float nota){
            cursos.push_back(make_pair(nombreCurso, nota));
        }

        float getPromedioGeneral(){
            float suma = 0;
            for (int i = 0; i < cursos.size(); i++){
                suma += cursos[i].second;
            }
            return suma / cursos.size();
        }

        bool operator<(Estudiante* e){
            return nombreCompleto < e->getNombreCompleto();
        }

        friend ostream& operator<<(ostream& os, Estudiante& e){
            os << e.nombreCompleto << " - " << e.legajo << " - " << e.getPromedioGeneral();
            return os;
        }
};

class Curso{
    private:
        vector<Estudiante*> estudiantes;
        int capacidad = 20;
    
    public:
        void inscribirEstudiante(Estudiante* e){
            if (estudiantes.size() < capacidad){
                estudiantes.push_back(e);
            }else{
                cout << "Error: El curso está completo" << endl;
            }
        }

        void desinscribirEstudiante(int legajo){
            for (int i = 0; i < estudiantes.size(); i++){
                if (estudiantes[i]->getLegajo() == legajo){
                    estudiantes.erase(estudiantes.begin() + i);
                    return;
                }
            }
            cout << "Error: No se encontró el estudiante" << endl;
        }

        bool estaInscripto(int legajo){
            for (int i = 0; i < estudiantes.size(); i++){
                if (estudiantes[i]->getLegajo() == legajo){
                    return true;
                }
            }
            return false;
        }

        bool estaCompleto(){
            return estudiantes.size() == capacidad;
        }

        void imprimirEstudiantes(){
            sort(estudiantes.begin(), estudiantes.end());
            for (int i = 0; i < estudiantes.size(); i++){
                cout << *estudiantes[i] << endl;
            }
        }

        Curso* copiarCurso(){
            Curso* nuevoCurso = new Curso();
            for (int i = 0; i < estudiantes.size(); i++){
                nuevoCurso->inscribirEstudiante(estudiantes[i]);
            }
            return nuevoCurso;
        }
}

int main(){
    Curso c;
    int opcion;

    do{
        cout << "Opciones: \n" << endl;
        cout << "1. Inscribir estudiante\n" << endl;
        cout << "2. Desinscribir estudiante\n" << endl;
        cout << "3. Ver si un estudiante está inscripto\n" << endl;
        cout << "4. Ver si el curso está completo\n" << endl;
        cout << "5. Imprimir lista de estudiantes\n" << endl;
        cout << "6. Copiar curso\n" << endl;
        cout << "7. Salir\n" << endl;
        cout << "Ingrese una opción: ";
        cin >> opcion;

        switch(opcion){
            case 1:{
                string nombreCompleto;
                int legajo;
                cout << "Ingrese el nombre completo del estudiante: ";
                cin >> nombreCompleto;
                cout << "Ingrese el legajo del estudiante: ";
                cin >> legajo;
                Estudiante* e = new Estudiante(nombreCompleto, legajo);
                c.inscribirEstudiante(e);
                break;
            }
            case 2:{
                int legajo;
                cout << "Ingrese el legajo del estudiante: ";
                cin >> legajo;
                c.desinscribirEstudiante(legajo);
                break;
            }
            case 3:{
                int legajo;
                cout << "Ingrese el legajo del estudiante: ";
                cin >> legajo;
                if (c.estaInscripto(legajo)){
                    cout << "El estudiante está inscripto" << endl;
                }else{
                    cout << "El estudiante no está inscripto" << endl;
                }
                break;
            }
            case 4:{
                if (c.estaCompleto()){
                    cout << "El curso está completo" << endl;
                }else{
                    cout << "El curso no está completo" << endl;
                }
                break;
            }
            case 5:
                c.imprimirEstudiantes();
                break;

            case 6:{
                Curso* nuevoCurso = c.copiarCurso();
                cout << "Curso copiado" << endl;
                break;
            }
            case 7:
                cout << "Saliendo..." << endl;
                break;
                
            default:
                cout << "Opción inválida" << endl;
                break;
        }
    } while (opcion != 7);

    return 0;
}