///Condicao para nao definir a classe mais de uma vez
#ifndef CDadosRegistradorPressao_h  
#define CDadosRegistradorPressao_h

///inclui a biblioteca vector pois ha declaracao de vetor
#include<vector>
#include<string>

class CDadosRegistradorPressao;

///Classe que contem dados registrados do registrador de pressao
class CDadosRegistradorPressao
{
 ///privados, so acessados por meio de funcoes get
 private: 
         ///pressao medida apos o fechamento da producao
         std::vector<double> pressaoMedida;     
         ///tempo apos o fechamento da producao em que foi medida a pressao
         std::vector<double> tempoSemProducao; 
         
 public:
       
        ///Funcao que importa os dados registrados do arquivo .dat, preenchendo os atributos da classe
        void Importa();
        
        ///Funcao que seta a pressaomedida
        void PressaoMedida(std::vector<double> _pressaoMedida);                
        ///Funcao get da posicao informada do vetor pressaomedida
        double PressaoMedida(int posicao) const;      
        ///Funcao get da pressaomedida                            
        std::vector<double> PressaoMedida() const;                               
        
        ///Funcao que seta o temposemproducao
        void  TempoSemProducao(std::vector<double> _tempoSemProducao); 
        ///Funcao get da posicao informada do vetor temposemproducao  
        double TempoSemProducao(int posicao) const;
        ///Funcao get do temposemproducao                             
        std::vector<double> TempoSemProducao() const;                           
 
};
#endif
