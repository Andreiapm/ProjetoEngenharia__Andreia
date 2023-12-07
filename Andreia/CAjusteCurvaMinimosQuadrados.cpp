#include "CAjusteCurvaMinimosQuadrados.h"

//inclui a biblioteca cmath pois usa a funcao logaritmica
#include <cmath>

//inclui a biblioteca vector pois usa funcoes dos vetores: push_back, resize
#include <vector>

//usa funcoes pertencentes ao namespace std
using namespace std;

//retorna o valor do coeficiente angular
double CAjusteCurvaMinimosQuadrados::CoeficienteAngular (vector<double> vx, vector<double> vy)
{
     double mnum = 0.0; //termo do denominador
     double mden = 0.0; //termo do numerador

     double mediax = estatistica.Media(vx);
     double mediay = estatistica.Media(vy);
     
     for (int j=0 ; j<vx.size() ; j++) //percorre todo o vetor
     { 
         //metodo dos minimos quadrados
        mnum = mnum + (vx[j] * (vy[j] - mediay));
        mden = mden + (vx[j] * (vx[j] - mediax));
     }
    
    return coeficienteAngular = mnum/mden;
       
}

double CAjusteCurvaMinimosQuadrados::CoeficienteAngularLog(std::vector<double> vx, std::vector<double> vy)
{
    double mnum = 0.0; //termo do denominador
    double mden = 0.0; //termo do numerador

    double mediax = estatistica.Media(vx);
    double mediay = estatistica.Media(vy);
     
    mnum = log10(vx[vx.size() - 1]) - log10(vx[0]);
    mden = vy[vy.size() - 1] - vy[0];
    
    return coeficienteAngular = mden/mnum;
}

//retorna o valor do coeficiente linear
double CAjusteCurvaMinimosQuadrados::CoeficienteLinear (vector<double> vx, vector<double> vy)
{
     return coeficienteLinear = estatistica.Media(vy) - (coeficienteAngular * estatistica.Media(vx));;
}

double CAjusteCurvaMinimosQuadrados::CoeficienteLinearP1h(double _P1h)
{
     return coeficienteLinear = _P1h;
}

//retorna o valor do coeficiente de correlacao
double CAjusteCurvaMinimosQuadrados::CoeficienteCorrelacao(vector<double> vx, vector<double> vy)
{
       double somar = 0.0;
       double variax = 0.0;
       double variay = 0.0;
       
       double mediax = estatistica.Media(vx);
       double mediay = estatistica.Media(vy);
       
       for (int j=0 ; j<vx.size() ; j++)
       {
           somar = somar + ((vx[j] - mediax) * (vy[j] - mediay));
           variax = variax + (pow ((vx[j] - mediax),2));
           variay = variay + (pow ((vy[j] - mediay),2));
       }
     
       return coeficienteCorrelacao = -somar / pow ((variax * variay),0.5); 
}
