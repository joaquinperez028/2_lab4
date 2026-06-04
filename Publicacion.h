#ifndef PUBLICACION_H
#define PUBLICACION_H

class Administra;

#include <string>
#include "Datatypes/TipoPublicacion.h"
#include "Datatypes/Opciones.h"
#include "Datatypes/Fecha.h"
#include "ICollection/interfaces/ICollectible.h"
#include "Datatypes/DTEspecifica.h"
#include "ICollection.h"
#include "Datatypes/DTPublicacion.h"

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
    ICollection* agendas;

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
    DTEspecifica* getDTEspecifica();
    void eliminarAgendas();
    string getNickInmo();
    DTPublicacion* getPublicacion();

};

#endif