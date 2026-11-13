#ifndef LINEARREGRESSION_H
#define LINEARREGRESSION_H
#include <vector>
using namespace std;

class LinearRegression {
private:
    vector<double> weights;
    double bias;
    vector<double> promCols;
    vector<double> dispCols;

    double promCol(const vector<vector<double>>& X, size_t c) const;
    double dispCol(const vector<vector<double>>& X, size_t c, double prom) const;
    void guardarEscala(const vector<vector<double>>& X);
    double estimarFila(const vector<double>& fila) const;
    void pasoAjuste(const vector<vector<double>>& X,
                    const vector<double>& y,
                    double tasa);

public:
    LinearRegression(int numCaracteristicas = 1);

    vector<double> getWeights() const;
    double getBias() const;

    vector<vector<double>> data_scaling(const vector<vector<double>>& X);
    vector<vector<double>> escalarPrueba(const vector<vector<double>>& X) const;

    void fit(const vector<vector<double>>& X, const vector<double>& y,
             double tasa, int rondas);
    vector<double> predict(const vector<vector<double>>& X) const;
    double score(const vector<vector<double>>& X, const vector<double>& y) const;
};

#endif