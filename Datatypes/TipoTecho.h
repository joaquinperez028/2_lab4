#ifndef TIPOTECHO_H
#define TIPOTECHO_H

#include <iostream>

enum class tipoTecho
{
    Liviano,
    DosAguas,
    Plano
};

inline std::ostream &operator<<(std::ostream &os, tipoTecho t)
{
    switch (t)
    {
    case tipoTecho::Liviano:
        os << "Liviano";
        break;
    case tipoTecho::DosAguas:
        os << "Dos aguas";
        break;
    case tipoTecho::Plano:
        os << "Plano";
        break;
    }
    return os;
}

#endif
