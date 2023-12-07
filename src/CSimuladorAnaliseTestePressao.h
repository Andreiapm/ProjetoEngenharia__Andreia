#ifndef CSimuladorAnaliseTestePressao_h
#define CSimuladorAnaliseTestePressao_h

#include <fstream>
#include <iostream>
///inclusao de arquivos de classe necessarios

#include "cgnuplot.h"
#include "CReservatorio.h"
#include "CFluido.h"
#include "CPoco.h"
#include "CDadosRegistradorPressao.h"
#include "CEstatistica.h"
#include "CAjusteCurva.h"
#include "CCaracterizacaoReservatorio.h"

#include "CMetodo.h"
#include "CBuildUp.h"
#include "CMetodoHorner.h"
#include "CMetodoMDH.h"



///criacao do objeto caracterizar da classe CCaracterizacao.h"

class CSimuladorAnaliseTestePressao;

///Classe que faz a analise do teste de pressao realizado no campo e infere as propriedades do reservatorio
class CSimuladorAnaliseTestePressao
{
      
 public: 
	 ///Nome do Arquivo exportado
	 std::string nome;
         ///pressao inicial que se encontrava o reservatorio     
         double pressaoInicial;
         ///queda de pressao referente ao fator de pelicula
         double pressaoDano; 
         ///indice de produtividade do reservatorio
         double indiceProdutividade;     
         ///eficiencia de fluxo do reservatorio
         double eficienciaFluxo;
         ///raio efetivo do poco
         double raioEfetivo;
         ///coeficiente de estocagem do poco
	 double coeficienteEstocagem;
	 ///tempo de duracao do efeito de estocagem
	 double tempoEstocagem;
	 ///cria objeto de armazenamento de dados
	 std::ofstream fout;
         ///criacao do objeto poco da classe CPoco
         CPoco poco;
         ///criacao do objeto fluido da classe CFluido
         CFluido fluido;
         ///criacao do objeto reservatorio da classe CReservatorio
         CReservatorio reservatorio;
         ///criacao do objeto registrador da classe CRegistrador
         CDadosRegistradorPressao registrador;
         ///criacao do objeto ajuste da classe CAjuste
         CAjusteCurva ajuste;
         ///criacao do objeto caracterizar da classe CCaracterizacao
         CCaracterizacaoReservatorio caracterizar;
         ///criacao do objeto buildup
         CBuildUP* buildup;
         ///criacao do objeto plot da classe CGnuplot
         //CGnuplot plot;
	 
 public:
        
        ///Funcao que calcula e preenche o atributo permeabilidade
        void CalculoPermeabilidade ();
        ///Funcao que calcula e preenche o atributo pressaoinicial
        void CalculoPressaoInicial ();
        ///Funcao que calcula e preenche o atributo fatorpelicula
        void CalculoFatorPelicula ();
        ///Funcao que calcula e preenche o atributo raioefetivo
        void CalculoRaioEfetivo ();
        ///Funcao que calcula e preenche os atributos indiceprodutividade, eficienciafluxo, pressaodano
        void CalculoIndices ();
        ///Funcao que calcula e preenche os atributos coeficienteestocagem e tempoestocagem
        void CalculoEstocagem ();
        ///Funcao que chama as entradas de dados necessarias
        void EntradaDados();
        ///Funcao principal que executa a simulacao do teste
        void Executar();
		
		///Varia parametros de reservatorio
		void Variacao();
        ///Funcao que exporta os dados para um arquivo.dat
        void Exporta ();

     
};



#endif
