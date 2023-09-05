/*
 ============================================================================
 Author        : G. Barlas
 Version       : 1.0
 Last modified : December 2014
 License       : Released under the GNU GPL 3.0
 Description   : 
 To build use  : mpicc mpiHello.c -o mpiHello
 ============================================================================
 */
#include<mpi.h>     //bibloteca básica para MPI
#include<string.h>
#include<stdio.h>
#define MESSTAG 0
#define MAXLEN 100
int
main (int argc, char **argv)
{
  //----(1) INICIO DEL ENTORNO----//
  MPI_Init (&argc, &argv);

  //----(2) CAPTURA DE DATOS DEL COMUNICADOR----//
  int rank, num, i;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &num);
  
  //----(3) DISTRIBUCION DEL TRABAJO----//
  if (rank %2 == 0)
    {
        char mess[] = "Hello World";
        int dest_rank = (rank + 1) % num; 
        printf("%d sent to %d: %s\n", rank, dest_rank, mess);

        MPI_Send(mess, strlen(mess) + 1, MPI_CHAR, dest_rank, MESSTAG, MPI_COMM_WORLD);
    }
    else
    {
        char mess[MAXLEN];
        MPI_Status status;
        int source_rank = (rank - 1 + num) % num; 

        MPI_Recv(mess, MAXLEN, MPI_CHAR, source_rank, MESSTAG, MPI_COMM_WORLD, &status);
        printf("%d received from %d: %s\n", rank, source_rank, mess);
    }
 
  //Esperar que se sincronicen los procesos
  MPI_Barrier(MPI_COMM_WORLD);

  //----(4) CLAUSURA DEL ENTORNO----//
  MPI_Finalize ();
  return 0;
}
