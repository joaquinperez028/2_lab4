#ifndef PUBLICACION_H
#define PUBLICACION_H

class Administra;

#include <string>
#include "Datatypes/TipoPublicacion.h"
#include "Datatypes/Opciones.h"
#include "Datatypes/Fecha.h"
#include "ICollection/interfaces/ICollectible.h"
#include "Datatypes/DTEspecifica.h"
#include "Datatypes/DTPublicacion.h"
#include "ICollection.h"

class AgendaVisita;

class Publicacion : public ICollectible
{
private:
    int codigo;
    std::string texto;
    float precio;
    Fecha fechaPublicacion;
    bool activa;
    TipoPublicacion tipo;
    Administra *administra;
    ICollection *agendas;

public:
    Publicacion(int codigo, std::string texto, float precio, Fecha fecha, TipoPublicacion tipo,
                Administra *adm);

    int getCodigo();
    std::string getTexto();
    float getPrecio();
    Fecha getFecha();
    bool esActiva();
    bool precioFranja(float min, float max);
    bool coincideTipo(TipoPublicacion tipo);
    bool compararInteres(Opciones interes);
    void desactivar();
    Administra *getAdministra();

    virtual ~Publicacion();
    DTEspecifica *getDTEspecifica();

    void agregarAgenda(AgendaVisita *agenda);
    void eliminarAgendas();
    ICollection *listarAgendas();
    string getNickInmo();
    DTPublicacion *getPublicacion();
};

#endif