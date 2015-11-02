/***********************************************************************
 * Filename      : show_info.c
 * Author        : Xingguang wei
 * Email         : jxweixingguang@163.com
 * Create Date   : 2015-11-02
 * Last modified : 2015-11-02 14:50
 * Description   : 
 * ********************************************************************/

#include "course_check.h"
#include <stdio.h>

void show_stuinfo(STU * stu)
{
	puts("**********************INFOMATION CARD**************************");
	printf("   NAME\t: %s\t\t\t\t GENDER\t: %c\n",stu->name,stu->gender);
	printf("   ID\t: %s\t\t\t GRADE\t: %s\n",stu->ID,stu->grade);
	printf("   AGE\t: %d\t\t\t\t IN_LAB\t: %c\n",stu->age,stu->inlab);
	puts("***************************************************************");
}

void show_tchinfo(TCH * tch)
{
	puts("**********************INFOMATION CARD**************************");
	printf("   NAME\t\t: %s\t\t\t TITLE\t: %s\n",tch->name,tch->title);
	printf("   GENDER\t: %c\t\t\t IN_LAB\t: %c\n",tch->gender,tch->inlab);
	printf("   RESEARCH AREA: %s",tch->research_area);
	puts("***************************************************************");
}
