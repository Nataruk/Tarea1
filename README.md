**EJECUCIÓN DEL PROGRAMA**

Nombre: Biblioteca v1.0
Nombre Estudiante: Vicente Alonso Parada Herrera

Al ejecutar el programa, aparece un menú con 11 opciones, al terminar la ejecución de una opción, se imprime el menú:

1) Esta opción permite **registrar un archivo**, donde se solicitan algunos datos del libro (título, autor, género, ISBN, ubicación).
2) Esta opción **muestra los datos de un libro especifico** que solicita el usuario. Al usuario se le solicita ingresar el titulo y autor del libro que desea mostar los datos. En caso de no existir se imprimirá iun aviso
3) Esta opción **muestra el titulo y el autor de todos los libros** registrados (incluyendo los que se importan mediante CSV). En caso de no haber libros registrados o importados, se muestra un mensaje.
4) Esta opcion permite **reservar un libro**, solicitando el título, autor y el nombre del estudiante, luego se almacena la reserva. Si el libro se encuentra reservado, entonces el programa avisa que no se ha podido realizar la reserva.
5) Esta opcion permite **cancelar la reserva de un libro especifico** solicitando título, autor y nombre del estudiante. En caso de no existir la reserva del libro, se imprime un mensaje.
6) Esta opción permite **retirar un libro**, solicitando el título, autor y nombre del estudiante. En caso de no haber sido reservado o haber cancelado la reserva se imprime un mensaje de aviso al respecto.
7) Esta opcion permite **devolver un libro**, solicitando el título y autor del libro a devolver. En caso de no haber sido retirado, se imprimirá un mensaje de aviso.
8) Esta opción **muestra los libros prestados**, en caso de no haber niguno, imprime un aviso.
9) Esta opción permite **importar libros desde un CSV**, solcitando el nombre del archivo a importar. En caso de no existir se imprime un aviso.
10) Esta opción permite **exportar libros a un CSV**, solicitando el nombre del archivo que se desea exportar libros. En caso de no existir se iprimirá un mensaje de aviso.
11) Esta opción permite **Salir del programa**, donde se imprimirá un mensaje para notificar su finalizanción.


**FALLOS**

1) Cuando se solicita una opción y se ingresa un tipo de dato diferente a un numero entero, entonces el programa entra en un bucle infinito.
2) Al leer la primera linea del archivo CSV la incorpora a la lista del programa(titulo, autor, etc...)
3) Al momento de escribir el nombre y autor para retirar o reservar un libro, aparecen pegadas lineas de impresion.
4) El programa solo lee strings sin espacios, sino, lo interpreta como una string diferente.
