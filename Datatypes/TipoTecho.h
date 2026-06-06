#ifndef TIPOTECHO_H
#define TIPOTECHO_H

#include <iostream>

enum class TipoTecho
{
    Liviano,
    DosAguas,
    Plano
};

inline std::ostream &operator<<(std::ostream &os, TipoTecho t)
{
    switch (t)
    {
    case TipoTecho::Liviano:
        os << "Liviano";
        break;
    case TipoTecho::DosAguas:
        os << "Dos aguas";
        break;
    case TipoTecho::Plano:
        os << "Plano";
        break;
    }
    return os;
}

#endif
