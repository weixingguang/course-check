/***********************************************************************
 * Filename      : course-check.c
 * Author        : Xingguang wei
 * Email         : jxweixingguang@163.com
 * Create Date   : 2015-10-31
 * Last modified : 2015-10-31 18:50
 * Description   : 
 * ********************************************************************/

#include "mysql_tool.h"
#include "course_check.h"

STU * stu_malloc()
{
	STU * stu     = malloc(sizeof(STU));
	stu->ID       = malloc(10 * sizeof(char));
	stu->name     = malloc(20 * sizeof(char));
	stu->password = malloc(20 * sizeof(char));
	stu->age      = 20;
	stu->gender   = 'M';
	stu->grade    = malloc(6 * sizeof(char));
	stu->inlab    = 'Y';

	return stu;
}

TCH * tch_malloc()
{
	TCH * tch = malloc(sizeof(TCH));
	tch->ID            = malloc(10 * sizeof(char));
	tch->name          = malloc(20 * sizeof(char));
	tch->password      = malloc(20 * sizeof(char));
	tch->gender        = 'M';
	tch->title         = malloc(20 * sizeof(char));
	tch->research_area = malloc(50 * sizeof(char));
	tch->inlab         = 'N';

	return tch;
}

int main()
{
	int option;
	MYSQL mysql;
	connect_to_mysql(&mysql,"lab_database");
	create_tables(&mysql);
  welcome_info();
	scanf("%d",&option);
	switch( option )
	{
		case 1:					//student register
			{
				STU * stu	= stu_malloc();
				stuinfo_check(stu);
				stu_register(&mysql,stu);
				show_stuinfo(stu);
			}
			break;
		case 2:					//teacher register
			{
				TCH * tch = tch_malloc();
				tchinfo_check(tch);
				tch_register(&mysql,tch);
				show_tchinfo(tch);
			}
			break;
		case 3:					//student login
			break;
		case 4:					//teacher login
			break;
		case 5:					//exit
		default:
			exit(1);
			break;
	}
	mysql_close(&mysql);
}
