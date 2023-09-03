#include <stdio.h>
//#include "lista.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "lista.h"
//Esta función permite imprimir el menú
void imprimirMenu();


int main() {
  
  int opcion = 0;
  bool continuar = true, hayLibros = false, importo = false;
  char titulo[50];
  char autor[50];
  char genero[50];
  char ISBN[50];
  char ubicacion[50];
  char nombre_estudiante[50];
  struct Libro * libro = NULL;
  
  while (continuar){
    //mostramos el menu para que usuario sepa que opcion seleccionar
    imprimirMenu();
    //se solicita la opción
    printf("Ingrese una opción: ");
    scanf("%i", &opcion);
    //********************
    if (opcion == 11){
      printf("\n");
      system("clear");
      printf("[INFO] Programa finalizado");
      continuar = false;
    }
    //********************
    if (opcion < 1 || opcion > 11){
      system("clear");
      printf("[ERROR] Ingrese una opción válida\n");
      printf("\n");
      continue;
    }
    // ******************
    if (opcion == 1){ // registrar un libro
      hayLibros = true; // es un flag para indicar que se creo la lista en otras opciones
      system("clear");
      printf("//REGISTRAR UN LIBRO\n\n");
      printf("Ingrese el título del libro: \n");
      scanf("%s", titulo);
      printf("Ingrese el autor: \n");
      scanf("%s", autor);
      printf("Ingrese el genero del libro: \n");
      scanf("%s", genero);
      printf("Ingrese el ISBN: \n");
      scanf("%s", ISBN);
      printf("Ingrese la ubicacion del libro: \n");
      scanf("%s", ubicacion);
      // llamamos a la funcion agregar libro
      agregarLibro(&libro, titulo, autor ,genero, ISBN, ubicacion);
      system("clear");
      printf("[INFO] Datos guardados correctamente\n");
      printf("\n");
    }
    
    //*******************+*
    if (opcion == 2){ // mostrar datos de libro
      system("clear");
      if (hayLibros == false && importo == false){ // verificar si se importaron o se registraron libros antes de mostrar datos
        printf("[INFO] No hay libros en la lista\n");
      }else{
        printf("//DATOS DE LIBRO ESPECIFICO\n\n");
        mostrarLibro(libro);
      }
    }
    //*********************
    if (opcion == 3){ // mostrar todos los libros
      system("clear");
      printf("//MOSTRAR TODOS LOS LIBROS\n\n");
      mostrarTodosLosLibros(libro);
    }
    //***************************
    if (opcion == 4){ // reservar libro
      system("clear");
      if (hayLibros) { // Verifica que haya libros en la lista antes de intentar reservar
        printf("//RESERVAR UN LIBRO\n\n");
        char titulo[50];
        char autor[50];
        char nombre_estudiante[50];
        printf("Ingrese el título del libro que desea reservar: ");
        scanf("%s", titulo);
        
        printf("Ingrese el autor del libro que desea reservar: ");
        scanf("%s", autor);
        printf("Ingrese nombre para la reserva: ");
        scanf("%s", nombre_estudiante);
        
        reservarLibro(libro, titulo, autor, nombre_estudiante);
      } else {
        printf("[INFO] No hay libros en la lista para reservar.\n");
      }
    }
    //************************
    if (opcion == 5){ // cancelar reserva de libro
      system("clear");
      
      if (hayLibros) { // Verifica que haya libros en la lista antes de intentar cancelar una reserva
        printf("//CANCELAR RESERVA DE LIBRO");

        printf("Ingrese el título del libro: \n");
        scanf(" %99[^\n]", titulo); // Agrega un espacio antes de % para ignorar espacios en blanco previos
        
        printf("Ingrese el autor: \n");
        scanf(" %99[^\n]", autor); // Agrega un espacio antes de % para ignorar espacios en blanco previos
        
        printf("Ingrese el nombre del estudiante: \n");
        scanf(" %99[^\n]", nombre_estudiante); // Agrega un espacio antes de % para ignorar espacios en blanco previos

        cancelarReserva(libro, titulo, autor, nombre_estudiante);
      } else {
        printf("[INFO] No hay libros en la lista para cancelar una reserva.\n");
      }
      printf("\n");
    }
    //***********************
    if (opcion == 6){ // retirar libro
      char titulo[50];
      char autor[50];
      char nombre_estudiante[50];
      system("clear");
      if (hayLibros) { // Verifica que haya libros en la lista antes de intentar retirar un libro
        printf("//RETIRAR UN LIBRO\n\n");
        printf("Ingrese el título del libro: ");
        scanf("%s", titulo);

        printf("Ingrese el autor del libro: ");
        scanf("%s", autor);

        printf("Ingrese nombre para retirar el libro: ");
        scanf("%s", nombre_estudiante);

        retirarLibro(libro, titulo, autor, nombre_estudiante);
      } else {
        printf("[INFO] No hay libros en la lista para retirar.\n");
      }
    }
    //************************
    if (opcion == 7){ // devolver libro
      system("clear");
      if (hayLibros) { // Verifica que haya libros en la lista antes de intentar devolver un libro
        printf("//DEVOLVER UN LIBRO\n\n");
        char titulo[50];
        char autor[50];

        printf("Ingrese el título del libro a devolver: ");
        scanf("%s", titulo);

        printf("Ingrese el autor del libro a devolver: ");
        scanf("%s", autor);

        devolverLibro(libro, titulo, autor);
      } else {
        printf("[INFO] No hay libros en la lista para devolver.\n");
      }
    }
    //************************
    if (opcion == 8) { // mostrar libros prestados
      system("clear");
      if (hayLibros) { // Verifica que haya libros en la lista antes de mostrar libros prestados
        printf("//LIBROS PRESTADOS\n\n");
        mostrarLibrosPrestados(libro);
      } else {
        printf("[INFO] No hay libros en la lista para mostrar libros prestados.\n");
      }
    }
    
    if (opcion == 9){
      system("clear");
      printf("//IMPORTAR UN ARCHIVO\n\n");
      char nombreArchivo[100];
      printf("Ingrese el nombre del archivo CSV: ");
      scanf("%s", nombreArchivo);
    
    // Construye la ruta completa al archivo CSV en tu repositorio de Replit
      char rutaCompleta[200];
      snprintf(rutaCompleta, sizeof(rutaCompleta), "/home/runner/TAREA1/%s", nombreArchivo);
  
      importarLibrosDesdeCSV(rutaCompleta, &libro);
      importo = true;
      hayLibros = true;
    }
    
    if (opcion == 10){ // exportar libros a un CSV
      system("clear");
      if (hayLibros){
        printf("//EXPORTAR LIBROS\n\n");
        char nombreArchivo[100];
        printf("Ingrese el nombre del archivo CSV para exportar: ");
        scanf("%s", nombreArchivo);
        exportarLibrosACSV(nombreArchivo, libro);
      
        printf("\n");
      }
      else{
        printf("[INFO] No hay libros para exportar");
        printf("\n");
      }
      
    }
  }
  return 0;
}

void imprimirMenu(){
  printf("**Biblioteca v1.0**\n");
  printf("\n");
  printf("Por favor seleccione una opción:\n");
  printf("\n");
  printf("1) Registrar Libro\n");
  printf("2) Mostrar datos de libro\n");
  printf("3) Mostrar todos los libros\n");
  printf("4) Reservar libro\n");
  printf("5) Cancelar reserva de libro\n");
  printf("6) Retirar libro\n");
  printf("7) Devolver libro\n");
  printf("8) Mostrar libros prestados\n");
  printf("9) Importar libros (Archivo CSV)\n");
  printf("10) Exportar libros (Archivo CSV)\n");
  printf("11) Salir\n");
  printf("\n");
}