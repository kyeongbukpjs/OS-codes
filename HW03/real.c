#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
int length = 10000;
int data[10000];
int k = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct{
	int l;
	int r;
}LR;

LR lr[1000000];
pthread_t id[1000000];
void test(){for(int i = 0; i < length-1; ++i)if(data[i]>data[i+1])printf("err, %d\n",i);else printf("0");}
void initialize_array(){
	for(int i = 0; i < length; ++i) data[i] = rand() % 300 + 1;}

void *quick_sort( void * a){
	LR * tmp = (LR*) a;


	int left = tmp->l;
	int right = tmp->r;
	int pivot = data[(tmp->l+tmp->r)/2];

	do{
		while(data[left] < pivot) left++;
            while(data[right] > pivot) right--;
            if(left <= right){    
            
                int temp = data[left];
                data[left] = data[right];
                data[right] = temp;
               
                left++;
                right--;
		}
	}while(left <= right);       
        if(tmp->l < right) {pthread_mutex_lock( &mutex );
         k +=1;
         lr[k].l = tmp->l; 
         lr[k].r = right;pthread_mutex_unlock( &mutex );
         pthread_create(&id[k], NULL, quick_sort, (void*)&lr[k]);}

        if(tmp->r > left) {pthread_mutex_lock( &mutex );
         k +=1;
         lr[k].l = left; 
         lr[k].r = tmp->r;pthread_mutex_unlock( &mutex );
         pthread_create(&id[k], NULL, quick_sort, (void*)&lr[k]);}
}
void print_array(){
	for(int i = 0; i < length; ++i)printf("%d  ",data[i]);}

void main(){
	initialize_array();
	print_array();
	lr[0].l = 0;
	lr[0].r = length-1;
	pthread_create(&id[k], NULL, quick_sort, (void*)&lr[0]);
	
	for(int i=0; i<=k; i++){
		pthread_join(id[i], NULL);
	}
	printf("\n\n");
	print_array();
	test();

}
	
