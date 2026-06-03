#include "DTAdministrados.h"

DTAdministrados ::DTAdministrados(fecha fechaComienzo, int identificador, direccion dir)
{
    this->fechaComienzo = fechaComienzo;
    this->identificador = identificador;
    this->dir = dir;
}

fecha DTAdministrados ::getFechaComienzo()
{
    return this->fechaComienzo;
}

int DTAdministrados ::getIdentificador()
{
    return this->identificador;
}

direccion DTAdministrados ::getDir()
{
    return this->dir;
}

std::ostream &operator<<(std::ostream &os, const DTAdministrados &dt)
{
    os << "Id: " << dt.identificador
       << " | Inicio administracion: " << dt.fechaComienzo
       << " | Direccion: " << dt.dir;
    return os;
}
