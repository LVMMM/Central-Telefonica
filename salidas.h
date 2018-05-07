#ifndef SALIDAS_H_INCLUDED
#define SALIDAS_H_INCLUDED
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <string>
#include "red.h"


class Salidas
{
    /*
      Una salida con tiene a una red y
      es la encargada de intepretar y
      realizar los calculos para imprimir por pantalla reportes sobre la red y sus llamadas.
      Contiene un menú para interactuar con el usuario.


      Define operaciones como:

            * Mostrar Menu en pantalla
            * Ejecutar reportes
            * Limpiar pantalla
            * Presionar tecla
    */
private:
    // Métodos menú
    /*PRE: Solo se debera ingresar numeros de centrales e internos que se procesaron del txt*/
    /*POST: Muestra los totales de las llamadas de un interno x de la central A a un interno y de la central B*/
    void llamadasTotalesXAYB(Red* red);
    /*POST: Muestra el interno que mas hablo de cada central y el que mas hablo de toda la red*/
    void internoMasHablo(Red* red);
    /*POST: Muestra el interno que mas llamo de cada central y el que mas llamo de toda la red*/
    void internoMasLLamo(Red* red);
    /*POST: Muestra el interno que mas le dio ocupado de cada central y el que mas le dio ocupado de toda la red*/
    void internoMasLeDioOcupado(Red* red);
    /*POST: Muestra el interno al que mas llamaron de cada central y al que mas llamoron de toda la red*/
    void internoMasLLamaron(Red* red);
    /*POST: Muestra el interno que mas gasto de cada central y el que mas gasto de toda la red*/
    void internoMasGasto(Red* red);
    /*POST: Muestra el interno al que mas le hablaron de cada central y al que mas le hablaron de toda la red*/
    void internoMasLeHablaron(Red* red);
    /*POST: Muestra el interno que mas dio ocupado de cada central y el que mas dio ocupado de toda la red*/
    void internoMasDioOcupado(Red* red);
    /*PRE: Solo se debera ingresar numeros de centrales e internos que se procesaron del txt*/
    /*POST: Muestra las llamadas emitidas por un interno x de la central A*/
    void llamadasEmitidasXA(Red* red);
    /*PRE: Solo se debera ingresar numeros de centrales e internos que se procesaron del txt*/
    /*POST: Muestra las llamadas recibidas por un interno x de la central A*/
    void llamadasRecibidasXA(Red* red);
    /*PRE: Solo se debera ingresar numeros de centrales e internos que se procesaron del txt*/
    /*POST: Muestra las llamadas emitidas por un interno x de la central A y recibidas por un interno y de la central B*/
    void llamadasXAYB(Red* red);
    /*PRE: Solo se debera ingresar numeros de centrales e internos que se procesaron del txt*/
    /*POST: Muestra las llamadas emitidas por un interno y de la central B y recibidas por un interno x de la central A*/
    void llamadasYBXA(Red* red);
    /*POST: Muestra la cantidad de llamadas anuladas por falta de enlace por central*/
    void listadoAnuladas(Red* red);
    /*POST: Muestra la lista de central-internos*/
    void listadoInternos(Red* red);
    /*POST: Muestra la lista de enlaces*/
    void listadoEnlaces(Red* red);
    /*POST: Muestra el listado de centrales */
    void listadoCentrales(Red* red);
public:
    /*Constructor*/
    /*POST: Una vez que se crea la clase muestra el menu con toda las opcciones de reportes. Se termina el programa con la tecla 'S'*/
    Salidas();
    // Métodos generales
    void clearScreen();
    void pressKey();
};

#endif // SALIDAS_H_INCLUDED
