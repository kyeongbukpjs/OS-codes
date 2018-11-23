#include <stdio.h>
#include <stdlib.h>


typedef struct node {
	void * data_ptr; // access data using pointer
	struct node* next; // node should be point another node or NULL
} NODE; 

typedef struct {
	int count;// LLIST should have counter to check whether error has occured, or to check if LLIST is empty
	NODE* front;
	NODE* rear;
	NODE* pos; // use position to add or delete node by index

} LLIST;

LLIST* create_list();
bool add_node_at(LLIST* list, unsigned int index, void* data);
bool del_node_at(LLIST* list, unsigned int index);
 

LLIST* create_list(
	){
	LLIST* list = (LLIST*)malloc(sizeof(LLIST));
	if(list){
		list->front=NULL;
		list->rear=NULL;
		list->pos=NULL;
		list->count = 0; // because created list is empty
	}
return list;
}

bool add_node_at(
	LLIST* list, unsigned int index, void* data) {
	if(index>(list->count))
		return false; // index out of range
	NODE* new_p;
	new_p=(NODE*)malloc(sizeof(NODE));
	if(!new_p) return false; // malloc failed
	new_p->data_ptr=data;
	new_p->next=NULL;
	if(list->count==0){ // when the data is inserted to the empty list 
		list->front=new_p;
		list->rear=new_p;
		(list->count)++;
		return true;
	}
	int iter_i=0;
	if(index==0){ // when the data is inserted to the front
		new_p->next=list->front;
		list->front=new_p;
		(list->count)++;
		return true;
	}
	iter_i++;
	list->pos=list->front;
	while(iter_i!=index){
		list->pos=list->pos->next;
		iter_i++;
	}
	if(iter_i==list->count){
		list->pos->next=new_p;
		list->rear=new_p;
		(list->count)++;
		return true;
	}
	else{
		new_p->next=list->pos->next;
		list->pos->next=new_p;
		(list->count)++;
		return true;
	}
}


bool del_node_at(LLIST* list, unsigned int index)
{
	if(list->count==0)
		return false;
	else if(index>=list->count)
		return false;
	if(list->count==1){
		free(list->front);
		list->front=NULL;
		list->rear=NULL;
		list->count=0;
		return true;
	}
	int iter_i=0;
	list->pos=list->front;
	NODE* pre=NULL;
	while(iter_i!=index){
		pre=list->pos;
		list->pos=list->pos->next;
		iter_i++;
	}
	if(index==0){
		list->front=list->pos->next;
		free(list->pos);
		list->pos=NULL;
		(list->count)--;
		return true;
	}
	if(index==(list->count-1)){
		list->rear=pre;
		pre->next=NULL;
		free(list->pos);
		list->pos=NULL;
		(list->count)--;
		return true;
	}
	else{
		pre->next=list->pos->next;
		free(list->pos);
		list->pos=NULL;
		(list->count)--;
		return true;
	}return false;
}

// main start
int main(int argc, char* argv[]){
	int ducks = atoi(argv[1]); // convert argv[1](string) to int type
	if (argc != 2)
		//when the number of argument of main function is not 2
		return printf("The number of command line arguments is wrong "); 
	else{
		if (ducks<=0)
			return printf("The number of ducks should be bigger than zero"); 
		else{

			LLIST* fishing_rod = create_list(); // create empty list

			//start catching ducks from here

			int data_space[ducks]; // I've created array to assign different ducks using pointer

			printf("start fishing!\n");
			for(int i = 1;i <= ducks; i ++){
				data_space[i-1] = i;
		
				if(add_node_at(fishing_rod, i-1,&data_space[i-1]))// because add_node_at function returns boolean value
					printf("Duck %d has caught!\n", i); 

			}
			
			//print caught ducks
		
			fishing_rod->pos=fishing_rod->front;
			int iter = 0;
			while(fishing_rod->pos != NULL){// before the pos becomes NULL, print caugt ducks 
				
				printf("Duck %d", *(int*)fishing_rod->pos->data_ptr);
				fishing_rod->pos=fishing_rod->pos->next;
				if(fishing_rod->pos != NULL)// before the pos becomes NULL, print arrow(-->)
					printf(" --> ");
				iter++;
			}
			printf("\nfree the caught ducks!!\n"); //freeing ducks
				
			for(int i = ducks-1;i >=0; i --){
				if(del_node_at(fishing_rod,i)) // possible because delete function returns boolean type
					printf("Duck %d has freed!!\n",i+1);
			}
		
			


		}


	}


}