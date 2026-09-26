//Roberto Lopez Rodriguez 

#include<iostream>
int main()
{
    std::cout<<"Dame la edad de tu amigo y la tuya ";
    int edadAmigo, edadMia;
    std::cin>>edadAmigo>>edadMia;
    if(edadMia > edadAmigo){
        std:: cout<<"Tu eres mas viejo/n";
    }
    else 
    {
    if(edadMia < edadAmigo)
    {
        std::cout<<"Tu amigo es mas viejo/n";
       
    }
     else{
            std:: cout<<"Son igual de viejos/n";
        }
    }
}