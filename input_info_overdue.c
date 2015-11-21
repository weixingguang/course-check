/***********************************************************************
 * Filename      : input_info.c
 * Author        : Xingguang wei
 * Email         : jxweixingguang@163.com
 * Create Date   : 2015-11-01
 * Last modified : 2015-11-21 12:10
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


//TODO change and add union
void input_userinfo(USER * user)
{
	int c;

	char * name          = malloc( 20*sizeof(char) );
	char * ID            = malloc( 20*sizeof(char) );
	char * password      = malloc( 20*sizeof(char) );
	char * title				 = malloc( 20 * sizeof(char) );
	char * research_area = malloc( 50 * sizeof(char) );
	char * grade         = malloc( 6*sizeof(char) );
	char  gender				 = 'M';
	int age			         = 18;

	//name
	printf("please input your name [within 20 chars] : ");
	while ( scanf("%s",name) )
	{
		while ( (c=getchar()) != '\n' && c != EOF );
		if ( strlen(name) == 0 || strlen(name) > 20  )
			printf("Input error, please input your name [within 20 chars] again: ");
		else
			break;
	}

	//ID
	printf("please input your ID [10 bits] : ");
	while ( scanf("%s",ID) )
	{
		while ( (c=getchar()) != '\n' && c != EOF );
		if( strlen(ID) != 10 )
			printf("Input error, please input your ID [10 bits] again: ");
		else
			break;
	}

	//password
	char * password1 = malloc(sizeof(char*));
	char * password2 = malloc(sizeof(char*));
	while ( 1 )
	{
		printf("please input your password [10-20 bits]: ");
		scanf("%s",password1);
		while ( (c=getchar()) != '\n' && c != EOF );
		printf("please confirm your password [10-20 bits] again: ");
		scanf("%s",password2);
		while ( (c=getchar()) != '\n' && c != EOF );

		if( strcmp(password1,password2) == 0 )
		{
			strcpy(password,password1);

			if( strlen(password) < 10 || strlen(password) >20)
				printf("password should within 10bits and 20 bits, please input your password again.\n");
			else
				break;
		}
		else
		{
			printf("Input error, the password isn't the same as the first time!\n");
		}
	}
	free(password1);
	free(password2);

	//gender
	printf("please input your gender [M for man, F for female] : ");
	while ( scanf("%c",&gender) )
	{
		while ( (c=getchar()) != '\n' && c != EOF );
		if ( gender != 'M' && gender != 'F' )
			printf("Input error,input your gender [M for man, F for female] again: ");
		else
			break;
	}

	if ( user->ue_flag == 1 )
	{
		//title
		printf("please input your title : ");
		while ( scanf("%s",title) )
		{
			while ( (c=getchar()) != '\n' && c != EOF );
			if ( strlen(title) < 1 || strlen(title) > 20 )
				printf("Input error, please input your title again: ");
			else
				break;
		}

		//research_area
		printf("please input your research area within 50 characters : ");
		while ( fgets(research_area,50,stdin) )
		{
			*(research_area+strlen(research_area)-1) = '\0';
			if ( strlen(research_area) < 1 )
				printf("Input error, please input your research area within 50 characters again : ");
			else
				break;
		}
	}
	else
	{
		//age
		printf("please input your age : ");
		scanf("%d",&age);
		while ( (c=getchar()) != '\n' && c != EOF );

		//grade
		int option;
		printf("please input yur grade [0,1,2,3] : ");
		while ( scanf("%d",&option) )
		{
			while ( (c=getchar()) != '\n' && c != EOF );
			if ( option == 0)
			{
				strcpy(grade,"zero");
				break;
			}
			else if ( option == 1 )
			{
				strcpy(grade,"first");
				break;
			}
			else if ( option == 2)
			{
				strcpy(grade,"second");
				break;
			}
			else if ( option == 3)
			{
				strcpy(grade,"third");
				break;
			}
			else
				printf("Input error, please input yur grade [0,1,2,3] again : ");
		}
	}

	if( user->ue_flag == 1 )
	{
		strcpy(user->ue->tch->name,name);
		strcpy(user->ue->tch->ID,ID);
		strcpy(user->ue->tch->password,password);
		user->ue->tch->gender = gender;
		strcpy(user->ue->tch->title,title);
		strcpy(user->ue->tch->research_area,research_area);
	}
	else
	{
		strcpy(user->ue->stu->name,name);
		strcpy(user->ue->stu->ID,ID);
		strcpy(user->ue->stu->password,password);
		user->ue->stu->age = age;
		user->ue->stu->gender = gender;
		strcpy(user->ue->stu->grade,grade);
	}
	
}
