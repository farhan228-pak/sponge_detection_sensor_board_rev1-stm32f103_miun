#include "user.h"
#include "stm32f1xx_hal.h"
#include "stdio.h"
#include "stdlib.h"
//#include "gpio.h" 
#include "tim.h"
#include "VT100.h"
long count0=0;
long count1=0;
int gap=0,read=0,sponge_count=0;
long counter=0,start_fre=0,last_fre=1,new_fre=0;
//long fre_samples[256];
int sample_count=0,states=0,print_cycle=0,last_val=0,dif_val=0;
uint64_t sum=0;
long frequency[20];

float last_frequency=0 ;
float Base_frequency=0;
float step_frequency=0;
float new_frequency=0;



//TIM_HandleTypeDef htim2;
void graph (void)
{
	printf (CLS);
	printf (HOME);
	GOTOXY(10,20);
	printf ("Wet Spong-");
		GOTOXY(15,15);
	printf ("Semi-wet Spong-");
	GOTOXY(20,20);
	printf ("Dry Spong-");
		GOTOXY(25,20);
	printf (" No Spong-");
	
	GOTOXY(10,30);

	for(int i=0; i<=21;i++)
	{
	printf ("|");
	GOTOXY(10+i,30);	
		HAL_Delay(10);
	}
	
	for(int i=0; i<=40;i++)
	{
	
		GOTOXY(30,31+i);
		printf ("_");
		
		HAL_Delay(10);
	}
	
	
	
	HAL_Delay(1000);
}

void GOTOXY(int x, int y)
{
	
	printf ("\033[");
  printf ("%i;",x);
printf ("%i",y);
//printf ("%i;",x);	
printf ("H");	
}

void Mov_CUB(int x)
{
	
	printf ("\033[");
  printf ("%i",x);
	
printf ("D");	
}


void get_samples_value(void)
{

if(read==1 && sample_count<=16384)
{
	HAL_TIM_Base_Stop(&htim2);
		sum=sum+counter;
		sample_count++;	
	read=0;
	gap = 0;
	HAL_TIM_Base_Start(&htim2);
}
	
}

void frequency_average(void)
{
	if(sample_count>=16384)
{
	//HAL_TIM_Base_Stop(&htim2);
	sum= sum>>14;
	frequency[f0]=sum; 
//	HAL_TIM_Base_Start(&htim2);
}

}

	void display_frequency(void)
{
if(sample_count>=16384)
{
	HAL_TIM_Base_Stop(&htim2);

	start_fre =frequency[f0];
	new_fre = frequency[f0+sponge_count];
	Base_frequency = (32000000/start_fre);//recorded at the start with 16384 samples	

	last_frequency = (32000000/last_fre);
	
	new_frequency  = (32000000/new_fre);
	
	step_frequency = abs (new_frequency - last_frequency);// diffrence between two frequinces
if(step_frequency>50 || sponge_count==0)
{
	printf("\n\rstart_freq f0=%3.2f  ",Base_frequency);
	printf("Sponge_count=%i ",sponge_count);
	printf("NEW_freq f%i=%3.2f  ",sponge_count , new_frequency);
	printf("last_freq=%3.2f  ",last_frequency);
	printf("Diffrence=%3.2f  ",step_frequency);
	printf("NEW_freq =%3.2f  ", new_frequency);
	if(sponge_count==10)
		sponge_count =0;
	sponge_count++;
}
else{
	Mov_CUB(20);
	printf (CLR_Line);
	printf("NEW_freq =%3.2f  ", new_frequency);
}
//printf("new\n\r");
	HAL_Delay (1);
	last_fre =new_fre ;
	sum =0;
	read=0;
	gap = 0;
	sample_count=0;
	print_cycle=1;// used to break continous loop in main code untill one line is printed
	HAL_TIM_Base_Start(&htim2);

}
		
	}

	
	void switch_states(void)
	{
		switch(states)
		{
			case 0:
							get_samples_value(); //take 16384 samples
							if(sample_count>=16384)
							{
							states=1;
							
							}
			break;
			
			case 1:
							frequency_average();
								sample_count=0;
								read=0;
								gap=0;
							states = 2;
			break;
			
			case 2:
							
			
						get_samples_value(); //take 16384 samples
						 if(sample_count>=16384)
							{
							//HAL_TIM_Base_Stop(&htim2);
							sum= sum>>14;
							frequency[f0+sponge_count]=sum; 
							//	HAL_TIM_Base_Start(&htim2);
							}
							states =3;
			case 3:
						display_frequency();
					
					states =2;
			break;
				
			default :
				break;
			
		}
	}
	
	long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}	
	
	
	
	

