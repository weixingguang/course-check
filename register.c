/***********************************************************************
 * Filename      : register.c
 * Author        : Xingguang wei
 * Email         : jxweixingguang@163.com
 * Create Date   : 2015-11-01
 * Last modified : 2015-11-02 23:29
 * Description   : 
 * ********************************************************************/

#include "course_check.h"

int user_register(MYSQL * mysql, USER * user)
{
	input_userinfo(user);

	int res;
	char * mysql_order = malloc(300 *  sizeof(char) );
	if ( user->ue_flag == 1 )
	sprintf(mysql_order,"insert into teacher_info\
		 	(ID,name,password,gender,title,research_area,inlab) \
			values('%s', '%s','%s','%c','%s','%s', '%c')",
			user->ue->tch->ID, user->ue->tch->name, user->ue->tch->password, user->ue->tch->gender, user->ue->tch->title, user->ue->tch->research_area, user->ue->tch->inlab);
	else
	sprintf(mysql_order,"insert into student_info \
			(ID,name,password,age,gender,grade,inlab) \
			values('%s','%s', '%s', '%d', '%c', '%s', '%c')",
			user->ue->stu->ID, user->ue->stu->name, user->ue->stu->password, user->ue->stu->age, user->ue->stu->gender, user->ue->stu->grade, user->ue->stu->inlab );

	res = mysql_query(mysql,mysql_order);
	free(mysql_order);
	if( res )
	{
		printf("insert into table student_info error %s\n",mysql_error(mysql));
		return 1;
	}

	show_user_info(user);

	return 0;
}
