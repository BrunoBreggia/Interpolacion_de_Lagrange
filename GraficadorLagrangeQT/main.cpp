/**
  * \brief Interpolador de Lagrange interactivo
  * \author Breggia, Bruno M.
  * \date 10 de Mayo, 2021
**/

#include <QApplication>
#include <vector>
#include <iostream>
#include "interpoladordelagrange.h"
#include "sistemacoordenado.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    InterpoladorDeLagrange interpolador;

    interpolador.agregar_punto(1,1);
    interpolador.agregar_punto(3,5);
    interpolador.agregar_punto(5,-2);
    interpolador.agregar_punto(6,2);
    interpolador.agregar_punto(-1,3);
    interpolador.guardar_en_archivo("cuartica.csv", -1, 8, 0.2);

    // Agregar funcion para obtener puntos
    // Guardar puntos a graficar

    SistemaCoordenado sist;
    sist.graficar_coordenadas(&app,-5,5);

    return app.exec();
}
