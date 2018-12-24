# unix-minishell
Versión reducida del intérprete de órdenes de UNIX.


El intérprete de órdenes es la puerta de entrada tradicional a UNIX. Como cualquier proceso en UNIX, minishell utilizará por defecto la entrada estándar *teclado* para leer las líneas de órdenes a interpretar y ejecutarlas, y la salida estándar *pantalla* para presentar el resultado de las órdenes ejecutadas. Además, para notificar los errores que se puedan producir, usará por defecto la salida de error estándar *pantalla*.

# Objetivos
* Ejecución de órdenes simples externas en primer plano, por ejemplo `ls -l`.
* Ejecución de la orden interna `exit`.
* Ejecución de órdenes en segundo plano o background, mediante el caracter `&`.
* Listado de procesos lanzados, mediante la orden `jobs`.
* Ejecución de secuencias de órdenes, mediante el caracter `;`.