#ifndef TIPOPUBLICACION_H
#define TIPOPUBLICACION_H

#include <iostream>

enum class tipoPublicacion
{
    Venta,
    Alquiler
};

inline std::ostream &operator<<(std::ostream &os, tipoPublicacion t)
{
    switch (t)
    {
    case tipoPublicacion::Venta:
        os << "Venta";
        break;
    case tipoPublicacion::Alquiler:
        os << "Alquiler";
        break;
    }
    return os;
}

#endif
