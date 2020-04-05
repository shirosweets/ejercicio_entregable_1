/* Materia: Algoritmos y Estructura de Datos II - 2020 FAMAF
    <<<<< EJERCICIO ENTREGABLE 1 >>>>>

Alumna:  
    - Vispo, Valentina Solange

Link de descarga: https://wiki.cs.famaf.unc.edu.ar/lib/exe/fetch.php?media=algo2:main:ejercicio_entregable_1.zip

Teórico:
https://wiki.cs.famaf.unc.edu.ar/lib/exe/fetch.php?media=algo2:main:2020.03.recurrenciasdyv.y.jerarquia.pdf
https://www.youtube.com/watch?v=rQxUUjNBhd8
https://youtu.be/n5D1KExw30Y

Videos explicativos:
<Búsqueda binaria>
https://youtu.be/HyZVdkkCf2Q
*/

/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/* Se pide la implementación de 2 funciones cuyo esqueleto se encuentra en el archivo main.c
1) Escribe un algoritmo que encuentre la cima de un arreglo dado (asumiendo que
efectivamente tiene una cima) utilizando una búsqueda secuencial, desde el comienzo
del arreglo hacia el final.
2) Escribe un algoritmo que resuelva el mismo problema del inciso anterior utilizando la
idea de búsqueda binaria.

Vídeos profe: https://drive.google.com/file/d/1-E08AEbmw6gPAno2jN1w9J2ndIJvLQi2/view
*/

/* Then, this project's includes, alphabetically ordered */
#include "array_helpers.h"

/* Maximum allowed length of the array */
static const unsigned int MAX_SIZE = 100000u;

void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n"
           "Save an array given in a file in disk.\n"
           "\n"
           "The input file must have the following format:\n"
           " * The first line must contain only a positive integer,"
           " which is the length of the array.\n"
           " * The second line must contain the members of the array"
           " separated by one or more spaces. Each member must be an integer."
           "\n\n"
           "In other words, the file format is:\n"
           "<amount of array elements>\n"
           "<array elem 1> <array elem 2> ... <array elem N>\n\n",
           program_name);
}
/*
fun esCima(in : a:array[1..n] of nat) ret confirm : bool
    var max_ind, j: nat
    max_ind := 1
    for i:=2 to n do  -> if a[i]>a[max_ind] then max_ind := i  fi od

    j :=1
   do (j<max_ind   AND   a[j]<a[j+1]) --->   j:=j+1  od

   do (j<n   AND   a[j]>a[j+1]) --->   j:=j+1  od
*/

  // Funcion agregada por mi, comprueba si la matriz tiene cima 
bool esCima (int a[], int length){ // Inicio funcion esCima
  int i,n;
  n=(length-1);
  i=0;
  while (i<n && a[i]<a[i+1]){
    i++;
  }
  while(i<n && a[i]>a[i+1]){
    i++;
  }
  if (i==n){
    printf("\n\n >>> Tiene cima <<<\n");
    return true;
  }
  else{
    printf("\n\n >>> No tiene cima <<<\n");
    return false;
  }
} // Fin funcion esCima

// Ej 1: Funtion that finds the peak on the array, if it does not exist, return -1
int array_peak_sequential(int a[], unsigned int length) { // Inicio funcion array_peak_sequential
  unsigned int i = 0;
  if(esCima(a, length) && length>0){
    while(i<length && a[i]<a[i+1]){
      ++i;
    }
  }
  else{
    return -1;
  }
  return i;
  //please change whatever you need here to make it work.
  //return 0;
} // Fin funcion array_peak_sequential

/*      PSEUDOCODIGO

    if a[mid-1] <= a[mid] >= a[mid+1] then cima = mid
                a[mid-1] <= a[mid] <= a[mid+1] then cima = cima_bynary_search(a, mid+1, rgt)
                a[mid-1] >= a[mid] >= a[mid+1] then cima = cima_binary_search(a, lft, mid-1)
                fi

*/

int array_peak_binary_rec (int a[], int length, int izq, int der){ // Inicio funcion array_peak_binary_rec
  int cima_b=0;
  int mid;
  if(esCima(a, length)==true){
    mid=(der+izq)/2;
    printf("1er mid:%d", mid);
    printf(", der:%d izq:%d\n", der, izq);
    if(a[mid-1]<a[mid] && a[mid]>a[mid+1]){ // Si el elemento del medio es mayor que el de la 
    // derecha y es mayor que el que está a la izquierda
      cima_b=mid;
      printf("2do mid:%d", mid);
    }
    else if(a[mid-1]<a[mid] && a[mid]<a[mid+1]){ // Si el elemento del medio es mayor que el de la 
    // derecha pero es menor que el que está a la izquierda
      printf("\n\n 3 mid: %d", mid);
      printf("\n\n 3 izq: %d", izq);
      printf("\n\n 3 der: %d", der);
      printf("\n\n 3 length: %d", length);
      mid= array_peak_binary_rec(a, length, mid+1, der);
    }
    else if(a[mid-1]>a[mid] && a[mid]>a[mid+1]){ // Si el elemento del medio es menor que el de la 
    // derecha pero es mayor que el que está a la izquierda
      printf("\n\n 4 mid: %d", mid);
      printf("\n\n 4 izq: %d", izq);
      printf("\n\n 4 der: %d", der);
      printf("\n\n 4 length: %d", length);
      mid= array_peak_binary_rec(a, length, izq, mid-1);
    }
    else if(a[der]<a[der+1]){
      cima_b=0;
    }
    else if(a[length-1]>a[length-2]){
      cima_b=length-1;
    }
  }
  else{
    return cima_b;
  }
  printf("\n\n REC cima_b: %d", cima_b);
  return cima_b;
} // Fin funcion array_peak_binary_rec

// Ej 2: Funtion that finds the peak on the array, if it does not exist, return -1
int array_peak_binary(int a[], unsigned int length) { // Inicio funcion array_peak_binary
    int cima_b;
    cima_b= array_peak_binary_rec(a, length, 0, length-1);
    printf("k: %d", cima_b);
    return cima_b;
    //please change whatever you need here to make it work.
    //return 0;
} // Fin funcion array_peak_binary

/* Nehuen
int array_peak_binary_rec (int a[], int length, int izq, int der){ // Inicio funcion array_peak_binary_rec
    int mid,k;
    mid=(izq+der)/2;
    if(esCima(a, length)){
        k=-1;
        if(length==1){
            k=0;
        }
        else if(a[length-1]>a[length-2]){
            k=length-1;
        }
        else if(a[mid]>a[mid+1] && a[mid]>a[mid-1]){
            k=mid;
        }
        else if(a[mid]<a[mid+1] && a[mid]>a[mid-1]){
            array_peak_binary_rec(a, length, izq, mid-1);
        }
        else if(a[mid]>a[mid+1] && a[mid]<a[mid-1]){
            array_peak_binary_rec(a, length, mid+1, der);
        }
    }
    else{
        k=-1;
    }
    printf("k: %d", k);
    return k;
} // Fin funcion array_peak_binary_rec
*/

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < 2) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }
    result = argv[1];
    return (result);
}

int main(int argc, char *argv[]) {
  /* Arreglo con cima: [1] [2] n=1
  [1 2 3] [3 2 1] n=3
  [5 4 3 2 1], [1 2 3 4 5], [1 2 5 2 1] n=5
  [1 2 3 4 3 2 1] n=7 */
  // Asumo que existe cima directamente
  printf(" ********* Inicio programa *********\n");
  char *filepath = NULL;

  /* parse the filepath given in command line arguments */
  filepath = parse_filepath(argc, argv);

  /* create an array of MAX_SIZE elements */
  int array[MAX_SIZE];

  /* parse the file to fill the array and obtain the actual length */
  unsigned int length = array_from_file(array, MAX_SIZE, filepath);

  /* show the ordered array in the screen */
  array_dump(array, length);

  int this_is_the_peak = array_peak_sequential(array, length);
  printf("\n The peak is: %d", this_is_the_peak);

  printf("\n\n array_peak_binary");
  //TODO: Uncomment this to do part b
  //array_peak_binary(array, length);

  printf("\n\n ********* Fin programa *********\n");
  return (1);
}
/*
 Para correrlo al programa
gcc -Wall -Werror -Wextra -pedantic -std=c99 -c array_helpers.c
gcc -Wall -Werror -Wextra -pedantic -std=c99 -o lab_extra *.o main.c

Para ejecutarlo
./lab_extra input/unsorted-100.in
*/

/*
Chicos por si le sirve a alguien entendi los errores al compilar el trabajo que tenemos que entregar:
Primero los dos codigos para compilar escribanlo ustedes, no lo copien estan mal copiados, debe haber un espacio de mas o lago asi
Despues para ejecutar el programa no tienen que usar "./lab_extra ../input/unsorted-100.in" porque esta pidiendo que vuela 
atras y busque la carpeta input pero la carpeta input esta en el mismo lugar donde estan trabajando entonces 
tienen que usar: "./lab_extra input/unsorted-100.in" y va a compilar perfecto
*/

/*
Los siguientes arreglos tienen cima?
    1)   [1] 
Sí, en la primera posición: todos los elementos anteriores (0 elementos) están en orden creciente, 
y todos los siguientes (0 elementos) en orden decreciente.
    2)   [1,1,2,3,2,1] o con cualquier numero repetido que no sea la " cima"(en este caso 3)
No, porque los elementos del principio no están en orden creciente estricto (estricto significa 
que no hay repetidos).
    3)   [1,2,3,4,5] (o en orden descendente)
Sí
*/

/* Aclaro, cuando digo "usar búsqueda binaria" quiero decir usar la idea de la búsqueda binaria. 
No hay que usar las funciones binary_search y binary_search_rec tal cual están, si no que hay 
que definir funciones cima y cima_rec usando las mismas ideas que esas funciones. */

/* Hola, mirando el enunciado nos dice:

"cima de a es un valor k en el intervalo 1, . . . , n tal que a[1..k] está ordenado 
crecientemente y a[k..n] está ordenado decrecientemente"

Veamos entonces que si ese valor k es 1, la cima está en el primer elemento, y si k es n, 
está en el último. */