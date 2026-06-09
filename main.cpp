#include <iostream>
#include <limits>
#include <string>
#include <cstdlib>
#include <exception>
#include <stdexcept>
#include "Factory.h"
#include "Datatypes/Status.h"
#include "Datatypes/Direccion.h"
#include "Datatypes/Fecha.h"
#include "Datatypes/TipoTecho.h"
#include "Datatypes/DTpropietario.h"
#include "Datatypes/DTPropiedad.h"
#include "Datatypes/DTInmuebleRep.h"
#include "Datatypes/DTInmueble.h"
#include "Datatypes/DTPublicacion.h"
#include "Datatypes/Opciones.h"
#include "Datatypes/DTAdministrados.h"
#include "Datatypes/DTInmobiliaria.h"
#include "Datatypes/TipoPublicacion.h"
#include "Datatypes/DTEspecifica.h"
#include "Datatypes/DTCasa.h"
#include "Datatypes/DTApartamento.h"
#include "ICollection/interfaces/IIterator.h"
#include "Inmobiliaria.h"
#include "Sistema.h"

using namespace std;

static bool esLetra(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

static bool esDigito(char c)
{
    return c >= '0' && c <= '9';
}

static bool esCaracterValido(char c, bool permitirEspacios)
{
    if (permitirEspacios && c == ' ')
        return true;

    if (c == '_')
        return true;

    return esLetra(c) || esDigito(c);
}

static bool esTextoValido(const string &texto, bool permitirEspacios)
{
    if (texto.empty())
        return false;

    for (char c : texto)
    {
        if (!esCaracterValido(c, permitirEspacios))
            return false;
    }

    return true;
}

static void consumirSaltoLinea()
{
    if (!cin.good())
        cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

static void recuperarEstadoEntrada()
{
    cin.clear();
    consumirSaltoLinea();
}

static void limpiarPantalla()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

static void pausarAntesDeContinuar()
{
    cout << "\nPresione Enter para continuar...";
    if (!cin.good())
        cin.clear();

    cin.get();

    if (!cin.good())
        cin.clear();

    limpiarPantalla();
}

typedef void (*CasoDeUsoFn)(ISistema *);

static void ejecutarCasoDeUsoSeguro(CasoDeUsoFn caso, ISistema *sistema, const string &nombre)
{
    try
    {
        caso(sistema);
    }
    catch (const exception &e)
    {
        recuperarEstadoEntrada();
        cout << "\nError en " << nombre << ": " << e.what() << endl;
        cout << "Se cancela la operacion y se vuelve al menu." << endl;
    }
    catch (...)
    {
        recuperarEstadoEntrada();
        cout << "\nError inesperado en " << nombre << "." << endl;
        cout << "Se cancela la operacion y se vuelve al menu." << endl;
    }
}

static void liberarDatatypes(ICollection *coleccion)
{
    if (coleccion == nullptr)
        return;

    IIterator *it = coleccion->getIterator();
    while (it->hasCurrent())
    {
        delete it->getCurrent();
        it->next();
    }
    delete it;
    delete coleccion;
}

static string leerTextoValido(const string &mensaje, bool permitirEspacios)
{
    string entrada;

    while (true)
    {
        cout << mensaje;
        getline(cin, entrada);

        if (!cin.good())
        {
            recuperarEstadoEntrada();
            continue;
        }

        if (esTextoValido(entrada, permitirEspacios))
            return entrada;

        cout << "Entrada invalida. Solo letras (a-z, A-Z), numeros (0-9) y guion bajo (_)";
        if (permitirEspacios)
            cout << ", y espacios";
        cout << "." << endl;
    }
}

static void mostrarMenu()
{
    cout << "\n========== MENU ==========" << endl;
    cout << " 1. Caso de uso 1 - Alta de usuario" << endl;
    cout << " 2. Caso de uso 2 - Alta de publicacion" << endl;
    cout << " 3. Caso de uso 3 - Consulta de publicaciones" << endl;
    cout << " 4. Caso de uso 4 - Eliminar inmueble" << endl;
    cout << " 5. Caso de uso 5 - Alta de administracion" << endl;
    cout << " 6. Cargar datos de prueba" << endl;
    cout << " 7. Listar propietarios" << endl;
    cout << " 8. Listar inmuebles" << endl;
    cout << " 9. Listar publicaciones" << endl;
    cout << "10. Alta inmueble a propietario existente" << endl;
    cout << "11. Asociar propietario a inmobiliaria" << endl;
    cout << " 0. Salir" << endl;
    cout << "==========================" << endl;
    cout << "Ingrese una opcion: ";
}

static int leerEntero(const string &mensaje)
{
    int valor;
    while (true)
    {
        cout << mensaje;
        if (cin >> valor)
        {
            consumirSaltoLinea();
            return valor;
        }
        cout << "Entrada invalida. Debe ser un numero entero." << endl;
        recuperarEstadoEntrada();
    }
}

static float leerFloat(const string &mensaje)
{
    float valor;
    while (true)
    {
        cout << mensaje;
        if (cin >> valor)
        {
            consumirSaltoLinea();
            return valor;
        }
        cout << "Entrada invalida. Debe ser un numero real." << endl;
        recuperarEstadoEntrada();
    }
}

static bool leerSiNo(const string &mensaje)
{
    while (true)
    {
        cout << mensaje << " (s/n): ";
        char c;
        if (!(cin >> c))
        {
            recuperarEstadoEntrada();
            continue;
        }
        consumirSaltoLinea();
        if (c == 's' || c == 'S')
            return true;
        if (c == 'n' || c == 'N')
            return false;
        cout << "Respuesta invalida. Ingrese 's' o 'n'." << endl;
    }
}

static bool contieneCaracter(const string &texto, char c)
{
    for (char ch : texto)
    {
        if (ch == c)
            return true;
    }
    return false;
}

static int leerDiaConstruccion()
{
    while (true)
    {
        int dia = leerEntero("Dia construccion: ");
        if (dia >= 0 && dia <= 31)
            return dia;
        cout << "Dia invalido. Debe estar entre 0 y 31." << endl;
    }
}

static int leerMesConstruccion()
{
    while (true)
    {
        int mes = leerEntero("Mes construccion: ");
        if (mes >= 0 && mes <= 12)
            return mes;
        cout << "Mes invalido. Debe estar entre 0 y 12." << endl;
    }
}

static int leerAnioConstruccion()
{
    while (true)
    {
        int anio = leerEntero("Anio construccion: ");
        if (anio >= 1000 && anio <= 2026)
            return anio;
        cout << "Anio invalido. Debe estar entre 1000 y 2026." << endl;
    }
}

static Status registrarInmueble(ISistema *sistema, int &codigoInmueble)
{
    codigoInmueble = -1;

    int numPuerta = leerEntero("Numero de puerta: ");
    string calle = leerTextoValido("Calle: ", true);
    string localidad = leerTextoValido("Localidad: ", true);
    string departamento = leerTextoValido("Departamento: ", true);
    Direccion dir(numPuerta, calle, localidad, departamento);

    float superficie = leerFloat("Superficie (m2): ");

    int dia = leerDiaConstruccion();
    int mes = leerMesConstruccion();
    int anio = leerAnioConstruccion();
    Fecha f(dia, mes, anio);

    cout << "Tipo de inmueble: \n1- Casa   \n2- Apartamento \nOpcion: ";
    int tipoInm = 0;
    while (true)
    {
        if (cin >> tipoInm && (tipoInm == 1 || tipoInm == 2))
        {
            consumirSaltoLinea();
            break;
        }
        cout << "Opcion invalida. Elija 1 o 2: ";
        recuperarEstadoEntrada();
    }

    Status stInm = Status::ERROR;
    if (tipoInm == 1)
    {
        bool esPH = leerSiNo("Es propiedad horizontal (pH)?");

        cout << "Tipo de techo: \n1- Liviano  \n2- Dos aguas  \n3- Plano \nOpciones: ";
        int ttec = 0;
        while (true)
        {
            if (cin >> ttec && ttec >= 1 && ttec <= 3)
            {
                consumirSaltoLinea();
                break;
            }
            cout << "Opcion invalida. Elija 1, 2 o 3: ";
            recuperarEstadoEntrada();
        }
        TipoTecho techo = TipoTecho::Liviano;
        if (ttec == 2)
            techo = TipoTecho::DosAguas;
        else if (ttec == 3)
            techo = TipoTecho::Plano;

        stInm = sistema->altaCasa(dir, superficie, f, techo, esPH);
    }
    else
    {
        int numPiso = leerEntero("Numero de piso: ");
        bool ascensor = leerSiNo("Posee ascensor?");
        float gastosComunes = leerFloat("Gastos comunes: ");

        stInm = sistema->altaApto(dir, superficie, f, numPiso, ascensor, gastosComunes);
    }

    if (stInm == Status::OK)
        codigoInmueble = sistema->obtenerUltimoCodigoInmueble();

    return stInm;
}

static void casoDeUso1(ISistema *sistema)
{
    int opcion = -1;

    do
    {
        cout << "\n--- Caso de uso 1: Alta de usuario ---" << endl;
        cout << " 1. Alta cliente" << endl;
        cout << " 2. Alta propietario" << endl;
        cout << " 3. Alta inmobiliaria" << endl;
        cout << " 0. Volver al menu principal" << endl;
        cout << "Opcion: ";

        if (!(cin >> opcion))
        {
            opcion = -1;
            recuperarEstadoEntrada();
            cout << "Opcion invalida." << endl;
            continue;
        }
        consumirSaltoLinea();

        if (opcion == 0)
            break;

        try
        {
        string nickname = leerTextoValido("Nickname (sin espacios): ", false);
        string contrasenia;
        while (true)
        {
            cout << "Contrasenia (minimo 6 caracteres): ";
            getline(cin, contrasenia);
            if (contrasenia.size() >= 6)
                break;
            cout << "La contrasenia debe tener al menos 6 caracteres." << endl;
        }
        string nombre = leerTextoValido("Nombre: ", true);

        string email;
        while (true)
        {
            cout << "Email: ";
            getline(cin, email);
            if (!email.empty() && contieneCaracter(email, '@'))
                break;
            cout << "Email invalido." << endl;
        }

        Status st = Status::ERROR;

        if (opcion == 1)
        {
            // Alta cliente
            string apellido = leerTextoValido("Apellido: ", true);
            string documento = leerTextoValido("Documento (solo letras y numeros): ", false);

            st = sistema->altaCliente(nickname, nombre, contrasenia, email, apellido, documento);
            cout << "\n"
                 << (st == Status::OK ? "Alta cliente: OK" : "Alta cliente: ERROR (nickname ya existe)") << endl;
        }
        else if (opcion == 2)
        {
            // Alta propietario
            string numCuenta = leerTextoValido("Numero de cuenta: ", false);
            string banco = leerTextoValido("Banco: ", true);
            string telefono = leerTextoValido("Telefono: ", false);

            st = sistema->altaPropietario(nickname, nombre, contrasenia, email, numCuenta, banco, telefono);
            cout << "\n"
                 << (st == Status::OK ? "Alta propietario: OK" : "Alta propietario: ERROR (nickname ya existe)") << endl;

            if (st == Status::OK)
            {
                bool seguir = leerSiNo("Desea registrar un inmueble para este propietario?");
                while (seguir)
                {
                    cout << "\n--- Alta inmueble del propietario ---" << endl;
                    int codigoInmueble = -1;
                    Status stInm = registrarInmueble(sistema, codigoInmueble);

                    cout << "\n"
                         << (stInm == Status::OK ? "Alta inmueble: OK" : "Alta inmueble: ERROR (verifique propietario recordado)") << endl;

                    seguir = leerSiNo("Desea registrar otro inmueble para este propietario?");
                }
            }
        }
        else if (opcion == 3)
        {
            int numPuerta = leerEntero("Numero de puerta: ");
            string calle = leerTextoValido("Calle: ", true);
            string localidad = leerTextoValido("Localidad: ", true);
            string departamento = leerTextoValido("Departamento: ", true);
            Direccion dir(numPuerta, calle, localidad, departamento);

            string telefono = leerTextoValido("Telefono: ", false);

            string url;
            while (true)
            {
                cout << "URL del sitio web: ";
                getline(cin, url);
                if (!url.empty())
                    break;
                cout << "URL invalida." << endl;
            }

            st = sistema->altaInmobiliaria(nickname, nombre, contrasenia, email, dir, telefono, url);
            cout << "\n"
                 << (st == Status::OK ? "Alta inmobiliaria: OK" : "Alta inmobiliaria: ERROR (nickname ya existe)") << endl;

            if (st == Status::OK)
            {
                bool seguir = leerSiNo("Desea agregar propietarios representados para esta inmobiliaria?");
                while (seguir)
                {
                    cout << "\n--- Propietarios registrados ---" << endl;
                    ICollection *props = sistema->listarPropietarios();
                    IIterator *it = props->getIterator();
                    while (it->hasCurrent())
                    {
                        DTPropietario *dt = dynamic_cast<DTPropietario *>(it->getCurrent());
                        if (dt != nullptr)
                        {
                            cout << "  " << *dt << endl;
                        }
                        it->next();
                    }
                    delete it;

                    string nickProp = leerTextoValido("Ingrese nickname del propietario a representar: ", false);
                    Status stAsoc = sistema->asociarPropietario(nickProp);
                    if (stAsoc == Status::OK)
                        cout << "\nSe asocio el propietario indicado a la inmobiliaria recien creada." << endl;
                    else
                        cout << "\nERROR: el propietario no existe o ya tiene una inmobiliaria asociada." << endl;

                    seguir = leerSiNo("Desea agregar otro propietario representado?");
                }
            }
        }
        else
        {
            cout << "Opcion invalida en Caso de uso 1." << endl;
        }

        if (opcion != 0)
            pausarAntesDeContinuar();
        }
        catch (const exception &e)
        {
            recuperarEstadoEntrada();
            cout << "\nError en Caso de uso 1: " << e.what() << endl;
            cout << "Se cancela la operacion y se vuelve al menu." << endl;
            pausarAntesDeContinuar();
            break;
        }
        catch (...)
        {
            recuperarEstadoEntrada();
            cout << "\nError inesperado en Caso de uso 1." << endl;
            cout << "Se cancela la operacion y se vuelve al menu." << endl;
            pausarAntesDeContinuar();
            break;
        }

    } while (opcion != 0);

    limpiarPantalla();
}

static void casoDeUso2(ISistema *sistema)
{
    cout << "\n--- Caso de uso 2: Alta de publicacion ---" << endl;

    ICollection *inmobiliarias = sistema->listarInmobiliarias();
    IIterator *itInmo = inmobiliarias->getIterator();
    bool hayInmobiliarias = false;

    cout << "\nInmobiliarias registradas:" << endl;
    while (itInmo->hasCurrent())
    {
        DTInmobiliaria *inmo = dynamic_cast<DTInmobiliaria *>(itInmo->getCurrent());
        if (inmo != nullptr)
        {
            cout << "  Nickname: " << inmo->getNickname()
                 << " | Nombre: " << inmo->getNombre() << endl;
            hayInmobiliarias = true;
        }
        itInmo->next();
    }
    delete itInmo;

    if (!hayInmobiliarias)
    {
        cout << "  (No hay inmobiliarias registradas)" << endl;
        liberarDatatypes(inmobiliarias);
        return;
    }

    string nickInmo = leerTextoValido("Ingrese nickname de la inmobiliaria: ", false);

    ICollection *administrados = sistema->seleccionarInmobiliaria(nickInmo);
    if (administrados == nullptr)
    {
        cout << "Inmobiliaria no encontrada." << endl;
        liberarDatatypes(inmobiliarias);
        return;
    }

    cout << "\nInmuebles administrados por la inmobiliaria:" << endl;
    IIterator *itAdm = administrados->getIterator();
    bool hayAdministrados = false;

    while (itAdm->hasCurrent())
    {
        DTAdministrados *dt = dynamic_cast<DTAdministrados *>(itAdm->getCurrent());
        if (dt != nullptr)
        {
            cout << "  " << *dt << endl;
            hayAdministrados = true;
        }
        itAdm->next();
    }
    delete itAdm;

    if (!hayAdministrados)
    {
        cout << "  (No hay inmuebles administrados por esta inmobiliaria)" << endl;
        delete administrados;
        liberarDatatypes(inmobiliarias);
        return;
    }

    int codigoInmueble = leerEntero("Ingrese codigo del inmueble: ");

    cout << "Tipo de publicacion: \n 1- Venta \n 2- Alquiler \nOpcion: ";
    int tipoOpcion = 0;
    while (true)
    {
        if (cin >> tipoOpcion && (tipoOpcion == 1 || tipoOpcion == 2))
        {
            consumirSaltoLinea();
            break;
        }
        cout << "Opcion invalida. Elija 1 o 2: ";
        recuperarEstadoEntrada();
    }

    TipoPublicacion tipoPub = (tipoOpcion == 1) ? TipoPublicacion::Venta : TipoPublicacion::Alquiler;

    string texto;
    while (true)
    {
        cout << "Texto descriptivo de la publicacion: ";
        getline(cin, texto);
        if (!texto.empty())
            break;
        cout << "El texto no puede estar vacio." << endl;
    }

    float precio = leerFloat("Precio: ");

    Status st = sistema->altaPublicacion(codigoInmueble, tipoPub, texto, precio);

    if (st == Status::OK)
        cout << "Alta publicacion: OK" << endl;
    else
        cout << "Alta publicacion: ERROR (inmueble no administrado o ya existe publicacion activa del mismo tipo para hoy)" << endl;

    delete administrados;
    liberarDatatypes(inmobiliarias);
}

static void casoDeUso3(ISistema *sistema)
{
    cout << "\n--- Caso de uso 3: Consulta de publicaciones ---" << endl;

    cout << "Tipo de publicacion: \n1- Venta \n2- Alquiler \nOpcion: ";
    int tipoOpcion = 0;
    while (true)
    {
        if (cin >> tipoOpcion && (tipoOpcion == 1 || tipoOpcion == 2))
        {
            consumirSaltoLinea();
            break;
        }
        cout << "Opcion invalida. Elija 1 o 2: ";
        recuperarEstadoEntrada();
    }

    string tipoPub = (tipoOpcion == 1) ? "Venta" : "Alquiler";

    float precioMin = leerFloat("Precio minimo: ");
    float precioMax = leerFloat("Precio maximo: ");
    while (precioMax < precioMin)
    {
        cout << "El precio maximo debe ser mayor o igual al minimo." << endl;
        precioMax = leerFloat("Precio maximo: ");
    }

    cout << "Interes en inmuebles: \n1- Todos  \n2- Solo casas  \n3- Solo apartamentos \nOpciones: ";
    int interesOpcion = 0;
    while (true)
    {
        if (cin >> interesOpcion && interesOpcion >= 1 && interesOpcion <= 3)
        {
            consumirSaltoLinea();
            break;
        }
        cout << "Opcion invalida. Elija 1, 2 o 3: ";
        recuperarEstadoEntrada();
    }

    Opciones interes = Opciones::Todos;
    if (interesOpcion == 2)
        interes = Opciones::InteresCasa;
    else if (interesOpcion == 3)
        interes = Opciones::InteresApto;

    ICollection *publicaciones = sistema->listarPublicaciones(tipoPub, precioMin, precioMax, interes);
    IIterator *it = publicaciones->getIterator();
    bool hayPublicaciones = false;

    cout << "\nPublicaciones encontradas:" << endl;
    while (it->hasCurrent())
    {
        DTPublicacion *dt = dynamic_cast<DTPublicacion *>(it->getCurrent());
        if (dt != nullptr)
        {
            cout << "  Codigo: " << dt->getCodigoPubli()
                 << " | Fecha: " << dt->getFechaPubli()
                 << " | Texto: " << dt->getTextoDescriptivo()
                 << " | Precio: " << dt->getPrecio()
                 << " | Inmobiliaria: " << dt->getNomInmo() << endl;
            hayPublicaciones = true;
        }
        it->next();
    }
    delete it;

    if (!hayPublicaciones)
    {
        cout << "  (No hay publicaciones que cumplan los criterios indicados)" << endl;
        delete publicaciones;
        return;
    }

    if (leerSiNo("Desea ver el detalle completo de una publicacion?"))
    {
        int codigoPub = leerEntero("Ingrese el codigo de la publicacion: ");

        DTEspecifica *detalle = sistema->listarEspecifica(codigoPub);
        if (detalle == nullptr)
        {
            cout << "No existe una publicacion con ese codigo." << endl;
        }
        else
        {
            cout << "\nDetalle del inmueble:" << endl;
            DTCasa *casa = dynamic_cast<DTCasa *>(detalle);
            if (casa != nullptr)
            {
                cout << "  " << *casa << endl;
            }
            else
            {
                DTApartamento *apto = dynamic_cast<DTApartamento *>(detalle);
                if (apto != nullptr)
                    cout << "  " << *apto << endl;
                else
                    cout << "  " << *detalle << endl;
            }
            delete detalle;
        }
    }

    delete publicaciones;
}

static void casoDeUso4(ISistema *sistema)
{
    cout << "\n--- Caso de uso 4: Eliminar inmueble ---" << endl;

    ICollection *propiedades = sistema->listarPropiedades();
    IIterator *it = propiedades->getIterator();
    bool hayPropiedades = false;

    cout << "\nInmuebles registrados:" << endl;
    while (it->hasCurrent())
    {
        DTPropiedad *dt = dynamic_cast<DTPropiedad *>(it->getCurrent());
        if (dt != nullptr)
        {
            cout << "  " << *dt << endl;
            hayPropiedades = true;
        }
        it->next();
    }
    delete it;

    if (!hayPropiedades)
    {
        cout << "  (No hay inmuebles registrados)" << endl;
        delete propiedades;
        return;
    }

    int codigo = leerEntero("\nIngrese el codigo del inmueble: ");

    DTInmueble *detalle = sistema->mostrarDetalle(codigo);
    if (detalle == nullptr)
    {
        cout << "No existe un inmueble con ese codigo." << endl;
        delete propiedades;
        return;
    }

    cout << "\nDetalle del inmueble:" << endl;
    cout << "  " << *detalle << endl;
    delete detalle;

    if (leerSiNo("Desea eliminar este inmueble?"))
    {
        Status st = sistema->eliminarInmueble(codigo);
        if (st == Status::OK)
            cout << "Inmueble eliminado correctamente." << endl;
        else
            cout << "Error al eliminar el inmueble." << endl;
    }
    else
    {
        cout << "Operacion cancelada. El sistema permanece sin cambios." << endl;
    }

    delete propiedades;
}

static void casoDeUso5(ISistema *sistema)
{
    cout << "\n--- Caso de uso 5: Alta de administracion ---" << endl;

    ICollection *inmobiliarias = sistema->listarInmobiliarias();
    IIterator *itInmo = inmobiliarias->getIterator();
    bool hayInmobiliarias = false;

    cout << "\nInmobiliarias registradas:" << endl;
    while (itInmo->hasCurrent())
    {
        DTInmobiliaria *inmo = dynamic_cast<DTInmobiliaria *>(itInmo->getCurrent());
        if (inmo != nullptr)
        {
            cout << "  Nickname: " << inmo->getNickname()
                 << " | Nombre: " << inmo->getNombre() << endl;
            hayInmobiliarias = true;
        }
        itInmo->next();
    }
    delete itInmo;

    if (!hayInmobiliarias)
    {
        cout << "  (No hay inmobiliarias registradas)" << endl;
        liberarDatatypes(inmobiliarias);
        return;
    }

    string nickInmo = leerTextoValido("Ingrese nickname de la inmobiliaria: ", false);

    ICollection *inmuebles = sistema->listarInmueblesRepresentados(nickInmo);
    if (inmuebles == nullptr)
    {
        cout << "Inmobiliaria no encontrada." << endl;
        liberarDatatypes(inmobiliarias);
        return;
    }

    IIterator *itInm = inmuebles->getIterator();
    bool hayInmuebles = false;

    cout << "\nInmuebles de propietarios representados por la inmobiliaria:" << endl;
    while (itInm->hasCurrent())
    {
        DTInmuebleRep *dt = dynamic_cast<DTInmuebleRep *>(itInm->getCurrent());
        if (dt != nullptr)
        {
            cout << "  " << *dt << endl;
            hayInmuebles = true;
        }
        itInm->next();
    }
    delete itInm;

    if (!hayInmuebles)
    {
        cout << "  (No hay inmuebles de propietarios representados por esta inmobiliaria)" << endl;
        IIterator *itClean = inmuebles->getIterator();
        while (itClean->hasCurrent())
        {
            delete itClean->getCurrent();
            itClean->next();
        }
        delete itClean;
        delete inmuebles;
        liberarDatatypes(inmobiliarias);
        return;
    }

    int codigoInmueble = leerEntero("Ingrese codigo del inmueble a administrar: ");

    Status st = sistema->altaAdministracion(codigoInmueble);
    if (st == Status::OK)
        cout << "Alta administracion: OK (fecha de comienzo: fecha actual)" << endl;
    else
        cout << "Alta administracion: ERROR (inmobiliaria o inmueble invalido, o ya administrado)" << endl;

    IIterator *itClean = inmuebles->getIterator();
    while (itClean->hasCurrent())
    {
        delete itClean->getCurrent();
        itClean->next();
    }
    delete itClean;
    delete inmuebles;
    liberarDatatypes(inmobiliarias);
}

static void listarPropietarios(ISistema *sistema)
{
    cout << "\n--- Listado de propietarios ---" << endl;

    ICollection *propietarios = sistema->listarPropietarios();
    IIterator *it = propietarios->getIterator();
    bool hayPropietarios = false;

    while (it->hasCurrent())
    {
        DTPropietario *dt = dynamic_cast<DTPropietario *>(it->getCurrent());
        if (dt != nullptr)
        {
            cout << "  " << *dt << endl;
            hayPropietarios = true;
        }
        it->next();
    }
    delete it;

    if (!hayPropietarios)
        cout << "  (No hay propietarios registrados)" << endl;

    delete propietarios;
}

static void listarInmuebles(ISistema *sistema)
{
    cout << "\n--- Listado de inmuebles ---" << endl;

    ICollection *propiedades = sistema->listarPropiedades();
    IIterator *it = propiedades->getIterator();
    bool hayInmuebles = false;

    while (it->hasCurrent())
    {
        DTPropiedad *dt = dynamic_cast<DTPropiedad *>(it->getCurrent());
        if (dt != nullptr)
        {
            cout << "  " << *dt << endl;
            hayInmuebles = true;
        }
        it->next();
    }
    delete it;

    if (!hayInmuebles)
        cout << "  (No hay inmuebles registrados)" << endl;

    delete propiedades;
}

static void listarPublicaciones(ISistema *sistema)
{
    cout << "\n--- Listado de publicaciones ---" << endl;

    ICollection *publicaciones = sistema->listarPublicaciones("Todos", 0.0f, 999999999.0f, Opciones::Todos);
    IIterator *it = publicaciones->getIterator();
    bool hayPublicaciones = false;

    while (it->hasCurrent())
    {
        DTPublicacion *dt = dynamic_cast<DTPublicacion *>(it->getCurrent());
        if (dt != nullptr)
        {
            cout << "  " << *dt << endl;
            hayPublicaciones = true;
        }
        it->next();
    }
    delete it;

    if (!hayPublicaciones)
        cout << "  (No hay publicaciones activas registradas)" << endl;

    delete publicaciones;
}

bool ok = false;

static void cargarDatosPrueba(ISistema *sistema)
{

    if (ok == false)
    {
        cout << "\n--- Cargando datos de prueba ---" << endl;

        Status st = sistema->altaCliente("juan123", "Juan", "pass123", "juan@mail.com", "Perez", "12345678");
        cout << (st == Status::OK ? "Alta cliente: OK" : "Alta cliente: ERROR") << endl;

        // --- Inmobiliaria 1: Inmo Central + propietaria Ana ---
        st = sistema->altaPropietario("ana_prop", "Ana", "pass789", "ana@mail.com", "00112233", "Santander", "099111222");
        cout << (st == Status::OK ? "Alta propietario (ana_prop): OK" : "Alta propietario (ana_prop): ERROR") << endl;

        Fecha fechaCasaAna(1, 1, 2005);
        Direccion dirCasaAna(123, "Av. Brasil", "Montevideo", "Montevideo");
        st = sistema->altaCasa(dirCasaAna, 120.5, fechaCasaAna, TipoTecho::Liviano, false);
        cout << (st == Status::OK ? "Alta casa Ana (id 1): OK" : "Alta casa Ana: ERROR") << endl;

        Fecha fechaAptoAna(1, 6, 2015);
        Direccion dirAptoAna(456, "18 de Julio", "Montevideo", "Montevideo");
        st = sistema->altaApto(dirAptoAna, 65.0, fechaAptoAna, 4, true, 8500);
        cout << (st == Status::OK ? "Alta apartamento Ana (id 2): OK" : "Alta apartamento Ana: ERROR") << endl;

        Direccion dirInmoCentral(100, "Av. Italia", "Montevideo", "Montevideo");
        st = sistema->altaInmobiliaria("inmo_central", "Inmo Central", "passInmo", "contacto@inmocentral.com", dirInmoCentral, "24001234", "http://inmocentral.com");
        cout << (st == Status::OK ? "Alta inmobiliaria (inmo_central): OK" : "Alta inmobiliaria (inmo_central): ERROR") << endl;

        st = sistema->asociarPropietario("ana_prop");
        cout << (st == Status::OK ? "Asociar ana_prop <-> inmo_central: OK" : "Asociar ana_prop <-> inmo_central: ERROR") << endl;

        ICollection *admCentral = sistema->seleccionarInmobiliaria("inmo_central");
        delete admCentral;

        st = sistema->altaAdministracion(1);
        cout << (st == Status::OK ? "Alta administracion inmo_central (casa id 1): OK" : "Alta administracion inmo_central (casa id 1): ERROR") << endl;

        st = sistema->altaAdministracion(2);
        cout << (st == Status::OK ? "Alta administracion inmo_central (apto id 2): OK" : "Alta administracion inmo_central (apto id 2): ERROR") << endl;

        st = sistema->altaPublicacion(1, TipoPublicacion::Venta, "Casa amplia en Av Brasil", 250000);
        cout << (st == Status::OK ? "Alta publicacion venta casa id 1: OK" : "Alta publicacion venta casa id 1: ERROR") << endl;

        st = sistema->altaPublicacion(2, TipoPublicacion::Alquiler, "Apartamento centrico 18 de Julio", 35000);
        cout << (st == Status::OK ? "Alta publicacion alquiler apto id 2: OK" : "Alta publicacion alquiler apto id 2: ERROR") << endl;

        Fecha fechaVisita(15, 6, 2026);
        st = sistema->altaAgendaVisita("juan123", 1, fechaVisita, "Telefono");
        cout << (st == Status::OK ? "Alta agenda visita juan123 (pub id 1): OK" : "Alta agenda visita juan123 (pub id 1): ERROR") << endl;

        // --- Inmobiliaria 2: Inmo del Sur + propietario Luis ---
        st = sistema->altaPropietario("luis_prop", "Luis", "pass456", "luis@mail.com", "99887766", "BBVA", "098333444");
        cout << (st == Status::OK ? "Alta propietario (luis_prop): OK" : "Alta propietario (luis_prop): ERROR") << endl;

        Fecha fechaCasaLuis(15, 3, 1998);
        Direccion dirCasaLuis(890, "Bvar. Artigas", "Montevideo", "Montevideo");
        st = sistema->altaCasa(dirCasaLuis, 95.0, fechaCasaLuis, TipoTecho::DosAguas, true);
        cout << (st == Status::OK ? "Alta casa Luis (id 3): OK" : "Alta casa Luis: ERROR") << endl;

        Fecha fechaAptoLuis(10, 9, 2020);
        Direccion dirAptoLuis(2100, "Rambla Republica", "Montevideo", "Montevideo");
        st = sistema->altaApto(dirAptoLuis, 48.5, fechaAptoLuis, 8, false, 6200);
        cout << (st == Status::OK ? "Alta apartamento Luis (id 4): OK" : "Alta apartamento Luis: ERROR") << endl;

        Direccion dirInmoSur(550, "Av. Giannattasio", "Montevideo", "Canelones");
        st = sistema->altaInmobiliaria("inmo_sur", "Inmo del Sur", "passSur", "info@inmosur.com", dirInmoSur, "26005678", "http://inmosur.com");
        cout << (st == Status::OK ? "Alta inmobiliaria (inmo_sur): OK" : "Alta inmobiliaria (inmo_sur): ERROR") << endl;

        st = sistema->asociarPropietario("luis_prop");
        cout << (st == Status::OK ? "Asociar luis_prop <-> inmo_sur: OK" : "Asociar luis_prop <-> inmo_sur: ERROR") << endl;

        ICollection *admSur = sistema->seleccionarInmobiliaria("inmo_sur");
        delete admSur;

        st = sistema->altaAdministracion(3);
        cout << (st == Status::OK ? "Alta administracion inmo_sur (casa id 3): OK" : "Alta administracion inmo_sur (casa id 3): ERROR") << endl;

        st = sistema->altaAdministracion(4);
        cout << (st == Status::OK ? "Alta administracion inmo_sur (apto id 4): OK" : "Alta administracion inmo_sur (apto id 4): ERROR") << endl;

        st = sistema->altaPublicacion(3, TipoPublicacion::Venta, "Casa con pH en Bvar Artigas", 180000);
        cout << (st == Status::OK ? "Alta publicacion venta casa id 3: OK" : "Alta publicacion venta casa id 3: ERROR") << endl;

        st = sistema->altaPublicacion(4, TipoPublicacion::Alquiler, "Apto con vista a la rambla", 28000);
        cout << (st == Status::OK ? "Alta publicacion alquiler apto id 4: OK" : "Alta publicacion alquiler apto id 4: ERROR") << endl;

        cout << "\nResumen datos de prueba:" << endl;
        cout << "  Clientes: juan123" << endl;
        cout << "  Inmobiliaria inmo_central -> propietaria ana_prop -> inmuebles 1 (casa) y 2 (apto)" << endl;
        cout << "  Inmobiliaria inmo_sur     -> propietario luis_prop -> inmuebles 3 (casa) y 4 (apto)" << endl;
        cout << "  Publicaciones: venta id1, alquiler id2, venta id3, alquiler id4" << endl;
        cout << "  Agenda visita: juan123 -> publicacion id 1 (15/6/2026, Telefono)" << endl;
        cout << "Datos de prueba cargados." << endl;
        ok = true;
    }
    else
    {
        cout << "Los datos ya fueron cargados" << endl;
    }
}

static void asociarPropietarioAInmo(ISistema *sistema)
{
    cout << "\n--- Asociar propietario a inmobiliaria ---" << endl;

    ICollection *inmobiliarias = sistema->listarInmobiliarias();
    IIterator *itInmo = inmobiliarias->getIterator();
    bool hayInmobiliarias = false;

    cout << "\nInmobiliarias registradas:" << endl;
    while (itInmo->hasCurrent())
    {
        DTInmobiliaria *inmo = dynamic_cast<DTInmobiliaria *>(itInmo->getCurrent());
        if (inmo != nullptr)
        {
            cout << "  Nickname: " << inmo->getNickname()
                 << " | Nombre: " << inmo->getNombre() << endl;
            hayInmobiliarias = true;
        }
        itInmo->next();
    }
    delete itInmo;

    if (!hayInmobiliarias)
    {
        cout << "  (No hay inmobiliarias registradas)" << endl;
        liberarDatatypes(inmobiliarias);
        return;
    }

    string nickInmo = leerTextoValido("Ingrese nickname de la inmobiliaria: ", false);

    ICollection *propietarios = sistema->listarPropietarios();
    IIterator *itProp = propietarios->getIterator();
    bool hayPropietarios = false;

    cout << "\nPropietarios registrados:" << endl;
    while (itProp->hasCurrent())
    {
        DTPropietario *dt = dynamic_cast<DTPropietario *>(itProp->getCurrent());
        if (dt != nullptr)
        {
            cout << "  " << *dt << endl;
            hayPropietarios = true;
        }
        itProp->next();
    }
    delete itProp;

    if (!hayPropietarios)
    {
        cout << "  (No hay propietarios registrados)" << endl;
        delete propietarios;
        liberarDatatypes(inmobiliarias);
        return;
    }

    string nickProp = leerTextoValido("Ingrese nickname del propietario a asociar: ", false);

    Status st = sistema->asociarPropietarioAInmo(nickInmo, nickProp);
    if (st == Status::OK)
        cout << "Asociacion propietario-inmobiliaria: OK" << endl;
    else
        cout << "Asociacion propietario-inmobiliaria: ERROR (inmobiliaria o propietario invalido, o propietario ya tiene inmobiliaria)" << endl;

    delete propietarios;
    liberarDatatypes(inmobiliarias);
}

static void altaInmueblePropietarioExistente(ISistema *sistema)
{
    cout << "\n--- Alta inmueble a propietario existente ---" << endl;

    ICollection *inmobiliarias = sistema->listarInmobiliarias();
    IIterator *itInmo = inmobiliarias->getIterator();
    bool hayInmobiliarias = false;

    cout << "\nInmobiliarias registradas:" << endl;
    while (itInmo->hasCurrent())
    {
        DTInmobiliaria *inmo = dynamic_cast<DTInmobiliaria *>(itInmo->getCurrent());
        if (inmo != nullptr)
        {
            cout << "  Nickname: " << inmo->getNickname()
                 << " | Nombre: " << inmo->getNombre() << endl;
            hayInmobiliarias = true;
        }
        itInmo->next();
    }
    delete itInmo;

    if (!hayInmobiliarias)
    {
        cout << "  (No hay inmobiliarias registradas)" << endl;
        liberarDatatypes(inmobiliarias);
        return;
    }

    string nickInmo = leerTextoValido("Ingrese nickname de la inmobiliaria: ", false);

    ICollection *administrados = sistema->seleccionarInmobiliaria(nickInmo);
    if (administrados == nullptr)
    {
        cout << "Inmobiliaria no encontrada." << endl;
        liberarDatatypes(inmobiliarias);
        return;
    }
    delete administrados;

    ICollection *propietarios = sistema->listarPropietariosRepresentados(nickInmo);
    if (propietarios == nullptr)
    {
        cout << "Inmobiliaria no encontrada." << endl;
        liberarDatatypes(inmobiliarias);
        return;
    }

    IIterator *itProp = propietarios->getIterator();
    bool hayPropietarios = false;

    cout << "\nPropietarios representados por la inmobiliaria:" << endl;
    while (itProp->hasCurrent())
    {
        DTPropietario *dt = dynamic_cast<DTPropietario *>(itProp->getCurrent());
        if (dt != nullptr)
        {
            cout << "  " << *dt << endl;
            hayPropietarios = true;
        }
        itProp->next();
    }
    delete itProp;

    if (!hayPropietarios)
    {
        cout << "  (No hay propietarios representados por esta inmobiliaria)" << endl;
        delete propietarios;
        liberarDatatypes(inmobiliarias);
        return;
    }

    string nickProp = leerTextoValido("Ingrese nickname del propietario: ", false);

    bool propietarioValido = false;
    IIterator *itVal = propietarios->getIterator();
    while (itVal->hasCurrent())
    {
        DTPropietario *dt = dynamic_cast<DTPropietario *>(itVal->getCurrent());
        if (dt != nullptr && dt->getNickname() == nickProp)
            propietarioValido = true;
        itVal->next();
    }
    delete itVal;

    if (!propietarioValido)
    {
        cout << "El propietario no esta representado por la inmobiliaria seleccionada." << endl;
        IIterator *itClean = propietarios->getIterator();
        while (itClean->hasCurrent())
        {
            delete itClean->getCurrent();
            itClean->next();
        }
        delete itClean;
        delete propietarios;
        liberarDatatypes(inmobiliarias);
        return;
    }

    if (sistema->seleccionarPropietario(nickProp) != Status::OK)
    {
        cout << "Propietario no encontrado." << endl;
        IIterator *itClean = propietarios->getIterator();
        while (itClean->hasCurrent())
        {
            delete itClean->getCurrent();
            itClean->next();
        }
        delete itClean;
        delete propietarios;
        liberarDatatypes(inmobiliarias);
        return;
    }

    int codigoInmueble = -1;
    Status stInm = registrarInmueble(sistema, codigoInmueble);

    if (stInm != Status::OK)
    {
        cout << "Alta inmueble: ERROR (verifique propietario seleccionado)" << endl;
        delete propietarios;
        liberarDatatypes(inmobiliarias);
        return;
    }

    cout << "Alta inmueble: OK (codigo " << codigoInmueble << ")" << endl;
    cout << "Use el caso de uso 5 para dar de alta la administracion del inmueble." << endl;

    IIterator *itClean = propietarios->getIterator();
    while (itClean->hasCurrent())
    {
        delete itClean->getCurrent();
        itClean->next();
    }
    delete itClean;
    delete propietarios;
    liberarDatatypes(inmobiliarias);
}

static void borrarSistemaCompleto(ISistema *sistema)
{
    cout << "\n--- Borrando sistema y todas sus colecciones ---" << endl;

    Sistema *s = dynamic_cast<Sistema *>(sistema);
    if (s != nullptr)
    {
        s->limpiarInmuebles();
        s->limpiarPublicaciones();
        s->limpiarUsuarios();
    }

    cout << "Sistema borrado correctamente." << endl;
}

int main()
{
    ISistema *sistema = Factory::getSistema();
    int opcion = -1;

    limpiarPantalla();

    do
    {
        try
        {
            mostrarMenu();
            if (!(cin >> opcion))
            {
                opcion = -1;
                recuperarEstadoEntrada();
                cout << "\nOpcion invalida. Intente nuevamente." << endl;
                pausarAntesDeContinuar();
                continue;
            }
            consumirSaltoLinea();

            switch (opcion)
            {
            case 1:
                ejecutarCasoDeUsoSeguro(casoDeUso1, sistema, "Caso de uso 1");
                break;
            case 2:
                ejecutarCasoDeUsoSeguro(casoDeUso2, sistema, "Caso de uso 2");
                break;
            case 3:
                ejecutarCasoDeUsoSeguro(casoDeUso3, sistema, "Caso de uso 3");
                break;
            case 4:
                ejecutarCasoDeUsoSeguro(casoDeUso4, sistema, "Caso de uso 4");
                break;
            case 5:
                ejecutarCasoDeUsoSeguro(casoDeUso5, sistema, "Caso de uso 5");
                break;
            case 6:
                ejecutarCasoDeUsoSeguro(cargarDatosPrueba, sistema, "Cargar datos de prueba");
                break;
            case 7:
                ejecutarCasoDeUsoSeguro(listarPropietarios, sistema, "Listar propietarios");
                break;
            case 8:
                ejecutarCasoDeUsoSeguro(listarInmuebles, sistema, "Listar inmuebles");
                break;
            case 9:
                ejecutarCasoDeUsoSeguro(listarPublicaciones, sistema, "Listar publicaciones");
                break;
            case 10:
                ejecutarCasoDeUsoSeguro(altaInmueblePropietarioExistente, sistema, "Alta inmueble a propietario existente");
                break;
            case 11:
                ejecutarCasoDeUsoSeguro(asociarPropietarioAInmo, sistema, "Asociar propietario a inmobiliaria");
                break;
            case 0:
                borrarSistemaCompleto(sistema);
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "\nOpcion invalida. Intente nuevamente." << endl;
                break;
            }

            if (opcion != 0 && opcion != 1)
                pausarAntesDeContinuar();
        }
        catch (const exception &e)
        {
            recuperarEstadoEntrada();
            cout << "\nError en el menu: " << e.what() << endl;
            cout << "Se continua con el menu principal." << endl;
            pausarAntesDeContinuar();
        }
        catch (...)
        {
            recuperarEstadoEntrada();
            cout << "\nError inesperado en el menu." << endl;
            cout << "Se continua con el menu principal." << endl;
            pausarAntesDeContinuar();
        }

    } while (opcion != 0);

    return 0;
}
