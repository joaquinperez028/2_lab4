#include <iostream>
#include <limits>
#include <string>
#include "Factory.h"
#include "Datatypes/Status.h"
#include "Datatypes/Direccion.h"
#include "Datatypes/Fecha.h"
#include "Datatypes/TipoTecho.h"
#include "Datatypes/DTpropietario.h"
#include "Datatypes/DTAdministrados.h"
#include "Datatypes/TipoPublicacion.h"
#include "ICollection/interfaces/IIterator.h"
#include "Inmobiliaria.h"

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
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

static string leerTextoValido(const string &mensaje, bool permitirEspacios)
{
    string entrada;

    while (true)
    {
        cout << mensaje;
        getline(cin, entrada);

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
    cout << " 3. Caso de uso 3" << endl;
    cout << " 4. Caso de uso 4" << endl;
    cout << " 5. Cargar datos de prueba" << endl;
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
        cin.clear();
        consumirSaltoLinea();
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
        cin.clear();
        consumirSaltoLinea();
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
            cin.clear();
            consumirSaltoLinea();
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

static void casoDeUso1(ISistema *sistema){
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
            cin.clear();
            consumirSaltoLinea();
            cout << "Opcion invalida." << endl;
            continue;
        }
        consumirSaltoLinea();

        if (opcion == 0)
            break;

        // Datos comunes
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
            cout << (st == Status::OK ? "Alta cliente: OK" : "Alta cliente: ERROR (nickname ya existe)") << endl;
        }
        else if (opcion == 2)
        {
            // Alta propietario
            string numCuenta = leerTextoValido("Numero de cuenta: ", false);
            string banco = leerTextoValido("Banco: ", true);

            st = sistema->altaPropietario(nickname, nombre, contrasenia, email, numCuenta, banco);
            cout << (st == Status::OK ? "Alta propietario: OK" : "Alta propietario: ERROR (nickname ya existe)") << endl;

            if (st == Status::OK)
            {
                bool seguir = leerSiNo("¿Desea registrar un inmueble para este propietario?");
                while (seguir)
                {
                    cout << "\n--- Alta inmueble del propietario ---" << endl;
                    // Direccion
                    int numPuerta = leerEntero("Numero de puerta: ");
                    string calle = leerTextoValido("Calle: ", true);
                    string localidad = leerTextoValido("Localidad: ", true);
                    string departamento = leerTextoValido("Departamento: ", true);
                    Direccion dir(numPuerta, calle, localidad, departamento);

                    float superficie = leerFloat("Superficie (m2): ");

                    int dia = leerEntero("Dia construccion: ");
                    int mes = leerEntero("Mes construccion: ");
                    int anio = leerEntero("Año construccion: ");
                    Fecha f(dia, mes, anio);

                    cout << "Tipo de inmueble: 1) Casa  2) Apartamento: ";
                    int tipoInm = 0;
                    while (true)
                    {
                        if (cin >> tipoInm && (tipoInm == 1 || tipoInm == 2))
                        {
                            consumirSaltoLinea();
                            break;
                        }
                        cout << "Opcion invalida. Elija 1 o 2: ";
                        cin.clear();
                        consumirSaltoLinea();
                    }

                    Status stInm = Status::ERROR;
                    if (tipoInm == 1)
                    {
                        bool esPH = leerSiNo("¿Es propiedad horizontal (pH)?");

                        cout << "Tipo de techo: 1) Liviano  2) Dos aguas  3) Plano: ";
                        int ttec = 0;
                        while (true)
                        {
                            if (cin >> ttec && ttec >= 1 && ttec <= 3)
                            {
                                consumirSaltoLinea();
                                break;
                            }
                            cout << "Opcion invalida. Elija 1, 2 o 3: ";
                            cin.clear();
                            consumirSaltoLinea();
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
                        bool ascensor = leerSiNo("¿Posee ascensor?");
                        float gastosComunes = leerFloat("Gastos comunes: ");

                        stInm = sistema->altaApto(dir, superficie, f, numPiso, ascensor, gastosComunes);
                    }

                    cout << (stInm == Status::OK ? "Alta inmueble: OK" : "Alta inmueble: ERROR (verifique propietario recordado)") << endl;

                    seguir = leerSiNo("¿Desea registrar otro inmueble para este propietario?");
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

            st = sistema->altaInmobiliaria(nickname, nombre, contrasenia, dir, telefono, url);
            cout << (st == Status::OK ? "Alta inmobiliaria: OK" : "Alta inmobiliaria: ERROR (nickname ya existe)") << endl;

            if (st == Status::OK)
            {
                bool seguir = leerSiNo("¿Desea agregar propietarios representados para esta inmobiliaria?");
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
                    sistema->asociarPropietario(nickProp);
                    cout << "Se intento asociar el propietario indicado a la inmobiliaria recien creada." << endl;

                    seguir = leerSiNo("¿Desea agregar otro propietario representado?");
                }
            }
        }
        else
        {
            cout << "Opcion invalida en Caso de uso 1." << endl;
        }

    } while (opcion != 0);
}

static void casoDeUso2(ISistema *sistema){
    cout << "\n--- Caso de uso 2: Alta de publicacion ---" << endl;

    ICollection *inmobiliarias = sistema->listarInmobiliarias();
    IIterator *itInmo = inmobiliarias->getIterator();
    bool hayInmobiliarias = false;

    cout << "\nInmobiliarias registradas:" << endl;
    while (itInmo->hasCurrent())
    {
        Inmobiliaria *inmo = dynamic_cast<Inmobiliaria *>(itInmo->getCurrent());
        if (inmo != nullptr)
        {
            cout << "  Nickname: " << inmo->getNickName()
                 << " | Nombre: " << inmo->getNombre() << endl;
            hayInmobiliarias = true;
        }
        itInmo->next();
    }
    delete itInmo;

    if (!hayInmobiliarias)
    {
        cout << "  (No hay inmobiliarias registradas)" << endl;
        delete inmobiliarias;
        return;
    }

    string nickInmo = leerTextoValido("Ingrese nickname de la inmobiliaria: ", false);

    ICollection *administrados = sistema->seleccionarInmobiliaria(nickInmo);
    if (administrados == nullptr)
    {
        cout << "Inmobiliaria no encontrada." << endl;
        delete inmobiliarias;
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
        delete inmobiliarias;
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
        cin.clear();
        consumirSaltoLinea();
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
    delete inmobiliarias;
}

static void casoDeUso3(ISistema *sistema)
{
    cout << "\n--- Caso de uso 3 ---" << endl;
    cout << "Pendiente de implementar." << endl;
    (void)sistema;
}

static void casoDeUso4(ISistema *sistema)
{
    cout << "\n--- Caso de uso 4 ---" << endl;
    cout << "Pendiente de implementar." << endl;
    (void)sistema;
}

static void cargarDatosPrueba(ISistema *sistema)
{
    cout << "\n--- Cargando datos de prueba ---" << endl;

    Status st = sistema->altaCliente("juan123", "Juan", "pass123", "juan@mail.com", "Perez", "12345678");
    cout << (st == Status::OK ? "Alta cliente: OK" : "Alta cliente: ERROR") << endl;

    // --- Inmobiliaria 1: Inmo Central + propietaria Ana ---
    st = sistema->altaPropietario("ana_prop", "Ana", "pass789", "ana@mail.com", "00112233", "Santander");
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
    st = sistema->altaInmobiliaria("inmo_central", "Inmo Central", "passInmo", dirInmoCentral, "24001234", "http://inmocentral.com");
    cout << (st == Status::OK ? "Alta inmobiliaria (inmo_central): OK" : "Alta inmobiliaria (inmo_central): ERROR") << endl;

    sistema->asociarPropietario("ana_prop");
    cout << "Asociar ana_prop <-> inmo_central: OK" << endl;

    ICollection *admCentral = sistema->seleccionarInmobiliaria("inmo_central");
    delete admCentral;

    st = sistema->altaAdministracion(1);
    cout << (st == Status::OK ? "Alta administracion inmo_central (casa id 1): OK" : "Alta administracion inmo_central (casa id 1): ERROR") << endl;

    st = sistema->altaAdministracion(2);
    cout << (st == Status::OK ? "Alta administracion inmo_central (apto id 2): OK" : "Alta administracion inmo_central (apto id 2): ERROR") << endl;

    // --- Inmobiliaria 2: Inmo del Sur + propietario Luis ---
    st = sistema->altaPropietario("luis_prop", "Luis", "pass456", "luis@mail.com", "99887766", "BBVA");
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
    st = sistema->altaInmobiliaria("inmo_sur", "Inmo del Sur", "passSur", dirInmoSur, "26005678", "http://inmosur.com");
    cout << (st == Status::OK ? "Alta inmobiliaria (inmo_sur): OK" : "Alta inmobiliaria (inmo_sur): ERROR") << endl;

    sistema->asociarPropietario("luis_prop");
    cout << "Asociar luis_prop <-> inmo_sur: OK" << endl;

    ICollection *admSur = sistema->seleccionarInmobiliaria("inmo_sur");
    delete admSur;

    st = sistema->altaAdministracion(3);
    cout << (st == Status::OK ? "Alta administracion inmo_sur (casa id 3): OK" : "Alta administracion inmo_sur (casa id 3): ERROR") << endl;

    st = sistema->altaAdministracion(4);
    cout << (st == Status::OK ? "Alta administracion inmo_sur (apto id 4): OK" : "Alta administracion inmo_sur (apto id 4): ERROR") << endl;

    cout << "\nResumen datos de prueba:" << endl;
    cout << "  Clientes: juan123" << endl;
    cout << "  Inmobiliaria inmo_central -> propietaria ana_prop -> inmuebles 1 (casa) y 2 (apto)" << endl;
    cout << "  Inmobiliaria inmo_sur     -> propietario luis_prop -> inmuebles 3 (casa) y 4 (apto)" << endl;
    cout << "Datos de prueba cargados." << endl;
}

int main()
{
    ISistema *sistema = Factory::getSistema();
    int opcion = -1;

    do
    {
        mostrarMenu();
        cin >> opcion;
        consumirSaltoLinea();

        switch (opcion)
        {
        case 1:
            casoDeUso1(sistema);
            break;
        case 2:
            casoDeUso2(sistema);
            break;
        case 3:
            casoDeUso3(sistema);
            break;
        case 4:
            casoDeUso4(sistema);
            break;
        case 5:
            cargarDatosPrueba(sistema);
            break;
        case 0:
            cout << "Saliendo..." << endl;
            break;
        default:
            cout << "Opcion invalida. Intente nuevamente." << endl;
            break;
        }

    } while (opcion != 0);

    return 0;
}
