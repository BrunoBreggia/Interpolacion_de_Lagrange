#include "interpoladordelagrange.h"

InterpoladorDeLagrange::InterpoladorDeLagrange()
{
    puntos.reserve(10);
}

void InterpoladorDeLagrange::agregar_punto(const T px, const T py)
{
    puntos.push_back( point(px,py) );
}

void InterpoladorDeLagrange::clear()
{
    puntos.clear();
}

T InterpoladorDeLagrange::interpolar(const T x) const
{
    T sum = 0;
    T prod = 1;
    for (unsigned i=0; i<puntos.size(); ++i)
    {
        prod = puntos[i].y;
        for (unsigned j=0; j<puntos.size(); ++j)
        {
            if (j == i) continue;

            prod *= (x - puntos[j].x) / (puntos[i].x - puntos[j].x);
        }
        sum += prod;
    }
    return sum;
}

vector<point> InterpoladorDeLagrange::get_puntos(T inicio, T fin, T paso) const
{
    T cant_puntos = (fin-inicio)/paso;
    vector<point> resultados;
    resultados.reserve(int(cant_puntos));

    for (T x=inicio; x<fin; x+=paso)
    {
        resultados.push_back( point(x,interpolar(x)) );
    }

    return resultados;
}

void InterpoladorDeLagrange::guardar_en_archivo(string nombre, T inicio, T fin, T paso) const
{
    vector<point> resultados = get_puntos(inicio, fin, paso);
    ofstream file_output(nombre.c_str());
    stringstream ss;
    ostream_iterator<string> itr (file_output,"\n");
    if (file_output.is_open())
    {
        //cout << resultados.size() << endl;
        for(unsigned i=0; i<resultados.size(); ++i)
        {
            //cout << "entro" << endl;
            //file_output << resultados[i].x << ", " << resultados[i].y << endl;
            ss.str("");
            ss << resultados[i].x << ", " << resultados[i].y;
            (*itr) = ss.str();
            ++itr;
        }
    }
    else
    {
        cout << "Archivo no abierto" << endl;
    }
    file_output.close();
}
