/***********************************************************************
 * Filename      : show_info.c
 * Author        : Xingguang wei
 * Email         : jxweixingguang@163.com
 * Create Date   : 2015-11-02
 * Last modified : 2015-11-02 14:50
 * Description   : 
 * ********************************************************************/

#include "course_check.h"

void show_welcome_info()
{
	puts("***************************************************************************");
	puts("Welcome to course check system!");
	puts("[option 1 ] A new user, Regist first.");
	puts("[option 2 ] A registered user, Login please.");
	puts("[option 3 ] EXIT.");
	puts("***************************************************************************");
	printf("please input your optioon: ");
}

void show_menu(USER * user)
{
	puts("***************************************************************************");
	puts("[option 1 ] Change password            [option 2 ] Sign in/out");
	puts("[option 3 ] Show user info             [option 4 ] Show inlab user");
	puts("[option 5 ] Show student classtable    [option 6 ] Show sign time table ");
	puts("[option 7 ] Show sign statistic");
	if ( user->ue_flag == IS_STU )
	{
	puts("[option 8 ] Input student classtable");
	}
	puts("***************************************************************************");
}

void show_user_info(USER * user)
{
	if ( user->ue_flag == 1 )
	{
		puts("**********************INFOMATION CARD**************************");
		printf("   NAME\t\t: %s\t\t\t TITLE\t: %s\n",user->ue->tch->name,user->ue->tch->title);
		printf("   GENDER\t: %c\t\t\t IN_LAB\t: %c\n",user->ue->tch->gender,user->ue->tch->inlab);
		printf("   RESEARCH AREA: %s\n",user->ue->tch->research_area);
		puts("***************************************************************");
	}
	else
	{
		puts("**********************INFOMATION CARD**************************");
		printf("   NAME\t: %s\t\t\t\t GENDER\t: %c\n",user->ue->stu->name,user->ue->stu->gender);
		printf("   ID\t: %s\t\t\t GRADE\t: %s\n",user->ue->stu->ID,user->ue->stu->grade);
		printf("   AGE\t: %d\t\t\t\t IN_LAB\t: %c\n",user->ue->stu->age,user->ue->stu->inlab);
		puts("***************************************************************");
	}
}

