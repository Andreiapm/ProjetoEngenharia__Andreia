#include "CSimuladorAnaliseTestePressao.h"

//inclui a biblioteca iostrem pois usa funcoes de entrada e saida de dados para a tela
#include <iostream>

//inclui a biblioteca cmath pois usa a funcao logaritmica
#include <cmath>

//inclui a biblioteca vector pois usa funcoes dos vetores: push_back, resize
#include <vector>

//inclui a biblioteca que guarda os dados
#include <fstream>

//inclui biblioteca string que le caracteres
#include <string>

//biblioteca que permite manipulacao de variaveis
#include <sstream>

//usa funcoes pertencentes ao namespace std
using namespace std;

///sobrecarga operador >>
std::istream &operator>>(std::istream &is, CMetodo &metodo)
{
   unsigned int a;
   is >> a;
   metodo = static_cast<CMetodo>(a);

   return is;
}

///Funcao principal que executa a simulacao do teste
void CSimuladorAnaliseTestePressao::Executar()
{
    cout << endl << "PROGRAMA PARA CALCULO DE PARAMETROS DE RESERVATORIO POR TESTES DE PRESSAO" << endl 
         << endl << "1-Rodar o Programa" << endl << "2-Sair" << endl << endl;
    int i = 0;
    cin >> i;
    
    while (i==1) //quando terminar a execucao do programa, se o usuario quiser, o programa roda novamente
    {
         CMetodo ans;
            do
            {
               cout << "Escolha o metodo a ser aplicado: 1 - Horner, 2 - MDH " << endl;
               cin >> ans;
               cin.get();

               switch (ans)
               {
               case CMetodo::METODO_HORNER:
                  buildup = new CMetodoHorner();
                  break;
               case CMetodo::METODO_MDH:
                  buildup = new CMetodoMDH();
                  break;
               default:
                  cout << "Opcao invalida!!" << endl;
                  ans = CMetodo::none; 
                  break;
               }

            }while (ans == CMetodo::none);

           cout << "Entrada de Dados do teste de pressao realizado " << endl 
                  << "-------------------------------------------------" << endl;
     
             EntradaDados();
             double P1h = 0.0;
             if(ans == CMetodo::METODO_MDH)
               {
                  cout << "entre com valor P1h" << endl;
                  cin >> P1h;
                  cin.get();
               }

             cout << "Entrada de Dados Finalizada" << endl 
                  << "-------------------------------------------------" << endl << endl;
             cout << "Importacao dos dados do registrador de Pressao" << endl 
                  << "-------------------------------------------------" << endl << endl;
    
             registrador.Importa();
             cout << "Dados do registrador importados com sucesso" << endl << endl;
             
             cout << "Regressao Linear dos Dados" << endl 
                  << "-------------------------------------------------" << endl << endl;
                  
             ajuste.Regressao (registrador.TempoSemProducao(), registrador.PressaoMedida(), poco.TempoProducao(), ans, P1h);
             
             cin.get ();
              cout << "Localizando o Periodo Transiente" << endl 
                  << "-------------------------------------------------" << endl << endl;
             
             ajuste.Ajuste(registrador.TempoSemProducao(), registrador.PressaoMedida(), poco.TempoProducao(), ans, P1h);
             
             cout << "Regressao linear feita com sucesso" << endl
                  << "-------------------------------------------------" << endl;
             cout << "Ajuste N = " << ajuste.n << endl;
    
             //GERA O GRAFICO CASO USUARIO QUEIRA
             
             cout << "Deseja gerar o grafico: " << endl << "1-Sim" << endl << "2-Nao" << endl << endl << endl;
             int j;
             cin >> j;
             
             if (j==1)
             {	     

                      CGnuplot plot;
                      //gera o grafico com a reta perfeita obtida
                     if(ans == CMetodo::METODO_HORNER)
                     {
	                  plot.plot_slope (ajuste.m,ajuste.n);
	                  cin.get();
	                  if (ajuste.efeitoEstocagem==1)
             	      //compara com os pontos originais
	                  plot.plot_xy (ajuste.logt,registrador.PressaoMedida());
	                  cin.get();
                     } else if (ans == CMetodo::METODO_MDH)
                     {
                     plot.XLogscale();
	                  plot.plot_logSlope (ajuste.m,ajuste.n);
	                  cin.get();
	                  if (ajuste.efeitoEstocagem==1)
             	      //compara com os pontos originais
	                  plot.plot_xy (ajuste.logt,registrador.PressaoMedida());
	                  cin.get();
                     }
             }
  
  
             cout << "Parametros do Reservatorio" << endl 
                  << "-------------------------------------------------" << endl << endl;
             //CALCULOS
             CalculoPermeabilidade();
             CalculoPressaoInicial();
             CalculoFatorPelicula(); //guardar
             CalculoRaioEfetivo();
             CalculoIndices();
             Exporta();
             cin.get();
	     
             //se nao ocorreu estocagem
             if (ajuste.efeitoEstocagem==false)
                 cout << "Reservatorio sem o periodo de estocagem" << endl;
             else
                 {
                      CalculoEstocagem ();
                      //zera o valor em caso de novo calculo
                      ajuste.efeitoEstocagem = false;
                      }
    
             cout << "Caracterizacao do Reservatorio." << endl
                  << "-------------------------------------------------" << endl;
                  
             caracterizar.Caracterizacao(buildup->getPermeabilidade(), buildup->getPelicula(), indiceProdutividade, poco.RaioPoco(), raioEfetivo);
             cin.get();
	     
	     Variacao();
	     
             //Nova Escolha
             cout << "\n1-Rodar o Programa" << endl << "2-Sair" << endl << endl;
             cin >> i;
             }
}

//chama as outras entradas de dados
void CSimuladorAnaliseTestePressao::EntradaDados()
{ 
     reservatorio.EntradaSistemaUnidades();
     reservatorio.EntradaDados();
     reservatorio.Erro();
     fluido.EntradaDados();
     fluido.Erro();
     poco.EntradaDados();
     poco.Erro();      
}

//Calcula a permeabilidade
void CSimuladorAnaliseTestePressao::CalculoPermeabilidade ()
{
      buildup->CalculoPermeabilidade(reservatorio.SistemaUnidade(), poco.Vazao(), fluido.FatorVolumeFormacao(), fluido.Viscosidade(), ajuste.m, reservatorio.Altura());
    
}

//Calcula a pressao inicial
void CSimuladorAnaliseTestePressao::CalculoPressaoInicial()
{
      pressaoInicial = ajuste.n;
      cout << "Pressao Inicial: " << pressaoInicial;
      
      if (reservatorio.SistemaUnidade()==141.2)
         cout << " psi" << endl;
      
      if (reservatorio.SistemaUnidade()==19.03)
         cout << " kgf/cm2" << endl;
      
      if (reservatorio.SistemaUnidade()==0.3183)
         cout << " Pascal" << endl;
      
    		
}


//Calcula fator pelicula
void CSimuladorAnaliseTestePressao::CalculoFatorPelicula ()
{
       buildup->CalculoFatorPelicula(ajuste.m, poco.TempoProducao(), ajuste.n, poco.PressaoPoco(), reservatorio.SistemaUnidade(), reservatorio.Porosidade(), fluido.Viscosidade(), fluido.Compressibilidade(), poco.RaioPoco());
}

//Calcula raio efetivo
void CSimuladorAnaliseTestePressao::CalculoRaioEfetivo()
{
       raioEfetivo = poco.RaioPoco() * exp(-buildup->getPelicula()); 
       cout << "Raio Efetivo: " << raioEfetivo;
       
       if ((reservatorio.SistemaUnidade()==0.3183) || (reservatorio.SistemaUnidade()==19.03))
         cout << " metros" << endl;
       
       if (reservatorio.SistemaUnidade()==141.2)
         cout << " ft" << endl;
}

//Calcula do indice de produtividade, eficiencia de fluxo e queda de pressao referente ao dano
void CSimuladorAnaliseTestePressao::CalculoIndices ()
{
       pressaoDano = 0.869 * (-ajuste.m) * buildup->getPelicula();
       
       indiceProdutividade = poco.Vazao() / (pressaoInicial - poco.PressaoPoco());
       
       eficienciaFluxo = (pressaoInicial - poco.PressaoPoco() - pressaoDano) / (pressaoInicial - poco.PressaoPoco());
       
       cout << "Queda de Pressao devido ao dano: " << pressaoDano << endl;
       
       //Exibir em porcentagens
       cout << "Indice de Produtividade: " << indiceProdutividade*100.0 << " % " << endl << 
            "Eficiencia de Fluxo: " << eficienciaFluxo*100.0 << " % " << endl;
  	 
}

void CSimuladorAnaliseTestePressao::Variacao()
{
  cout << "-------------------------------------------------" << endl;
  cout << "Deseja variar algum parametro?" << endl;
  cout << "1- Sim | 2 - Nao" << endl;
  int resp;
  cin >> resp;
  cin.get();
  do
  {
    if (resp!=1 && resp!=2)
      {
	cout << "Alternativa Invalida" << endl;
	cout << "1- Sim | 2 - Nao" << endl;
	cin >> resp;
	cin.get();
      }
  }
  while (resp!=1 && resp!=2);
  if (resp == 1)
  {
     cout << "\nQual parametro deseja variar? " << endl;
     cout << "| 1 - Porosidade | 2 - Fator Volume de Formacao | 3 - Compressibilidade  | 4 - Viscosidade | " << endl;
     cin >> resp;
     cin.get();
  do
  {
    if (resp!=1 && resp!=2 && resp!=3 && resp!=4)
      {
	cout << "Alternativa Invalida" << endl;
	cout << "| 1 - Porosidade | 2 - Fator Volume de Formacao | 3 - Compressibilidade  | 4 - Viscosidade | " << endl;
	cin >> resp;
	cin.get();
      }
  }
  while (resp!=1 && resp!=2 && resp!=3 && resp!=4);
  int intervalo;
  double dp;
     switch (resp)
    {
      case 1:
	cout << "Digite um valor inicial para porosidade" << endl;
	double porosidadeInicial;
	cin >> porosidadeInicial;
	cin.get();
     while ((porosidadeInicial < 0.00) || ( porosidadeInicial > 1.00))
	  { 
	  cout << "Reinforme a porosidade Inicial: " << endl; 
          cin >> porosidadeInicial;
          cin.get();
	  }        
	cout << "Digite um valor Final para porosidade" << endl;
	double porosidadeFinal;
	cin >> porosidadeFinal;
	cin.get();
     while ((porosidadeFinal < 0.00) || ( porosidadeFinal > 1.00) || (porosidadeInicial > porosidadeFinal))
	  { 
          cout << "Reinforme a porosidade Final: " << endl; 
          cin >> porosidadeFinal;
          cin.get();
	  }
	cout << "Em quantos intervalos deseja dividir a porosidade?" << endl;
	cin >> intervalo;
	cin.get();
	dp=(porosidadeFinal - porosidadeInicial)/intervalo;
    for (int x = porosidadeInicial;porosidadeInicial <= porosidadeFinal;porosidadeInicial=porosidadeInicial+dp)
	{
	  reservatorio.Porosidade(porosidadeInicial);
   cout << "\nCalculo para porosidade : "<< porosidadeInicial <<endl;
   cout << "-------------------------------------------------" << endl;
	     CalculoPermeabilidade();
             CalculoPressaoInicial();
             CalculoFatorPelicula(); //guardar
             CalculoRaioEfetivo();
             CalculoIndices();
  cout << "-------------------------------------------------" << endl;
	  
   ostringstream strs;
   strs << porosidadeInicial;
   string porosidadeString = strs.str();
	     
   string formato = ").dat";
   string Saida = nome+"porosidade("+porosidadeString+formato;
		///abre aquivo    
  fout.open (Saida.c_str());
    
  fout << "Permeabilidade: " << buildup->getPermeabilidade();
      if ((reservatorio.SistemaUnidade()==141.2) || (reservatorio.SistemaUnidade()==19.03))
  fout << " milidarcy" << endl;
      if (reservatorio.SistemaUnidade()==0.3183)
         fout << " metros quadrados" << endl; ///criacao do objeto armazena da classe CSimuladorAnaliseTestePressao   
  fout << "Pressao Inicial: " << pressaoInicial;
      
      if (reservatorio.SistemaUnidade()==141.2)
         fout << " psi" << endl;
      
      if (reservatorio.SistemaUnidade()==19.03)
         fout << " kgf/cm2" << endl;
      
      if (reservatorio.SistemaUnidade()==0.3183)
         fout << " Pascal" << endl;
	 fout << "Fator de Pelicula: " << buildup->getPelicula() << endl;
	 fout << "Raio Efetivo: " << raioEfetivo;
       
      if ((reservatorio.SistemaUnidade()==0.3183) || (reservatorio.SistemaUnidade()==19.03))
         fout << " metros" << endl;
       
      if (reservatorio.SistemaUnidade()==141.2)
         fout << " ft" << endl;
	 fout << "Queda de Pressao devido ao dano: " << pressaoDano << endl;
       
       //Exibir em porcentagens
  fout << "Indice de Produtividade: " << indiceProdutividade*100.0 << " % " << endl <<"Eficiencia de Fluxo: " << eficienciaFluxo*100.0 << " % " << endl;
  fout.close();
  cout << "Dados Salvos com sucesso!" << endl;
  cout << "-------------------------------------------------" << endl;
  cin.get();
	}
    break;
 
      case 2:
	cout << "Digite um valor inicial para fator volume de formacao" << endl;
	double FatorVolformacaoInicial;
	cin >> FatorVolformacaoInicial;
	cin.get();
	 while ((FatorVolformacaoInicial < 0.00))
	  { 
	  cout << "Reinforme o fator volume de formacao Inicial: " << endl; 
          cin >> FatorVolformacaoInicial;
          cin.get();
	  }        
	cout << "Digite um valor Final para fator volume de formacao" << endl;
	double FatorVolformacaoFinal;
	cin >> FatorVolformacaoFinal;
	cin.get();
     while ((FatorVolformacaoFinal < 0.00)||(FatorVolformacaoInicial >FatorVolformacaoFinal))
	  { 
          cout << "Reinforme o fator volume de formacao Final: " << endl; 
          cin >> FatorVolformacaoFinal;
          cin.get();
	  }
	cout << "Em quantos intervalos deseja dividir o fator volume de formacao?" << endl;
	cin >> intervalo;
	cin.get();
	dp=(FatorVolformacaoFinal - FatorVolformacaoInicial)/intervalo;
    for (int x = FatorVolformacaoInicial;FatorVolformacaoInicial <= FatorVolformacaoFinal;FatorVolformacaoInicial+=dp)
	{
	  fluido.FatorVolumeFormacao(FatorVolformacaoInicial);
      cout << "\nCalculo para fator volume de formacao : "<< FatorVolformacaoInicial <<endl;
      cout << "-------------------------------------------------" << endl;
	   CalculoPermeabilidade();
      CalculoPressaoInicial();
      CalculoFatorPelicula(); //guardar
      CalculoRaioEfetivo();
      CalculoIndices();
      cout << "-------------------------------------------------" << endl;
	  
   ostringstream strs;
   strs << FatorVolformacaoInicial;
   string FatorVolformacaoString = strs.str();
	     
   string formato = ").dat";
   string Saida = nome+"FatorVolF("+FatorVolformacaoString+formato;
		///abre aquivo    
  fout.open (Saida.c_str());
    
  fout << "Permeabilidade: " << buildup->getPermeabilidade();
      if ((reservatorio.SistemaUnidade()==141.2) || (reservatorio.SistemaUnidade()==19.03))
  fout << " milidarcy" << endl;
      if (reservatorio.SistemaUnidade()==0.3183)
         fout << " metros quadrados" << endl; ///criacao do objeto armazena da classe CSimuladorAnaliseTestePressao   
  fout << "Pressao Inicial: " << pressaoInicial;
      
      if (reservatorio.SistemaUnidade()==141.2)
         fout << " psi" << endl;
      
      if (reservatorio.SistemaUnidade()==19.03)
         fout << " kgf/cm2" << endl;
      
      if (reservatorio.SistemaUnidade()==0.3183)
         fout << " Pascal" << endl;
	 fout << "Fator de Pelicula: " << buildup->getPelicula() << endl;
	 fout << "Raio Efetivo: " << raioEfetivo;
       
      if ((reservatorio.SistemaUnidade()==0.3183) || (reservatorio.SistemaUnidade()==19.03))
         fout << " metros" << endl;
       
      if (reservatorio.SistemaUnidade()==141.2)
         fout << " ft" << endl;
	 fout << "Queda de Pressao devido ao dano: " << pressaoDano << endl;
       
       //Exibir em porcentagens
  fout << "Indice de Produtividade: " << indiceProdutividade*100.0 << " % " << endl <<"Eficiencia de Fluxo: " << eficienciaFluxo*100.0 << " % " << endl;
  fout.close();
  cout << "Dados Salvos com sucesso!" << endl;
  cout << "-------------------------------------------------" << endl;
  cin.get();
	}
    
    break;
    
      case 3:
	cout << "Digite um valor inicial para Compressibilidade" << endl;
	double CompressibilidadeInicial;
	cin >> CompressibilidadeInicial;
	cin.get();
	while ((CompressibilidadeInicial < 0.00))
	  { 
	  cout << "Reinforme a compressibilidade: " << endl; 
          cin >> CompressibilidadeInicial;
          cin.get();
	  }        
	cout << "Digite um valor Final para Compressibilidade" << endl;
	double CompressibilidadeFinal;
	cin >> CompressibilidadeFinal;
	cin.get();
     while ((CompressibilidadeFinal < 0.00) || (CompressibilidadeInicial > CompressibilidadeFinal))
	  { 
          cout << "Reinforme a Compressibilidade: " << endl; 
          cin >> CompressibilidadeFinal;
          cin.get();
	  }
	cout << "Em quantos intervalos deseja dividir o Compressibilidade?" << endl;
	cin >> intervalo;
	cin.get();
	dp=(CompressibilidadeFinal - CompressibilidadeInicial)/intervalo;
    for (int x = CompressibilidadeInicial;CompressibilidadeInicial <= CompressibilidadeFinal;CompressibilidadeInicial+=dp)
	{
	  fluido.Compressibilidade(CompressibilidadeInicial);
   cout << "\nCalculo para Compressibilidade : "<< CompressibilidadeInicial <<endl;
   cout << "-------------------------------------------------" << endl;
	     CalculoPermeabilidade();
             CalculoPressaoInicial();
             CalculoFatorPelicula(); //guardar
             CalculoRaioEfetivo();
             CalculoIndices();
  cout << "-------------------------------------------------" << endl;
	  
   ostringstream strs;
   strs << CompressibilidadeInicial;
   string CompressibilidadeString = strs.str();
	     
   string formato = ").dat";
   string Saida = nome+"Compressibilidade("+CompressibilidadeString+formato;
		///abre aquivo    
  fout.open (Saida.c_str());
    
  fout << "Permeabilidade: " << buildup->getPermeabilidade();
      if ((reservatorio.SistemaUnidade()==141.2) || (reservatorio.SistemaUnidade()==19.03))
  fout << " milidarcy" << endl;
      if (reservatorio.SistemaUnidade()==0.3183)
         fout << " metros quadrados" << endl; ///criacao do objeto armazena da classe CSimuladorAnaliseTestePressao   
  fout << "Pressao Inicial: " << pressaoInicial;
      
      if (reservatorio.SistemaUnidade()==141.2)
         fout << " psi" << endl;
      
      if (reservatorio.SistemaUnidade()==19.03)
         fout << " kgf/cm2" << endl;
      
      if (reservatorio.SistemaUnidade()==0.3183)
         fout << " Pascal" << endl;
	 fout << "Fator de Pelicula: " << buildup->getPelicula() << endl;
	 fout << "Raio Efetivo: " << raioEfetivo;
       
      if ((reservatorio.SistemaUnidade()==0.3183) || (reservatorio.SistemaUnidade()==19.03))
         fout << " metros" << endl;
       
      if (reservatorio.SistemaUnidade()==141.2)
         fout << " ft" << endl;
	 fout << "Queda de Pressao devido ao dano: " << pressaoDano << endl;
       
       //Exibir em porcentagens
  fout << "Indice de Produtividade: " << indiceProdutividade*100.0 << " % " << endl <<"Eficiencia de Fluxo: " << eficienciaFluxo*100.0 << " % " << endl;
  fout.close();
  cout << "Dados Salvos com sucesso!" << endl;
  cout << "-------------------------------------------------" << endl;
  cin.get();
	}
    break;
    
      case 4:
	cout << "Digite um valor inicial para Viscosidade" << endl;
	double ViscosidadeInicial;
	cin >> ViscosidadeInicial;
	cin.get();
	while ((ViscosidadeInicial < 0.00))
	  { 
	  cout << "Reinforme a compressibilidade: " << endl; 
          cin >> ViscosidadeInicial;
          cin.get();
	  } 
	cout << "Digite um valor Final para Viscosidade" << endl;
	double ViscosidadeFinal;
	cin >> ViscosidadeFinal;
	cin.get();
     while ((ViscosidadeFinal < 0.00) || (ViscosidadeInicial > ViscosidadeFinal))
	  { 
          cout << "Reinforme a Viscosidade: " << endl; 
          cin >> ViscosidadeFinal;
          cin.get();
	  }
	cout << "Em quantos intervalos deseja dividir o Viscosidade?" << endl;
	cin >> intervalo;
	cin.get();
	dp=(ViscosidadeFinal - ViscosidadeInicial)/intervalo;
    for (int x = ViscosidadeInicial;ViscosidadeInicial <= ViscosidadeFinal;ViscosidadeInicial+=dp)
	{
	  fluido.Viscosidade(ViscosidadeInicial);
   cout << "\nCalculo para Viscosidade : "<< ViscosidadeInicial <<endl;
   cout << "-------------------------------------------------" << endl;
	     CalculoPermeabilidade();
             CalculoPressaoInicial();
             CalculoFatorPelicula(); //guardar
             CalculoRaioEfetivo();
             CalculoIndices();
  cout << "-------------------------------------------------" << endl;
	  
   ostringstream strs;
   strs << ViscosidadeInicial;
   string ViscosidadeString = strs.str();
	     
   string formato = ").dat";
   string Saida = nome+"Viscosidade("+ViscosidadeString+formato;
		///abre aquivo    
  fout.open (Saida.c_str());
    
  fout << "Permeabilidade: " << buildup->getPermeabilidade();
      if ((reservatorio.SistemaUnidade()==141.2) || (reservatorio.SistemaUnidade()==19.03))
  fout << " milidarcy" << endl;
      if (reservatorio.SistemaUnidade()==0.3183)
         fout << " metros quadrados" << endl; ///criacao do objeto armazena da classe CSimuladorAnaliseTestePressao   
  fout << "Pressao Inicial: " << pressaoInicial;
      
      if (reservatorio.SistemaUnidade()==141.2)
         fout << " psi" << endl;
      
      if (reservatorio.SistemaUnidade()==19.03)
         fout << " kgf/cm2" << endl;
      
      if (reservatorio.SistemaUnidade()==0.3183)
         fout << " Pascal" << endl;
	 fout << "Fator de Pelicula: " << buildup->getPelicula() << endl;
	 fout << "Raio Efetivo: " << raioEfetivo;
       
      if ((reservatorio.SistemaUnidade()==0.3183) || (reservatorio.SistemaUnidade()==19.03))
         fout << " metros" << endl;
       
      if (reservatorio.SistemaUnidade()==141.2)
         fout << " ft" << endl;
	 fout << "Queda de Pressao devido ao dano: " << pressaoDano << endl;
       
       //Exibir em porcentagens
  fout << "Indice de Produtividade: " << indiceProdutividade*100.0 << " % " << endl <<"Eficiencia de Fluxo: " << eficienciaFluxo*100.0 << " % " << endl;
  fout.close();
  cout << "Dados Salvos com sucesso!" << endl;
  cout << "-------------------------------------------------" << endl;
  cin.get();
	}
	
    break;
    }
  }
}

void CSimuladorAnaliseTestePressao::Exporta()
{
		//armazena a string digitada em nomeSaida
   
   cout << "\nInforme o nome do arquivo de saida com os parametros calculados pelo simulador: " << endl;
   cin >> nome;
   cin.get();
//    getline (cin, nome);    
   string formato = ".dat";
   string Saida = nome+formato;
		///abre aquivo    
  fout.open (Saida.c_str());
    
  fout << "Permeabilidade: " << buildup->getPermeabilidade();
      if ((reservatorio.SistemaUnidade()==141.2) || (reservatorio.SistemaUnidade()==19.03))
  fout << " milidarcy" << endl;
      if (reservatorio.SistemaUnidade()==0.3183)
         fout << " metros quadrados" << endl; ///criacao do objeto armazena da classe CSimuladorAnaliseTestePressao   
  fout << "Pressao Inicial: " << pressaoInicial;
      
      if (reservatorio.SistemaUnidade()==141.2)
         fout << " psi" << endl;
      
      if (reservatorio.SistemaUnidade()==19.03)
         fout << " kgf/cm2" << endl;
      
      if (reservatorio.SistemaUnidade()==0.3183)
         fout << " Pascal" << endl;
	 fout << "Fator de Pelicula: " << buildup->getPelicula() << endl;
	 fout << "Raio Efetivo: " << raioEfetivo;
       
//      if ((reservatorio.SistemaUnidade()==ESistemaUnidade::SI) || (reservatorio.SistemaUnidade()==19.03))
      if ((reservatorio.SistemaUnidade()==0.3183) || (reservatorio.SistemaUnidade()==19.03))
         fout << " metros" << endl;
       
      if (reservatorio.SistemaUnidade()==141.2)
         fout << " ft" << endl;
	 fout << "Queda de Pressao devido ao dano: " << pressaoDano << endl;
       
       //Exibir em porcentagens
  fout << "Indice de Produtividade: " << indiceProdutividade*100.0 << " % " << endl <<"Eficiencia de Fluxo: " << eficienciaFluxo*100.0 << " % " << endl;
  fout.close();
  cout << "Dados Salvos com sucesso!" << endl;
  cout << "-------------------------------------------------" << endl;
}
//Calcula os parametros da estocagem, se houver
void CSimuladorAnaliseTestePressao::CalculoEstocagem()
{
     coeficienteEstocagem = (poco.Vazao() * fluido.FatorVolumeFormacao() * registrador.TempoSemProducao(0)) 
                            / (24.0 * (registrador.PressaoMedida(0) - poco.PressaoPoco()));
     
     tempoEstocagem = ((60.0 + 3.5 * buildup->getPelicula())/(buildup->getPermeabilidade() * reservatorio.Altura())) 
                    * reservatorio.SistemaUnidade() * 24.0 * coeficienteEstocagem * fluido.Viscosidade(); 
                    
     cout << "Coeficiente de Estocagem: " << coeficienteEstocagem << endl 
        << "Tempo de Estocagem: " << tempoEstocagem;
     
      if ((reservatorio.SistemaUnidade()==141.2) || (reservatorio.SistemaUnidade()==19.03))
         cout << " horas" << endl;
      
      if (reservatorio.SistemaUnidade()==0.3183)
         cout << " segundos" << endl;
      
}


               
