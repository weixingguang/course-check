/***********************************************************************
 * Filename      : register.c
 * Author        : Xingguang wei
 * Email         : jxweixingguang@163.com
 * Create Date   : 2015-11-01
 * Last modified : 2015-11-02 23:29
 * Description   : 
 * ********************************************************************/

#include "mysql_tool.h"
#include "course_check.h"

void welcome_info()
{
	puts("*********************************************************");
	puts("Welcome to course check system!");
	puts("[option 1 ] A new student user, register first.");
	puts("[option 2 ] A new teacher user, register first.");
	puts("[option 3 ] A registered student, please login.");
	puts("[option 4 ] A registered teacher, please login.");
	puts("[option 5 ] EXIT.");
	puts("*********************************************************");
	printf("please input your optioon: ");
}

int stu_register(MYSQL * mysql,STU * stu)
{
	int res;
	char * mysql_order = malloc(300 *  sizeof(char) );
	sprintf(mysql_order,"insert into student_info \
			(ID,name,password,age,gender,grade,inlab) \
			values('%s',' %s', '%s', '%d', '%c', '%s', '%c')",
			stu->ID, stu->name, stu->password, stu->age, stu->gender, stu->grade, stu->inlab );
	res = mysql_query(mysql,mysql_order);
	free(mysql_order);
	if( res )
	{
		printf("insert into table student_info error %s\n",mysql_error(mysql));
		return 1;
	}

	return 0;
}

int tch_register(MYSQL * mysql,TCH * tch)
{
	int res;
	char * mysql_order = malloc(300 * sizeof(char));
	sprintf(mysql_order,"insert into teacher_info\
		 	(ID,name,password,gender,title,research_area,inlab) \
			values('%s', '%s',' %s','%c','%s','%s', '%c')",
			tch->ID, tch->name, tch->password, tch->gender, tch->title, tch->research_area, tch->inlab);
	res = mysql_query(mysql,mysql_order);
	free(mysql_order);
	if ( res )
	{
		printf("insert into table teacher_info error %s\n",mysql_error(mysql));
		return 1;
	}

	return 0;
}
