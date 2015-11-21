/***********************************************************************
 * Filename      : course-check.c
 * Author        : Xingguang wei
 * Email         : jxweixingguang@163.com
 * Create Date   : 2015-10-31
 * Last modified : 2015-10-31 18:50
 * Description   : 
 * ********************************************************************/

#include "course_check.h"
STU * stu_malloc(STU * stu);
TCH * tch_malloc(TCH * tch);

int main()
{
	int option;
	USER * user = malloc( sizeof(USER) );
	user->ue = malloc( sizeof(UE) );
	TCH * tch = malloc( sizeof(TCH) );
	STU * stu = malloc( sizeof(STU) );

	puts("0: I am a Student ");
	puts("1: I am a Teacher ");
	printf("please choose your choice: ");
	scanf("%d",&user->ue_flag);

	if ( user->ue_flag == IS_TCH )
		//FIXME warning:cast to pointer from integer of different size
		user->ue->tch = tch_malloc(tch);
	else
		user->ue->stu = stu_malloc(stu);

	MYSQL mysql;
	connect_to_mysql(&mysql,"lab_database");
	create_tables(&mysql);
  show_welcome_info();
	scanf("%d",&option);
	switch( option )
	{
		case 1:					//user regist
			user_register(&mysql,user);
			break;
		case 2:					//user login
			if ( !user_login(&mysql,user) )
			{
				puts("<<<<< Login successful! >>>>>");
				show_menu(user);
				scanf("%d",&option);
				switch ( option )
				{
					case 1:
						change_password(&mysql,user);
						break;
					case 2:
						user_sign(&mysql,user);
						break;
					case 3:
						search_userinfo(&mysql);
						break;
					case 4:
						show_inlab_user(&mysql);
						break;
					case 5:
						show_classtable(&mysql);
						break;
					case 6:
						show_signtable(&mysql);
						break;
					case 7:
						//TODO show sign time statistic
						show_signtime_statistic(&mysql);
						break;
					case 8:
						if( user->ue_flag == IS_STU )
							input_class(&mysql,user);
						else
							printf("You needn't input classtable!\n");
						break;

				}
			}
		case 3:					//exit
		default:
			exit(1);
			break;
	}
	mysql_close(&mysql);
}
