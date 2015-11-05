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
			values('%s','%s', '%s', '%d', '%c', '%s', '%c')",
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
			values('%s', '%s','%s','%c','%s','%s', '%c')",
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

void input_class(MYSQL * mysql,char * ID)
{
	char * class[11];
	int index;
	for(index=0;index<11;index++)
		class[index]= malloc( 30 * sizeof(char));

	char * myorder = malloc(500 * sizeof(char) );
	printf("please input your class by class1[8:00-9:00],class2[9:00-10:00].....class11[8:30-9:30].\n");
	printf("if you don't have class on that time, please input NULL\n");

	char *week[5]={"Monday","Tuesday","Wednesday","Thursday","Friday"};
	for(index=0;index<5;index++)
	{
		printf("please input your class on [%s] like math english physical : ",week[index]);

		scanf("%s%s%s%s%s%s%s%s%s%s%s",class[0],class[1],class[2],class[3],class[4],class[5],
				class[6],class[7],class[8],class[9],class[10]);
		sprintf(myorder,"insert into student_class \
				(ID,week,class1,class2,class3,class4,class5,class6,class7,class8,class9,class10,class11)\
				values('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s')",
				ID,week[index],class[0],class[1],class[2],class[3],class[4],class[5],class[6],class[7],class[8],class[9],class[10]);
		mysql_query(mysql,myorder);
	}
}

void tch_signin(MYSQL * mysql)
{
	char * myorder = malloc( 200 * sizeof(char) );
	printf("please input your ID: ");
  char * ID = malloc( 10 * sizeof(char) );
	scanf("%s",ID);
	sprintf(myorder,"select inlab from teacher_info where ID='%s'",ID);
	mysql_query(mysql,myorder);
	MYSQL_RES * res = mysql_store_result(mysql);
	MYSQL_ROW row = mysql_fetch_row(res);
	printf("inlab %c\n",row[0][0]);
	sprintf(myorder,"update teacher_info set inlab='Y' where ID ='%s'",ID);
	mysql_free_result(res);
	mysql_query(mysql,myorder);
	sprintf(myorder,"select inlab from teacher_info where ID='%s'",ID);
	mysql_query(mysql,myorder);
	res = mysql_store_result(mysql);
	row = mysql_fetch_row(res);
	printf("inlab %c\n",row[0][0]);

}

void tch_signout(MYSQL * mysql)
{
	char * myorder = malloc( 200 * sizeof(char) );
	printf("please input your ID: ");
  char * ID = malloc( 10 * sizeof(char) );
	scanf("%s",ID);
	sprintf(myorder,"select inlab from teacher_info where ID='%s'",ID);
	mysql_query(mysql,myorder);
	MYSQL_RES * res = mysql_store_result(mysql);
	MYSQL_ROW row = mysql_fetch_row(res);
	printf("inlab %c\n",row[0][0]);
	sprintf(myorder,"update teacher_info set inlab='N' where ID ='%s'",ID);
	mysql_free_result(res);
	mysql_query(mysql,myorder);
	sprintf(myorder,"select inlab from teacher_info where ID='%s'",ID);
	mysql_query(mysql,myorder);
	res = mysql_store_result(mysql);
	row = mysql_fetch_row(res);
	printf("inlab %c\n",row[0][0]);
}

void stu_signin(MYSQL * mysql)
{
	char * myorder = malloc( 200 * sizeof(char) );
	printf("please input your ID: ");
	char * ID = malloc(10 * sizeof(char) );
	scanf("%s",ID);
	mysql_query(mysql,"select time(now()) < '12:00:00' ");
	MYSQL_RES * res = mysql_store_result(mysql);
	MYSQL_ROW row = mysql_fetch_row(res);
	if( row[0][0] == '1' )
	{
		sprintf(myorder,"select ID from student_timetable where ID='%s' and date=date(now())",ID);
		mysql_query(mysql,myorder);
		res = mysql_store_result(mysql);
		if( mysql_num_rows(res) == 0 )
			sprintf(myorder,"insert into student_timetable (ID,date,week,m_in) values('%s',now(),dayname(now()),now())",ID);
		else
			sprintf(myorder,"update student_timetable set m_in=now() where ID='%s' and date=date(now())",ID);
	}
	mysql_query(mysql,"select time(now()) > '12:00:00' and time(now()) < '18:00:00' ");
	res = mysql_store_result(mysql);
	row = mysql_fetch_row(res);
	if( row[0][0] == '1' )
	{
		sprintf(myorder,"select ID from student_timetable where ID='%s' and date=date(now())",ID);
		mysql_query(mysql,myorder);
		res = mysql_store_result(mysql);
		if( mysql_num_rows(res) == 0 )
			sprintf(myorder,"insert into student_timetable (ID,date,week,a_in) values('%s',now(),dayname(now()),now())",ID);
		else
			sprintf(myorder,"update student_timetable set a_in=now() where ID='%s' and date=date(now())",ID);
	}

	mysql_query(mysql,"select time(now()) > '18:00:00' ");
	res = mysql_store_result(mysql);
	row = mysql_fetch_row(res);
	if( row[0][0] == '1' )
	{
		sprintf(myorder,"select ID from student_timetable where ID='%s' and date=date(now())",ID);
		mysql_query(mysql,myorder);
		res = mysql_store_result(mysql);
		if( mysql_num_rows(res) == 0 )
			sprintf(myorder,"insert into student_timetable (ID,date,week,n_in) values('%s',now(),dayname(now()),now())",ID);
		else
			sprintf(myorder,"update student_timetable set n_in=now() where ID='%s' and date=date(now())",ID);
	}

	mysql_query(mysql,myorder);
}

void stu_signout(MYSQL * mysql)
{
	char * myorder = malloc( 200 * sizeof(char) );
	printf("please input your ID: ");
	char * ID = malloc(10 * sizeof(char) );
	scanf("%s",ID);
	mysql_query(mysql,"select time(now()) < '12:00:00' ");
	MYSQL_RES * res = mysql_store_result(mysql);
	MYSQL_ROW row = mysql_fetch_row(res);
	if( row[0][0] == '1' )
	{
		sprintf(myorder,"select ID from student_timetable where ID='%s' and date=date(now())",ID);
		mysql_query(mysql,myorder);
		res = mysql_store_result(mysql);
		if( mysql_num_rows(res) == 0 )
			sprintf(myorder,"insert into student_timetable (ID,date,week,m_out) values('%s',now(),dayname(now()),now())",ID);
		else
			sprintf(myorder,"update student_timetable set m_out=now() where ID='%s' and date=date(now())",ID);
	}
	mysql_query(mysql,"select time(now()) > '12:00:00' and time(now()) < '18:00:00' ");
	res = mysql_store_result(mysql);
	row = mysql_fetch_row(res);
	if( row[0][0] == '1' )
	{
		sprintf(myorder,"select ID from student_timetable where ID='%s' and date=date(now())",ID);
		mysql_query(mysql,myorder);
		res = mysql_store_result(mysql);
		if( mysql_num_rows(res) == 0 )
			sprintf(myorder,"insert into student_timetable (ID,date,week,a_out) values('%s',now(),dayname(now()),now())",ID);
		else
			sprintf(myorder,"update student_timetable set a_out=now() where ID='%s' and date=date(now())",ID);
	}

	mysql_query(mysql,"select time(now()) > '18:00:00' ");
	res = mysql_store_result(mysql);
	row = mysql_fetch_row(res);
	if( row[0][0] == '1' )
	{
		sprintf(myorder,"select ID from student_timetable where ID='%s' and date=date(now())",ID);
		mysql_query(mysql,myorder);
		res = mysql_store_result(mysql);
		if( mysql_num_rows(res) == 0 )
			sprintf(myorder,"insert into student_timetable (ID,date,week,n_out) values('%s',now(),dayname(now()),now())",ID);
		else
			sprintf(myorder,"update student_timetable set n_out=now() where ID='%s' and date=date(now())",ID);
	}

	mysql_query(mysql,myorder);
}
