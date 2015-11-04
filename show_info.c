/***********************************************************************
 * Filename      : show_info.c
 * Author        : Xingguang wei
 * Email         : jxweixingguang@163.com
 * Create Date   : 2015-11-02
 * Last modified : 2015-11-02 14:50
 * Description   : 
 * ********************************************************************/

#include "course_check.h"
#include "mysql_tool.h"
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

void search_stuinfo(MYSQL * mysql)
{
	char * myorder = malloc( 200 * sizeof(char) );
	char * name = malloc( 20 * sizeof(char) ); 
	printf("please input the name you want to research: ");
	scanf("%s",name);
	sprintf(myorder,"select gender,ID,age,grade,inlab from student_info where name='%s' ",name);
	mysql_query(mysql,myorder);
	MYSQL_RES * res = mysql_store_result(mysql);
	MYSQL_ROW row = mysql_fetch_row(res);
	puts("**********************INFOMATION CARD**************************");
	printf("   NAME\t: %s\t\t\t\t GENDER\t: %c\n",name,(char)row[0][0]);
	printf("   ID\t: %s\t\t\t GRADE\t: %s\n",row[1],row[3]);
	printf("   AGE\t: %d\t\t\t\t IN_LAB\t: %c\n",atoi(row[2]),row[4][0]);
	puts("***************************************************************");
	mysql_free_result(res);
	free(name);
	free(myorder);
}

TCH * search_tchinfo(MYSQL * mysql)
{
	char * myorder = malloc( 200 * sizeof(char) );
	char * name = malloc( 20 * sizeof(char) ); 
	printf("please input the name you want to search: ");
	scanf("%s",name);
	sprintf(myorder,"select title,gender,inlab,research_area from teacher_info where name='%s' ",name);
	mysql_query(mysql,myorder);
	MYSQL_RES * res = mysql_store_result(mysql);
	MYSQL_ROW row = mysql_fetch_row(res);
	puts("**********************INFOMATION CARD**************************");
	printf("   NAME\t\t: %s\t\t\t TITLE\t: %s\n",name,row[0]);
	printf("   GENDER\t: %c\t\t\t IN_LAB\t: %c\n",row[1][0],row[2][0]);
	printf("   RESEARCH AREA: %s",row[3]);
	puts("***************************************************************");
	mysql_free_result(res);
	free(name);
	free(myorder);
}

void show_classtable(MYSQL * mysql)
{
	printf("please input the ID you want to search: ");
	char * myorder = malloc( 200 * sizeof(char) );
	char * ID = malloc( 10 * sizeof(char) );
	scanf("%s",ID);
	MYSQL_RES * res;
	MYSQL_ROW row;
	int index=0;
	char *week[5]={"monday","tuesday","wednesday","thursday","friday"};
	for(index=0;index<5;index++)
	{
		sprintf(myorder,"select class1,class2,class3 class4,class5,class6,class7,class8,class9,class10,class11 from student_class where ID='%s' and week='%s'",ID,week[index]);
		mysql_query(mysql,myorder);
		res = mysql_store_result(mysql);
		row = mysql_fetch_row(res);
		printf("[%-10s]%10s,%10s,%10s,%10s,%10s,%10s,%10s,%10s,%10s,%10s,%10s\n",
				week[index],row[0],row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8],row[9],row[10]);
	}
	mysql_free_result(res);
}
