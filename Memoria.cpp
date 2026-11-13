#include "Memoria.h"
#include "LinearRegression.h"
#include <iostream>
#include <vector>
using namespace std;

LinearRegression modeloGlobal(4);

void AnalisisMemoria() {
    LinearRegression modeloLocal(4);
    LinearRegression* modeloDinamico = new LinearRegression(4);

    cout << " UN MODELO EN CADA MEMORIA " << endl;
    cout << "Global:   direccion " << &modeloGlobal << "  tamano " << sizeof(modeloGlobal) << endl;
    cout << "Local:    direccion " << &modeloLocal << "  tamano " << sizeof(modeloLocal) << endl;
    cout << "Dinamico: direccion " << modeloDinamico << "  tamano " << sizeof(*modeloDinamico) << endl;
    cout << "El puntero modeloDinamico (la variable) vive en: " << &modeloDinamico
         << "  tamano " << sizeof(modeloDinamico) << endl;
    cout << endl;

    cout << " ARREGLO DE 3 MODELOS EN MEMORIA DINAMICA " << endl;
    LinearRegression* arreglo = new LinearRegression[3];
    cout << "Direccion del arreglo: " << arreglo << endl;
    for (int i = 0; i < 3; i++) {
        cout << "  elemento " << i << ": " << &arreglo[i] << endl;
    }
    cout << "tamano de un elemento: " << sizeof(arreglo[0]) << endl;
    cout << "tamano total (3 elementos): " << 3 * sizeof(LinearRegression) << endl;
    cout << "sizeof(arreglo), solo el puntero: " << sizeof(arreglo) << endl;
    cout << endl;

    cout << " VECTOR DE 3 MODELOS EN MEMORIA DINAMICA " << endl;
    vector<LinearRegression>* v = new vector<LinearRegression>(3, LinearRegression(4));
    cout << "Direccion del objeto vector: " << v << endl;
    cout << "Direccion del primer modelo: " << &(*v)[0] << endl;
    cout << "sizeof del objeto vector: " << sizeof(*v) << endl;
    cout << "tamano de los 3 modelos en el heap: " << v->size() * sizeof(LinearRegression) << endl;

    delete[] arreglo;
    delete v;
    delete modeloDinamico;
}