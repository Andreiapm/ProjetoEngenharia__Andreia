///Condicao para nao definir a classe mais de uma vez
#ifndef CEstatistica_h
#define CEstatistica_h

///inclui vector pois ha parametros declarados que sao vetores
#include <vector>     

class CEstatistica;

///Classe que calcula estatisticas do vetor, como media e desvio padrao, util para regressao
class CEstatistica
{
private:
       
  double media;
  double desvio;
  
public:
  
  ///retorna a media do vetor informado
  double Media(std::vector<double> v); 
  
  ///retorna o desvio padrao do vetor informado
  double DesvioPadrao(std::vector<double> v);
  
};

#endif
