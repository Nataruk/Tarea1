#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "lista.h"

// Implementación de agregarLibro
void agregarLibro(struct Libro** cabeza, char titulo[], char autor[], char genero[], char ISBN[], char ubicacion[]) {
  // Validar que los strings no tengan un largo mayor a 50 caracteres
  if (strlen(titulo) > 50 || strlen(autor) > 50 || strlen(genero) > 50 || strlen(ISBN) > 50 || strlen(ubicacion) > 50) {
    printf("Error: Los datos del libro exceden la longitud permitida.\n");
    return;
  }

  // Crear un nuevo libro
  struct Libro* nuevoLibro = (struct Libro*)malloc(sizeof(struct Libro));
  
  // Copiar los datos del libro
  strcpy(nuevoLibro->titulo, titulo);
  strcpy(nuevoLibro->autor, autor);
  strcpy(nuevoLibro->genero, genero);
  strcpy(nuevoLibro->ISBN, ISBN);
  strcpy(nuevoLibro->ubicacion, ubicacion);
  strcpy(nuevoLibro->estado, "Disponible");
  nuevoLibro->reservas = NULL;
  
  // Configurar los punteros
  nuevoLibro->siguiente = NULL;
  nuevoLibro->anterior = NULL;
  
  // Si la lista está vacía, el nuevo libro se convierte en la cabeza
  if (*cabeza == NULL) {
    *cabeza = nuevoLibro;
  } else {
    struct Libro* actual = *cabeza;
    while (actual->siguiente != NULL) {
        actual = actual->siguiente;
    }
    actual->siguiente = nuevoLibro;
    nuevoLibro->anterior = actual;
  }
}

// Implementación de mostrarLibros
void mostrarLibro(struct Libro* cabeza) {
  char titulo[50];
  char autor[50];
  
  printf("Ingrese el título del libro: ");
  scanf("%s", titulo);
  
  printf("Ingrese el autor del libro: ");
  scanf("%s", autor);
  
  struct Libro* actual = cabeza;
  bool encontrado = false;

  while (actual != NULL) {
    if (strcmp(actual->titulo, titulo) == 0 && strcmp(actual->autor, autor) == 0) {
      printf("Título: %s\n", actual->titulo);
      printf("Autor: %s\n", actual->autor);
      printf("Género: %s\n", actual->genero);
      printf("ISBN: %s\n", actual->ISBN);
      printf("Ubicación: %s\n", actual->ubicacion);
      printf("Estado: %s\n", actual->estado);
      encontrado = true;
      break; // Termina el bucle una vez que se encuentra el libro
    }
    actual = actual->siguiente;
  }

  if (!encontrado) {
    printf("El libro no se encuentra en la lista.\n");
  }
}

void mostrarTodosLosLibros(struct Libro* cabeza) {
  struct Libro* actual = cabeza;

  if (actual == NULL) {
    printf("No hay libros registrados en la lista.\n");
  } else {
    printf("Libros registrados:\n");
    while (actual != NULL) {
      printf("Título: %s\n", actual->titulo);
      printf("Autor: %s\n", actual->autor);
      printf("\n");
      actual = actual->siguiente;
    }
  }
}

void reservarLibro(struct Libro* cabeza, char titulo[], char autor[], char nombre_estudiante[]) {
  struct Libro* actual = cabeza;
  bool encontrado = false;

  while (actual != NULL) {
    if (strcmp(actual->titulo, titulo) == 0 && strcmp(actual->autor, autor) == 0) {
      encontrado = true;
      break;
    }
    actual = actual->siguiente;
  }

  if (!encontrado) {
    printf("El libro no se encuentra en la lista.\n");
    return;
  }

  // Crear una nueva reserva
  struct Reserva* nuevaReserva = (struct Reserva*)malloc(sizeof(struct Reserva));
  strcpy(nuevaReserva->nombre_estudiante, nombre_estudiante);
  nuevaReserva->siguiente = NULL;

  // Agregar la reserva a la cola de reservas del libro
  if (actual->reservas == NULL) {
    actual->reservas = nuevaReserva;
  } else {
    struct Reserva* reservaActual = actual->reservas;
    while (reservaActual->siguiente != NULL) {
      reservaActual = reservaActual->siguiente;
    }
    reservaActual->siguiente = nuevaReserva;
  }

  printf("Libro reservado por %s\n", nombre_estudiante);
}

void cancelarReserva(struct Libro* cabeza, char titulo[], char autor[], char nombre_estudiante[]) {
  struct Libro* actual = cabeza;
  bool encontrado = false;

  while (actual != NULL) {
    if (strcmp(actual->titulo, titulo) == 0 && strcmp(actual->autor, autor) == 0) {
        encontrado = true;
        break;
    }
    actual = actual->siguiente;
  }

  if (!encontrado) {
    printf("El libro no se encuentra en la lista.\n");
    return;
  }

  // Buscar y eliminar la reserva si existe
  struct Reserva* reservaActual = actual->reservas;
  struct Reserva* reservaAnterior = NULL;
  bool reservaEncontrada = false;

  while (reservaActual != NULL) {
    if (strcmp(reservaActual->nombre_estudiante, nombre_estudiante) == 0) {
      reservaEncontrada = true;
      break;
    }
    reservaAnterior = reservaActual;
    reservaActual = reservaActual->siguiente;
  }

  if (reservaEncontrada) {
    // Eliminar la reserva
    if (reservaAnterior != NULL) {
      reservaAnterior->siguiente = reservaActual->siguiente;
    } else {
      actual->reservas = reservaActual->siguiente;
    }
    free(reservaActual);
    printf("Reserva cancelada para %s en el libro '%s' por '%s'.\n", nombre_estudiante, titulo, autor);
  } else {
    printf("No se encontró una reserva para %s en el libro '%s' por '%s'.\n", nombre_estudiante, titulo, autor);
  }
}

void retirarLibro(struct Libro* cabeza, char titulo[], char autor[], char nombre_estudiante[]) {
  struct Libro* actual = cabeza;
  bool encontrado = false;

  while (actual != NULL) {
    if (strcmp(actual->titulo, titulo) == 0 && strcmp(actual->autor, autor) == 0) {
        encontrado = true;
        break;
    }
    actual = actual->siguiente;
  }

  if (!encontrado) {
    printf("El libro no se encuentra en la lista.\n");
    return;
  }

  if (strcmp(actual->estado, "Disponible") == 0) {
    // El libro está disponible para ser retirado
    strcpy(actual->estado, "Prestado");
    printf("El libro '%s' por '%s' ha sido prestado a '%s'.\n", titulo, autor, nombre_estudiante);
  } else if (strcmp(actual->estado, "Reservado") == 0) {
    // El libro está reservado, verificamos la cola de reservas
    if (actual->reservas != NULL && strcmp(actual->reservas->nombre_estudiante, nombre_estudiante) == 0) {
      // El estudiante actual es el primero en la cola de reservas
      strcpy(actual->estado, "Prestado");
      // Eliminar la reserva
      struct Reserva* reservaAnterior = actual->reservas;
      actual->reservas = actual->reservas->siguiente;
      free(reservaAnterior);
      printf("El libro '%s' por '%s' ha sido prestado a '%s'.\n", titulo, autor, nombre_estudiante);
    } else {
      printf("El libro '%s' por '%s' está reservado, pero no es el turno de '%s' para retirarlo.\n", titulo, autor, nombre_estudiante);
    }
  } else if (strcmp(actual->estado, "Prestado") == 0) {
    printf("El libro '%s' por '%s' ya ha sido prestado y no está disponible.\n", titulo, autor);
  }
}

void devolverLibro(struct Libro* cabeza, char titulo[], char autor[]) {
  struct Libro* actual = cabeza;
  bool encontrado = false;

  while (actual != NULL) {
      if (strcmp(actual->titulo, titulo) == 0 && strcmp(actual->autor, autor) == 0) {
          encontrado = true;
          break;
      }
      actual = actual->siguiente;
  }

    if (!encontrado) {
      printf("El libro no se encuentra en la lista.\n");
      return;
    }

    if (strcmp(actual->estado, "Prestado") == 0) {
      printf("El libro '%s' por '%s' ha sido devuelto y está ahora disponible.\n", titulo, autor);
      strcpy(actual->estado, "Disponible");
    } else if (strcmp(actual->estado, "Reservado") == 0) {
      if (actual->reservas != NULL) {
        // Hay una cola de reservas, el libro no puede ser devuelto sin haber sido retirado primero
        printf("El libro '%s' por '%s' está reservado, debe ser retirado antes de devolverlo.\n", titulo, autor);
      } else {
        // No hay reservas, cambiar el estado a "Disponible"
        strcpy(actual->estado, "Disponible");
        printf("El libro '%s' por '%s' ha sido devuelto y está ahora disponible.\n", titulo, autor);
      }
    } else {
      // El libro no está prestado ni reservado
      printf("El libro '%s' por '%s' no está prestado ni reservado, no se puede devolver.\n", titulo, autor);
    }
}

void mostrarLibrosPrestados(struct Libro* cabeza) {
  struct Libro* actual = cabeza;
  bool hayLibrosPrestados = false;

  while (actual != NULL) {
    if (strcmp(actual->estado, "Prestado") == 0) {
      hayLibrosPrestados = true;
      printf("Libro prestado: '%s' por '%s' a '%s'\n", actual->titulo, actual->autor, actual->nombre_Prestado);
    }
    actual = actual->siguiente;
  }

  if (!hayLibrosPrestados) {
    printf("[INFO] No hay libros prestados en este momento.\n");
  }
}

void importarLibrosDesdeCSV(const char* nombreArchivo, struct Libro** cabeza) {
  FILE* archivo = fopen(nombreArchivo, "r");
  bool flag = true;
  if (archivo == NULL) {
    printf("No se pudo abrir el archivo '%s'\n", nombreArchivo);
    return;
  }

  char linea[1024]; // Suponemos que las líneas del archivo CSV no superarán los 1024 caracteres

  while (fgets(linea, sizeof(linea), archivo)) {
    // Eliminamos el carácter de nueva línea al final de la línea
    size_t longitud = strlen(linea);
    if (longitud > 0 && linea[longitud - 1] == '\n') {
      linea[longitud - 1] = '\0';
    }

    // Variables para almacenar los campos
    char titulo[50]; 
    char autor[50];  
    char genero[50];
    char ISBN[50];
    char ubicacion[50];
    char estado[50];
    char nombre_Prestado[50];

    // Usa sscanf para dividir la línea en campos
    if (sscanf(linea, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]", titulo, autor, genero, ISBN, ubicacion, estado, nombre_Prestado) == 7) {
      // Crear un nuevo libro con 7 campos (libro prestado)
      struct Libro* nuevoLibro = (struct Libro*)malloc(sizeof(struct Libro));
      strcpy(nuevoLibro->titulo, titulo);
      strcpy(nuevoLibro->autor, autor);
      strcpy(nuevoLibro->genero, genero);
      strcpy(nuevoLibro->ISBN, ISBN);
      strcpy(nuevoLibro->ubicacion, ubicacion);
      strcpy(nuevoLibro->estado, estado);
      strcpy(nuevoLibro->nombre_Prestado, nombre_Prestado);
      nuevoLibro->reservas = NULL;
      nuevoLibro->siguiente = NULL;

      // Agregar el libro a la lista de libros
      if (*cabeza == NULL) {
        *cabeza = nuevoLibro;
      } else {
        struct Libro* actual = *cabeza;
        while (actual->siguiente != NULL) {
          actual = actual->siguiente;
        }
        actual->siguiente = nuevoLibro;
      }
    } else if (sscanf(linea, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]", titulo, autor, genero, ISBN, ubicacion, estado) == 6) {
      // Crear un nuevo libro con 6 campos (libro no prestado)
      struct Libro* nuevoLibro = (struct Libro*)malloc(sizeof(struct Libro));
      strcpy(nuevoLibro->titulo, titulo);
      strcpy(nuevoLibro->autor, autor);
      strcpy(nuevoLibro->genero, genero);
      strcpy(nuevoLibro->ISBN, ISBN);
      strcpy(nuevoLibro->ubicacion, ubicacion);
      strcpy(nuevoLibro->estado, estado);
      strcpy(nuevoLibro->nombre_Prestado, "");
      nuevoLibro->reservas = NULL;
      nuevoLibro->siguiente = NULL;

      // Agregar el libro a la lista de libros
      if (*cabeza == NULL) {
        *cabeza = nuevoLibro;
      } else {
        struct Libro* actual = *cabeza;
        while (actual->siguiente != NULL) {
          actual = actual->siguiente;
        }
        actual->siguiente = nuevoLibro;
      }
    } else {
      flag = false;
      printf("Error: La línea no contiene la cantidad correcta de campos: '%s'\n", linea);
    }
  }
  if (flag){
    printf("[INFO] Se importaron correctamente los datos\n\n");
  }
  fclose(archivo);
}


// esta funcion va aexportar lo que contiene la losta a un archivo nuevo de tipo CSV
void exportarLibrosACSV(const char* nombreArchivo, struct Libro* cabeza) {
  FILE* archivo = fopen(nombreArchivo, "w");
  if (archivo == NULL) {
    printf("No se pudo abrir el archivo '%s' para escritura.\n", nombreArchivo);
    return;
  }

  struct Libro* actual = cabeza;

  while (actual != NULL) {
    fprintf(archivo, "%s,%s,%s,%s,%s,%s\n", actual->titulo, actual->autor, actual->genero, actual->ISBN, actual->ubicacion, actual->estado);

    // Si el libro tiene una cola de reservas, escribir los datos de las reservas
    if (actual->reservas != NULL) {
      struct Reserva* reservaActual = actual->reservas;
      while (reservaActual != NULL) {
        fprintf(archivo, ",,%s,%s\n", reservaActual->nombre_estudiante);
        reservaActual = reservaActual->siguiente;
      }
    }

    actual = actual->siguiente;
  }

  fclose(archivo);
  printf("[INFO] Los datos se han exportado exitosamente al archivo '%s'.\n", nombreArchivo);
}


