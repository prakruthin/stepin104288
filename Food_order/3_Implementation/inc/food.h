
#ifndef __FOOD_H__
#define __FOOD_H__

#include<stdio.h>
//#include<iostream.h>
//#include<curses.h>
#include<string.h>
#include<stdlib.h>

void returnfunc(void);
void returnfunc1(void);

void mainmenu(void);

int checkid(int);

void administration(void);
void customer(void);

void addrecord(void);
void deleterecord(void);
void searchrecord(void);
void viewrecord(void);

void vegetarian(void);
void nonvegetarian(void);
void details(void);
void aboutus(void);

void Password(void);
int getdata();

void addfood(void);
int getmenudata();
int checkmenuid(int c);

void viewmenu(void);
void viewmenu1(void);
void deletefood(void);
void placeorder(void);

int add(int,int);
#endif 

