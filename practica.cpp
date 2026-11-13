#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "Datos.h"
#include "LinearRegression.h"
#include "Memoria.h"
using namespace std;

void Probar(const string& titulo, const string& ruta) {
    
    cout << titulo << endl;
    cout << endl;

    vector<vector<double>> datos = leerCSV(ruta);
    vector<vector<double>> X;
    vector<double> y;
    separarXy(datos, X, y);

    vector<vector<double>> Xent, Xpru;
    vector<double> yent, ypru;
    DivEntrenamiento(X, y, Xent, yent, Xpru, ypru);
    cout << "Filas de entrenamiento: " << Xent.size() << endl;
    cout << "Filas de prueba: " << Xpru.size() << endl;

    LinearRegression modelo(X[0].size());
    vector<vector<double>> XentEsc = modelo.data_scaling(Xent);
    modelo.fit(XentEsc, yent, 0.1, 1000);

    cout << "weights: ";
    for (double w : modelo.getWeights()) cout << w << " ";
    cout << endl;
    cout << "bias: " << modelo.getBias() << endl;

    vector<vector<double>> XpruEsc = modelo.escalarPrueba(Xpru);
    vector<double> yEst = modelo.predict(XpruEsc);
    for (size_t i = 0; i < yEst.size(); i++) {
        cout << "y est: " << yEst[i] << "   y real: " << ypru[i] << endl;
    }

    double mse = modelo.score(XpruEsc, ypru);
    cout << "score (MSE en prueba): " << mse << endl;
    cout << "error tipico (raiz del MSE): " << sqrt(mse) << endl;
    cout << endl;
}

int main() {
    Probar("Regresion Simple (helados)", "datos/Ice_cream_selling_data.csv");
    Probar("Regresion multiple (notas)", "datos/student_exam_scores.csv");
    AnalisisMemoria();
}