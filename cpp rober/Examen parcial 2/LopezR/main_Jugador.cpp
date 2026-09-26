#include <iostream>
#include"Jugador.cpp"
using namespace std;

int main()
{  
     
     int total=2;//Total de equipos
     string nome,sede;
     
     //vector de tipo equipo
     Equipo  **liga;
     
     liga = new Equipo*[total];
     int n = 3;//Total de jugadores
     
     for (int i=0; i < total; i++)
     {
         cout << endl << "Nombre del equipo: " << i+1 << " ";
         fflush(stdin);
         getline(cin,nome);
         cout << endl << "Ciudad sede: ";
     fflush(stdin);
         getline(cin,sede);
        
         //vector de jugador para cada equipo
         Jugador *j;
         j = new Jugador[n];
         for(int x = 0; x < n; x++)
         {
             j[x].llenar();
          }//for x
        
         //instanciar equipo
         liga[i] = new Equipo(nome,sede,n,j);
     } //for i
    
    for(int i=0; i < total; i++)
        imprimir(*liga[i]);
    
    cin.get();   
    return 0;
}