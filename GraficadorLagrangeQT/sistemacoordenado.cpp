#include "sistemacoordenado.h"

SistemaCoordenado::SistemaCoordenado()
{
    xMin = 0;
    xMax = 0;
    yMin = 0;
    yMax = 0;

    puntos_seleccionados.reserve(10);
    //puntos_curva.reserve(10000);

}

void SistemaCoordenado::graficar_coordenadas(QApplication *pApp, float pxMin, float pxMax)
{
    xMin = pxMin;
    xMax = pxMax;
    yMin = -5;
    yMax = 5;
    resize(500,500);
    show();
    pApp->exec();
}

void SistemaCoordenado::initializeGL()
{
    glClearColor(0,0,0,0);
}

void SistemaCoordenado::resizeGL(int ancho, int alto)
{
    glViewport( 0 , 0 , ancho, alto );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( xMin , xMax , yMin , yMax , -1 , 1 );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    anchoPixeles = ancho;
    altoPixeles = alto;
}

void SistemaCoordenado::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT );

    dibujar_ejes();
    trazar_curva();
    dibujar_puntos();
}

void SistemaCoordenado::mouseReleaseEvent(QMouseEvent *qme)
{
    point pt;
    pt.x = (qme->x() - anchoPixeles/2.0)/anchoPixeles*(xMax-xMin);
    pt.y = (altoPixeles/2.0 - qme->y())/altoPixeles*(yMax-yMin);
    //CHEQUEO DE IGUAL ABSCISA

    // Actualizo atributos
    puntos_seleccionados.push_back(pt);

    //cout << pt.x << ends << pt.y << endl;
    repaint();
}

void SistemaCoordenado::keyPressEvent(QKeyEvent *qke)
{
    switch (qke->key()) {
    case Qt::Key_X:
        if(puntos_seleccionados.size() != 0)
        {
            for (point p : puntos_seleccionados)
                interpolador.agregar_punto(p.x,p.y);
            puntos_curva = interpolador.get_puntos(xMin,xMax);
            interpolador.clear();
        }
        repaint();
        break;
    case Qt::Key_Backspace:
        if (puntos_seleccionados.size() > 0)
            puntos_seleccionados.pop_back();
        repaint();
        break;
    case 32: //space
        puntos_curva.clear();
        puntos_seleccionados.clear();
        repaint();
        break;
    case 70: // F
        close();
        break;
    }

}

void SistemaCoordenado::dibujar_ejes()
{
    glColor3f( 0, 1, 0.5 );
    glBegin( GL_LINES );
    {
        glVertex2f( xMin , 0.0f );
        glVertex2f( xMax , 0.0f );
        glVertex2f( 0.0f , yMin );
        glVertex2f( 0.0f , yMax );
    }
    glEnd();
}

void SistemaCoordenado::dibujar_puntos()
{
    glColor3f( 1, 0, 0 );
    glPointSize(5);
    for (point p : puntos_seleccionados) {
        glBegin( GL_POINTS );
        {
            glVertex2f(p.x,p.y);
//            glVertex2f( p.x-5 , p.y+5 );
//            glVertex2f( p.x+5 , p.y-5 );
//            glVertex2f( p.x+5 , p.y+5 );
//            glVertex2f( p.x-5 , p.y-5 );
        }
        glEnd();
    }
}

void SistemaCoordenado::trazar_curva()
{
    glColor3f( 0, 0, 1 );
    glPointSize(3);
    glLineWidth(3);
    glBegin( GL_LINE_STRIP );
    {
        for (point p : puntos_curva) {
            glVertex2f(p.x,p.y);
    }
    }
    glEnd();
}
