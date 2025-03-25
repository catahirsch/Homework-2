// Programe una clase que permita expresar un determinado momento en el tiempo en
// el siguiente formato: HHh, MMm, SSs p.m./a.m. Por ejemplo: “03h, 14m, 42s p.m.”.
// Para este ejercicio, puede utilizar la librería iomanip con la funcionalidad provista por
// setw y/o setfill.
// Deberá ser capaz de:
// a. Poder ser inicializada sin parámetros (en cuyo caso el tiempo es 0h, 0m, 0s a.m.)
// b. Poder ser inicializada pasándole sólo la hora (en cuyo caso el tiempo es “HHh,
// 0m, 0s a.m.”).
// c. Poder ser inicializada pasándole sólo la hora y los minutos (en cuyo caso el
// tiempo es “HHh, MMm, 0s a.m.”)
// d. Poder ser inicializada pasándole sólo la hora, los minutos y los segundos (en
// cuyo caso el tiempo es “HHh, MMm, SSs a.m.”)
// e. Poder ser inicializada pasándole la hora, los minutos, los segundos y
// “p.m.”/”a.m.” (en cuyo caso el tiempo es “HHh, MMm, SSs p.m./a.m.”).
// f. Agregar funcionalidad a los puntos 1.b-1.e de manera tal que no se introduzcan
// valores fuera de los rangos (por ejemplo, es incorrecto introducir MM = 74).
// g. Permitir cambiar y leer en forma individual: la hora, los minutos, los segundos y
// si se trata de a.m. o p.m. También leer todo junto en el formato pedido.
// h. Escribir un método que escriba por pantalla la hora en formato de hora 0 a 24,
// donde no se utiliza “p.m.”/”a.m.”, por ejemplo, 13hs p.m. no es válido.
// i. Escriba un código que permita verificar cada una de las funcionalidades pedidas
// en 1.a-1.g. Para la verificación se deberá pedir que se interactúe con el
// programa ingresando los datos por teclado. Por ejemplo, en el caso de ingresar
// un valor erróneo, indicar esto por pantalla y permitir ingresar un nuevo valor o
// bien permitir salir del programa

#include <ctime>
#include <iomanip>
#include <iostream>
#include <thread>
#include <chrono> 
using namespace std;

class Tiempo{
    private:
        int horas, minutos, segundos;
        string AmPm;
        string formato;
    
    public:
        Tiempo(){
            setTiempo(0, 0, 0, "a.m.");
        }

        Tiempo(int horas){
            setTiempo(horas, 0, 0, "a.m.");
        }

        Tiempo(int horas, int minutos){
            setTiempo(horas, minutos, 0, "a.m.");
        }

        Tiempo(int horas, int minutos, int segundos){
            setTiempo(horas, minutos, segundos, "a.m.");
        }

        Tiempo(int horas, int minutos, int segundos, string AmPm){
            setTiempo(horas, minutos, segundos, AmPm);
        }
        
        void setHoras(int h){
            if (h<0 || h>=24){
                cout << "Error: Valor fuera de rango de horas" << endl;
                return;
            }
            if(h>12){
                AmPm = "p.m.";
                h -= 12;
            }
            else{
                AmPm = "a.m.";
                if(h==0){
                    h = 12;
                }
            }
            horas = h;
        }

        void setMinutos(int m){
            if (m<0 || m>59){
                cout << "Error: Valor fuera de rango de minutos" << endl;
                return;
            }
            minutos = m;
        }

        void setSegundos(int s){
            if (s<0 || s>59){
                cout << "Error: Valor fuera de rango de segundos" << endl;
                return;
            }
            segundos = s;
        }

        void setAmPm(string AmPm){
            if (AmPm != "a.m." && AmPm != "p.m."){
                cout << "Error: Valor incorrecto de a.m./p.m." << endl;
                return;
            }
            this->AmPm = AmPm;
        }

        void setTiempo(int h, int m, int s, string AmPm){
            setHoras(h);
            setMinutos(m);
            setSegundos(s);
            if (h <= 12) {
                setAmPm(AmPm);
            }
        }

        void printTiempo12(){
            cout << setw(2) << setfill('0') << horas << "h, " << setw(2) << setfill('0') << minutos << "m, " << setw(2) << setfill('0') << segundos << "s " << AmPm << endl;
        }

        void printTiempo24(){
            int horas24 = horas;  
            if(horas == 12 && AmPm == "a.m."){
                horas24 = 0;
            }else if(horas != 12 && AmPm == "p.m."){
                horas24 += 12;
            }
            cout << setw(2) << setfill('0') << horas24 << "h, " << setw(2) << setfill('0') << minutos << "m, " << setw(2) << setfill('0') << segundos << "s" << endl;
        }

        int getHoras(){
            return horas;
        }

        int getMinutos(){
            return minutos;
        }

        int getSegundos(){
            return segundos;
        }

        string getAmPm(){
            return AmPm;
        }
};

int main(){
    Tiempo t;
    int opcion;

    do{
        cout<<"Opciones: \n" << endl;
        cout<<"1. Mostrar la hora actual (formato 12h)\n"<<endl;
        cout<<"2. Mostrar la hora actual (formato 24h)\n"<<endl;
        cout<<"3. Ingresar hora\n"<<endl;
        cout<<"4. Cambiar horas\n"<<endl;
        cout<<"5. Cambiar minutos\n"<<endl;
        cout<<"6. Cambiar segundos\n"<<endl;
        cout<<"7. Cambiar AM/PM\n"<<endl;
        cout<<"8. Mostrar tiempo\n"<<endl;
        cout<<"9. Salir\n"<<endl;
        cout<<"Opcion: ";
        cin>>opcion;

        switch(opcion){
            case 1:
                t.printTiempo12();
                break;
            
            case 2:
                t.printTiempo24();
                break;
            
            case 3:{
                int h, m, s;
                string ampm;
                cout<<"Ingrese la hora: ";
                cin>>h;
                cout<<"Ingrese los minutos: ";
                cin>>m;
                cout<<"Ingrese los segundos: ";
                cin>>s;
                if (h<12){
                    cout<<"Ingrese (a.m./p.m.): ";
                    cin>>ampm;
                }
                t.setTiempo(h, m, s, ampm);
                break;
            }
            case 4:{
                int h;
                cout<<"Ingrese la hora: ";
                cin>>h;
                t.setHoras(h);
                break;
            }
            case 5:{
                int m;
                cout<<"Ingrese los minutos: ";
                cin>>m;
                t.setMinutos(m);
                break;
            }
            case 6:{
                int s;
                cout<<"Ingrese los segundos: ";
                cin>>s;
                t.setSegundos(s);
                break;
            }
            case 7:{
                string ampm;
                cout<<"Ingrese (a.m./p.m.): ";
                cin>>ampm;
                t.setTiempo(t.getHoras(), t.getMinutos(), t.getSegundos(), ampm);
                break; 
            }
            case 8:
                if (t.getHoras()>12){
                    t.printTiempo24();
                }
                else{
                    t.printTiempo12();
                }
                break;

            case 9:
                cout << "Saliendo..." << endl;
                break;
            
            default:
                cout << "Opcion invalida" << endl;
                break;
            
        }
        this_thread::sleep_for(chrono::seconds(2));

    } while (opcion != 9);

    return 0;
}
