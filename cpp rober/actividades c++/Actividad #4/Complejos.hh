#ifndef COMPLEJOS_HH
#define COMPLEJOS_HH
#include<iostream>
using namespace std;

class Complejo
{
    private:
    double real;
    double imaginario;
    public:
    Complejo(double real = 0, double imaginario = 0);
    void setReal(double);
    void setImaginario(double);
    double getReal();
    double getImaginario();

    Complejo* Sumar(Complejo*);
    Complejo* Restar(Complejo*);
    Complejo* Multiplicar(Complejo*);
    Complejo* Dividir(Complejo*);
    Complejo* multiEscalar(double);

    void toString();
    bool equals(Complejo*);
};

#endif
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include <iostream>
#include <vector>
using namespace std;

class Termino {
public:
    int coef; // Coeficiente
    int exp;  // Exponente

    Termino(int c = 0, int e = 0) : coef(c), exp(e) {}
};

class Polinomio {
    int orden;                // Orden del polinomio
    vector<Termino> terminos; // Vector de términos

public:
    Polinomio(int ord = 0);
    void setcof(int, int);
    void setexp(int, int);
    int getcof(int) const;
    int getexp(int) const;

    Polinomio operator+(const Polinomio&) const;
    Polinomio operator-(const Polinomio&) const;
    Polinomio operator*(const Polinomio&) const;
    Polinomio& operator=(const Polinomio&);
    Polinomio& operator+=(const Polinomio&);
    Polinomio& operator-=(const Polinomio&);
    Polinomio& operator*=(const Polinomio&);

    friend ostream& operator<<(ostream&, const Polinomio&);
    friend istream& operator>>(istream&, Polinomio&);
};

#include <iostream>
#include <fstream>
using namespace std;

class Termino {
public:
    int cof;
    int exp;
    Termino(int cof = 0, int exp = 0);
    void setcof(int);
    void setexp(int);
    int getcof();
    int getexp();
};

Termino::Termino(int cof, int exp) {
    this->cof = cof;
    this->exp = exp;
}

void Termino::setcof(int cof) {
    this->cof = cof;
}

void Termino::setexp(int exp) {
    this->exp = exp;
}

int Termino::getcof() {
    return cof;
}

int Termino::getexp() {
    return exp;
}

class Polinomio {
    int orden;
    Termino* ter;
public:
    Polinomio(int orden = 0);
    ~Polinomio();
    void llenarPolinomio();
    Polinomio operator +(const Polinomio&) const;
    Polinomio operator -(const Polinomio&) const;
    Polinomio operator *(const Polinomio&) const;
    Polinomio& operator =(const Polinomio&);
    Polinomio& operator +=(const Polinomio&);
    Polinomio& operator -=(const Polinomio&);
    Polinomio& operator *=(const Polinomio&);
    friend ostream &operator<<(ostream &, const Polinomio &);
    friend istream &operator>>(istream &, Polinomio &);
};

Polinomio::Polinomio(int orden) : orden(orden) {
    ter = new Termino[orden + 1];
    for (int i = 0; i <= orden; ++i) {
        ter[i].setexp(orden - i);
    }
}

Polinomio::~Polinomio() {
    delete[] ter;
}

void Polinomio::llenarPolinomio() {
    for (int i = 0; i <= orden; i++) {
        cout << "Dame el coeficiente para x^" << ter[i].getexp() << ": ";
        int coef;
        cin >> coef;
        ter[i].setcof(coef);
    }
}

Polinomio Polinomio::operator +(const Polinomio& P) const {
    Polinomio res(orden);
    for (int i = 0; i <= orden; i++) {
        res.ter[i].setcof(ter[i].getcof() + P.ter[i].getcof());
    }
    return res;
}

Polinomio Polinomio::operator -(const Polinomio& P) const {
    Polinomio res(orden);
    for (int i = 0; i <= orden; i++) {
        res.ter[i].setcof(ter[i].getcof() - P.ter[i].getcof());
    }
    return res;
}

Polinomio Polinomio::operator *(const Polinomio& P) const {
    Polinomio res(orden + P.orden);
    for (int i = 0; i <= orden; i++) {
        for (int j = 0; j <= P.orden; j++) {
            int newExp = ter[i].getexp() + P.ter[j].getexp();
            int newCof = ter[i].getcof() * P.ter[j].getcof();
            bool found = false;
            for (int k = 0; k <= res.orden; k++) {
                if (res.ter[k].getexp() == newExp) {
                    res.ter[k].setcof(res.ter[k].getcof() + newCof);
                    found = true;
                    break;
                }
            }
            if (!found) {
                for (int k = 0; k <= res.orden; k++) {
                    if (res.ter[k].getcof() == 0) {
                        res.ter[k].setexp(newExp);
                        res.ter[k].setcof(newCof);
                        break;
                    }
                }
            }
        }
    }
    return res;
}

Polinomio& Polinomio::operator =(const Polinomio& P) {
    if (this != &P) {
        delete[] ter;
        orden = P.orden;
        ter = new Termino[orden + 1];
        for (int i = 0; i <= orden; i++) {
            ter[i] = P.ter[i];
        }
    }
    return *this;
}

Polinomio& Polinomio::operator +=(const Polinomio& P) {
    *this = *this + P;
    return *this;
}

Polinomio& Polinomio::operator -=(const Polinomio& P) {
    *this = *this - P;
    return *this;
}

Polinomio& Polinomio::operator *=(const Polinomio& P) {
    *this = *this * P;
    return *this;
}

ostream& operator<<(ostream& co, const Polinomio& P) {
    for (int i = 0; i <= P.orden; i++) {
        if (P.ter[i].getcof() != 0) {
            co << P.ter[i].getcof() << "x^" << P.ter[i].getexp() << " ";
        }
    }
    return co;
}

istream& operator>>(istream& ci, Polinomio& P) {
    for (int i = 0; i <= P.orden; i++) {
        cout << "Introduce el coeficiente para x^" << P.ter[i].getexp() << ": ";
        int coef;
        ci >> coef;
        P.ter[i].setcof(coef);
    }
    return ci;
}

int main() {
    int orden;
    cout << "Introduce el orden del polinomio: ";
    cin >> orden;

    Polinomio p1(orden), p2(orden);
    cout << "Introduce el primer polinomio:\n";
    cin >> p1;
    cout << "Introduce el segundo polinomio:\n";
    cin >> p2;

    Polinomio