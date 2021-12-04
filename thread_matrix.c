/*
main thread crea 5 thread, condividono una variabile "totale" e un  array bidimensionale 5x5,
il main thread crea la matrice e i 5 thread fanno la somma delle 5 righe
il main thread aspetta i thread e termina.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define N 2

int totale = 0; //buffer zona critica
int matrix[N][N]; //buffer zona critica




int sommariga(void* n_rigax){ //i=n_riga
    int * address = (int *)n_rigax;
    int n_riga = *address;
    int return_value=0;
    for(int i=1;i<=N;i++){
        return_value=return_value+matrix[n_riga][i];
    }

    printf("La somma della riga %d  e'  { %d }\n ",n_riga,return_value);
    totale=totale+return_value;
    //sleep(1);
    pthread_exit(NULL);
}

int main(){
    int res;
    pthread_t thread[N]; //tid dei 5 thread
    void *thread_result[N];
    
    for(int i=1;i<=N;i++){
        for(int j=1;j<=N;j++){
            printf("\nInserire elemento %d x %d : ",i,j);
            scanf("%d",&matrix[i][j]);
        }
    }
    printf("\nMATRIX:   ");

    for(int i=1;i<=N;i++){
        printf("\n");
        for(int j=1;j<=N;j++){
            printf(" %d ",matrix[i][j]);
        }
    }
    sleep(1);
    printf("\nMain here. Creating the 5 threads\n");
    for(int i=1;i<=N;i++){
        res=pthread_create(&thread[i],NULL,sommariga,(void *)&i); //e (void *)matrix[N] se non fosse globale
        sleep(1);
        if(res!=0){
            //perror("Create [%d] failed\n",i);
            printf("Create [%d] failed\n",i);
            exit(EXIT_FAILURE);
        }else
            printf("Thread [%d] created successfully\n",i);
    }

    printf("Threads created successfully\n");
    //sleep(1);
    printf("Thread are now running...\n");
    
    /*
    
    for(int i=1;i<=N;i++){
        //res=pthread_join(thread[i],&thread_result[i]);
        res=pthread_join(thread[i],NULL);
        //res=pthread_join(thread[i],&thread_result[i]); //e (void *)matrix[N] se non fosse globale
         //DOPO IL PRIMO JOIN ESCE SEGMENTATION FAULT
        if(res!=0){
            //perror("Join [%d] failed\n",i);
            printf("Join [%d] failed\n",i);
            exit(EXIT_FAILURE);
        }//else
            //printf("Thread [%d] joined successfully\n",i);
        
        
    } */
    
    sleep(4);
    printf("La somma totale delle righe è %d\n",totale);

    printf("All thread exited successfully\n");
    
    printf("Now exiting\n");


    exit(EXIT_SUCCESS);

    

}
