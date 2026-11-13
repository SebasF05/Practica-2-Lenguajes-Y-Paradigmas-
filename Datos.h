#ifndef DATOS_H
#define DATOS_H
#include <string>
#include <vector>
using namespace std;

vector<vector<double>> leerCSV(const string& ruta);

void separarXy(const vector<vector<double>>& datos,
               vector<vector<double>>& X,
               vector<double>& y);

void DivEntrenamiento(const vector<vector<double>>& X, const vector<double>& y,
                      vector<vector<double>>& Xent, vector<double>& yent,
                      vector<vector<double>>& Xpru, vector<double>& ypru);

#endif