/***********************************************************************
 * Filename      : login.c
 * Author        : Xingguang wei
 * Email         : jxweixingguang@163.com
 * Create Date   : 2015-11-03
 * Last modified : 2015-11-03 22:29
 * Description   : 
 * ********************************************************************/

#include "course_check.h"

int user_login(MYSQL * mysql,USER * user)
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

	if( user->ue_flag == 1 )
		sprintf(myorder,"select password from teacher_info where ID=%s",ID);
	else
		sprintf(myorder,"select password from student_info where ID=%s",ID);

	mysql_query(mysql,myorder);
	MYSQL_RES * res = mysql_store_result(mysql);
	MYSQL_ROW row = mysql_fetch_row(res);

	int res_value = (strcmp(password,row[0]) == 0) ? 0 : 1;
	mysql_free_result(res);
	free(password);
	free(myorder);
	free(ID);

	return res_value;
}

