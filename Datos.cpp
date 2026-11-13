#include "Datos.h"
#include <iostream>
#include <fstream>
#include <sstream>

vector<vector<double>> leerCSV(const string& ruta) {
    vector<vector<double>> datos;
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir: " << ruta << endl;
        return datos;
    }

    string linea;
    getline(archivo, linea);

    while (getline(archivo, linea)) {
        vector<double> fila;
        stringstream ss(linea);
        string celda;
        while (getline(ss, celda, ',')) {
            fila.push_back(stod(celda));
        }
        datos.push_back(fila);
    }
    return datos;
}

void separarXy(const vector<vector<double>>& datos,
               vector<vector<double>>& X,
               vector<double>& y) {
    for (const vector<double>& fila : datos) {
        y.push_back(fila.back());
        X.push_back(vector<double>(fila.begin(), fila.end() - 1));
    }
}

void DivEntrenamiento(const vector<vector<double>>& X, const vector<double>& y,
                      vector<vector<double>>& Xent, vector<double>& yent,
                      vector<vector<double>>& Xpru, vector<double>& ypru) {
    for (size_t i = 0; i < X.size(); i++) {
        if (i % 10 == 0 || i % 10 == 3 || i % 10 == 6) {
            Xpru.push_back(X[i]);
            ypru.push_back(y[i]);
        } else {
            Xent.push_back(X[i]);
            yent.push_back(y[i]);
        }
    }
}