#include "LinearRegression.h"
#include <cmath>

LinearRegression::LinearRegression(int numCaracteristicas) {
    weights = vector<double>(numCaracteristicas, 0.0);
    bias = 0.0;
}

vector<double> LinearRegression::getWeights() const { return weights; }

double LinearRegression::getBias() const { return bias; }

double LinearRegression::promCol(const vector<vector<double>>& X, size_t c) const {
    double acum = 0.0;
    for (size_t f = 0; f < X.size(); f++) acum += X[f][c];
    return acum / X.size();
}

double LinearRegression::dispCol(const vector<vector<double>>& X, size_t c, double prom) const {
    double acum = 0.0;
    for (size_t f = 0; f < X.size(); f++) {
        double dist = X[f][c] - prom;
        acum += dist * dist;
    }
    return sqrt(acum / X.size());
}

void LinearRegression::guardarEscala(const vector<vector<double>>& X) {
    size_t cols = X[0].size();
    promCols.assign(cols, 0.0);
    dispCols.assign(cols, 1.0);

    for (size_t c = 0; c < cols; c++) {
        promCols[c] = promCol(X, c);
        double d = dispCol(X, c, promCols[c]);
        dispCols[c] = (d == 0.0) ? 1.0 : d;
    }
}

double LinearRegression::estimarFila(const vector<double>& fila) const {
    double res = bias;
    for (size_t c = 0; c < fila.size(); c++) res += weights[c] * fila[c];
    return res;
}

void LinearRegression::pasoAjuste(const vector<vector<double>>& X,
                                  const vector<double>& y,
                                  double tasa) {
    size_t filas = X.size();
    size_t cols = X[0].size();

    vector<double> ajusteW(cols, 0.0);
    double ajusteB = 0.0;

    for (size_t f = 0; f < filas; f++) {
        double desvio = y[f] - estimarFila(X[f]);
        for (size_t c = 0; c < cols; c++) {
            ajusteW[c] += -2.0 / filas * desvio * X[f][c];
        }
        ajusteB += -2.0 / filas * desvio;
    }

    for (size_t c = 0; c < cols; c++) {
        weights[c] -= tasa * ajusteW[c];
    }
    bias -= tasa * ajusteB;
}

vector<vector<double>> LinearRegression::data_scaling(const vector<vector<double>>& X) {
    guardarEscala(X);
    return escalarPrueba(X);
}

vector<vector<double>> LinearRegression::escalarPrueba(const vector<vector<double>>& X) const {
    vector<vector<double>> esc = X;
    for (size_t f = 0; f < X.size(); f++) {
        for (size_t c = 0; c < X[f].size(); c++) {
            esc[f][c] = (X[f][c] - promCols[c]) / dispCols[c];
        }
    }
    return esc;
}

void LinearRegression::fit(const vector<vector<double>>& X, const vector<double>& y,
                           double tasa, int rondas) {
    for (int r = 0; r < rondas; r++) {
        pasoAjuste(X, y, tasa);
    }
}

vector<double> LinearRegression::predict(const vector<vector<double>>& X) const {
    vector<double> est;
    for (const vector<double>& fila : X) {
        est.push_back(estimarFila(fila));
    }
    return est;
}

double LinearRegression::score(const vector<vector<double>>& X, const vector<double>& y) const {
    vector<double> est = predict(X);
    double total = 0.0;
    for (size_t i = 0; i < y.size(); i++) {
        double desvio = y[i] - est[i];
        total += desvio * desvio;
    }
    return total / y.size();
}