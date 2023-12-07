///Condicao para nao definir a classe mais de uma vez
#ifndef CCaracterizacaoReservatorio_h
#define CCaracterizacaoReservatorio_h

class CCaracterizacaoReservatorio;


///Classe que caracteriza o reservatorio. 
class CCaracterizacaoReservatorio
{

 public:
       ///Funcao que analisa os resultados e caracteriza o reservatorio. 
        void Caracterizacao(double permeabilidade, double fatorpelicula, double indiceprodutividade, double raiopoco, double raioefetivo);
         
};
#endif
