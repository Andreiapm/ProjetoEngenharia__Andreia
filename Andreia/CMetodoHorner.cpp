#include "CMetodoHorner.h"

#include <iostream>
#include <cmath>

void CMetodoHorner::CalculoPermeabilidade(double _sistemaUnidade, double _vazao, double _fatorVolumeFormacao, double _viscosidade, double _m, double _altura)
{

    m_Permeabilidade = (1.151 * _sistemaUnidade * _vazao * _fatorVolumeFormacao * 
                    _viscosidade) / (-_m * _altura);
                    
      std::cout << "Permeabilidade: " << m_Permeabilidade;
  
      if ((_sistemaUnidade==141.2) || (_sistemaUnidade==19.03))
         std::cout << " milidarcy" << std::endl;
      
      if (_sistemaUnidade==0.3183)
         std::cout << " metros quadrados" << std::endl;

}

void CMetodoHorner::CalculoFatorPelicula(double _m, double _tempoProducao, double _n, double _pressao, double _sistemaUnidade, double _porosidade, double _viscosidade, double _compressibilidade, double _raioPoco)
{
    m_Pelicula = 1.151 * ((((_m * log10(_tempoProducao)) + _n - _pressao)/ 
                       -_m) - log10((_sistemaUnidade * m_Permeabilidade) / 
                       (_porosidade * _viscosidade * _compressibilidade
                       * _raioPoco  * _raioPoco)) - 0.3514 + log10 (_tempoProducao+1));

       
       std::cout << "Fator de Pelicula: " << m_Pelicula << std::endl;   
}
