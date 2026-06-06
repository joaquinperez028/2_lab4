#ifndef TIPOPUBLICACION_H
#define TIPOPUBLICACION_H

#include <iostream>

enum class TipoPublicacion
{
    Venta,
    Alquiler
};

inline std::ostream &operator<<(std::ostream &os, TipoPublicacion t)
{
    switch (t)
    {
    case TipoPublicacion::Venta:
        os << "Venta";
        break;
    case TipoPublicacion::Alquiler:
        os << "Alquiler";
        break;
    }
    return os;
}

#endif
