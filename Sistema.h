#ifndef SISTEMA_H
#define SISTEMA_H

#include "ISistema.h"
#include "Datatypes/Status.h"
#include "Datatypes/Fecha.h"
#include "ICollection.h"
#include "ICollection/interfaces/IDictionary.h"
#include "Datatypes/DTInmueble.h"

using namespace std;

class Usuario;
class Propietario;
class Inmobiliaria;

class Sistema : public ISistema
{
private:
    Sistema();
    static Sistema *instance;
    IDictionary *usuarios;
    IDictionary *inmuebles;
    IDictionary *publicaciones;
    Propietario *propRecordado;
    Inmobiliaria *inmoRecordada;
    int ultimoCodigoInmueble;
    int ultimoCodigoPub;
    Usuario *buscarPorNickname(string nickname);
    Inmobiliaria *inmoSeleccionada;

public:
    ~Sistema();
    static Sistema *getInstance();
    Status revisarNickname(string) override;                                             
    Status altaCliente(string, string, string, string, string, string) override;         
    Status altaPropietario(string, string, string, string, string, string, string) override;     
    Status altaCasa(Direccion, float, Fecha, TipoTecho, bool) override;                  
    Status altaApto(Direccion, float, Fecha, int, bool, float) override;                 
    Status altaInmobiliaria(string, string, string, string, Direccion, string, string) override; 
    ICollection *listarPropietarios() override;                                          
    Status seleccionarPropietario(string) override;
    int obtenerUltimoCodigoInmueble() override;
    void asociarPropietario(string) override;                                            
    ICollection *listarInmobiliarias() override;                                         
    ICollection *seleccionarInmobiliaria(string) override;                               
    Status altaPublicacion(int, TipoPublicacion, string, float) override;                
    ICollection *listarPublicaciones(string, float, float, Opciones) override;
    DTEspecifica *listarEspecifica(int codigoPubli) override;
    ICollection *listarPropiedades() override;                  
    DTInmueble *mostrarDetalle(int identificador) override;     
    Status eliminarInmueble(int) override;                      
    ICollection *listarInmueblesRepresentados(string) override; 
    ICollection *listarPropietariosRepresentados(string) override;
    Status altaAdministracion(int identificador) override;
    Fecha obtenerFechaActual(); 
    void limpiarInmuebles();
    void limpiarPublicaciones();
    void limpiarUsuarios();
};

#endif
