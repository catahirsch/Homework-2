#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>

using namespace std;

class Estudiante {
    private:
        string nombreCompleto;
        int legajo;
        vector<pair<string, float> > cursos;

    public:
        Estudiante(string nombreCompleto, int legajo, vector<pair<string, float> > cursos = {}) 
            : nombreCompleto(nombreCompleto), legajo(legajo) {}

        string getNombreCompleto() const { return nombreCompleto; }
        int getLegajo() const { return legajo; }

        void agregarCurso(string nombreCurso, float nota) {
            for (auto& curso : cursos) {
                if (curso.first == nombreCurso) { 
                    curso.second = nota; // Actualiza la nota si el curso ya está
                    return;
                }
            }
            cursos.push_back({nombreCurso, nota});
        }

        float getPromedioGeneral() const {
            if (cursos.empty()) return 0.0;
            float suma = 0;
            for (const auto& curso : cursos)
                suma += curso.second;
            return suma / cursos.size();
        }

        bool operator<(const Estudiante& e) const {
            return nombreCompleto < e.nombreCompleto;
        }

        friend ostream& operator<<(ostream& os, const Estudiante& e) {
            os << e.nombreCompleto << " - " << e.legajo 
            << " - Promedio: " << e.getPromedioGeneral();
            return os;
        }
};

class Curso {
    private:
        string nombre;
        vector<Estudiante*> estudiantes;
        static const int capacidad = 20;

    public:
        Curso(string nombre) : nombre(nombre) {}

        string getNombre() const { return nombre; }

        void inscribirEstudiante(Estudiante* e) {
            if (estudiantes.size() < capacidad) {
                estudiantes.push_back(e);
            } else {
                cout << "Error: El curso está completo" << endl;
            }
        }

        void desinscribirEstudiante(int legajo) {
            auto it = remove_if(estudiantes.begin(), estudiantes.end(), 
                                [legajo](Estudiante* e) { return e->getLegajo() == legajo; });
            if (it != estudiantes.end()) {
                estudiantes.erase(it, estudiantes.end());
            } else {
                cout << "Error: No se encontró el estudiante" << endl;
            }
        }

        bool estaInscripto(int legajo) const {
            return any_of(estudiantes.begin(), estudiantes.end(),
                        [legajo](Estudiante* e) { return e->getLegajo() == legajo; });
        }

        bool estaCompleto() const { return estudiantes.size() == capacidad; }

        void imprimirEstudiantes() const {
            vector<Estudiante*> copia = estudiantes;
            sort(copia.begin(), copia.end(), 
                [](Estudiante* a, Estudiante* b) { return *a < *b; });

            for (Estudiante* e : copia)
                cout << *e << endl;
        }

        Curso* copiarCurso() const {
            Curso* nuevoCurso = new Curso(this->nombre);
            for (Estudiante* e : estudiantes) {
                nuevoCurso->inscribirEstudiante(e);
            }
            return nuevoCurso;
        }

        friend ostream& operator<<(ostream& os, const Curso& c) {
            os << c.nombre;
            return os;
        }
};

int main() {
    int opcion;
    vector<Curso> cursos;
    vector<Estudiante*> estudiantes;

    do {
        cout << "\nOpciones:\n"
             << "1. Inscribir estudiante\n"
             << "2. Desinscribir estudiante\n"
             << "3. Ver si un estudiante está inscripto\n"
             << "4. Ver si el curso está completo\n"
             << "5. Imprimir lista de estudiantes\n"
             << "6. Copiar curso\n"
             << "7. Dar el promedio de un estudiante\n"
             << "8. Salir\n"
             << "Ingrese una opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: {
                string nombreCurso, nombreEstudiante;
                int legajo; float nota;
                cout << "Ingrese el nombre del curso: ";
                getline(cin, nombreCurso);

                cout << "Ingrese el nombre completo del estudiante: ";
                getline(cin, nombreEstudiante);
                cout << "Ingrese el legajo del estudiante: ";
                cin >> legajo;
                cout<<"Ingrese la nota del estudiante: ";
                cin >> nota;
                cin.ignore();

                // Buscar o crear curso
                Curso* curso = nullptr;
                for (auto& c : cursos) {
                    if (c.getNombre() == nombreCurso) {
                        curso = &c;
                        break;
                    }
                }
                if (!curso) {
                    cursos.emplace_back(nombreCurso); // Agrega un nuevo curso al vector
                    curso = &cursos.back(); // Ahora curso apunta a la nueva instancia creada
                }

                // Buscar o crear estudiante
                Estudiante* estudiante = nullptr;
                for (auto* e : estudiantes) {
                    if (e->getLegajo() == legajo) {
                        estudiante = e;
                        break;
                    }
                }
                if (!estudiante) {
                    estudiante = new Estudiante(nombreEstudiante, legajo);
                    estudiantes.push_back(estudiante);
                }

                curso->inscribirEstudiante(estudiante);
                estudiante->agregarCurso(nombreCurso, nota);
                break;
            }
            case 2: {
                int legajo; 
                string nombreCurso;
                cout << "Ingrese el legajo del estudiante: ";
                cin >> legajo;
                cin.ignore();
                cout << "Ingrese el nombre del curso: ";
                getline(cin, nombreCurso);

                // Buscar el curso y desinscribir al estudiante
                for (auto& c : cursos) {
                    if (c.getNombre() == nombreCurso) {
                        c.desinscribirEstudiante(legajo);
                        break;
                    }
                }

                // Eliminar el estudiante de la lista de estudiantes global si ya no tiene cursos
                auto it = remove_if(estudiantes.begin(), estudiantes.end(),
                                    [legajo](Estudiante* e) { return e->getLegajo() == legajo; });

                if (it != estudiantes.end()) {
                    for (auto iter = it; iter != estudiantes.end(); ++iter) {
                        delete *iter; // Liberar memoria
                    }
                    estudiantes.erase(it, estudiantes.end());
                }

                break;
            }
            case 3: {
                int legajo;
                string nombreCurso;
                cout << "Ingrese el legajo del estudiante: ";
                cin >> legajo;
                cin.ignore();
                cout << "Ingrese el nombre del curso: ";
                getline(cin, nombreCurso);

                bool encontrado = false;
                for (const auto& c : cursos) {
                    if (c.getNombre() == nombreCurso && c.estaInscripto(legajo)) {
                        cout << "El estudiante está inscripto en el curso" << endl;
                        encontrado = true;
                        break;
                    }
                }
                if (!encontrado) {
                    cout << "El estudiante no está inscripto en el curso" << endl;
                }
                break;
            }
            case 4: {
                string nombreCurso;
                cout << "Ingrese el nombre del curso: ";
                getline(cin, nombreCurso);

                for (const auto& c : cursos) {
                    if (c.getNombre() == nombreCurso) {
                        if (c.estaCompleto()) {
                            cout << "El curso está completo" << endl;
                        } else {
                            cout << "El curso no está completo" << endl;
                        }
                        break;
                    }
                }
                break;
            }
            case 5: {
                string nombreCurso;
                cout << "Ingrese el nombre del curso: ";
                getline(cin, nombreCurso);

                for (const auto& c : cursos) {
                    if (c.getNombre() == nombreCurso) {
                        c.imprimirEstudiantes();
                        break;
                    }
                }
                break;
            }
            case 6: {
                string nombreCurso;
                cout << "Ingrese el nombre del curso a copiar: ";
                getline(cin, nombreCurso);

                for (const auto& c : cursos) {
                if (c.getNombre() == nombreCurso) {
                    cursos.push_back(*c.copiarCurso());
                    cout << "Curso copiado" << endl;
                    break;
                    }
                }   

                break;
            }
            case 7: {
                int legajo;
                cout << "Ingrese el legajo del estudiante: ";
                cin >> legajo;

                for (const auto& e : estudiantes) {
                    if (e->getLegajo() == legajo) {
                        cout << "Promedio general: " << e->getPromedioGeneral() << endl;
                        break;
                    }
                }
                break;
            }
            case 8:
                cout << "Saliendo..." << endl;
                break;

            default:
                cout << "Opción inválida." << endl;
        }
        this_thread::sleep_for(chrono::seconds(2));
    } while (opcion != 8);

    return 0;
}
