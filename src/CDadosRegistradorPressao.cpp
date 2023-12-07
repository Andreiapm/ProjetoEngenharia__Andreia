#include "CDadosRegistradorPressao.h" //inclui o cabecalho da classe                   

//inclui biblioteca para importacao de arquivos de disco
#include <fstream>                    

//inclui a biblioteca iostrem pois usa funcoes cin, cout
#include <iostream>

//inclui a biblioteca vector pois usa vetores
#include <vector>

//inclui a biblioteca string pois usa variaveis string
#include <string>

//usa funcoes pertencentes ao namespace std
using namespace std;

void CDadosRegistradorPressao::Importa()
{
  //limpa os vetores de importacao para novo preenchimento
  tempoSemProducao.resize(0);
  pressaoMedida.resize(0);
  
  //indica o que o eixo x representa
  string eixox;                         
  //indica o que o eixo y representa
  string eixoy;                         
  double x;
  double y;
  //nome do arquivo com os dados a serem importados
  string nomeArquivo;                   
  
  cout << "Informe o nome do arquivo com os dados do registrador de pressao: " << endl;
  //armazena a string digitada em nomearquivo
  getline (cin,nomeArquivo);             
  
  //cria objeto de importacao
  ifstream fin;                         
  //converte a string de c++ para c, necessario para funcao 
  fin.open (nomeArquivo.c_str());       
  
  //pega o primeiro valor, o nome do eixo x
  fin >> eixox;   
  //pega o segundo valor, o nome do eixo y                      
  fin >> eixoy;                         
  
  //fazer ate o fim do arquivo
  while (!fin.eof())                    
  {
  //valores de x e y alternados e separados por um espaco
    fin >> x;  
    //para adicionar no fim do vetor, otimizando memoria                         
    tempoSemProducao.push_back (x);     
    fin >> y;
    pressaoMedida.push_back (y);
  }
}

//set
void  CDadosRegistradorPressao::PressaoMedida(vector<double> _pressaoMedida)
{
      pressaoMedida = _pressaoMedida;
}
     
//get da posicao
double  CDadosRegistradorPressao::PressaoMedida(int posicao) const
{
                return pressaoMedida[posicao];  
} 

//get
vector<double>  CDadosRegistradorPressao::PressaoMedida() const
{
                return pressaoMedida;  
} 
    
//set          
void  CDadosRegistradorPressao::TempoSemProducao(vector<double> _tempoSemProducao)
{    
     tempoSemProducao = _tempoSemProducao;
}

//get da posicao
double CDadosRegistradorPressao::TempoSemProducao(int posicao) const
{    
     return tempoSemProducao[posicao];      
}

//get
vector<double> CDadosRegistradorPressao::TempoSemProducao() const
{    
     return tempoSemProducao;      
}
