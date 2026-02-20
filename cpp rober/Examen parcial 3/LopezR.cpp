#include <iostream>
#include <fstream>
#include<cstring>
using namespace std;
fstream archivo;

void creaEstructura();

class Polinomio{
    int orden;
    int* cof;
    public:
    Polinomio(int orden = 0);
    ~Polinomio();
    void llenarPolinomio();
    Polinomio operator+(Polinomio&);
    Polinomio operator-(Polinomio&);
    Polinomio operator *(Polinomio&);
    Polinomio& operator =(const Polinomio&);
    Polinomio& operator +=(const Polinomio&);
    Polinomio& operator -=(const Polinomio&);
    Polinomio& operator *=(const Polinomio&);
    friend ostream &operator<<(ostream &, const Polinomio &);
    friend istream &operator>>(istream &, Polinomio &);
    void guardarpolinomio(Polinomio &);
};


Polinomio::Polinomio(int orden)
{
    this->orden =orden;

}
void Polinomio::llenarPolinomio() {
    for (int i = 0; i < orden+1; i++) {
        cout << "Dame el coeficiente para x^" << i << ": ";
        cin >> this->cof[i];
    }
    Polinomio Guardar(orden);
    for(int i = 0; i < orden+1; i++) {
        Guardar.cof[i] = this->cof[i];
    }
    guardarpolinomio(Guardar);
}
Polinomio Polinomio::operator +(Polinomio& P)
{
    if(P.orden <= this->orden)
    {
    Polinomio res(orden);
    for(int i = 0; i < this->orden; i++)
    {
    res.cof[i] = this->cof[i] + P.cof[i];
    }
    return res;
    }
        Polinomio res(P.orden);
    for(int i = 0; i < P.orden; i++)
    {
    res.cof[i] = this->cof[i] + P.cof[i];
    }
    return res;
}
Polinomio Polinomio::operator -(Polinomio& P)
{
    if(P.orden <= this->orden)
    {
    Polinomio res(orden);
    for(int i = 0; i < this->orden; i++)
    {
    res.cof[i] = this->cof[i] - P.cof[i];
    }
    return res;
    }
    Polinomio res(P.orden);
    for(int i = 0; i < P.orden; i++)
    {
    res.cof[i] = this->cof[i] - P.cof[i];
    return res;
    };
}
Polinomio Polinomio::operator *(Polinomio& P){
    Polinomio res(orden + P.orden);
    for (int i = 0; i <= orden; i++) {
        for (int j = 0; j <= P.orden; j++) {
                res.cof[i] = this->cof[i] * P.cof[i];
            }
        }
    return res;
}
Polinomio& Polinomio::operator =(const Polinomio& P) {
    if (this == &P) return *this;

    delete[] cof;

    orden = P.orden;
    cof = new int[orden + 1];

    for (int i = 0; i <= orden; i++) {
        cof[i] = P.cof[i];
    }

    return *this;
}

Polinomio& Polinomio::operator +=(const Polinomio& P) {

    if (P.orden > orden) {
        int* newCof = new int[P.orden + 1]();
        for (int i = 0; i <= orden; i++) {
            newCof[i] = cof[i];
        }
        delete[] cof;
        cof = newCof;
        orden = P.orden;
    }

    for (int i = 0; i <= P.orden; i++) {
        cof[i] += P.cof[i];
    }

    return *this;
}

Polinomio& Polinomio::operator -=(const Polinomio& P) {
    if (P.orden > orden) {
        int* newCof = new int[P.orden + 1]();
        for (int i = 0; i <= orden; i++) {
            newCof[i] = cof[i];
        }
        delete[] cof;
        cof = newCof;
        orden = P.orden;
    }

    for (int i = 0; i <= P.orden; i++) {
        cof[i] -= P.cof[i];
    }

    return *this;
}


Polinomio& Polinomio::operator *=(const Polinomio& P) {
    for (int i = 0; i <= orden; i++) {
        for (int j = 0; j <= P.orden; j++) {
                this->cof[i] *= P.cof[i];
            }
        }
    return *this;
}
ostream& operator<<(ostream& co, const Polinomio& P) {
    for (int i = 0; i <= P.orden; i++) {
        if (P.cof[i] != 0) {
            co << P.cof[i] << "x^" << i << "+";
    }
    }
   return co;
}
istream& operator>>(istream& ci, Polinomio& P) {
    for (int i = 0; i <= P.orden; i++) {
        cout << "Introduce el coeficiente para x^" << i << ": ";
        ci >> P.cof[i];
    }
    return ci;
}
void guardarpolinomio(Polinomio & P){
    int cuenta = 0; 
    archivo.seekp((cuenta) * sizeof(Polinomio), ios::beg);
    archivo.write((char*)&P, sizeof(Polinomio));
    cuenta ++;
}
void creaEstructura() {
    archivo.open("Polinomio.dat", ios::binary | ios::out);
    Polinomio blanco(0);
    for (int i = 0; i < 12; i++)
        archivo.write((char *)&blanco, sizeof(Polinomio));
    cout << "Se genero correctamente el archivo" << endl;
    archivo.close();
}

int main() {
    archivo.open("Polinomios.dat", ios::binary | ios::in | ios::out);
    creaEstructura();
    int orden;
    cout << "Introduce el orden del polinomio: ";
    cin >> orden;

    Polinomio p1(orden), p2(orden);
    cout << "Introduce el primer polinomio:\n";
    cin >> p1;
    cout << "Introduce el segundo polinomio:\n";
    cin >> p2;

    Polinomio suma = p1 + p2;
    Polinomio resta = p1 - p2;
    Polinomio multiplicacion = p1 * p2;

    cout << "Suma: " << suma << endl;
    cout << "Resta: " << resta << endl;
    cout << "Multiplicación: " << multiplicacion << endl;

    p1 += p2;
    cout << "p1 += p2: " << p1 << endl;

    p1 -= p2;
    cout << "p1 -= p2: " << p1 << endl;

    p1 *= p2;
    cout << "p1 *= p2: " << p1 << endl;
    return 0;
}
