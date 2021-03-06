#include "central.h"

using namespace std;

// Constructor

Central::Central(unsigned int nuevoId){
    this->id = nuevoId;
    this->listaInternos = new Lista<Interno*>;
    this->enlacesACentrales = new Lista<EnlaceACentral*>;
    this->anuladas = 0;
    // Etiqueta recorrido
    this->peso = 0;
    this->vieneDe = NULL;
    this->nivel = 0;
    this->estado = 0;
    // M�ximos
    this->maxMinutosEmitidos = NULL;
    this->maxLlamadasEmitidas = NULL;
    this->maxOcupadoEmitidas = NULL;
    this->maxLlamadasRecibidas = NULL;
    this->maxGasto = NULL;
    this->maxMinutoRecibidos = NULL;
    this->maxOcupadoRecibidos = NULL;
    cout << "creo el objeto Central que ocupa " << sizeof(Central) << " bytes en la direcci�n " << (unsigned)this;

}

// Destructor

/*

    Liberaci�n de memoria:

    Se borran los interno y los enlacesACentrales y las listas de punteros a estos.

*/

Central::~Central(){
    EnlaceACentral* enlaceABorrar = NULL;
    enlacesACentrales->iniciarCursor();
    while (enlacesACentrales->avanzarCursor()){
        enlaceABorrar = enlacesACentrales->obtenerCursor();
        delete enlaceABorrar;
    }
    cout << "borro el objeto Central que ocupa " << sizeof(EnlaceACentral) << " bytes en la direcci�n " << (unsigned)this;
    delete enlacesACentrales;
    Interno* internoABorrar = NULL;
    listaInternos->iniciarCursor();
    while (listaInternos->avanzarCursor()){
        internoABorrar = listaInternos->obtenerCursor();
        delete internoABorrar;
    }
    cout << "creo el objeto Interno que ocupa " << sizeof(Interno) << " bytes en la direcci�n " << (unsigned)this;
    delete listaInternos;
}

// M�todos

Interno* Central::buscarInterno(unsigned int idSolicitado){
    Interno* internoSolicitado = NULL;
    if (!listaInternos->estaVacia()){
        listaInternos->iniciarCursor();
        while (internoSolicitado==NULL && listaInternos->avanzarCursor()){
            Interno* internoActual = listaInternos->obtenerCursor();
            if (internoActual->obtenerId() == idSolicitado){
                internoSolicitado = internoActual;
            }
        }
    }
    return internoSolicitado;
}

Interno* Central::agregarInterno(unsigned int internoIdA){
    Interno* nuevoInterno;
    nuevoInterno = new Interno(internoIdA,this->obtenerId());
    this->listaInternos->agregar(nuevoInterno);
    return nuevoInterno;
}

void Central::agregarAnuladaFaltaEnlace(){
    this->anuladas++;
}

unsigned int Central::obtenerAnuladaFaltaEnlace(){
    return this->anuladas;
}

unsigned int Central::obtenerId(){
    return this->id;
}

Lista<EnlaceACentral*>* Central::obtenerEnlacesAOtrasCentrales(){
    return this->enlacesACentrales;
}

Lista<Interno*>* Central::obtenerListaInternos(){
    return this->listaInternos;
}

void Central::agregarEnlaceAOtraCentral(unsigned int idAgregar,unsigned int nuevoPeso){
    unsigned int centralEncontrada = buscarEnlaceAOtraCentral(idAgregar);



    if (centralEncontrada==0){
        EnlaceACentral* nuevoEnlaceACentral = new EnlaceACentral(idAgregar, nuevoPeso);
        enlacesACentrales->agregar(nuevoEnlaceACentral);
    }
}

unsigned int Central::buscarEnlaceAOtraCentral (unsigned int idSolicitado){
    unsigned int idActual = 0;

    if (!enlacesACentrales->estaVacia()){
        this->enlacesACentrales->iniciarCursor();
        bool centralEncontrada = false;
        EnlaceACentral* enlaceActual = NULL;

        while (this->enlacesACentrales->avanzarCursor()) {
            enlaceActual = this->enlacesACentrales->obtenerCursor();
            idActual = enlaceActual->obtenerIdOtraCentral();
            centralEncontrada = (idSolicitado==idActual);
        }
        if (!centralEncontrada){
            idActual=0;
        }
    }
    return idActual;
}


unsigned int Central::obtenerPeso(){
    return this->peso;
}

Central* Central::obtenerVieneDe(){
    return this->vieneDe;
}

unsigned int Central::obtenerNivel(){
    return this->nivel;
}

unsigned int Central::obtenerEstado(){
    return this->estado;
}

void Central::cambiarPeso(unsigned int nuevoPeso){
    this->peso = nuevoPeso;
}

void Central::cambiarVieneDe(Central* nuevoVieneDe){
    this->vieneDe = nuevoVieneDe;
}

void Central::cambiarNivel(unsigned int nuevoNivel){
    this->nivel = nuevoNivel;
}

void Central::cambiarEstado(unsigned int nuevoEstado){
    this->estado = nuevoEstado;
}

// M�todos m�ximos

void Central::calcularMaximosCentral(){

    if (!listaInternos->estaVacia()){

        Interno* internoActual = NULL;
        unsigned int parcialMinutosEmitidos = 0;
        unsigned int parcialLlamadasEmitidas = 0;
        unsigned int parcialOcupadasEmitidas = 0;
        unsigned int parcialMinutosRecibidos = 0;
        unsigned int parcialLlamadasRecibidas = 0;
        unsigned int parcialOcupadasRecibidas = 0;

        float parcialGasto = 0;
        float actualGasto = 0;

        listaInternos->iniciarCursor();

        while (listaInternos->avanzarCursor()){

            unsigned int actualMinutosEmitidos = 0;
            unsigned int actualLlamadasEmitidas = 0;
            unsigned int actualOcupadasEmitidas = 0;
            unsigned int actualMinutosRecibidos = 0;
            unsigned int actualLlamadasRecibidas = 0;
            unsigned int actualOcupadasRecibidas = 0;

            internoActual = listaInternos->obtenerCursor();

            actualMinutosEmitidos = internoActual->sumarMinutosEmitidos();
            if (parcialMinutosEmitidos < actualMinutosEmitidos){
                this->maxMinutosEmitidos = internoActual;
                parcialMinutosEmitidos = actualMinutosEmitidos;
            }

            actualLlamadasEmitidas = internoActual->sumarLlamadasEmitidas();
            if (parcialLlamadasEmitidas < actualLlamadasEmitidas){
                this->maxLlamadasEmitidas = internoActual;
                parcialLlamadasEmitidas = actualLlamadasEmitidas;
            }

            actualOcupadasEmitidas = internoActual->sumarOcupadasEmitidas();
            if (parcialOcupadasEmitidas  < actualOcupadasEmitidas){
                this->maxOcupadoEmitidas = internoActual;
                parcialOcupadasEmitidas = actualOcupadasEmitidas;
            }

            actualMinutosRecibidos = internoActual->sumarMinutosRecibidos();
            if (parcialMinutosRecibidos < actualMinutosRecibidos){
                this->maxMinutoRecibidos = internoActual;
                parcialMinutosRecibidos = actualMinutosRecibidos;
            }

            actualLlamadasRecibidas = internoActual->sumarLlamadasRecibidas();
            if (parcialLlamadasRecibidas < actualLlamadasRecibidas){
                this->maxLlamadasRecibidas = internoActual;
                parcialLlamadasRecibidas = actualLlamadasRecibidas;
            }

            actualOcupadasRecibidas = internoActual->sumarOcupadasRecibidas();
            if (parcialOcupadasRecibidas  < actualOcupadasRecibidas){
                this->maxOcupadoRecibidos = internoActual;
                parcialOcupadasRecibidas = actualOcupadasRecibidas;
            }

            actualGasto = internoActual->sumarGasto();
            if (parcialGasto  < actualGasto){
                this->maxGasto = internoActual;
                parcialGasto = actualGasto;
            }


        }

    }
}

Interno* Central::obtenerMaxMinutosEmitidos(){
    return this->maxMinutosEmitidos;
}

Interno* Central::obtenerMaxLlamadasEmitidas(){
    return this->maxLlamadasEmitidas;
}

Interno* Central::obtenerMaxOcupadasEmitidas(){
    return this->maxOcupadoEmitidas;
}
Interno* Central::obtenerMaxMinutosRecibidos(){
    return this->maxMinutoRecibidos;
}
Interno* Central::obtenerMaxLlamadasRecibidas(){
    return this->maxLlamadasRecibidas;
}
Interno* Central::obtenerMaxOcupadasRecibidas(){
    return this->maxOcupadoRecibidos;
}
Interno* Central::obtenerMaxGasto(){
    return this->maxGasto;
}
