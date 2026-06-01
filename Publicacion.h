#ifndef PUBLICACION_H
#define PUBLICACION_H

class Administra;

#include <string>
#include "datatypes/tipoPublicacion.h"
#include "datatypes/opciones.h"
#include "datatypes/fecha.h"
#include "ICollection/interfaces/ICollectible.h"

class Publicacion : public ICollectible
{
private:
    int codigo;
    std::string texto;
    float precio;
    fecha fechaPublicacion;
    bool activa;
    tipoPublicacion tipo;
    Administra *administra;

public:
    Publicacion(int codigo, std::string texto, float precio, fecha fecha, tipoPublicacion tipo,
                Administra *adm);

    int getCodigo();
    std::string getTexto();
    float getPrecio();
    fecha getFecha();
    bool esActiva();
    bool precioFranja(float min, float max);
    bool coincideTipo(tipoPublicacion tipo);
    bool compararInteres(opciones interes);
    void desactivar();
    Administra *getAdministra();

    virtual ~Publicacion();
};

#endif