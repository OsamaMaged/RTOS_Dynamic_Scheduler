

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include <stdlib.h>
/* Demo includes. */
#include "basic_io.h"
#include "time.h"
#include "stdint.h"
/* The task functions. */

int i,Ta,Tc,Tp,n;
float cpu=.0;
int times = 0;
int* P;
int* Period;
int* A;
int* C;
int* Priority;
int* Task_info;
int* kill;
int N=5;
xTaskHandle Handler1;
xTaskHandle Handler2;
xTaskHandle Handler3;
xTaskHandle Handler4;
xTaskHandle Handler5;
int latest_arrival_time=15;
int maximum_computation_time=8;
int maximum_period_multipler=17;
int maximum_kill_time=50;

static void random( int low,int high );
void delayMs(int);
void Kill_Task(int Task_Number);
void vTask1(void *pvParameters );
void vTask2(void *pvParameters );
void vTask3(void *pvParameters );
void vTask4(void *pvParameters );
void vTask5(void *pvParameters );
void schedule(void);
void priority(void);
void polling(void);
int largest(int* arr, int n);
void creating_task(int, int);
int Info(char type, int index);
void add(int v, int index);
/*-----------------------------------------------------------*/

int main( void )
{
	int k;
	int count;
	start:
	k=0;
	count = 0;
	cpu=0;
	random(2,N);
	n=i;
	Task_info = calloc(3*n, sizeof(int) );
	A = calloc(n, sizeof(int) );
	C = calloc(n, sizeof(int) );
	P = calloc(n, sizeof(int) );
	Period = calloc(n, sizeof(int) );
  Priority = calloc(n, sizeof(int) );
	kill=calloc(n,sizeof(int));
	printf("number of tasks is %d\n",n);
	for(k=0;k<3*n;k++)
	{ 
		if(k%3==0){
		printf("Task %d\n",++count);
		schedule();
		add(Ta,k);
			*(A+(k/3))=Ta;
			printf("Ta = %d\n",  *(Task_info+k) );
		add(Tc,k+1);
			*(C+(k/3))=Tc;
			printf("Tc = %d\n",  *(Task_info+k+1) );
		add(Tp,k+2);
			*(P+(k/3))=Tp;
			*(Period+(k/3))=Tp*100;
			printf("Tp = %d\n",  *(Task_info+k+2) );
			cpu=cpu+((float)Tc/(float)Tp);
			printf("%f \n",cpu);
			
			}
		}
		if(cpu>=0.7) {
			vPrintString("Failed schedulability");
			goto start;
	}
	printf("Schedulability is OK\n");
	priority();
	vTaskStartScheduler();
	//while(1);
}
/*-----------------------------------------------------------*/
void add(int v, int index)
{ 
	*(Task_info + index)=v;

}
void random(int low,int high)
{
	 i =(rand()%(high-low))+low;
}

/*-----------------------------------------------------------*/
void creating_task(int Priority, int TaskNumber)
{
		printf("%d: Task %d created\n",times,TaskNumber);
		random(Info('A',TaskNumber)+Info('C',TaskNumber)+Info('P',TaskNumber), Info('A',TaskNumber)+Info('C',TaskNumber)+Info('P',TaskNumber)+maximum_kill_time);
		*(kill+(TaskNumber-1))=i;
		printf("Task %d kill time: %d\n",TaskNumber,*(kill+(TaskNumber-1)));
		switch(TaskNumber){
		case 1:
		xTaskCreate( vTask1,"vTask1", 100, NULL, Priority,&Handler1);
		break;
		case 2:
		xTaskCreate( vTask2, "vTask2", 100, NULL, Priority,&Handler2);
		break;
		case 3:
		xTaskCreate( vTask3, "vTask3", 100, NULL, Priority,&Handler3);
		break;
		case 4:
		xTaskCreate( vTask4, "vTask4", 100, NULL, Priority,&Handler4);
		break;
		case 5:
		xTaskCreate( vTask5,"vTask5", 100, NULL, Priority,&Handler5);
		break;}
}
/*-----------------------------------------------------------*/

void vTask1(void *pvParameters){
portTickType xLastWakeTime;
xLastWakeTime = xTaskGetTickCount();
for(;;){
int comp;
printf("Task 1 starts\n");
for(comp=0;comp<*C;comp++){
polling();	
printf("%d: Task 1 running\n",times);
times++;
delayMs(100);
}
		printf("%d: Task 1 suspends\n",times);
vTaskDelayUntil( &xLastWakeTime, (*(Period+0) / portTICK_RATE_MS ) );

}

}

/*-----------------------------------------------------------*/
void vTask2(void *pvParameters ){
portTickType xLastWakeTime;
xLastWakeTime = xTaskGetTickCount();
for( ;; ){
int comp;
printf("Task 2 starts\n");
for(comp=0;comp<*(C+1);comp++){
polling();	
printf("%d: Task 2 running\n",times);
times++;
delayMs(100);
}
		printf("%d: Task 2 suspends\n",times);
vTaskDelayUntil( &xLastWakeTime, ( *(Period+1) / portTICK_RATE_MS ) );
}
}

void vTask3(void *pvParameters ){
portTickType xLastWakeTime;
xLastWakeTime = xTaskGetTickCount();
for( ;; ){
int comp;
printf("Task 3 starts\n");
for(comp=0;comp<*(C+2);comp++){
polling();	
printf("%d: Task 3 running\n",times);
times++;
delayMs(100);
}
printf("%d: Task 3 suspends\n",times);
vTaskDelayUntil( &xLastWakeTime, ( *(Period+2) / portTICK_RATE_MS ) );
}}

void vTask4(void *pvParameters ){
portTickType xLastWakeTime;
xLastWakeTime = xTaskGetTickCount();
for( ;; ){
int comp;
printf("Task 4 starts\n");
for(comp=0;comp<*(C+3);comp++){
polling();	
printf("%d: Task 4 running\n",times);
times++;
delayMs(100);
}
printf("%d: Task 4 suspends\n",times);
vTaskDelayUntil( &xLastWakeTime, ( *(Period+3) / portTICK_RATE_MS ) );
}}

void vTask5(void *pvParameters ){
portTickType xLastWakeTime;
xLastWakeTime = xTaskGetTickCount();
for( ;; ){
int comp;
printf("Task 5 starts\n");
for(comp=0;comp<*(C+5);comp++){
polling();	
printf("%d: Task 5 running\n",times);
times++;
delayMs(100);
}
printf("%d: Task 5 suspends\n",times);
vTaskDelayUntil( &xLastWakeTime, ( *(Period+4) / portTICK_RATE_MS ) );
}}
/*-----------------------------------------------------------*/
void priority(void){ 
int max,index,ind,a;
	int same_max;
	for(a = n;a >= 1; a--)
	{
	max = largest(P,n);
	
	for(ind=0;ind<n;ind++)	
		{ if(*(P+ind)== max)
		    {	index=ind; break;}
		}
	if(!(same_max==max))
		*(Priority+index)=a;
		else 	*(Priority+index)=a+1;
		
	same_max = max;
for(i=0;i<n;i++)
		if(*(P+i)==max)
   {	*(P+i)=-1;break;}
	}
}

/*-----------------------------------------------------------*/
int largest(int* arr, int n) 
{ 
    int i; 
    int max = *(arr+0);   
    for (i = 1; i < n; i++) 
     { if (*(arr+i) > max) 
         {max = *(arr+i);} }
				 
	 	
		
//vPrintStringAndNumber("",max);
    return max; 
} 
/*-----------------------------------------------------------*/
void schedule(void)
{
//generating random numbers for 
	// n tasks, Ta, Tp and Tc
	random(0,latest_arrival_time);
	Ta=i;
	random(1,maximum_computation_time);
	Tc=i;
	//safe mode
	//random(3*Tc, maximum_period_multipler*Tc);
	//no guarantee mode
	random(3*Tc,10*Tc);
	Tp=i;
}

/*-----------------------------------------------------------*/
void polling(){
int i;
for( i=0; i<n;i++){
if(times==*(A+i)){
*(A+i)=-1;
creating_task(*(Priority+i),i+1);
}
if(times==*(kill+i)&&times!=0)
{
Kill_Task(i+1);
}
}

}
void vApplicationIdleHook( void )
{
	while(1){
	polling();
	printf("%d: Idle\n",times);
	times++;
	delayMs(100);
	}
}
/*-----------------------------------------------------------*/
void delayMs(int n){
  int i, j;
  for(i = 0 ; i < 2*n; i++)
    for(j = 0; j < 1080; j++)
    {} /* do nothing for 1 ms */
		}

/*-----------------------------------------------------------*/
	void Kill_Task(int Task_Number)
{ 
printf("%d: Task %d killed\n",times,Task_Number);
random(*(kill+(Task_Number-1))+2,*(kill+(Task_Number-1))+latest_arrival_time);
*(Task_info+((Task_Number-1)*3))=i;
*(A+(Task_Number-1))=i;
switch(Task_Number){
case 1:
vTaskDelete(Handler1);break;
case 2:
vTaskDelete(Handler2);break;
case 3:
vTaskDelete(Handler3);break;
case 4:
vTaskDelete(Handler4);break;
case 5:
vTaskDelete(Handler5);break;
}
printf("Task %d new arrival time is %d\n",Task_Number,i);
}

int Info(char type, int index)
	{  index= ((index-1)*3);
			switch(type){
				case 'A':
					return *(Task_info+index);				
				case 'C':
					return *(Task_info+index+1);				
				case 'P':
					return *(Task_info+index+2);						
	}	

}