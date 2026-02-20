#ifndef EMPLEADO_HH
#define EMPLEADO_HH
#include<iostream>
#include"Persona.hh"

class Empleado:public Persona //Empleado hereda caracteristifca de Persona  
{
    protected:
        int id;
        double sueldo;
    public:
        //constructor (debe de tener el mismo nombre de l clase)
        Empleado(int id = 0, double sueldo = 0); 
        //get 
        int getId();
        double getSueldo();
        //set
        void setId(int);
        void setSueldo(double);
        string metodoEmpleadoPublic();
    private:
        string metodoEmpleadoPrivate();
    protected:
        string metodoEmpleadoProtected();
};
#endif