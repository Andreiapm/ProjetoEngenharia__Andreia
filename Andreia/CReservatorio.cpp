#include "CReservatorio.h"

//inclui a biblioteca iostrem pois usa funcoes de entrada e saida de dados para a tela
#include <iostream>

//usa funcoes pertencentes ao namespace std
using namespace std;

//funcao de entrada de dados da classe
void CReservatorio::EntradaDados()
{
 
 cout << "Informe a porosidade da rocha reservatorio: " << endl;
 cin >> porosidade;
 cin.get(); 
 
 cout << "Informe a altura do reservatorio: " << endl;
 cin >> altura;
 cin.get();

}

//Funcao que preenche o sistemaunidade por um pequeno menu  
void CReservatorio::EntradaSistemaUnidades()
{
  cout << "Qual o sistema de unidades utilizado para informar os parametros:" << endl << 
       "1 - Americano (Oilfield)" << endl << "2 - Brasileiro (Petrobras)" << endl << 
       "3 - Sistema Internacional" << endl;
  int i;
  cin >> i;
  cin.get();
  
  //repete a entrada enquanto o valor for equivocado
  while ((i!=1)&&(i!=2)&&(i!=3))
  {
          cout << "Reinforme o sistema de unidades utilizado." << endl;
          cin>>i;
          cin.get(); 
  }
  
  if(i==1)
              sistemaUnidade = 141.2; 
  
  if(i==2)
              sistemaUnidade = 19.03;
  
  if (i==3)
              sistemaUnidade = 0.3183;
}

//funcao que acusa e conserta erro de entrada
void CReservatorio::Erro()
{
  //repete a entrada enquanto o valor for equivocado
  while (altura<0.00)
  { 
          cout << "Reinforme a altura: "<<endl; 
          cin >> altura;
          cin.get();
  }
  
  while ((porosidade<0.00) || (porosidade>1.00))
  { 
          cout << "Reinforme a porosidade: " << endl; 
          cin >> porosidade;
          cin.get();
  }        
  
}

//set
void CReservatorio::Porosidade(double _porosidade)
{
  porosidade = _porosidade;
}

//get
double CReservatorio::Porosidade() const
{
  return porosidade;   
}

//set
void CReservatorio::Altura(double _altura)
{
  altura = _altura;
}

//get
double CReservatorio::Altura() const
{
  return altura;   
}

//set
void CReservatorio::SistemaUnidade(double _sistemaUnidade)
{
  sistemaUnidade = _sistemaUnidade; 
}

//get
double CReservatorio::SistemaUnidade() const
{
  return sistemaUnidade;   
}
