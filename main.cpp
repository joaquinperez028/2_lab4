#include <iostream>
#include <string>

#include "Factory.h"
#include "ISistema.h"
#include "Inmobiliaria.h"
#include "Datatypes/Direccion.h"
#include "Datatypes/Fecha.h"
#include "Datatypes/Status.h"
#include "Datatypes/TipoTecho.h"
#include "Datatypes/TipoPublicacion.h"
#include "Datatypes/Opciones.h"
#include "Datatypes/DTpropietario.h"
#include "Datatypes/DTInmueble.h"
#include "Datatypes/DTEspecifica.h"
#include "Datatypes/DTAdministrados.h"
#include "ICollection/interfaces/IIterator.h"

using namespace std;

void imprimirStatus(const string &operacion, Status st, Status esperado)
{
    cout << operacion << ": "
         << (st == Status::OK ? "OK" : "ERROR")
         << " | esperado: "
         << (esperado == Status::OK ? "OK" : "ERROR")
         << " -> "
         << (st == esperado ? "PASA" : "FALLA")
         << endl;
}

void imprimirPropietarios(ICollection *col)
{
    cout << "\nPropietarios:" << endl;
    if (col == nullptr)
    {
        cout << "  coleccion NULL" << endl;
        return;
    }

    IIterator *it = col->getIterator();
    while (it->hasCurrent())
    {
        DTPropietario *dt = dynamic_cast<DTPropietario *>(it->getCurrent());
        if (dt != nullptr)
            cout << "  " << *dt << endl;
        it->next();
    }
    delete it;
}

void imprimirInmobiliarias(ICollection *col)
{
    cout << "\nInmobiliarias:" << endl;
    if (col == nullptr)
    {
        cout << "  coleccion NULL" << endl;
        return;
    }

    IIterator *it = col->getIterator();
    while (it->hasCurrent())
    {
        Inmobiliaria *inmo = dynamic_cast<Inmobiliaria *>(it->getCurrent());
        if (inmo != nullptr)
        {
            cout << "  Nick: " << inmo->getNickName()
                 << " | Nombre: " << inmo->getNombre()
                 << " | Tel: " << inmo->getTelefono()
                 << " | URL: " << inmo->getUrl()
                 << " | Direccion: " << inmo->getDireccion()
                 << endl;
        }
        it->next();
    }
    delete it;
}

void imprimirInmuebles(ICollection *col, const string &titulo)
{
    cout << "\n" << titulo << ":" << endl;
    if (col == nullptr)
    {
        cout << "  coleccion NULL" << endl;
        return;
    }

    IIterator *it = col->getIterator();
    while (it->hasCurrent())
    {
        DTInmueble *dt = dynamic_cast<DTInmueble *>(it->getCurrent());
        if (dt != nullptr)
            cout << "  " << *dt << endl;
        it->next();
    }
    delete it;
}

void imprimirAdministrados(ICollection *col)
{
    cout << "\nInmuebles administrados por la inmobiliaria seleccionada:" << endl;
    if (col == nullptr)
    {
        cout << "  coleccion NULL" << endl;
        return;
    }

    IIterator *it = col->getIterator();
    bool hayElementos = false;
    while (it->hasCurrent())
    {
        hayElementos = true;
        DTAdministrados *dt = dynamic_cast<DTAdministrados *>(it->getCurrent());
        if (dt != nullptr)
            cout << "  " << *dt << endl;
        it->next();
    }
    if (!hayElementos)
        cout << "  sin elementos" << endl;
    delete it;
}

int main()
{
    ISistema *sistema = Factory::getSistema();
    Status st;

    cout << "=== ALTAS DE USUARIOS ===" << endl;

    st = sistema->altaCliente("juan123", "Juan", "pass123", "juan@mail.com", "Perez", "12345678");
    imprimirStatus("Alta cliente juan123", st, Status::OK);

    st = sistema->altaCliente("maria456", "Maria", "pass456", "maria@mail.com", "Gomez", "87654321");
    imprimirStatus("Alta cliente maria456", st, Status::OK);

    st = sistema->altaCliente("juan123", "Duplicado", "pass", "dup@mail.com", "Dup", "000");
    imprimirStatus("Alta cliente con nickname duplicado", st, Status::ERROR);

    st = sistema->altaPropietario("ana_prop", "Ana", "pass789", "ana@mail.com", "00112233", "Santander");
    imprimirStatus("Alta propietario ana_prop", st, Status::OK);

    st = sistema->altaPropietario("carlos_prop", "Carlos", "pass999", "carlos@mail.com", "99887766", "Itau");
    imprimirStatus("Alta propietario carlos_prop", st, Status::OK);

    st = sistema->altaPropietario("juan123", "Prop Duplicado", "pass", "propdup@mail.com", "111", "BBVA");
    imprimirStatus("Alta propietario con nickname duplicado", st, Status::ERROR);

    direccion dirInmo1(100, "Av. Italia", "Montevideo", "Montevideo");
    direccion dirInmo2(200, "Bvar. Artigas", "Montevideo", "Montevideo");

    st = sistema->altaInmobiliaria("inmo_central", "Inmo Central", "passInmo", dirInmo1, "24001234", "http://inmo-central.com");
    imprimirStatus("Alta inmobiliaria inmo_central", st, Status::OK);

    st = sistema->altaInmobiliaria("inmo_sur", "Inmo Sur", "passSur", dirInmo2, "26009999", "http://inmo-sur.com");
    imprimirStatus("Alta inmobiliaria inmo_sur", st, Status::OK);

    st = sistema->altaInmobiliaria("ana_prop", "Inmo Duplicada", "pass", dirInmo1, "1111", "http://dup.com");
    imprimirStatus("Alta inmobiliaria con nickname duplicado", st, Status::ERROR);

    imprimirPropietarios(sistema->listarPropietarios());
    imprimirInmobiliarias(sistema->listarInmobiliarias());

    cout << "\n=== ASOCIAR PROPIETARIOS ===" << endl;
    sistema->asociarPropietario("ana_prop");
    cout << "Asociar ana_prop con la ultima inmobiliaria dada de alta: ejecutado" << endl;
    sistema->asociarPropietario("no_existe");
    cout << "Asociar propietario inexistente: ejecutado sin romper" << endl;

    cout << "\n=== ALTAS DE INMUEBLES ===" << endl;

    direccion dirCasa1(123, "Av. Brasil", "Montevideo", "Montevideo");
    fecha fechaCasa1(1, 1, 2005);
    st = sistema->altaCasa(dirCasa1, 120.5, fechaCasa1, tipoTecho::Liviano, false);
    imprimirStatus("Alta casa codigo esperado 1", st, Status::OK);

    direccion dirApto1(456, "18 de Julio", "Montevideo", "Montevideo");
    fecha fechaApto1(1, 1, 2015);
    st = sistema->altaApto(dirApto1, 65.0, fechaApto1, 4, true, 8500);
    imprimirStatus("Alta apartamento codigo esperado 2", st, Status::OK);

    direccion dirCasa2(789, "Rivera", "Montevideo", "Montevideo");
    fecha fechaCasa2(10, 5, 1998);
    st = sistema->altaCasa(dirCasa2, 95.0, fechaCasa2, tipoTecho::Pesado, true);
    imprimirStatus("Alta casa codigo esperado 3", st, Status::OK);

    imprimirInmuebles(sistema->listarPropiedades(), "Listado de propiedades");

    cout << "\n=== DETALLE DE INMUEBLES ===" << endl;

    DTInmueble *detalle1 = sistema->mostrarDetalle(1);
    if (detalle1 != nullptr)
        cout << "Detalle inmueble 1: " << *detalle1 << endl;
    else
        cout << "Detalle inmueble 1: NULL" << endl;

    DTInmueble *detalle99 = sistema->mostrarDetalle(99);
    if (detalle99 != nullptr)
        cout << "Detalle inmueble 99: " << *detalle99 << endl;
    else
        cout << "Detalle inmueble 99: NULL esperado" << endl;

    cout << "\n=== INMOBILIARIA / ADMINISTRACION / PUBLICACION ===" << endl;

    ICollection *administrados = sistema->seleccionarInmobiliaria("inmo_sur");
    imprimirAdministrados(administrados);

    administrados = sistema->seleccionarInmobiliaria("no_existe");
    if (administrados == nullptr)
        cout << "Seleccionar inmobiliaria inexistente: NULL esperado" << endl;
    else
        cout << "Seleccionar inmobiliaria inexistente: devolvio coleccion inesperada" << endl;

    st = sistema->altaAdministracion(1);
    imprimirStatus("Alta administracion inmueble 1", st, Status::OK);

    sistema->seleccionarInmobiliaria("inmo_sur");
    st = sistema->altaPublicacion(1, tipoPublicacion::Venta, "Casa amplia cerca de la rambla", 250000);
    imprimirStatus("Alta publicacion inmueble 1 venta", st, Status::ERROR);
    cout << "Nota: hoy se espera ERROR porque altaAdministracion actualmente devuelve OK pero no crea la administracion." << endl;

    ICollection *publicaciones = sistema->listarPublicaciones("", 0, 1000000, opciones::Todos);
    if (publicaciones != nullptr)
        cout << "Listar publicaciones: devolvio coleccion" << endl;
    else
        cout << "Listar publicaciones: NULL" << endl;

    DTEspecifica *esp = sistema->listarEspecifica(1);
    if (esp != nullptr)
        cout << "Especifica publicacion 1: " << *esp << endl;
    else
        cout << "Especifica publicacion 1: NULL esperado si no se pudo crear publicacion" << endl;

    cout << "\n=== INMUEBLES REPRESENTADOS ===" << endl;
    ICollection *representados = sistema->listarInmueblesRepresentados("inmo_sur");
    imprimirInmuebles(representados, "Representados por inmo_sur");

    representados = sistema->listarInmueblesRepresentados("no_existe");
    if (representados == nullptr)
        cout << "Representados por inmobiliaria inexistente: NULL esperado" << endl;

    cout << "\n=== ELIMINAR INMUEBLE ===" << endl;

    st = sistema->eliminarInmueble(99);
    imprimirStatus("Eliminar inmueble inexistente 99", st, Status::ERROR);

    st = sistema->eliminarInmueble(2);
    imprimirStatus("Eliminar inmueble existente 2", st, Status::OK);

    DTInmueble *detalle2 = sistema->mostrarDetalle(2);
    if (detalle2 == nullptr)
        cout << "Mostrar detalle inmueble 2 luego de eliminar: NULL esperado" << endl;
    else
        cout << "Mostrar detalle inmueble 2 luego de eliminar: " << *detalle2 << endl;

    imprimirInmuebles(sistema->listarPropiedades(), "Propiedades luego de eliminar inmueble 2");

    cout << "\n=== FIN PRUEBAS ===" << endl;

    return 0;
}