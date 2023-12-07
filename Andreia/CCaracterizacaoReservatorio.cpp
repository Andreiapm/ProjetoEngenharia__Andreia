#include "CCaracterizacaoReservatorio.h"

//inclui a biblioteca iostrem pois usa funcoes de entrada e saida de dados para a tela
#include <iostream>

//usa funcoes pertencentes ao namespace std
using namespace std;

//Funcao que caracteriza o reservatorio, dado os parametros calculados
void CCaracterizacaoReservatorio::Caracterizacao (double permeabilidade, double fatorpelicula, double indiceprodutividade, double raiopoco, double raioefetivo)
{
     //condicoes que se satisfeitas, escrevem na tela caracteristicas do reservatorio.

    
  if (permeabilidade<=10)
     cout << "1 - Reservatorio com permeabilidade ruim." << endl;
  
  if ((permeabilidade<100)&&(permeabilidade>10))
     cout << "1 - Reservatorio com permeabilidade boa." << endl;
  
  if (permeabilidade>=100)
     cout << "1 - Reservatorio com permeabilidade excelente." << endl;
    
  if (fatorpelicula==0)
     cout << "2 - Reservatorio sem dano e sem estimulo." << endl;
  
  if (fatorpelicula<0)
     cout << "2 - Reservatorio estimulado" << endl;
             
  if ((fatorpelicula>0)&&(fatorpelicula<5))
     cout << "2 - Reservatorio com dano baixo, nao necessita de processos de acidificacao e/ou fraturamento hidraulico." << endl;
     
  if ((fatorpelicula>5)&&(fatorpelicula<10))
     cout << "2 - Reservatorio com dano intermediario, pode ser usado processos de acidificacao e/ou fraturamento hidraulico." << endl;
  
  if (fatorpelicula>10)
     cout << "2 - Reservatorio com dano alto, necessita de processos de acidificacao e/ou fraturamento hidraulico." << endl;
 
  if (indiceprodutividade<=0.01)
     cout << "3 - Reservatorio com produtividade baixo, considerar uso de tecnicas de recuperacao secundaria." << endl;
     
  if ((indiceprodutividade>0.01)&&(indiceprodutividade<0.1))
     cout << "3 - Reservatorio com produtividade regular, considerar uso de tecnicas de recuperacao secundaria." << endl;   

  if (indiceprodutividade>0.1)
     cout << "3 - Reservatorio com produtividade boa." << endl;   

  if ((raioefetivo/raiopoco)<=0.0001)
     cout << "4 - Razao de dano alto, pois o raio efetivo e muito menor que o raio do poco real, afetando a produtividade." << endl;
  
}

