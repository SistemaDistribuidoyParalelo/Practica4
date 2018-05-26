/*#include "mpi.h"
int main( int argc, char *argv[]){
    char message[20];
    int myrank;
    MPI_Status status;
    MPI_Init ( &argc, &argv );
    MPI_Comm_rank( MPI_COMM_WORLD, &myrank );
    if (myrank == 0) { 
      // code for process zero 
      strcpy(message,"Hello, there");
      MPI_Send(message, strlen(message)+1, MPI_CHAR, 1, 99, MPI_COMM_WORLD);
      }else if (myrank == 1){ 
      // code for process one 
      MPI_Recv(message, 20, MPI_CHAR, 0, 99, MPI_COMM_WORLD, &status);
      printf("received :%s:\n", message);
      }
      MPI_Finalize();
     return 0;
}
*/

#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	int *receive_vector;
	//int receive_vector[2];
	int i;	
	MPI_Status status;
	int vector[4]={1,2,3,4};
  int sendVector[4], *rbuf;
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int id;
    MPI_Comm_rank(MPI_COMM_WORLD, &id);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);
	
	receive_vector = (int*)malloc(sizeof(int)*2); 

	MPI_Scatter(vector, 2, MPI_INT, receive_vector, 2, MPI_INT, 0, MPI_COMM_WORLD);
	for(i=0;i<2;i++){
			printf("Procesador %s, id %d -- receive_vector[%d]: %d\n", processor_name, id, i, receive_vector[i]);	
      receive_vector[i]++;   
      }
  MPI_Gather(receive_vector,2,MPI_INT,vector,2,MPI_INT,0,MPI_COMM_WORLD); 
  //MPI_Gather(vector,4,MPI_INT, rbuf,100,MPI_INT,root, comm); el root corresponde al hilo 0
 	for(i=0;i<4;i++){
		printf("receive_vector[%d]: %d\n",i, vector[i]);	
    receive_vector[i]++;   
  }

  
    // Finalize the MPI environment.
    MPI_Finalize();
}
