/*--------------------------------------
Roberto Lopez Rodriguez
Actividad 4
Proposito: Escribe un programa en C++ que genere lo siguiente:
El porcentaje tanto de hombres como de mujeres registrados en el hospital.
El número de pacientes de cada una de las categorías de condición.
El nombre y teléfono de todos los pacientes que tuvieron una condición de ingreso de máxima gravedad (5).
Fecha de modificacion: 13/03/24 */



#include <iostream>
#include <iomanip>

using namespace std;

struct Domicilio {
    string calle= "";
    int numero;
    string colonia = "";
    int codigoPostal = 0;
    string ciudad= "";
    int telefono = 0;
};

struct Paciente {
    string nombreApellido= "";
    int edad;
    char sexo;
    int condicion;
    Domicilio domicilio;
};

void porcentaje(int, Paciente *);
void numCondicion(int, Paciente *);
void maxGravedad(int, Paciente *);
int main() {
    const int N= 100;
    Paciente * hospital;
    hospital = new Paciente[N];
    int numPacient = 2;
    hospital[0].domicilio.calle = "Luna";
    hospital[0].domicilio.numero = 121;
    hospital[0].domicilio.codigoPostal = 23453;
    hospital[0].domicilio.colonia = "Piramides";
    hospital[0].domicilio.ciudad = "Aguascalientes";
    hospital[0].domicilio.telefono = 56374821;
    hospital[0].nombreApellido= "Roberto Lopez";
    hospital[0].edad = 23;
    hospital[0].sexo = 'H';
    hospital[0].condicion = 5;

    hospital[1].domicilio.calle = "Lagos de luna";
    hospital[1].domicilio.numero = 123;
    hospital[1].domicilio.codigoPostal = 27849;
    hospital[1].domicilio.colonia = "Piramides";
    hospital[1].domicilio.ciudad = "Aguascalientes";
    hospital[1].domicilio.telefono = 4990000000;
    hospital[1].nombreApellido= "Filipina gutierrez";
    hospital[1].edad = 25;
    hospital[1].sexo = 'M';
    hospital[1].condicion = 4;

    porcentaje(numPacient, hospital);
    numCondicion(numPacient, hospital);
    maxGravedad(numPacient, hospital);
    return 0;
}
void porcentaje(int n, Paciente *Hospital)
{
    int numM = 0, numH = 0;
    for (int i = 0; i < n; ++i) {
        if (Hospital[i].sexo == 'H' || Hospital[i].sexo == 'h') {
           numH ++;
        } else if (Hospital[i].sexo == 'M' || Hospital[i].sexo == 'm') {
           numM ++;
        }
    }
    float porcentajeHombres = static_cast<float>(numH) / n * 100;
    float porcentajeMujeres = static_cast<float>(numM) / n * 100;
    cout << endl << "El prodcentaje de muejres es " << porcentajeMujeres;
    cout << endl << "El prodcentaje de Hombres es es " << porcentajeHombres<< endl;
}
void numCondicion(int n, Paciente * Hospital)
{
    int cond1 = 0, cond2 = 0, cond3 = 0, cond4 = 0, cond5 = 0;
    for (int i = 0; i < n; ++i) {
        switch (Hospital[i].condicion) {
            case 1:
                cond1++;
                break;
            case 2:
                cond2++;
                break;
            case 3:
                cond3++;
                break;
            case 4:
                cond4++;
                break;
            case 5:
                cond5++;
                break;
            default:
                break;
        }
    }

    // Impresión de resultados
    cout << "Numero de pacientes en condicion 1: " << cond1 << endl;
    cout << "Numero de pacientes en condicion 2: " << cond2 << endl;
    cout << "Numero de pacientes en condicion 3: " << cond3 << endl;
    cout << "Numero de pacientes en condicion 4: " << cond4 << endl;
    cout << "Numero de pacientes en condicion 5: " << cond5 << endl;
}
void maxGravedad(int n, Paciente *Hospital)
{
    cout << "Pacientes con condición de ingreso de maxima gravedad (5):" << endl;
    for (int i = 0; i < n; ++i) {
        if (Hospital[i].condicion == 5) {
            cout << "Nombre: " << Hospital[i].nombreApellido << ", Telefono: " << Hospital[i].domicilio.telefono << endl;
        }
    }

}