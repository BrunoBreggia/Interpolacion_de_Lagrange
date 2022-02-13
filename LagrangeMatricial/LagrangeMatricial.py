# -*- coding: utf-8 -*-
"""
Created on Fri May  7 11:07:34 2021

@author: Bruno M. Breggia
"""

from typing import Tuple, List
from collections.abc import Callable
import numpy as np
import matplotlib.pyplot as plt
from itertools import combinations
import time


# %% timeIt
def timeIt(func:Callable) -> Callable:
    """
    Funcion decoradora que recibe una funcion y devuelve una version cronometrada 
    de la misma que muestra por pantalla su tiempo de ejecucion (en segundos).

    Parameters
    ----------
    func : Callable
        Funcion a cronometrar.

    Returns
    -------
    wrapper : Callable
        Version cronometrada de la funcion pasada como argumento.

    """
    
    def wrapper(*args, **kwargs):
        start = time.time()
        result = func(*args, **kwargs)
        sec = time.time() - start
        print(func)
        print(f'Tiempo de interpolacion: {sec:.5}s')
        return result
    
    return wrapper

# %% Funcion interpolante de lagrange
def lagrange(puntos:List[Tuple[float,float]]) -> Callable:
    """
    Devuelve una funcion closure que interpola puntos mediante el metodo de Lagrange.
    Recibe los puntos como una secuencia de pares de elementos.

    Parameters
    ----------
    puntos : List[Tuple[float,float]]
        Puntos de partida para la interpolacion.

    Returns
    -------
    interpolador : Callable
        Funcion closure que interpola mediante el metodo de Lagrange. Es de complejidad
        O(n^2).

    """
    
    X, Y = 0, 1
    
    @timeIt
    def interpolador(px:np.array):
        suma = 0
        prod = 1
        for i in range(len(puntos)):
            prod = puntos[i][Y]
            for j in range(len(puntos)):
                if j != i:
                    prod *= (px-puntos[j][X])/(puntos[i][X]-puntos[j][X])
            suma += prod
        return suma
    
    return interpolador

# %% lagrangeMatricial
@timeIt
def lagrangeMatricial(puntos:List[Tuple[float,float]], getCoeficientes:bool=False):
    """
    Devuelve una funcion closure que interpola puntos a partir de los
    coeficientes del polinomio interpolante, obtenidos mediante algebra matricial
    a partir de la formula de Lagrange. La funcion que devuelve realiza 
    solamente un producto punto (complejidad O(n)).

    Parameters
    ----------
    puntos : List[Tuple[float,float]]
        Puntos de partida para la interpolacion.
    getCoeficientes : bool
        Bandera que indica si se quiere obtener los coeficientes del polinomio 
        interpolante en lugar de la funcion.

    Returns
    -------
    coeficientes : np.array
        Vector con los coeficientes del polinomio interpolante. Se devuelve si
        getCoeficientes es True.
    interpolador : Callable
        Funcion closure que interpola a partir de los coeficientes polinomiales.
        Se devuelve si getCoeficientes es False.

    """
    
    n = len(puntos)
    X, Y = 0, 1
    
    # Calculo del vector b
    b = [0]*n
    b = np.array(b, np.float64)
    for i in range(n):
        prod = puntos[i][Y]
        for j in range(n):
            if j != i:
                prod /= (puntos[i][X]-puntos[j][X])
        b[i] = prod
    
    # Calculo de la matriz m
    m = [[0]*n]*n
    m = np.array(m, np.float64)
    for row in range(n):
        abscisas = [puntos[i][X] for i in range(n) if i != row]
        for col in range(n):
            m[row][col] = (-1)**(col) * sum([np.prod(tpl) for tpl in combinations(abscisas, col)])
    
    # Calculo de vector de coeficientes
    coeficientes = np.flip(np.transpose(b) @ m)
    
    if getCoeficientes:
        return coeficientes
    
    # Funcion closure
    @timeIt
    def interpolador(px:np.array): 
        
        #Calculo el vector x
        x = [[0]*len(px)]*n
        x = np.array(x, np.float64)
        for i in range(n):
            x[i,:] = px**i
        
        # Producto punto entre x y vector de coeficientes    
        return coeficientes @ x
        
    return interpolador

# %% main
def main():
    
    puntos = [(-3, 7),
              (0, -5),
              (5, 3.3),
              # (2.3, 5)
              ]
    
    # tiempos = np.arange(-2,2,0.5)
    # seno = 100*np.sin(2*np.pi*0.5*tiempos)
    # puntos = np.column_stack( (tiempos, seno) )
    
    # interpolador = lagrange(puntos)
    interpolador = lagrangeMatricial(puntos)
    
    # Graficacion
    fig, ax = plt.subplots(1, 1, figsize=(15, 7), sharex=True)
    fig.suptitle("Funcion interpolante", fontsize=18)
    abscisas = np.arange(-6.5,6.5,0.02)
    ordenadas = interpolador(abscisas)
    ax.plot(abscisas,
            ordenadas,
            label='Interpolacion de Lagrange',
            color='green')
    # ax.scatter(tiempos, seno)
    ax.legend(loc="upper right", fontsize=15)
    ax.grid()

# %% if __name__ == '__main__'
if __name__ == '__main__':
    plt.close('all')
    main()
    
    