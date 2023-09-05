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
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  MPI_Comm_size (MPI_COMM_WORLD, &num);
  
  //----(3) DISTRIBUCION DEL TRABAJO----//
  if (rank == 0)
    {
        char mess[] = "Hello World";
        printf("%i sent %s\n", rank, mess);

        for (i = 1; i < num; i++)
        {
            MPI_Send(mess, strlen(mess) + 1, MPI_CHAR, i, MESSTAG, MPI_COMM_WORLD);
        }
    }
    else
    {
        char mess[MAXLEN];
        MPI_Status status;

        MPI_Recv(mess, MAXLEN, MPI_CHAR, 0, MESSTAG, MPI_COMM_WORLD, &status);
        printf("%i received %s\n", rank, mess);
    }

  //----(4) CLAUSURA DEL ENTORNO----//
  MPI_Finalize ();
  return 0;
}
