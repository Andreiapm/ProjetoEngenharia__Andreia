///Condicao para nao definir a classe mais de uma vez
#ifndef CPoco_h  
#define CPoco_h

class CPoco;

///Classe contendo as caracteristicas do poco
class CPoco
{
      ///privados, so acessados por meio de funcoes get
      private:
         
         ///raio do poco
         double raioPoco;
         ///vazao de producao
         double vazao;
         ///tempo de producao
         double tempoProducao;
         ///pressao no poco
         double pressaoPoco;

      public:
 
        ///Funcao que recebe dados do usuario, preenchendo atributos raiopoco, vazao, tempoproducao, pressaopoco
        void EntradaDados();
        
        ///Funcao que verifica se houve erro na entrada de dados e pede nova entrada ate nao ocorrer erro
        void Erro();
        
        ///Funcao que seta o raiopoco
        void RaioPoco(double _raioPoco); 
        ///Funcao get do raiopoco         
        double RaioPoco() const;  
        
        ///Funcao que seta a vazao
        void Vazao(double _vazao); 
        ///Funcao get da vazao  
        double Vazao() const;              

        ///Funcao que seta o tempoproducao
        void TempoProducao(double _tempoProducao); 
        ///Funcao get do tempoproducao
        double TempoProducao() const;         
                   
        ///Funcao que seta a pressaopoco
        void PressaoPoco(double _pressaoPoco);
        ///Funcao get da pressaopoco  
        double PressaoPoco() const;                                 
         
};
#endif
