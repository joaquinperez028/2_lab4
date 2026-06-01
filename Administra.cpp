#include "Administra.h"
#include "ICollection/collections/List.h"
#include "Publicacion.h"

using namespace std;

Administra ::Administra(Inmobiliaria *inmo, Inmueble *inm)
{

    this->inmobiliaria = inmo;
    this->inmueble = inm;

    this->publicaciones = new List();
}

Inmobiliaria *Administra ::getInmobiliaria()
{
    return this->inmobiliaria;
}

Inmueble *Administra ::getInmueble()
{
    return this->inmueble;
}

void Administra ::agregarPublicacion(Publicacion *pub)
{
    publicaciones->add(pub);
}

Administra ::~Administra() {

};

bool Administra ::existePubAciva(tipoPublicacion tipo, fecha fechaHoy)
{
    Iterator *it = publicaciones->getIterator();

    while (it->hasCurrent())
    {
        Publicacion *pub = (Publicacion *)it->getCurrent();
        if (pub->coincideTipo(tipo) && pub->getFecha() == fechaHoy && pub->esActiva())
            return true;
        it->next();
    }
    return false;
}

void Administra ::crearPublicacion(int codigo, tipoPublicacion tipo, std::string texto, float precio,
                                   fecha fechaHoy)
{
    Publicacion *pub = new Publicacion(codigo, texto, precio, fechaHoy, tipo, this);
    agregarPublicacion(pub);
}