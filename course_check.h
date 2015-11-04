/***********************************************************************
 * Filename      : course_check.h
 * Author        : Xingguang wei
 * Email         : jxweixingguang@163.com
 * Create Date   : 2015-10-31
 * Last modified : 2015-11-03 23:40
 * Description   : 
 * ********************************************************************/

#include <stdlib.h>

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

