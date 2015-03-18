#include <stdlib.h> 
#include <stdio.h> 
#include <pthread.h>
#include <time.h>
#include <unistd.h>


int cpu_count;
int precision;

pthread_mutex_t can_print;

int global_enable_print=1;

int a2i(const char *s) {
int sign=1;
if (*s == '-') {
sign=-1;
s++;
}
int num=0;
while(*s){
num=((*s) - '0') + num * 10;
s++;
}
return num*sign;
}

void *caculate_pi(void *dummy) {
	int enable_print=0;
	pthread_mutex_lock(&can_print);
	if (global_enable_print == 1) {
		global_enable_print=0;
		enable_print=1;
	}
	pthread_mutex_unlock(&can_print);
	//printf("enabled %d\n", enable_print);
	int a=10000,b=0,c=precision*7/2,d=0,e=0,g=0; 
	int *f = (int*)calloc(precision * 7 / 2 + 1, sizeof(int));
	if (f == NULL) {
		printf("can alloc memory\n");
		return;
	}
	for(;b-c;) {
		f[b++]=a/5; 
	}
	for(;d=0,g=c*2;c-=14) {
		for(b=c;d+=f[b]*a,f[b]=d%--g,d/=g--,--b;d*=b);
		if (enable_print == 1) {
			printf("%.4d",e+d/a);
			fflush(stdout);
		}
		e=d%a;
	}
	free(f);
	return 0;
}


int main(int argc, char *argv[]) 
{   
if (argc < 2) {
//printf("usage %s precision\n eg: %s 2000\n", argv[0], argv[0]);
precision=20;
} else {
char* argv1=argv[1];
precision=a2i(argv1);
}
cpu_count = sysconf(_SC_NPROCESSORS_ONLN);
int i;
clock_t t_start=clock();
printf("simple PI caculator, precision %d, using %d threads\n", precision, cpu_count);
pthread_t *tid=malloc(cpu_count * sizeof(pthread_t));
for (i=0; i<cpu_count; i++) {
pthread_create(&tid[i], NULL, caculate_pi, NULL);
}
for (i=0; i<cpu_count; i++) {
pthread_join(tid[i], NULL);
}
clock_t t_end=clock();
printf("\n");
printf("Elapsed: %f seconds\n", (double)(t_end-t_start) / CLOCKS_PER_SEC);
return 0;
} 
