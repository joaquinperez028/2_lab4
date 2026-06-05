#include <iostream>
#include <limits>
#include <string>
#include "Factory.h"
#include "Datatypes/Status.h"
#include "Datatypes/Direccion.h"
#include "Datatypes/Fecha.h"
#include "Datatypes/TipoTecho.h"
#include "Datatypes/DTpropietario.h"
#include "ICollection/interfaces/IIterator.h"

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

        cout << "Entrada invalida. Solo letras (a-z, A-Z) y numeros (0-9)";
        if (permitirEspacios)
            cout << ", y espacios";
        cout << "." << endl;
    }
}

static void mostrarMenu()
{
    cout << "\n========== MENU ==========" << endl;
    cout << " 1. Caso de uso 1 - Alta de usuario" << endl;
    cout << " 2. Caso de uso 2" << endl;
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

// ---------------- Caso de uso 1 ----------------

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
                    direccion dir(numPuerta, calle, localidad, departamento);

                    float superficie = leerFloat("Superficie (m2): ");

                    int dia = leerEntero("Dia construccion: ");
                    int mes = leerEntero("Mes construccion: ");
                    int anio = leerEntero("Año construccion: ");
                    fecha f(dia, mes, anio);

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
                        tipoTecho techo = tipoTecho::Liviano;
                        if (ttec == 2)
                            techo = tipoTecho::DosAguas;
                        else if (ttec == 3)
                            techo = tipoTecho::Plano;

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
            direccion dir(numPuerta, calle, localidad, departamento);

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

static void casoDeUso2(ISistema *sistema)
{
    cout << "\n--- Caso de uso 2 ---" << endl;
    cout << "Pendiente de implementar." << endl;
    (void)sistema;
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

    st = sistema->altaPropietario("ana_prop", "Ana", "pass789", "ana@mail.com", "00112233", "Santander");
    cout << (st == Status::OK ? "Alta propietario: OK" : "Alta propietario: ERROR") << endl;

    direccion dirInmo(100, "Av. Italia", "Montevideo", "Montevideo");
    st = sistema->altaInmobiliaria("inmo_central", "Inmo Central", "passInmo", dirInmo, "24001234", "http://inmo.com");
    cout << (st == Status::OK ? "Alta inmobiliaria: OK" : "Alta inmobiliaria: ERROR") << endl;

    ICollection *propietarios = sistema->listarPropietarios();
    cout << "Propietarios disponibles:" << endl;
    IIterator *itProp = propietarios->getIterator();
    while (itProp->hasCurrent())
    {
        DTPropietario *dt = dynamic_cast<DTPropietario *>(itProp->getCurrent());
        if (dt != nullptr)
        {
            cout << "  " << *dt << endl;
        }
        itProp->next();
    }
    delete itProp;

    sistema->asociarPropietario("ana_prop");
    cout << "Asociar propietario (ana_prop <-> inmo_central): OK" << endl;

    fecha fechaCasa(1, 1, 2005);
    direccion dirCasa(123, "Av. Brasil", "Montevideo", "Montevideo");
    st = sistema->altaCasa(dirCasa, 120.5, fechaCasa, tipoTecho::Liviano, false);
    cout << (st == Status::OK ? "Alta casa: OK" : "Alta casa: ERROR") << endl;

    fecha fechaApto(1, 1, 2015);
    direccion dirApto(456, "18 de Julio", "Montevideo", "Montevideo");
    st = sistema->altaApto(dirApto, 65.0, fechaApto, 4, true, 8500);
    cout << (st == Status::OK ? "Alta apartamento: OK" : "Alta apartamento: ERROR") << endl;

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
