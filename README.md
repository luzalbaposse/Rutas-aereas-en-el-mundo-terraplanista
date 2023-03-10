# 🛩️ Rutas aereas en el mundo terraplanista
## 👉 Trabajo Práctico 1 - Tecnología Digital II

El objetivo de este TP es implementar un conjunto de funciones sobre distintas estructuras de datos simples y construir además una serie de casos de test para comprobar su correcto funcionamiento. Las funciones a implementar se realizarán sobre dos tipos de datos. Por un lado strings de C, es decir, cadenas de caracteres terminadas en null, y por otro un nuevo tipo denominado airTrip. Este último modelará la lista de paradas de un viaje en avión. Internamente, el tipo airTrip utilizará una lista enlazada para guardar datos de cada una de las paradas. Estos datos representarán coordenadas sobre un mundo de cada lugar a visitar. 
A fin de simplificar el problema y las operaciones, vamos a considerar al mundo como plano, es decir, las coordenadas de latitud y longitud se moverán en un espacio de coordenadas cartesianas.
Esto nos permitirá calcular distancia entre dos puntos usando la raíz de los cuadrados (teorema de Pitágoras) y no tener que calcular el arco del círculo máximo que los une ambos puntos en una esfera.
