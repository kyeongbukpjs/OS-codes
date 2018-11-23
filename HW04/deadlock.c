#include <stdio.h>
#include <pthread.h>
pthread_mutex_t land, homi;
int goguma = 0;
int gamja = 0;

void *grandmother(){

	pthread_mutex_lock(&land);
	printf(" -> 할머니가 고구마를 심으려고 하신다.\n");
	
	printf("할머니 : 고구마를 심기 위해선 호미가 필요해!\n");
	pthread_mutex_lock(&homi); 
	printf("할머니 : 고구마를 마저 심기 위해선 텃밭을 써야해!\n");
	pthread_mutex_unlock(&homi);
	goguma +=1;
	printf(" -> 할머니가 고구마를 수확하셨습니다.\n\n");

	pthread_mutex_unlock(&land);

	pthread_exit(NULL);
}

void *grandfather(){

	pthread_mutex_lock(&homi);

	printf(" -> 할아버지가 감자를 심으려고 하신다.\n");

	printf("할아버지 : 감자를 심기 위해서는 텃밭을 써야해!\n");
	pthread_mutex_lock(&land); 
	printf("할아버지 : 감자를 마저 심기 위해선 호미가 필요해!\n");
	pthread_mutex_unlock(&land);
	gamja += 1;
	printf(" -> 할아버지가 감자를 수확하셨습니다.\n\n");

	pthread_mutex_unlock(&homi);

	pthread_exit(NULL);
}

int main() {
	int i;
	printf("시골에 할머니 할아버지가 살고 계십니다. \n\n집 앞마당에 작은 텃밭이 있는데,\n\n할머니는 고구마를 키우고 싶어하십니다.\n\n할아버지는 감자를 키우고 싶어하십니다.\n\n 작물을 수확하기위해서는 텃밭과 호미가 필요합니다.\n\n각각 하나씩 밖에 갖고 있지 않습니다. \n\n 고집이 센 할아버지 할머니는 서로 호미와 텃밭을 갖고 \n\n양보하지 않아 Deadlock이 걸립니다.\n\n###############################################\n\n\n");

	pthread_mutex_init(&land,NULL);
	pthread_mutex_init(&homi,NULL);

	pthread_t t1[10000];
	pthread_t t2[10000];

	for(i=0; i<10000; i++){
		pthread_create(&t1[i],NULL,grandmother,NULL);
		pthread_create(&t2[i],NULL,grandfather,NULL);
	
		pthread_join(t1[i],NULL);
		pthread_join(t2[i],NULL);
		printf("%d 개의 고구마\n",goguma);
		printf("%d 개의 감자\n\n\n",gamja);

	}

	

	return 0;
}