#ifndef TIPOTECHO_H
#define TIPOTECHO_H

#include <iostream>

enum class tipoTecho
{
    Liviano,
    Pesado
};

inline std::ostream &operator<<(std::ostream &os, tipoTecho t)
{
    switch (t)
    {
    case tipoTecho::Liviano:
        os << "Liviano";
        break;
    case tipoTecho::Pesado:
        os << "Pesado";
        break;
    }
    return os;
}

#endif
