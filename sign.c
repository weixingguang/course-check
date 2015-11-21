/***********************************************************************
 * Filename      : sign.c
 * Author        : Xingguang wei
 * Email         : jxweixingguang@163.com
 * Create Date   : 2015-11-11
 * Last modified : 2015-11-11 16:34
 * Description   : 
 * ********************************************************************/

#include "course_check.h"

void tch_sign(MYSQL * mysql, int sign_flag);
void stu_sign(MYSQL * mysql, int sign_flag);

void user_sign(MYSQL * mysql,USER * user)
{
	int sign_flag;
	puts("[ option 1 ] Sign in        [ option 2 ] Sign out");
	printf("please input your choice: ");
	scanf("%d",&sign_flag);
	if( user->ue_flag == IS_TCH )
		tch_sign(mysql,sign_flag);
	else
		stu_sign(mysql,sign_flag);
}

void tch_sign(MYSQL * mysql,int sign_flag)
{
  char * ID = malloc( 10 * sizeof(char) );
	printf("please input your ID: ");
	scanf("%s",ID);

	char * myorder = malloc( 200 * sizeof(char) );

	if ( sign_flag == SIGN_IN )
		sprintf(myorder,"update teacher_info set inlab='Y' where ID ='%s'",ID);
	else
		sprintf(myorder,"update teacher_info set inlab='N' where ID ='%s'",ID);

	mysql_query(mysql,myorder);
	MYSQL_RES * res = mysql_store_result(mysql);
	MYSQL_ROW row = mysql_fetch_row(res);
	if ( sign_flag == SIGN_IN )
		printf("Sign in successfully! Inlab %c\n",row[0][0]);
	else
		printf("Sign out successfully! Inlab %c\n",row[0][0]);
	mysql_free_result(res);

}

void stu_sign(MYSQL * mysql, int sign_flag)
{
	char * mytable = "student_timetable";
	char mytime[10] = {'\0'};

	char * myorder = malloc( 200 * sizeof(char) );
	printf("please input your ID: ");
	char * ID = malloc(10 * sizeof(char) );
	scanf("%s",ID);

	mysql_query(mysql," select time(now()) ");
	MYSQL_RES * res = mysql_store_result(mysql);
	MYSQL_ROW row = mysql_fetch_row(res);
	char hour[] = "12";
	strncpy(hour,row[0],2);
 
  char * end_op = "_in";	
	if( sign_flag == SIGN_OUT )
		end_op = "_out";	

	if( atoi(hour) < 12 )
	{
		strcat(mytime,"m");
	}
	else if( atoi(hour) > 12 && atoi(hour) < 18 )
	{
		strcat(mytime,"a");
	}
	else if( atoi(hour) > 18 )
	{
		strcat(mytime,"n");
	}

	strcat(mytime,end_op);

	sprintf(myorder,"select ID from %s where ID='%s' and date=date(now())",mytable,ID);
	mysql_query(mysql,myorder);
	res = mysql_store_result(mysql);
	if( mysql_num_rows(res) == 0 )
		sprintf(myorder,"insert into %s (ID,date,week,%s) values('%s',now(),dayname(now()),now())",mytable,mytime,ID);
	else
		sprintf(myorder,"update %s set %s=now() where ID='%s' and date=date(now())",mytable,mytime,ID);

	mysql_query(mysql,myorder);
}
