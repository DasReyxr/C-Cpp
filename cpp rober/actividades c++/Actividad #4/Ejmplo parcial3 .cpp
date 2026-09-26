#inlude <iostream>
#include <fstream>
using namespace std;

#define NUM 10

class Polinomio {
    int orden;
    int* cof;
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
    friend ostream& operator<<(ostream&, const Polinomio&);
    friend istream& operator>>(istream&, Polinomio&);
};

Polinomio::Polinomio(int orden) : orden(orden) {
    cof = new int[orden + 1]();
}

Polinomio::~Polinomio() {
    delete[] cof;
}

void Polinomio::llenarPolinomio() {
    for (int i = 0; i <= orden; i++) {
        cout << "Dame el coeficiente para x^" << i << ": ";
        cin >> cof[i];
    }
}

Polinomio Polinomio::operator +(const Polinomio& P) const {
    int maxOrden = max(orden, P.orden);
    Polinomio res(maxOrden);

    for (int i = 0; i <= maxOrden; i++) {
        if (i <= orden) res.cof[i] += cof[i];
        if (i <= P.orden) res.cof[i] += P.cof[i];
    }

    return res;
}

Polinomio Polinomio::operator -(const Polinomio& P) const {
    int maxOrden = max(orden, P.orden);
    Polinomio res(maxOrden);

    for (int i = 0; i <= maxOrden; i++) {
        if (i <= orden) res.cof[i] += cof[i];
        if (i <= P.orden) res.cof[i] -= P.cof[i];
    }

    return res;
}

Polinomio Polinomio::operator *(const Polinomio& P) const {
    int newOrden = orden + P.orden;
    Polinomio res(newOrden);

    for (int i = 0; i <= orden; i++) {
        for (int j = 0; j <= P.orden; j++) {
            res.cof[i + j] += cof[i] * P.cof[j];
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
    for (int i = P.orden; i >= 0; i--) {
        if (P.cof[i] != 0) {
            if (i != P.orden && P.cof[i] > 0) co << " + ";
            if (P.cof[i] < 0) co << " - ";
            if (abs(P.cof[i]) != 1 || i == 0) co << abs(P.cof[i]);
            if (i > 0) co << "x";
            if (i > 1) co << "^" << i;
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

int main() {
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