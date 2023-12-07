///Condicao para nao definir a classe mais de uma vez
#ifndef CAjusteCurva_h                                    
#define CAjusteCurva_h

///inclui a biblioteca vector pois ha declaracao de vetor
#include <vector>

///inclui o cabecalho da classe pai
#include "CAjusteCurvaMinimosQuadrados.h"
#include "CMetodo.h"                

///Declaracao da Classe filha de CAjusteCurvaMinimosQuadrados
class CAjusteCurva;             

///Classe que executa a regressao linear e ajusta ate a correlacao satisfatoria
class CAjusteCurva: public CAjusteCurvaMinimosQuadrados
{
 public:
         ///coef. angular
         double m;
         ///coef. linear
         double n;
         ///coef. de correlacao                        
         double r;
         ///indica que o coef. de correlacao nao foi satisfatorio (ha estocagem)                                            
	     bool efeitoEstocagem;
         ///ajuste de variavel para logaritmica                    
         std::vector<double> logt;       
 
 public:
        ///Funcao que executa a regressao linear atraves do metodo dos minimos quadrados
        void Regressao(std::vector<double> vx, std::vector<double> vy, double z, CMetodo _metodo, double _P1h);
        ///Funcao que ajusta a regressao para o periodo correto, removendo os pontos referentes a estocagem
        void Ajuste(std::vector<double> vx, std::vector<double> vy, double z, CMetodo _metodo, double _P1h);
         
};

///Fim da condicao de definicao da classe
#endif
