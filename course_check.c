/***********************************************************************
 * Filename      : course-check.c
 * Author        : Xingguang wei
 * Email         : jxweixingguang@163.com
 * Create Date   : 2015-10-31
 * Last modified : 2015-10-31 18:50
 * Description   : 
 * ********************************************************************/

#include "mysql_tool.h"

int main()
{
	MYSQL mysql;
	connect_to_mysql(&mysql,"lab_database");
	create_tables(&mysql);
	mysql_close(&mysql);
}
