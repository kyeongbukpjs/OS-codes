#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

void * alpha(void * arg);
void * space(void * arg);
void * marks(void * arg);

static sem_t sem_one;
static sem_t sem_two;
static sem_t sem_three;



int main(){
	pthread_t id_a, id_s, id_m;

	sem_init(&sem_one, 0, 0);
	sem_init(&sem_two, 0 ,0);
	sem_init(&sem_three, 0 ,1);
		
	pthread_create(&id_a, NULL, alpha, NULL);
		
	pthread_create(&id_s, NULL, space, NULL);
		

	pthread_create(&id_m, NULL, marks, NULL);

	pthread_join(id_a, NULL);
	pthread_join(id_s, NULL);
	pthread_join(id_m, NULL);

	sem_destroy(&sem_one);
	sem_destroy(&sem_two);
	sem_destroy(&sem_three);
	printf("\n");
	return 0;
}

void * alpha(void * arg){
	char _alpha[] = "Heywatchit";
	int i;

	for(i=0;i<strlen(_alpha);i++){
		
		sem_wait(&sem_one);
		printf("%c",_alpha[i]);
		if(i==2) sem_post(&sem_three);
		else if(i==7) sem_post(&sem_two);
		else if(i==9)sem_post(&sem_three);
		else sem_post(&sem_one);
	}
	return NULL;
}
void * space(void * arg){
	int i;
	for(i=0;i<2;i++){
	sem_wait(&sem_two);
	printf(" ");
	
	sem_post(&sem_one);
	}
	return NULL;
}
void * marks(void * arg){
	char _marks[] = "\",!\"";
	int i;

	for(i=0;i<strlen(_marks);i++){
	
		sem_wait(&sem_three);
		printf("%c",_marks[i]);
		if(i==0)sem_post(&sem_one);
		else if(i==1)sem_post(&sem_two);
		else sem_post(&sem_three);

	}
	return NULL;
}