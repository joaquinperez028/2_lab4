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