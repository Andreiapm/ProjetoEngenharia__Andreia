#ifndef METODOHORNER_H
#define METODOHORNER_H

#include "CBuildUp.h"

class CMetodoHorner : public CBuildUP {

    public:

        CMetodoHorner() {};
        ~CMetodoHorner() {};

        virtual void CalculoPermeabilidade(double _sistemaUnidade, double _vazao, double _fatorVolumeFormacao, double _viscosidade, double _m, double _altura) override;
        virtual void CalculoFatorPelicula(double _m, double _tempoProducao, double _n, double _pressao, double _sistemaUnidade, double _porosidade, double _viscosidade, double _compressibilidade, double _raioPoco) override;


};

#endif