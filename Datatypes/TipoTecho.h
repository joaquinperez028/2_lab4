#ifndef TIPOTECHO_H
#define TIPOTECHO_H

#include <iostream>

enum class TipoTecho
{
    Liviano,
    Pesado
};

inline std::ostream &operator<<(std::ostream &os, TipoTecho t)
{
    switch (t)
    {
    case TipoTecho::Liviano:
        os << "Liviano";
        break;
    case TipoTecho::Pesado:
        os << "Pesado";
        break;
    }
    return os;
}

#endif
