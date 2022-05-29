#ifndef __MY_FILE__

#define __MY_FILE__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define B_L 31
#define MAX_B_L 32

#define SCAN_ERROR 1

typedef struct 
{
	char brand[B_L];
	int number;
	int displacement;
	double weight;
} cars;

int get_car_by_pos(FILE *f, cars *car, int pos);
int put_car_by_pos(FILE *f, cars *car, int pos);
int file_size(FILE *f, int *size);
int delete_car(FILE *f, int pos, int size);
int file_delete_car(FILE *f);
int file_sort_by_field(FILE *f, char field[]);
int str_scan(char brand[], int n);
int car_scan(cars *car);

#endif
