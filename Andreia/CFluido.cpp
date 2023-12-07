#include "CFluido.h"

//inclui a biblioteca iostrem pois usa funcoes de entrada e saida de dados para a tela
#include <iostream>

using namespace std;


//funcao de entrada de dados da classe
void CFluido::EntradaDados()
{
 cout << "Informe o fator volume-formacao do fluido: " << endl;
 cin >> fatorVolumeFormacao;
 cin.get();
 
 cout << "Informe a viscosidade do fluido: " << endl;
 cin >> viscosidade;
 cin.get(); 
 
 cout << "Informe a compressibilidade total (fluido+rocha): " << endl;
 cin >> compressibilidade;
 cin.get();
}

//funcao que acusa e conserta erro de entrada
void CFluido::Erro()
{
  
  //repete a entrada enquanto o valor for equivocado
   
  while (fatorVolumeFormacao<0.00)
  {
         cout << "Reinforme o Fator Volume-Formacao: " << endl;
         cin >> fatorVolumeFormacao;
         cin.get();
  }
  
  while (viscosidade<0.00)
  { 
          cout << "Reinforme a viscosidade." << endl; 
          cin >> viscosidade;
          cin.get();
  }
  
  while (compressibilidade<0.00)
  {
          cout << "Reinforme a compressibilidade." << endl; 
          cin >> compressibilidade;
          cin.get();
  }
}


//set
void CFluido::FatorVolumeFormacao(double _fatorVolumeFormacao)
{
  fatorVolumeFormacao = _fatorVolumeFormacao;   
}

//get
double CFluido::FatorVolumeFormacao() const
{
  return fatorVolumeFormacao;   
}

//set
void CFluido::Viscosidade(double _viscosidade)
{
  viscosidade = _viscosidade;
}

//get
double CFluido::Viscosidade() const
{
  return viscosidade;   
}

//set
void CFluido::Compressibilidade(double _compressibilidade)
{
  compressibilidade = _compressibilidade;   
}

//get
double CFluido::Compressibilidade() const
{
  return compressibilidade;   
}

