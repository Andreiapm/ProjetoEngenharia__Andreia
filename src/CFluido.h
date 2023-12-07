///Condicao para nao definir a classe mais de uma vez
#ifndef CFluido_h
#define CFluido_h   

class CFluido;

///Classe contendo as caracteristicas do fluido produzido
class CFluido
{
      ///privados, so acessados por meio de funcoes get
      private:
              
         ///Fator Volume formacao do fluido      
         double fatorVolumeFormacao;     
         ///Viscosidade
         double viscosidade;
         ///Compressibilidade Total
         double compressibilidade;
         
      public:
        
        ///Funcao que recebe dados do usuario, preenchendo atributos fatorvolumeformacao, viscosidade, 
        /// compressibilidade
        void EntradaDados();
        
        ///Funcao que verifica se houve erro na entrada de dados e pede nova entrada ate nao ocorrer erro
        void Erro();
        
        ///Funcao que seta o fatorvolumeformacao
        void FatorVolumeFormacao(double _fatorVolumeFormacao);
        ///Funcao get do fatorvolumeformacao
        double FatorVolumeFormacao() const;   
        
        ///Funcao que seta a viscosidade
        void Viscosidade(double _viscosidade);
        ///Funcao get da viscosidade
        double Viscosidade() const;
        
        ///Funcao que seta a compressibilidade
        void Compressibilidade(double _compressibilidade);
        ///Funcao get da compressibilidade
        double Compressibilidade() const;
 
};
#endif
