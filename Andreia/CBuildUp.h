#ifndef CBUILDUP_H
#define CBUILDUP_H

/**
 * Classe virtual para metodos aplicaveis
 * Declaração dos calculos basicos de reservatorio
 * 
 * @param m_Permeabilidade, m_Viscosidade
 * 
*/

class CBuildUP {

    public:

    virtual ~CBuildUP() = default;

    virtual void CalculoPermeabilidade(double _sitemaUnidade, double _vazao, double _fatorVolumeFormacao, double _viscosidade, double _m, double _altura);
    virtual void CalculoFatorPelicula(double _m, double _tempoProducao, double _n, double _pressao, double _sistemaUnidade, double _porosidade, double _viscosidade, double _compressibilidade, double _raioPoco );

    double getPermeabilidade() { return m_Permeabilidade; }
    double getPelicula() {return m_Pelicula; }

    protected:

        double m_Permeabilidade;
        double m_Pelicula;

};

#endif