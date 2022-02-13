# -*- coding: utf-8 -*-
"""
Created on Wed May 12 23:38:34 2021

@author: Bruno M. Breggia
"""

from typing import List, Tuple
import numpy as np
import matplotlib.pyplot as plt


class LagrangeBaricentrico:
    """
    Clase que implementa el metodo de Interpolacion Baricentrica 
    de Lagrange, tal como se describe en el paper "Barycentric Lagrange
    Interpolation", de Jean-Paul Berrut y Lloyd Trefethen (Society for
    Industrial and Applied Mathematics, 2004).
    DOI: 10.1137/S0036144502417715
    
    Este paper propone un metodo de interpolacion basado en el 
    interpolador de Lagrange, capaz de funcionar con complejidad O(n), 
    con previo calculo de "coeficientes baricentricos". El calculo de
    dichos coeficientes puede ser de complejidad O(n^2) o menor, segun
    la distribucion de los puntos en el eje de las abscisas. El agregado
    de puntos implica una actualizacion de los coeficientes con 
    complejidad O(n).
    """
    
    def __init__(self, puntos:List=[]):
        """
        Inicializador de la clase, se le puede pasar una lista de tuplas
        de pares de numeros, para que sean los puntos iniciales para la
        interpolacion.

        Parameters
        ----------
        puntos : List[Tuple[float,float]], optional
            Lista de puntos iniciales para el interpolador. Por defecto
            la lista inicia vacia.

        Returns
        -------
        None.

        """
        
        self.puntos = puntos
        
        # Orden del polinomio
        self.orden = len(self.puntos)-1 if self.puntos else None
        
        # Calculo coeficientes baricentricos
        self.w = None
        self.precalculo()
        
        pass
    
    def __call__(self, px):
        return self.interpolar(px)
    
    def precalculo(self):
        """
        Calculo de los coeficientes baricentricos.
        Algoritmo con complejidad O(n^2)

        """
        X = 0
        
        self.w = np.array([0]*len(self.puntos), np.float64)
        for i in range(len(self.w)):
            prod = 1
            for j in range(len(self.w)):
                if j!= i:
                    prod *= (self.puntos[i][X] - self.puntos[j][X])
            self.w[i] = 1/prod
        pass
    
    def interpolar(self, px:float) -> float:
        """
        Evalua la interpolacion en el punto px.
        Algoritmo con complejidad O(n)

        Parameters
        ----------
        px : float
            Abscisa a evaluar.

        Returns
        -------
        py : float
            Ordenada correspondiente a la abscisa provista.

        """
        X, Y = 0, 1
        
        L = np.prod( [ px-self.puntos[i][X]
                      for i in range(len(self.puntos)) ], 0 )
        
        suma = 0
        for i in range(len(self.puntos)):
            suma += self.w[i]*self.puntos[i][Y]/(px-self.puntos[i][X])
        
        return L*suma
            
    def agregar(self, px, py):
        """
        Agrega un nuevo punto de referencia al interpolador.
        Se actualizan los coeficientes baricentricos.
        La actualizacion es de complejidad O(n)

        Parameters
        ----------
        px : float
            Abscisa del punto agregado.
        py : float
            Ordenada del punto agregado.

        """
        X = 0
        
        # Agrego a la lista de puntos
        self.puntos.append( (px,py) )
        
        # Actualizo orden
        self.orden += 1
        
        # Actualizo coeficientes baricentricos
        prod = 1
        for i in range(len(self.w)):
            self.w[i] /= (self.puntos[i][X] - px)
            prod *= (px - self.puntos[i][X])
        self.w = np.append(self.w, [1/prod], 0)
    
    def pop(self):
        """
        Remueve el ultimo punto de referencia del interpolador
        
        """
        X = 0
        
        # Agrego a la lista de puntos
        px, _ = self.puntos.pop()
        
        # Actualizo orden
        self.orden -= 1
        
        # Actualizo coeficientes baricentricos
        self.w = np.delete(self.w, -1)
        for i in range(len(self.w)):
            self.w[i] *= (self.puntos[i][X] - px)
    
    pass


# %% main
def main():
    
    puntos = [(-3, 7),
              (0, -5),
              (5, 3.3),
              # (2.3, 5)
              ]
    
    interpolador = LagrangeBaricentrico(puntos)
    testeo(interpolador)
    
    interpolador.agregar(2.3, 5)
    testeo(interpolador)
    
    interpolador.agregar(-4, -10)
    testeo(interpolador)
    
    interpolador.pop()
    testeo(interpolador)
    
    pass


# %% testeo
def testeo(interpolador):
    
    # Graficacion
    fig, ax = plt.subplots(1, 1, figsize=(15, 7), sharex=True)
    fig.suptitle("Funcion interpolante", fontsize=18)
    abscisas = np.arange(-6.5,6.5,0.02)
    ordenadas = interpolador(abscisas)
    ax.plot(abscisas,
            ordenadas,
            label='Interpolacion de Lagrange',
            color='green')
    ax.legend(loc="upper right", fontsize=15)
    ax.grid()
    #plt.show()
    

# %% if __name__ == '__main__'
if __name__ == '__main__':
    plt.close('all')
    main()


