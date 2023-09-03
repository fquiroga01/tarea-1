Guía compilación y ejecución:

Configuración botón run:
make -s
./main

Al iniciar, el programa mostrará un menú en el que hay que escribir un número del 1 al 8 para indicar lo que el usuario desee realizar. Luego de seleccionar la opción, en todas las funciones que requieran imput, se pedirá el nombre del libro y su autor. Dependiendo de la función elegida, se pueden pedir otros datos, como el género o ISBN del libro en cuestión, o el nombre del usuario al momento de reservar/retirar/devolver. Para evitar errores, el ingreso de datos debe ser TODO EN MAYÚSCULAS, para así evitar tener que realizar modificaciones en las cadenas de caracteres. Cuando se termina de realizar la introducción de datos, la función terminará y se abrirá el menú nuevamente para que el usuario seleccione alguna otra opción según desee, y finalmente si se ingresa un número 0, el menú dejará de mostrarse y da el programa por terminado.

Funcionando correctamente:
-Función Registrar Libro.
-Función Mostrar Datos De Un Libro.
-Función Mostrar Todos Nuestros Libros.
-Función Cancelar Reserva De Un Libro.
-Función Devolver Un Libro
-Función Mostrar Libros Prestados.

Problemas conocidos:
-En la función Retirar Un Libro al ser usada por segunda vez, el código muestra el error exit status -1, se debe a un problema con el uso de punteros, ya que, en alguna parte de la función se debe tener algún puntero apuntando a otro vacío o inexistente, el cuál no pudo ser localizado.

-En la función Mostrar Libros Prestados, se intenta imprimir el nombre del estudiante al cuál se le haya prestado un libro (si es que existe tal caso) pero ocurre que se imprime <null>.

Contribuciones:

Felipe Núñez (3/3):
- Identificación y correción de problema con puntero dentro de las funciones Devolver/Retirar Un Libro. Sin la corrección no hubieran funcionado:
  - Retirar
  - Devolver
- Comentarios en funciones.



Francisco Quiroga (3/3):
- Esqueleto de las funciones necesitadas para la tarea.
  - Registrar
  - MostrarDatos
  - MostrarLibros
  - Reservar
  - MostrarPrestados
- Paso del código normal a utilización de arreglo de libros y cola de reserva.

El archivo README fue hecho por ambos.
