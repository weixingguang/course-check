/***********************************************************************
 * Filename      : course_check.h
 * Author        : Xingguang wei
 * Email         : jxweixingguang@163.com
 * Create Date   : 2015-10-31
 * Last modified : 2015-11-03 23:40
 * Description   : 
 * ********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define IS_TCH 1
#define IS_STU 0

#define SIGN_IN 1
#define SIGN_OUT 0

typedef struct Student{
	char * ID;
	char * name;
	char * password;
	int age;
	char gender;
	char * grade;
	char inlab;
} STU;


typedef struct Teacher{
	char * ID;
	char * name;
	char * password;
	char gender;
	char * title;
	char * research_area;
	char inlab;
} TCH;

typedef union Ue
{
	STU * stu;
	TCH * tch;
} UE;

typedef struct User{
	UE * ue;
	int ue_flag;
} USER;
