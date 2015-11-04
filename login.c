/***********************************************************************
 * Filename      : login.c
 * Author        : Xingguang wei
 * Email         : jxweixingguang@163.com
 * Create Date   : 2015-11-03
 * Last modified : 2015-11-03 22:29
 * Description   : 
 * ********************************************************************/

#include "mysql_tool.h"
#include <stdio.h>
#include <stdlib.h>

int stu_login(MYSQL * mysql)
{
	char c;
	char * ID = malloc( 10 * sizeof(char) );
	char * password = malloc( 20 * sizeof(char) );
  char * myorder = malloc( 100 * sizeof(char) );

	printf("please input your ID: ");
	scanf("%s",ID);
	while( ( c=getchar() )!='\n' && c !=EOF );
	printf("please input your password: ");
	scanf("%s",password);

	sprintf(myorder,"select password,gender from student_info where ID=%s",ID);
	mysql_query(mysql,myorder);
	MYSQL_RES * res = mysql_store_result(mysql);
	MYSQL_ROW row = mysql_fetch_row(res);

	//TODO free(password)
	if ( strcmp(password,row[0]) == 0 )
	{
		mysql_free_result(res);
		free(password);
		return 0;
	}
	else
	{
		mysql_free_result(res);
		free(password);
		return 1;
	}
}

int tch_login(MYSQL * mysql)
{
	char c;
	char * ID = malloc( 10 * sizeof(char) );
	char * password = malloc( 20 * sizeof(char) );
  char * myorder = malloc(100 * sizeof(char) );

	printf("please input your ID: ");
	scanf("%s",ID);
	while( ( c=getchar() )!='\n' && c !=EOF );
	printf("please input your password: ");
	scanf("%s",password);

	sprintf(myorder,"select password ,name from teacher_info where ID=%s",ID);
	mysql_query(mysql,myorder);
	MYSQL_RES * res = mysql_store_result(mysql);
	MYSQL_ROW row = mysql_fetch_row(res);
	
	//TODO free(password)
	if ( strcmp(password,row[0]) == 0 )
		return 0;
	else
		return 1;
}
