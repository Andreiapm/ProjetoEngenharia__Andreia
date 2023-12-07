#include "CEstatistica.h"

//inclui a biblioteca vector pois usa a funcao size
#include <vector>

//inclui a biblioteca cmath pois usa a funcao pow
#include <cmath>

using namespace std;

double CEstatistica::Media(vector<double> v)
{
  double soma = 0.0;
  //loop que faz a soma de todos os elementos do vetor
  for ( int i = 0 ; i < (v.size()) ; i++) 
     soma = soma + v[i];
  
  return media = soma/v.size();
}

double CEstatistica::DesvioPadrao(vector<double> v)
{    
  double soma = 0.0;
  double vquadrado = 0.0;
  desvio = 0.0;
  
  //loop que faz a soma dos elementos do vetor elevados ao quadrado
  for ( int i = 0 ; i < (v.size()) ; i++)
  {
   soma = soma + v[i];
   vquadrado = vquadrado + (v[i]*v[i]);
  }
  
  
  return desvio = pow(((vquadrado - ((1.0/v.size())*soma*soma))/(v.size()-1.0)),0.5);
}
