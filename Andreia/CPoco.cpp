#include "CPoco.h"

//inclui a biblioteca iostrem pois usa funcoes de entrada e saida de dados para a tela
#include <iostream>

//usa funcoes pertencentes ao namespace std
using namespace std;

//funcao de entrada de dados da classe
void CPoco::EntradaDados()
{
 cout << "Informe a vazao de producao: " << endl;
 cin >> vazao;
 cin.get();
 
 cout << "Informe o tempo de producao: " << endl;
 cin >> tempoProducao;
 cin.get();
 
 cout << "Informe a pressao no poco: " << endl;
 cin >> pressaoPoco;
 cin.get();
 
 cout << "Informe o raio do poco: " << endl;
 cin >> raioPoco;
 cin.get();
}

//funcao que acusa e conserta erro de entrada
void CPoco::Erro()
{

  //repete a entrada enquanto o valor for equivocado
  
  while (tempoProducao<0.00)
  { 
          cout << "Reinforme o tempo de producao: " << endl;
          cin >> tempoProducao;
          cin.get();
  
  }
  
  while (pressaoPoco<0.00) 
  {
          cout << "Reinforme a pressão no poco: " << endl;
          cin >> pressaoPoco;
          cin.get(); 
  
  }
  while ((raioPoco<0.00) || (raioPoco>3.0))
  { 
          cout << "Reinforme o raio do poco: " << endl;   
          cin >> raioPoco;
          cin.get();
  }
}

//set
void CPoco::Vazao(double _vazao)
{
  vazao = _vazao;   
}

//get
double CPoco::Vazao() const
{
  return vazao;   
}

//set
void CPoco::TempoProducao(double _tempoProducao)
{
  tempoProducao = _tempoProducao;   
}

//get
double CPoco::TempoProducao() const
{
  return tempoProducao;   
}

//set
void CPoco::PressaoPoco(double _pressaoPoco)
{
  pressaoPoco = _pressaoPoco;  
}

//get
double CPoco::PressaoPoco() const
{
  return pressaoPoco;   
}

//set
void CPoco::RaioPoco(double _raioPoco)
{
  raioPoco = _raioPoco;
}

//get
double CPoco::RaioPoco() const
{
  return raioPoco;   
}
