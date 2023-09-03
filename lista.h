#ifndef LISTA_H
#define LISTA_H

// Estructura para una reserva
struct Reserva {
    char nombre_estudiante[50];
    struct Reserva* siguiente;
};

// Estructura para un libro
struct Libro {
    char titulo[50];
    char autor[50];
    char genero[50];
    char ISBN[50];
    char ubicacion[50];
    char estado[50]; // "Disponible", "Prestado" o "Reservado"
    char nombre_Prestado[50];
    struct Reserva* reservas; // Cola de reservas
    struct Libro* siguiente;
    struct Libro* anterior;
};

// Declaraciones de funciones
void agregarLibro(struct Libro** cabeza, char titulo[], char autor[], char genero[], char ISBN[], char ubicacion[]);
void mostrarLibro(struct Libro* cabeza);
void mostrarTodosLosLibros(struct Libro* cabeza);
void reservarLibro(struct Libro* cabeza, char titulo[], char autor[], char nombre_estudiante[]);
void cancelarReserva(struct Libro* cabeza, char titulo[], char autor[], char nombre_estudiante[]);
void retirarLibro(struct Libro* cabeza, char titulo[], char autor[], char nombre_estudiante[]);
void devolverLibro(struct Libro* cabeza, char titulo[], char autor[]);
void mostrarLibrosPrestados(struct Libro* cabeza);
void importarLibrosDesdeCSV(const char* nombreArchivo, struct Libro** cabeza);
void exportarLibrosACSV(const char* nombreArchivo, struct Libro* cabeza);


#endif
