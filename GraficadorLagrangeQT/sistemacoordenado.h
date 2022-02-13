/*!
 *  \class      SistemaCoordenado
 *  \brief      Graficador que habilita una interpolacion de Lagrange interactiva
 *  \details    Grafica unos ejes coordenados sobre un plano. Haciendo click sobre
 *              el pixel de interes es posible selecionar los puntos con los cuales
 *              aplicar el metodo de interpolacion de Lagrange.
 *              * Con "backspace" se elimina el ultimo punto añadido.
 *              * Con la tecla "x" se corre el interpolador.
 *              * Con "space" se limpia todo el espacio de trabajo (puntos y curva).
 *  \author     Breggia, Bruno M.
 *  \version    1.0.0
 *  \date       Fecha de creación: 22-04-2021
 *  \date       Fecha de última modificación: 10-05-2021
 *  \warning    Esta clase no posee manejo de excepciones. Por ejemplo, si se
 *              seleccionan dos puntos con el mismo valor de abscisas, el programa
 *              se colgara.
 *  \copyright  Todos los derechos reservados.
*/

#ifndef SISTEMACOORDENADO_H
#define SISTEMACOORDENADO_H

#include <QOpenGLWidget>
#include <QApplication>
#include <QMouseEvent>
#include <QKeyEvent>
#include <vector>
#include "interpoladordelagrange.h"

using namespace std;

class SistemaCoordenado : public QOpenGLWidget
{
    Q_OBJECT

public:
    SistemaCoordenado();
    void graficar_coordenadas(QApplication* pApp, float pxMin, float pxMax);

protected:
    void initializeGL();
    void resizeGL( int ancho, int alto );
    void paintGL();

    void mouseReleaseEvent( QMouseEvent* qme );
    void keyPressEvent(QKeyEvent *qke);

private:
    void dibujar_ejes();
    void dibujar_puntos();
    void trazar_curva();

    InterpoladorDeLagrange interpolador;
    vector<point> puntos_seleccionados, puntos_curva;
    float xMin, xMax, yMin, yMax;
    int anchoPixeles, altoPixeles;

};

#endif // SISTEMACOORDENADO_H
