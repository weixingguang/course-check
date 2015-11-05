/***********************************************************************
 * Filename      : mysql_tool.c
 * Author        : Xingguang wei
 * Email         : jxweixingguang@163.com
 * Create Date   : 2015-10-29
 * Last modified : 2015-10-29 23:21
 * Description   : This file include some basic tool for the mysql
 * ********************************************************************/

#include "mysql_tool.h"

/* connect to mysql database */
/* successfully returns 0, otherwist returns 1*/
int connect_to_mysql(MYSQL *mysql,char * database_name)
{
	mysql_init(mysql);
	if( NULL == (mysql_real_connect(mysql,"localhost","wxg","123123",database_name,0,NULL,0) ) )
	{
		//connect to the database error
		printf("mysql_real_connetc error %s\n",mysql_error(mysql));
		return 1;
	}

	return 0;
}


/* check and create the tables*/
int create_tables(MYSQL *mysql)
{
	int nstate;
	nstate = mysql_query(mysql,
		"create table if not exists student_info(\
		ID char(10),\
		name varchar(20),\
		password varchar(20),\
		age tinyint,\
		gender enum('M','F'),\
		grade enum('zero','first','second','third'),\
		inlab enum('Y','N') )"
		);
	if ( nstate != 0)
	{
		printf("create table student_info error:%s\n",mysql_error(mysql));
		return 1;
	}
	nstate = mysql_query(mysql,
		"create table if not exists student_class(\
		ID char(10),\
		week enum('Monday','Tuesday','Wednesday','Thursday','Friday'),\
		class1 varchar(30),\
		class2 varchar(30),\
		class3 varchar(30),\
		class4 varchar(30),\
		class5 varchar(30),\
		class6 varchar(30),\
		class7 varchar(30),\
		class8 varchar(30),\
		class9 varchar(30),\
		class10 varchar(30),\
		class11 varchar(30))"
		);
	if ( nstate != 0)
	{
		printf("create table student_class error:%s\n",mysql_error(mysql));
		return 1;
	}
	nstate = mysql_query(mysql,
		"create table if not exists student_timetable(\
		ID char(10),\
		date date,\
		week enum('Monday','Tuesday','Wednesday','Thursday','Friday','Saturday','Sunday'),\
		m_in time,\
	  m_out time,\
	  a_in time,\
	  a_out time,\
	  n_in  time,\
		n_out time)"
		);
	if ( nstate != 0)
	{
		printf("create table student_timetable error:%s\n",mysql_error(mysql));
		return 1;
	}

	nstate = mysql_query(mysql,
		"create table if not exists teacher_info(\
		ID char(10),\
		name varchar(20),\
		password varchar(20),\
		gender enum('M','F'),\
		title varchar(20),\
		research_area varchar(50),\
		inlab enum('Y','N'))"\
		);
	if ( nstate != 0)
	{
		printf("create table teacher_info error:%s\n",mysql_error(mysql));
		return 1;
	}

}

