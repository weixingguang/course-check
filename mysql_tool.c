/***********************************************************************
 * Filename      : mysql_tool.c
 * Author        : Xingguang wei
 * Email         : jxweixingguang@163.com
 * Create Date   : 2015-10-29
 * Last modified : 2015-10-29 23:21
 * Description   : This file include some basic tool for the mysql
 * ********************************************************************/

/* connect to mysql database */
/* successfully returns 0, otherwist returns 1*/
int connect_to_mysql(MYSQL mysql,char * database_name)
{
	mysql_init(&mysql);
	if( NULL == (mysql_real_connect(&mysql,"localhost","wxg","123123",database_name,0,NULL,0) ) )
	{
		//connect to the database error
		printf("mysql_real_connetc error %s\n",mysql_error(&mysql));
		return 1;
	}

	return 0;
}

