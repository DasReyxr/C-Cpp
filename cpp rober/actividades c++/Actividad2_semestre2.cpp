/*--------------------------------------
Roberto Lopez Rodriguez
Actividad 2 
Proposito: Crear un codigo donde al colocar los colores de las franjas de una resistencia
te porporcione su valor y tolerancia
Fecha de modificacion: 21/02/24 */

#include<iostream>
#include<string.h>
using namespace std;
//structs

struct Codigo
{
    string franja1 = "", franja2 = "", franja3 = "", franja4 = "";

};
struct Resistor 
{
    float valor = 0.0, watts = 0.0;
    Codigo colores;
};
//protoripado
void lecturaRes(int, Resistor *);
int valCol(int, int, Resistor *);
void impresion( Resistor *);

int main()
{
    cout << "Dame cuantas resistencias vas a capturar: ";
    unsigned short num;
    cin >> num;
    Resistor rest[num];
    cout << "Recuerde que al capturar los datos todo debe ser en minusculas y sin espacios"<< endl;
    lecturaRes(num, rest);
    impresion(rest);
    cin.get();
    return 0;
}
void lecturaRes(int n, Resistor *resVal)
{
    for(int i = 0; i < n; i++)
   {
    cout << endl << "Dame el precio del resistor " << (i+1) << ": ";
    cin >> resVal[i].valor;
    cout << endl << "Dame los watts que soporta el resitor " << (i+1) << ": ";
    cin >> resVal[i].watts;
    fflush(stdin);
    cout << endl << "Ingresa el color de la primera franja del resistor " << (i+1) << ": ";
    getline(cin, resVal[i].colores.franja1);
    cout << endl << "Ingresa el color de la segunda franja del resistor " << (i+1) << ": ";
    getline(cin, resVal[i].colores.franja2);
    //fflush(stdin);
    cout << endl << "Ingresa el color de la tercera franja del resistor " << (i+1) << ": ";
    getline(cin, resVal[i].colores.franja3);
    cout << endl << "Ingresa el color de la cuarta franja del resistor " << (i+1) << ": ";
    getline(cin, resVal[i].colores.franja4);
   }
}
void impresion( Resistor *resVal)
{
    short int res;
    short int a = 1, NumRest = 0;
        cout << endl << "Que resistencia quieres visualizar(presione cero para terminar): ";
        cin >> NumRest; 
        while (NumRest !=0 )
        {
            NumRest--;
        cout << "\t\t"  << "Resistencia " << (NumRest + 1) << "";
        res = valCol(NumRest, a, resVal);
       cout << endl << resVal[NumRest].colores.franja1 << "\t" << 
       resVal[NumRest].colores.franja2 << "\t" << res << "%" << endl;
        for(int j = 1; j < 3;j++){
            res = valCol(NumRest, j, resVal);
            cout << res;
            a++;
        }
        res = valCol(NumRest, a, resVal);
        for (int i = 0; i < res; i++)
            cout << "0";
        
        a++;
        cout << " ohms con ";
        res = valCol(NumRest, a, resVal);
        if(res == 0)
        cout << "invalido";
        else
        cout << res << "% de tolerancia" << endl;
        a=1;  

        cout << endl << "Que resistencia quieres visualizar: ";
        cin >> NumRest;  
        }
}
int valCol(int j, int a, Resistor *resval)
{
    string A[10] = {"negro", "cafe", "rojo", "naranja", "amarillo", "verde", "azul","violeta", "gris", "blanco"};
    long int c = 0;
    switch (a)
    {
    case 1:
        for(int i = 0; i < 10; i++){
        if(resval[j].colores.franja1 == A[i])
            break;
        else
            c++;
    }
        break;
    
    case 2:
     for(int i = 0; i < 10; i++){
        if(resval[j].colores.franja2 == A[i])
            break;
        else
            c++;
    }
        break;
    case 3:
    c = 1;
    for(int i = 0; i < 10; i++){
        if(resval[j].colores.franja3 == A[i]){
            break;
        }
        else{
           c++;
        }
    }
    break;
    case 4:
    for(int i = 0; i < 10; i++){
        if(resval[j].colores.franja4 == "rojo"){
            c = 2;
            break;
        }else{
        if(resval[j].colores.franja4 == "dorado"){
            c = 5;
            break;
        }
        else{
            if(resval[j].colores.franja4 == "plateado"){
            c = 10;
            break;
            }
            }

        }
    }
        
    break;
    default:
    //cout << "Invalido";
    break;
    }
    return c;
}