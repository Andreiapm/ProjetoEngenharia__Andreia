///Condicao para nao definir a classe mais de uma vez
#ifndef CAjusteCurvaMinimosQuadrados_h  
#define CAjusteCurvaMinimosQuadrados_h

///inclui o cabecalho da classe que sera utilizada
#include "CEstatistica.h"              
///inclui vector pois ha parametros declarados que sao vetores
#include <vector>                     

class CAjusteCurvaMinimosQuadrados;

///Classe que obtem os coeficiente da regressao linear por meio do metodo dos minimos quadrados
class CAjusteCurvaMinimosQuadrados
{
 
 //encapsulamento que permite o acesso para a classe e para a classe herdeira
 protected:
        ///coeficiente angular da reta do tipo y=ax+b
        double coeficienteAngular;
        ///coeficiente linear da reta do tipo y=ax+b
        double coeficienteLinear;
        ///coeficiente de correlacao da reta do tipo y=ax+b
        double coeficienteCorrelacao;
        
        ///cria um objeto da classe CEstatistica para ser utilizado funcoes de calculo
        CEstatistica estatistica;   
        
 protected:

        ///Funcao que retorna o valor do coeficiente angular
        double CoeficienteAngular (std::vector<double> vx, std::vector<double> vy);

        ///Funao que retorna o valor do coeficiente angular logaritimico
        double CoeficienteAngularLog (std::vector<double> vx, std::vector<double> vy);
        
        ///Funcao que retorna o valor do coeficiente linear
        double CoeficienteLinear (std::vector<double> vx, std::vector<double> vy);
        ///Set do P1h
        double CoeficienteLinearP1h (double _P1h);
        
        ///Funcao que retorna o valor do coeficiente de correlacao
        double CoeficienteCorrelacao (std::vector<double> vx, std::vector<double> vy);

};

#endif
