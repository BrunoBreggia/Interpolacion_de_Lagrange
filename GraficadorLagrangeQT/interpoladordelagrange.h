/*!
 *  \class      InterpoladorDeLagrange
 *  \brief      Clase que aplica interpolacion de Lagrange a partir de una cantidad
 *              finita de puntos que se le pase mediante metodos.
 *  \details    Dados una cantidad n de puntos en el espacio euclideo 2-dimensional
 *              es capaz de generar puntos (x,y) pertenecientes a un polinomio de
 *              orden n-1 que pasa por todos los puntos iniciales administrados.
 *  \author     Breggia, Bruno M.
 *  \version    1.0.0
 *  \date       Fecha de creación: 22-04-2021
 *  \date       Fecha de última modificación: 10-05-2021
 *  \warning    Este algoritmo presenta complejidad O(n^2), es decir, puede incurrir
 *              demoras en tiempos de computo si se le exige interpolar polinomios
 *              a partir de una elevada cantidad de puntos.
 *  \warning    Tener en cuenta el fenomeno de Runge en los extremos de intervalos
 *              equiespaciados. Por esto mismo es relevante conocer la funcion que
 *              se quiera interpolar antes de utilizar este metodo.
 *  \copyright  Todos los derechos reservados.
*/

#ifndef INTERPOLADORDELAGRANGE_H
#define INTERPOLADORDELAGRANGE_H
#include <vector>
#include <string>
#include <fstream>
#include <iterator>
#include <sstream>
#include <iostream>
using namespace std;

typedef double T;

struct point
{
    T x = 0;
    T y = 0;
    point(T px=0,T py=0) : x(px), y(py) {}
    bool operator == (point p) {return (x==p.x && y==p.y);}
    bool operator != (point p) {return !(*this == p);}
};

class InterpoladorDeLagrange
{
public:
    InterpoladorDeLagrange();

    void agregar_punto(const T px, const T py);

    void clear();

    T interpolar(const T x) const;

    //vector<T> calcularCoeficientes();

    vector<point> get_puntos(T inicio, T fin, T paso=.05) const;

    void guardar_en_archivo(string nombre, T inicio, T fin, T paso=.2) const;

private:
    vector<point> puntos;

};

#endif // INTERPOLADORDELAGRANGE_H
