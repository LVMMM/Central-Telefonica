#include "salidas.h"

using namespace std;

/*Constructor*/
Salidas::Salidas()
{
    char opcion;
    char eleccionAlgoritmo;
    string ruta="";
    cout << "Ingrese nombre archivo (calls1.txt / calls2.txt)" << endl;
    cin >> ruta;
    while (ruta == "") {
        std::cout << "Ingrese nuevamente" << std::endl;
        std::cin >> ruta;
    };
    //this->clearScreen();
    char* pRuta;
    pRuta=&ruta[0];
    std::cout << "Elija el tipo de recorrido:" << std::endl;
    std::cout << "a. Camino minimo por km" << std::endl;
    std::cout << "b. Camino minimo por centavos" << std::endl;
    std::cin >> eleccionAlgoritmo;
    while (eleccionAlgoritmo != 'a' && eleccionAlgoritmo != 'b') {
        std::cout << "Ingrese nuevamente:  " << std::endl;
        std::cin >> eleccionAlgoritmo;
    };
    Red* red = new Red(pRuta, eleccionAlgoritmo);

    //this->clearScreen();
    cout << endl << "CENTRAL TELEFONICA" << endl << endl;
    while ( (opcion!='S') ){
        cout << endl << endl << "Ingrese la opcion deseada:" << endl << endl;
        cout << "A: Llamadas entre el interno X de la central A al interno de la central B" << endl;
        cout << "B: Interno que mas hablo de todo y de cada central" << endl; // Suma recibidas y emitidas
        cout << "C: Interno que mas llamo de todos y de cada central" << endl;
        cout << "D: Interno que mas le dio ocupado sus internos y de cada central" << endl; // Emitidas
        cout << "E: Interno al que mas llamaron de todos de cada central" << endl;
        cout << "F: Interno que mas gasto de todos y de cada central" << endl;
        cout << "G: Interno al que mas le hablaron de todos y de cada central" << endl;
        cout << "H: Interno que mas dio ocupado de todos y de cada central" << endl; // Recibidas
        cout << "I: Llamadas emitidas por el interno X de la central A" << endl;
        cout << "J: Llamadas recibidas por el interno X de la central A" << endl;
        cout << "K: Llamadas realizadas por X de la central A al interno Y de de la central B" << endl;
        cout << "L: Llamadas recibidas por X de la central A y realizadas por Y de la central B" << endl;
        cout << "M: Listado de llamadas anuladas por falta de enlaces por central" << endl;
        cout << "N: Listado de enlaces (origen, destino, canales)" << endl;
        cout << "O: Listado de internos (nombres, numeros)" << endl;
        cout << "P: Listado de centrales con su numeracion" << endl;
        cout << "S: Salir" << endl << endl;
        cout << "Ingrese letra:  "; cin >> opcion; cout << endl << endl;
        this->clearScreen();
        opcion=toupper(opcion);
        switch(opcion){
            case 'A':
                this->llamadasTotalesXAYB(red);
                break;
            case 'B':
                this->internoMasHablo(red);
                break;
            case 'C':
                this->internoMasLLamo(red);
                break;
            case 'D':
                this->internoMasLeDioOcupado(red);
                break;
            case 'E':
                this->internoMasLLamaron(red);
                break;
            case 'F':
                this->internoMasGasto(red);
                break;
            case 'G':
                this->internoMasLeHablaron(red);
                break;
            case 'H':
                this->internoMasDioOcupado(red);
                break;
            case 'I':
                this->llamadasEmitidasXA(red);
                break;
            case 'J':
                this->llamadasRecibidasXA(red);
                break;
            case 'K':
                this->llamadasXAYB(red); // Emitidas por x, recibidas por y
                break;
            case 'L':
                this->llamadasYBXA(red); // Recibidas por x, emitidas por y
                break;
            case 'M':
                this->listadoAnuladas(red);
                break;
            case 'N':
                this->listadoEnlaces(red);
                break;
            case 'O':
                this->listadoInternos(red);
                break;
            case 'P':
                this->listadoCentrales(red);
                break;
            case 'S':
                delete red;
                break;
            default:
                cout << "OPCION INCORRECTA" << endl;
                break;
        }
    }
}


// Métodos generales

void Salidas::clearScreen()
{
#ifdef _WIN32
    system("CLS");
#elif __linux__
    system("clear");
#endif
}

void Salidas::pressKey()
{
#ifdef _WIN32
    system("pause");
#elif __linux__
    system("read");
#endif
}

// Métodos menú

void Salidas::llamadasTotalesXAYB(Red* red)
{
    unsigned int internox = 0;
    unsigned int centralA = 0;
    unsigned int internoy = 0;
    unsigned int centralB = 0;
    cout << "Ingrese una central A: " << endl;
    cin >> centralA;
    //this->pressKey();
    //this->clearScreen();
    cout << "Ingrese un interno x: " << endl;
    cin >> internox;
    //this->pressKey();
    //this->clearScreen();
    cout << "Ingrese una central B: " << endl;
    cin >> centralB;
    //this->pressKey();
    //this->clearScreen();
    cout << "Ingrese un interno y: " << endl;
    cin >> internoy;
    //this->pressKey();
    //this->clearScreen();
    unsigned int llamadasCantidad = 0;
    unsigned int tiempo = 0;
    unsigned int ocupado = 0;
    Lista<DatosLlamadas*>* detalleLlamadas = red->buscarCentral(centralA)->buscarInterno(internox)->obtenerDetallesLlamadas();
    detalleLlamadas->iniciarCursor();
    while (detalleLlamadas->avanzarCursor())
    {
        DatosLlamadas* datos = detalleLlamadas->obtenerCursor();
        if ((datos->obtenerCentralId() == centralB) && (datos->obtenerIdLlamada() == internoy))
        {
            llamadasCantidad = llamadasCantidad + (datos->obtenerEmitidas() + datos->obtenerRecibidas());
            tiempo = tiempo + (datos->obtenerMinEmitidos() + datos->obtenerMinRecibidos());
            ocupado = ocupado + datos->obtenerOcupadoRecibido();
        }
    }
    cout << "detalle de llamadas totales de central " << setfill('0') << setw(4) << centralA << " interno " << setfill('0') << setw(4) << internox << endl;
    cout << "a la central " << setfill('0') << setw(4) << centralB << " interno " << setfill('0') << setw(4) << internoy << endl;
    cout << "Cantidad de Llamadas: " << llamadasCantidad << endl;
    cout << "Tiempo Hablado: " << tiempo << endl;
    cout << "Cantidad de veces Ocupado: " << ocupado << endl;
    this->pressKey();
    this->clearScreen();
}

void Salidas::internoMasHablo(Red* red){

    red->calcularMaximos();

    cout << endl << endl << "Interno que mas minutos hablo (minutos emitidos) de toda la red y de cada central" << endl << endl;

    Central* maximoCentral = red->obtenerMaxMinutosEmitidos();
    if (maximoCentral!=NULL){
        Interno* maximoInterno = maximoCentral->obtenerMaxMinutosEmitidos();
        cout << "MAXIMO RED. Central: " << setfill('0') << setw(4) << maximoCentral->obtenerId() << "  Interno:  " << setfill('0') << setw(4) << maximoInterno->obtenerId()<<endl  << endl;
    } else {
        cout << "No hubo llamados en la red" << endl << endl;
    }

    Lista<Central*>* centrales = red->obtenerListaDeCentrales();
    Central* centralActual = NULL;
    Interno* internoMax = NULL;
    centrales->iniciarCursor();
    while (centrales->avanzarCursor()){
        centralActual = centrales->obtenerCursor();
        internoMax = centralActual->obtenerMaxMinutosEmitidos();
        if (internoMax!=NULL){
            cout << "Maximo central:  " << setfill('0') << setw(4) << centralActual->obtenerId() << "  Interno:  " << setfill('0') << setw(4) << internoMax->obtenerId() << "  Minutos:  " << internoMax->sumarMinutosEmitidos() << endl << endl;
        }
    }

    this->pressKey();
    this->clearScreen();
}

void Salidas::internoMasLLamo(Red* red){
    red->calcularMaximos();

    cout << endl << endl << "Interno que mas llamo de toda la red y de cada central" << endl << endl;

    Central* maximoCentral = red->obtenerMaxLlamadasEmitidas();
    if (maximoCentral!=NULL){
        Interno* maximoInterno = maximoCentral->obtenerMaxLlamadasEmitidas();
        cout << "MAXIMO RED. Central: " << setfill('0') << setw(4) << maximoCentral->obtenerId() << "  Interno:  " << setfill('0') << setw(4) << maximoInterno->obtenerId()<<endl  << endl;
    } else {
        cout << "No hubo llamados en la red" << endl << endl;
    }

    Lista<Central*>* centrales = red->obtenerListaDeCentrales();
    Central* centralActual = NULL;
    Interno* internoMax = NULL;
    centrales->iniciarCursor();
    while (centrales->avanzarCursor()){
        centralActual = centrales->obtenerCursor();
        internoMax = centralActual->obtenerMaxLlamadasEmitidas();
        if (internoMax!=NULL){
            cout << "Maximo central:  " << setfill('0') << setw(4) << centralActual->obtenerId() << "  Interno:  " << setfill('0') << setw(4) << internoMax->obtenerId() << "  Cantidad:  " << internoMax->sumarLlamadasEmitidas() << endl << endl;
        }
    }
    this->pressKey();
    this->clearScreen();
}

void Salidas::internoMasLeDioOcupado(Red* red){

    red->calcularMaximos();

    cout << endl << endl << "Interno que mas le dio ocupado sus intentos de toda la red y de cada central" << endl << endl;

    Central* maximoCentral = red->obtenerMaxOcupadasEmitidas();
    if (maximoCentral!=NULL){
        Interno* maximoInterno = maximoCentral->obtenerMaxOcupadasEmitidas();
        cout << "MAXIMO RED. Central: " << setfill('0') << setw(4) << maximoCentral->obtenerId() << "  Interno:  " << setfill('0') << setw(4) << maximoInterno->obtenerId()<<endl  << endl;
    } else {
        cout << "No hubo intentos ocupados en la red" << endl << endl;
    }

    Lista<Central*>* centrales = red->obtenerListaDeCentrales();
    Central* centralActual = NULL;
    Interno* internoMax = NULL;
    centrales->iniciarCursor();
    while (centrales->avanzarCursor()){
        centralActual = centrales->obtenerCursor();
        internoMax = centralActual->obtenerMaxOcupadasEmitidas();
        if (internoMax!=NULL){
            cout << "Maximo central:  " << setfill('0') << setw(4) << centralActual->obtenerId() << "  Interno:  " << setfill('0') << setw(4) << internoMax->obtenerId() << "  Cantidad:  " << internoMax->sumarOcupadasEmitidas() << endl << endl;
        }
    }

    this->pressKey();
    this->clearScreen();
}

void Salidas::internoMasLLamaron(Red* red){

    red->calcularMaximos();

    cout << endl << endl << "Interno al que mas llamaron de toda la red y de cada central" << endl << endl;

    Central* maximoCentral = red->obtenerMaxLlamadasRecibidas();
    if (maximoCentral!=NULL){
        Interno* maximoInterno = maximoCentral->obtenerMaxLlamadasRecibidas();
        cout << "MAXIMO RED. Central: " << setfill('0') << setw(4) << maximoCentral->obtenerId() << "  Interno:  " << setfill('0') << setw(4) << maximoInterno->obtenerId()<<endl  << endl;
    } else {
        cout << "No hubo llamados en la red" << endl << endl;
    }

    Lista<Central*>* centrales = red->obtenerListaDeCentrales();
    Central* centralActual = NULL;
    Interno* internoMax = NULL;
    centrales->iniciarCursor();
    while (centrales->avanzarCursor()){
        centralActual = centrales->obtenerCursor();
        internoMax = centralActual->obtenerMaxLlamadasRecibidas();
        if (internoMax!=NULL){
            cout << "Maximo central:  " << setfill('0') << setw(4) << centralActual->obtenerId() << "  Interno:  " << setfill('0') << setw(4) << internoMax->obtenerId() << "  Cantidad:  " << internoMax->sumarLlamadasRecibidas() << endl << endl;
        }
    }

    this->pressKey();
    this->clearScreen();
}

void Salidas::internoMasGasto(Red* red){

    red->calcularMaximos();

    cout << endl << endl << "Interno que mas gasto de toda la red y de cada central" << endl << endl;

    Central* maximoCentral = red->obtenerMaxGasto();
    if (maximoCentral!=NULL){
        Interno* maximoInterno = maximoCentral->obtenerMaxGasto();
        cout << "MAXIMO RED. Central: " << setfill('0') << setw(4) << maximoCentral->obtenerId() << "  Interno:  " << setfill('0') << setw(4) << maximoInterno->obtenerId()<<endl  << endl;
    } else {
        cout << "No hubo llamados en la red" << endl << endl;
    }

    Lista<Central*>* centrales = red->obtenerListaDeCentrales();
    Central* centralActual = NULL;
    Interno* internoMax = NULL;
    centrales->iniciarCursor();
    while (centrales->avanzarCursor()){
        centralActual = centrales->obtenerCursor();
        internoMax = centralActual->obtenerMaxGasto();
        if (internoMax!=NULL){
            cout << "Maximo central:  " << setfill('0') << setw(4) << centralActual->obtenerId() << "  Interno:  " << setfill('0') << setw(4) << internoMax->obtenerId() << "  Centavos:  " << setw(4) << internoMax->sumarGasto() << endl << endl;
        }
    }

    this->pressKey();
    this->clearScreen();
}

void Salidas::internoMasLeHablaron(Red* red){

    red->calcularMaximos();

    cout << endl << endl << "Interno que mas minutos le hablaron de toda la red y de cada central" << endl << endl;

    Central* maximoCentral = red->obtenerMaxMinutosRecibidos();

    if (maximoCentral!=NULL){
        Interno* maximoInterno = maximoCentral->obtenerMaxMinutosRecibidos();
        cout << "MAXIMO RED. Central: " << setfill('0') << setw(4) << maximoCentral->obtenerId() << "  Interno:  " << setfill('0') << setw(4) << maximoInterno->obtenerId()<<endl  << endl;
    } else {
        cout << "No hubo llamados en la red" << endl << endl;
    }

    Lista<Central*>* centrales = red->obtenerListaDeCentrales();
    Central* centralActual = NULL;
    Interno* internoMax = NULL;
    centrales->iniciarCursor();
    while (centrales->avanzarCursor()){
        centralActual = centrales->obtenerCursor();
        internoMax = centralActual->obtenerMaxMinutosRecibidos();
        if (internoMax!=NULL){
            cout << "Maximo central:  " << setfill('0') << setw(4) << centralActual->obtenerId() << "  Interno:  " << setfill('0') << setw(4) << internoMax->obtenerId() << "  Minutos:  " << internoMax->sumarMinutosRecibidos() << endl << endl;
        }
    }

    //this->pressKey();
    //this->clearScreen();
}

void Salidas::internoMasDioOcupado(Red* red){

    red->calcularMaximos();

    cout << endl << endl << "Interno que mas dio ocupado de toda la red y de cada central" << endl << endl;

    Central* maximoCentral = red->obtenerMaxOcupadasRecibidas();
    if (maximoCentral!=NULL){
        Interno* maximoInterno = maximoCentral->obtenerMaxOcupadasRecibidas();
        cout << "MAXIMO RED. Central: " << setfill('0') << setw(4) << maximoCentral->obtenerId() << "  Interno:  " << setfill('0') << setw(4) << maximoInterno->obtenerId()<<endl  << endl;
    } else {
        cout << "No hubo intentos ocupados en la red" << endl << endl;
    }

    Lista<Central*>* centrales = red->obtenerListaDeCentrales();
    Central* centralActual = NULL;
    Interno* internoMax = NULL;
    centrales->iniciarCursor();
    while (centrales->avanzarCursor()){
        centralActual = centrales->obtenerCursor();
        internoMax = centralActual->obtenerMaxOcupadasRecibidas();
        if (internoMax!=NULL){
            cout << "Maximo central:  " << setfill('0') << setw(4) << centralActual->obtenerId() << "  Interno:  " << setfill('0') << setw(4) << internoMax->obtenerId() << "  Cantidad:  " << internoMax->sumarOcupadasRecibidas() << endl << endl;
        }
    }
    //this->pressKey();
    //this->clearScreen();
}

void Salidas::llamadasEmitidasXA(Red* red)
{
    unsigned int internox = 0;
    unsigned int centralA = 0;
    cout << "Ingrese una central A: " << endl;
    cin >> centralA;
    //this->pressKey();
    //this->clearScreen();
    cout << "Ingrese un interno x: " << endl;
    cin >> internox;
    //this->pressKey();
    //this->clearScreen();
    cout << "detalle de llamadas emitidas de central " << setfill('0') << setw(4) << centralA << " interno " << setfill('0') << setw(4) << internox << endl;
    Lista<DatosLlamadas*>* detalleLlamadas = red->buscarCentral(centralA)->buscarInterno(internox)->obtenerDetallesLlamadas();
    detalleLlamadas->iniciarCursor();
    while (detalleLlamadas->avanzarCursor())
    {
        DatosLlamadas* datosllamadas = detalleLlamadas->obtenerCursor();
        cout << "Interno al que llamo: "<<setfill('0') << setw(4) << datosllamadas->obtenerIdLlamada() << endl;
        cout << "Cantidad de llamadas emitidas: " << datosllamadas->obtenerEmitidas() << endl;
        cout << "Cantidad de minutos: " << datosllamadas->obtenerMinEmitidos() << endl;
    }
    //this->pressKey();
    //this->clearScreen();
}

void Salidas::llamadasRecibidasXA(Red* red)
{
    unsigned int internox = 0;
    unsigned int centralA = 0;
    cout << "Ingrese una central A: " << endl;
    cin >> centralA;
    //this->pressKey();
    //this->clearScreen();
    cout << "Ingrese un interno x: " << endl;
    cin >> internox;
    //this->pressKey();
    //this->clearScreen();
    cout << "detalle de llamadas emitidas de central " << setfill('0') << setw(4) << centralA << " interno " << setfill('0') << setw(4) << internox << endl;
    Lista<DatosLlamadas*>* detalleLlamadas = red->buscarCentral(centralA)->buscarInterno(internox)->obtenerDetallesLlamadas();
    detalleLlamadas->iniciarCursor();
    while (detalleLlamadas->avanzarCursor())
    {
        DatosLlamadas* datosllamadas = detalleLlamadas->obtenerCursor();
        cout << "Interno al que llamo: " <<setfill('0') << setw(4) << datosllamadas->obtenerIdLlamada() << endl;
        cout << "Cantidad de llamadas recibidas: " << datosllamadas->obtenerRecibidas() << endl;
        cout << "Cantidad de minutos: " << datosllamadas->obtenerMinRecibidos() << endl;
    }
    //this->pressKey();
    //this->clearScreen();
}

void Salidas::llamadasXAYB(Red* red)
{
    unsigned int internox = 0;
    unsigned int centralA = 0;
    unsigned int internoy = 0;
    unsigned int centralB = 0;
    cout << "Ingrese una central A: " << endl;
    cin >> centralA;
    //this->pressKey();
    //this->clearScreen();
    cout << "Ingrese un interno x: " << endl;
    cin >> internox;
    //this->pressKey();
    //this->clearScreen();
    cout << "Ingrese una central B: " << endl;
    cin >> centralB;
    //this->pressKey();
    //this->clearScreen();
    cout << "Ingrese un interno y: " << endl;
    cin >> internoy;
    //this->pressKey();
    //this->clearScreen();
    cout << "detalle de llamada de central " << setfill('0') << setw(4) << centralA << " interno " << setfill('0') << setw(4) << internox << endl;
        cout << "a la central " << setfill('0') << setw(4) << centralB << " interno " << setfill('0') << setw(4) << internoy << endl;
    Lista<DatosLlamadas*>* detalleLlamadas = red->buscarCentral(centralA)->buscarInterno(internox)->obtenerDetallesLlamadas();
    detalleLlamadas->iniciarCursor();
    while (detalleLlamadas->avanzarCursor())
    {
        DatosLlamadas* datosLlamadas = detalleLlamadas->obtenerCursor();
        if (datosLlamadas->obtenerIdLlamada() == internoy)
        {
            cout << "Cantidad de Llamadas: " << datosLlamadas->obtenerRecibidas() << endl;
            cout << "Tiempo Hablado: " << datosLlamadas->obtenerMinRecibidos() << endl;
            cout << "Cantidad de veces Ocupado: " << datosLlamadas->obtenerOcupadoRecibido() << endl;
        }
    }
    //this->pressKey();
    //this->clearScreen();
}

void Salidas::llamadasYBXA(Red* red)
{
    unsigned int internox = 0;
    unsigned int centralA = 0;
    unsigned int internoy = 0;
    unsigned int centralB = 0;
    cout << "Ingrese una central B: " << endl;
    cin >> centralB;
    //this->pressKey();
    //this->clearScreen();
    cout << "Ingrese un interno y: " << endl;
    cin >> internoy;
    //this->pressKey();
    //this->clearScreen();
    cout << "Ingrese una central A: " << endl;
    cin >> centralA;
    //this->pressKey();
    //this->clearScreen();
    cout << "Ingrese un interno x: " << endl;
    cin >> internox;
    //this->pressKey();
    //this->clearScreen();
    cout << "detalle de llamada de central " << setfill('0') << setw(4) << centralB << " interno " << setfill('0') << setw(4) << internoy << endl;
    cout << "a la central " << setfill('0') << setw(4) << centralA << " interno " << setfill('0') << setw(4) << internox << endl;
    Lista<DatosLlamadas*>* detalleLlamadas = red->buscarCentral(centralB)->buscarInterno(internoy)->obtenerDetallesLlamadas();
    detalleLlamadas->iniciarCursor();
    while (detalleLlamadas->avanzarCursor())
    {
        DatosLlamadas* datosLlamadas = detalleLlamadas->obtenerCursor();

        if (datosLlamadas->obtenerIdLlamada() == internox)
        {
            cout << "Cantidad de Llamadas: " << datosLlamadas->obtenerEmitidas() << endl;
            cout << "Tiempo Hablado: " << datosLlamadas->obtenerMinEmitidos() << endl;
            cout << "Cantidad de veces Ocupado: " << datosLlamadas->obtenerOcupadosEmitidos() << endl;
        }
    }
    //this->pressKey();
    //this->clearScreen();
}



void Salidas::listadoAnuladas(Red* red)
{
    red->obtenerListaDeCentrales()->iniciarCursor();
    while (red->obtenerListaDeCentrales()->avanzarCursor())
    {
        Central* central = red->obtenerListaDeCentrales()->obtenerCursor();
        if (central->obtenerAnuladaFaltaEnlace() != 0)
        {
            cout << "Central: " << setfill('0') << setw(4) << central->obtenerId() << " Cantidad de llamadas anuladas: " << central->obtenerAnuladaFaltaEnlace() << endl;
        }
    }
    //this->pressKey();
    //this->clearScreen();
}
void Salidas::listadoInternos(Red* red)
{
    cout << "Central " << "Interno" << endl;
    red->obtenerListaDeCentrales()->iniciarCursor();
    while (red->obtenerListaDeCentrales()->avanzarCursor())
    {
        Central* central = red->obtenerListaDeCentrales()->obtenerCursor();
        central->obtenerListaInternos()->iniciarCursor();
        while (central->obtenerListaInternos()->avanzarCursor())
        {
            Interno* interno = central->obtenerListaInternos()->obtenerCursor();
            cout << setfill('0') << setw(4) << central->obtenerId() << " - " << setfill('0') << setw(4) << interno->obtenerId() << endl;
        }
    }
    //this->pressKey();
    //this->clearScreen();
}



void Salidas::listadoEnlaces(Red* red)
{
    cout << "Lista de Enlaces" << endl << endl;
    red->obtenerListaDeEnlaces()->iniciarCursor();
    while (red->obtenerListaDeEnlaces()->avanzarCursor())
    {
        Enlace* Enlaces = red->obtenerListaDeEnlaces()->obtenerCursor();
        cout << "Origen: " << setfill('0') << setw(4) << Enlaces->obtenerCentralIdA() << " Destino: " << setfill('0') << setw(4) << Enlaces->obtenerCentralIdB() << " Cantidad de Canales " << Enlaces->obtenerCanales() << endl;
    }
    //this->pressKey();
    //this->clearScreen();
}
void Salidas::listadoCentrales(Red* red)
{
    red->obtenerListaDeCentrales()->iniciarCursor();
    unsigned int i = 1;
    while (red->obtenerListaDeCentrales()->avanzarCursor())
    {

        Central* Central = red->obtenerListaDeCentrales()->obtenerCursor();

        cout << "     Central: " << setfill('0') << setw(4) << Central->obtenerId() << "     ";
        if (i%3 == 0){ cout<<endl<<endl; };
        i++;
    }
    //this->pressKey();
    //this->clearScreen();
}
