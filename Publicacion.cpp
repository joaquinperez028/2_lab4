
#include "Publicacion.h"
#include "Administra.h"
#include "Inmueble.h"

using namespace std;

Publicacion ::Publicacion(int codigo, string texto, float precio, fecha fecha, tipoPublicacion tipo,
                          Administra *adm)
{
    this->codigo = codigo;
    this->texto = texto;
    this->precio = precio;
    this->fechaPublicacion = fecha;
    this->tipo = tipo;
    this->administra = adm;
    this->activa = true;
}

int Publicacion ::getCodigo()
{
    return this->codigo;
}

string Publicacion ::getTexto()
{
    return this->texto;
}

float Publicacion ::getPrecio()
{
    return this->precio;
}

bool Publicacion ::esActiva()
{
    if (this->activa == true)
        return true;
    return false;
}

bool Publicacion ::precioFranja(float min, float max)
{
    return (this->precio <= max && this->precio >= min);
}

bool Publicacion ::coincideTipo(tipoPublicacion tipo)
{
    if (this->tipo == tipo)
        return true;
    return false;
}

bool Publicacion ::compararInteres(opciones interes)
{
    if (interes == Todos)
        return true;

    if (interes == InteresApto && this->administra->getInmueble()->getTipo() == Apartamento)
        return true;

    if (interes == InteresCasa && this->administra->getInmueble()->getTipo() == Casa)
        return true;

    return false;
}

void Publicacion ::desactivar()
{
    this->activa = false;
}

Administra *Publicacion ::getAdministra()
{
    return this->administra;
}

Publicacion ::~Publicacion()
{
}
