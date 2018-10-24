#ifndef user_H
#define user_H
#include "stm32f1xx_hal.h"

extern long count0;
extern long count1;
extern int gap,read,sponge_count,print_cycle,last_val,dif_val;
extern long counter,start_fre,last_fre,new_fre;
//long fre_samples[256];
extern int sample_count,states;
extern uint64_t sum;
extern long frequency[20];
extern	float last_frequency ;
extern	float Base_frequency;
extern 	float step_frequency;
extern 	float new_frequency;

#define no_sponge 34050
#define dry_sponge 32100
#define semiwet_sponge 28000
#define wet_sponge  19000

#define f0	0	//base frequency
#define f1	1	//first frequency
#define f2	2	//second frequency
#define f3	3
#define f4  4
#define f5  5
#define f6  6
#define f7  7
#define f8  8
#define f9  9
#define f10 10
//extern TIM_HandleTypeDef htim2;

void graph (void);

void get_samples_value(void);

void frequency_average(void);

void display_frequency(void);

void switch_states(void);

long map(long x, long in_min, long in_max, long out_min, long out_max);


#endif
