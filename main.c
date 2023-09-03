#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct Reserva
{
    char nombreEstudiante[51];
    struct Reserva *siguiente;
} Reserva;

typedef struct QueueReserva
{
  Reserva *frente;
  Reserva *final;  //Definición del struct QueueReserva para manejar la cola de reservas.
} QueueReserva;

typedef struct
{
    char titulo[51];
    char autor[51];
    char genero[51];
    char ISBN[51];
    char ubicacion[51];
    char estado[51];
    QueueReserva *colaReservas;
} Libro;

typedef struct
{
    Libro libros[100];
    int cantLibros;
} Biblioteca;

void enqueue(QueueReserva *cola, const char *nombreEstudiante) //Función para agregar una reserva a la cola.
{
  Reserva *nuevaReserva = (Reserva *) malloc (sizeof(Reserva)); // Creación de una nueva reserva.
  if (nuevaReserva == NULL)
  {
    exit(EXIT_FAILURE);
  }
  strcpy(nuevaReserva->nombreEstudiante, nombreEstudiante);
  nuevaReserva->siguiente = NULL; //Se agrega el nombre del estudiante a la reserva.


  if (cola->final == NULL) //Se actualiza la cola.
  {
    cola->frente = nuevaReserva;
    cola->final = nuevaReserva;
  }
  else
  {
    cola->final->siguiente = nuevaReserva;
    cola->final = nuevaReserva;
  }
}

QueueReserva *createQueue() //Función para crear una cola de reservas vacías.
{
  QueueReserva *queue = (QueueReserva *)malloc(sizeof(QueueReserva));
  if (queue == NULL)
  {
    exit(EXIT_FAILURE);
  }
  queue->frente = NULL;
  queue->final = NULL;
  return queue;
}

void asignarUbicacionAleatoria(Libro *libro) //Función para asignar un aubicación aleatoria al libro.
{
    int seccion = rand() % 4;
    int numero = rand() % 26;
    char seccionLetra = 'A' + seccion;
    sprintf(libro->ubicacion, "%c%d", seccionLetra, numero);
}

//Función para agregar un libro a la biblioteca. 
void registrarLibro(Biblioteca *biblioteca)
{
    if (biblioteca->cantLibros >= 100)
    {
        printf("La biblioteca está llena, por favor vuelva más tarde.\n");
        return;
    }

    Libro nuevoLibro;

    printf("Ingrese el título de su libro: \n");
    fgets(nuevoLibro.titulo, sizeof(nuevoLibro.titulo), stdin);
    nuevoLibro.titulo[strcspn(nuevoLibro.titulo, "\n")] = '\0';

    printf("Ingrese el autor de su libro: \n");
    fgets(nuevoLibro.autor, sizeof(nuevoLibro.autor), stdin); //Se utiliza sizeof() para indicar el tamaño máximo de caracteres que se puede leer en la línea, para evitar desbordamientos de buffer.
  
    nuevoLibro.autor[strcspn(nuevoLibro.autor, "\n")] = '\0'; //Se elimina el salto de linea leido al ingresar datos por teclado

    printf("Ingrese el género de su libro: \n");
    fgets(nuevoLibro.genero, sizeof(nuevoLibro.genero), stdin);
    nuevoLibro.genero[strcspn(nuevoLibro.genero, "\n")] = '\0';

    printf("Ingrese el ISBN de su libro: \n");
    fgets(nuevoLibro.ISBN, sizeof(nuevoLibro.ISBN), stdin);
    nuevoLibro.ISBN[strcspn(nuevoLibro.ISBN, "\n\n")] = '\0';

    strcpy(nuevoLibro.estado, "disponible");
    nuevoLibro.colaReservas = NULL;

  //Se ingresan los datos de título, autor, género e ISBN del libro y se almacenan en nuevoLibro, se crea su estado y se define como disponible.
  
    asignarUbicacionAleatoria(&nuevoLibro);

    biblioteca->libros[biblioteca->cantLibros] = nuevoLibro;
    (biblioteca->cantLibros)++; //Se le asigna una ubicación al libro creado y se le suma uno al contador de cantidad de libros.

    printf("Se ha registrado su libro con éxito.\n");
}

void mostrarDatosLibro(Biblioteca biblioteca) //Función para mostrar los datos de un libro en específico (creado previamente).
{
    char tituloBuscado[51];
    char autorLibro[51];
    
    printf("Ingrese el título de su libro buscado: ");
    fgets(tituloBuscado, sizeof(tituloBuscado), stdin);
    tituloBuscado[strcspn(tituloBuscado, "\n")] = '\0';

    printf("Ingrese el autor de su libro buscado: ");
    fgets(autorLibro, sizeof(autorLibro), stdin);
    autorLibro[strcspn(autorLibro, "\n")] = '\0';

    //Se recorre la lista de libros hasta que coincidan los datos entregados con un libro de la lista, si coinciden,   se imprime.
    for (int i = 0 ; i < biblioteca.cantLibros ; i++)
    {
        Libro* libro = &(biblioteca.libros[i]); //Dentro del bucle, esta línea declara un puntero libro que apunta al i-ésimo libro en la biblioteca. El operador & se usa para obtener la dirección de memoria del libro en la posición i
        if (strcmp(libro->titulo, tituloBuscado) == 0 && strcmp(libro->autor, autorLibro) == 0)
        {
            printf("Resultados del libro que busca:\n");
            printf("Título: %s\n", libro->titulo);
            printf("Autor: %s\n", libro->autor);
            printf("Género: %s\n", libro->genero);
            printf("ISBN: %s\n", libro->ISBN);
            printf("Ubicación: %s\n", libro->ubicacion);
            printf("Estado: %s\n", libro->estado);
            
            //Si la cola de reservas no está vacía, se imprime el nombre del estudiante más antiguo en la cola que reservó el libro.
            if (libro->colaReservas != NULL)
            {
                printf("Reservas actuales:\n");
                Reserva *reservaActual = libro->colaReservas->frente;
                while (reservaActual != NULL) 
                {
                    printf("- Estudiante: %s\n", reservaActual->nombreEstudiante);
                    reservaActual = reservaActual->siguiente;
                }
            }
            else
            {
                printf("No hay reservas para este libro.\n");
            }
            return;
        }
    }
    printf("Lo sentimos, el libro buscado no está disponible.\n");
}

void mostrarTodosLosLibros(Biblioteca biblioteca)
{
    if (biblioteca.cantLibros == 0)
    {
        printf("No hay libros registrados en la biblioteca.\n"); //Si el contador de la cantidad de libros se encuentra en 0, imprimir que no hay libros registrados.
        return;
    }
    printf("Lista de libros:\n");
    //Se recorre la lista de libros y se muestra su título y su autor.
    for (int i = 0 ; i < biblioteca.cantLibros ; i++)
    {
        Libro* libro = &(biblioteca.libros[i]);
        printf("- Título: %s, Autor: %s\n", libro->titulo, libro->autor);
    }
}

void reservarLibro(Biblioteca *biblioteca) 
{
    char tituloBuscado[51];
    char autorLibro[51];
    char nombreEstudiante[51];

    printf("Ingrese el título del libro: ");
    fgets(tituloBuscado, sizeof(tituloBuscado), stdin);
    tituloBuscado[strcspn(tituloBuscado, "\n")] = '\0';

    printf("Ingrese el autor del libro: ");
    fgets(autorLibro, sizeof(autorLibro), stdin);
    autorLibro[strcspn(autorLibro, "\n")] = '\0';

    printf("Ingrese su nombre: ");
    fgets(nombreEstudiante, sizeof(nombreEstudiante), stdin);
    nombreEstudiante[strcspn(nombreEstudiante, "\n")] = '\0';

    for (int i = 0; i < biblioteca->cantLibros; i++) 
    {
        Libro *libro = &biblioteca->libros[i];
        if (strcmp(libro->titulo, tituloBuscado) == 0 && strcmp(libro->autor, autorLibro) == 0) //Se utiliza la función strcmp para comparar el título del libro (libro->titulo) con la cadena tituloBuscado y el autor del libro (libro->autor) con una cadena nb autorLibro.
        {
            //Si el titulo y autor coinciden con uno de la lista, se crea una nueva reserva.
            Reserva *nuevaReserva = malloc(sizeof(Reserva));
            strcpy(nuevaReserva->nombreEstudiante, nombreEstudiante);

            //Se verifica si el libro tiene una cola de reservas, si no la tiene, se crea.
            if (libro->colaReservas == NULL) 
            {
                libro->colaReservas = createQueue();
            }

            //Se agrega la nueva reserva a la cola de reservas del libro.
            enqueue(libro->colaReservas, nuevaReserva);

            printf("Libro reservado con éxito para %s.\n", nombreEstudiante);
            return;
        }
    }
    printf("El libro no fue encontrado.\n");
}

void cancelarReservaLibro(Biblioteca *biblioteca)
{
    char tituloBusqueda[51];
    char autorBusqueda[51]; //se define tamaño de los arreglos de carácteres para almacenar el título, autor y nombre del estudiante 
    char nombreEstudiante[51];
    
    printf("Ingrese el título del libro: ");
    fgets(tituloBusqueda, sizeof(tituloBusqueda), stdin);
    tituloBusqueda[strcspn(tituloBusqueda, "\n")] = '\0';

    printf("Ingrese el autor del libro: ");
    fgets(autorBusqueda, sizeof(autorBusqueda), stdin);
    autorBusqueda[strcspn(autorBusqueda, "\n")] = '\0';

    printf("Ingrese su nombre: ");
    fgets(nombreEstudiante, sizeof(nombreEstudiante), stdin);
    nombreEstudiante[strcspn(nombreEstudiante, "\n")] = '\0';
    for (int i = 0; i < biblioteca->cantLibros; i++)
    {
        Libro *libro = &biblioteca->libros[i];
        if (strcmp(libro->titulo, tituloBusqueda) == 0 && strcmp(libro->autor, autorBusqueda) == 0)
        {
            if (libro->colaReservas != NULL)
            {
                Reserva *reservaActual = libro->colaReservas->frente;
                Reserva *reservaAnterior = NULL;

                //Se busca la reserva actual del libro.
                while (reservaActual != NULL)
                {
                    if (strcmp(reservaActual->nombreEstudiante, nombreEstudiante) == 0) //Se compara el nombre ingresado con el almacenado en la reserva.
                    {
                        //Se elimina la reserva si coincide el nombre usado al reservar.
                        if (reservaAnterior == NULL)
                        {
                            libro->colaReservas->frente = reservaActual->siguiente;
                        }
                        else
                        {
                            reservaAnterior->siguiente = reservaActual->siguiente;
                        }
                        free(reservaActual); //Se libera la memoria de reservaActual
                        printf("Su reserva ha sido cancelada con éxito.\n");
                        return;
                    }
                    reservaAnterior = reservaActual;
                    reservaActual = reservaActual->siguiente; 
                }
            }
            printf("No se encontró su reserva para este libro.\n");
            return;
        }
    }
    printf("El libro buscado no fue encontrado.\n");
}

void retirarLibro(Biblioteca *biblioteca)
{
    char tituloBusqueda[51];
    char autorBusqueda[51];
    char nombreEstudiante[51];
    
    printf("Ingrese el título del libro: ");
    fgets(tituloBusqueda, sizeof(tituloBusqueda), stdin);
    tituloBusqueda[strcspn(tituloBusqueda, "\n")] = '\0';

    printf("Ingrese el autor del libro: ");
    fgets(autorBusqueda, sizeof(autorBusqueda), stdin);
    autorBusqueda[strcspn(autorBusqueda, "\n")] = '\0';

    printf("Ingrese su nombre: ");
    fgets(nombreEstudiante, sizeof(nombreEstudiante), stdin);
    nombreEstudiante[strcspn(nombreEstudiante, "\n")] = '\0';
    
    for (int i = 0 ; i < biblioteca->cantLibros ; i++)
    {
        Libro *libro = &(biblioteca->libros[i]);
        if (strcmp(libro->titulo, tituloBusqueda) == 0 && strcmp(libro->autor, autorBusqueda) == 0)
        {
            if (strcmp(libro->estado, "prestado") == 0 || (libro->colaReservas != NULL && strcmp(libro->colaReservas->frente->nombreEstudiante, nombreEstudiante) == 0)) //Se verifica si el libro está prestado o si hay una cola de reservas y si el nombre del estudiante que desea retirar el libro coincide con el nombre del estudiante en la parte frontal de la cola de reservas.
            {
                if (strcmp(libro->estado, "disponible") == 0)
                {  //si el libro está disponble, se actualiza su estado a prestado.
                    strcpy(libro->estado, "prestado");
                }
                
                if (libro->colaReservas != NULL)
                {
                    Reserva *nodoEliminar = libro->colaReservas->frente; 
                    libro->colaReservas->frente = libro->colaReservas->frente->siguiente; // Si existen reservas se elimina la más antigua. Se actualiza el frente de la cola y se libera la memoria del nodoEliminar.
        
                    free(nodoEliminar);
                }
                printf("Libro retirado con éxito.\n");
                return;
            }
            else
            {
                printf("Usted no puede retirar este libro, no está reservado en su nombre o no está disponible.\n");
                return;
            }
        }
    }
    printf("El libro no fue encontrado.\n");
}

void devolverLibro(Biblioteca *biblioteca)
{
    char tituloBusqueda[51];
    char autorBusqueda[51];
    char nombreEstudiante[51];
    
    printf("Ingrese el título de su libro: ");
    fgets(tituloBusqueda, sizeof(tituloBusqueda), stdin);
    tituloBusqueda[strcspn(tituloBusqueda, "\n")] = '\0';  
  
    printf("Ingrese el autor de su libro: ");
    fgets(autorBusqueda, sizeof(autorBusqueda), stdin);
    autorBusqueda[strcspn(autorBusqueda, "\n")] = '\0';  
  
    printf("Ingrese su nombre: ");
    fgets(nombreEstudiante, sizeof(nombreEstudiante), stdin);
    nombreEstudiante[strcspn(nombreEstudiante, "\n")] = '\0';
    
    for (int i = 0; i < biblioteca->cantLibros; i++)
    {
        Libro *libro = &biblioteca->libros[i];
        if (strcmp(libro->titulo, tituloBusqueda) == 0 && strcmp(libro->autor, autorBusqueda) == 0)
        {
            if (strcmp(libro->estado, "prestado") == 0 || libro->colaReservas != NULL && strcmp(libro->colaReservas->frente->nombreEstudiante, nombreEstudiante) == 0)
            {//Se verifica si el nombre y autor del libro corresponden a uno que haya sido registrado, de ser así, se cambia su estado prestado a disponible. Se elimina la reserva.
                strcpy(libro->estado, "disponible");
                Reserva *nodoEliminar = libro->colaReservas->frente;
                libro->colaReservas->frente = libro->colaReservas->frente;
                free(nodoEliminar);
                printf("Libro devuelto con éxito.\n");
                return;
            }
            else if (strcmp(libro->estado, "prestado") == 0 && strcmp(libro->colaReservas->frente->nombreEstudiante, nombreEstudiante) != 0)
            {
                printf("Usted no puede devolver este libro, no está prestado en su nombre.\n");
                return;
            }
        }
    }
    printf("El libro buscado no fue encontrado o no está prestado.\n");
}

void mostrarLibrosPrestados(Biblioteca biblioteca)
{
    int librosPrestados = 0;
    printf("Libros prestados:\n");
    
    for(int i = 0 ; i < biblioteca.cantLibros ; i++)
    {
        Libro *libro = &(biblioteca.libros[i]);
        if (strcmp(libro->estado, "prestado") == 0)
        {
            librosPrestados++; //Se hace un contador que iterará una vez por cada libro que haya sido registrado, se buscan los libros que tengan estado "prestado" para aumentarc el contador librosPrestados.
            printf("- Título: %s, Autor: %s", libro->titulo, libro->autor); 
            
            if (libro->colaReservas != NULL)
            {
                printf(", Prestado a: ");
                Reserva *reservaActual = libro->colaReservas->frente;
                while (reservaActual != NULL) 
                {
                    printf("%s, ", reservaActual->siguiente->nombreEstudiante);
                    reservaActual = reservaActual->siguiente;
                }
                printf("\n");
            }
            else
            {
                printf(", Sin reservas\n");
            }
        }
    }
    if (librosPrestados == 0)
    {
        printf("No hay libros prestados en este momento.\n");
    }
}
int main()
{
  srand(time(NULL));
  Biblioteca biblioteca;
  biblioteca.cantLibros = 0;
  //Dado un ingreso de número del usuario, entra en el switch y llama a la función correspondiente. Esto se detiene si el número ingresado es un 0.
  int opcion;
  do
    {
      printf("Bienvenido! Pulsa:\n");
      printf("1 Para: Registrar Libro.\n");
      printf("2 Para: Mostrar Datos De Un Libro.\n");
      printf("3 Para: Mostrar Todos Nuestros Libros.\n");
      printf("4 Para: Reservar Un Libro.\n");
      printf("5 Para: Cancelar Reserva De Un Libro.\n");
      printf("6 Para: Retirar Un Libro.\n");
      printf("7 Para: Devolver Un Libro.\n");
      printf("8 Para: Mostrar Libros Prestados.\n");
      printf("0 Para: Salir.\n\n");
      scanf("%d", &opcion);

      while (getchar() != '\n');
      
      switch(opcion)
        {
          case 1:
            {
              registrarLibro(&biblioteca);
              break;
            }
          case 2:
            {
              mostrarDatosLibro(biblioteca);
              break;
            }
          case 3:
            {
              mostrarTodosLosLibros(biblioteca);
              break;
            }
          case 4:
            {
              reservarLibro(&biblioteca);
              break;
            }
          case 5:
            {
              cancelarReservaLibro(&biblioteca);
              break;
            }
          case 6:
            {
              retirarLibro(&biblioteca);
              break;
            }
          case 7:
            {
              devolverLibro(&biblioteca);
              break;
            }
          case 8:
            {
              mostrarLibrosPrestados(biblioteca);
              break;
            }
          case 0:
            {
              printf("Saliendo del programa. Hasta luego!\n");
              break;
            }
          default:
            {
              break;
            }
        }
      }
    while ((opcion != 0));
    return 0;
}
