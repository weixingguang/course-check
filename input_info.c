/***********************************************************************
 * Filename      : input_info.c
 * Author        : Xingguang wei
 * Email         : jxweixingguang@163.com
 * Create Date   : 2015-11-01
 * Last modified : 2015-11-01 10:08
 * Description   : 
 * ********************************************************************/

#include "course_check.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void tchinfo_check(TCH * tch)
{
	int c;

	printf("please input your name [within 20 chars] : ");
	while ( (c=scanf("%s",tch->name)) )
	{
		while ( (c=getchar()) != '\n' && c != EOF );
		if ( strlen(tch->name) == 0 || strlen(tch->name) > 20  )
			printf("Input error, please input your name [within 20 chars] again: ");
		else
			break;
	}

	//ID
	printf("please input your ID [10 bits] : ");
	while ( scanf("%s",tch->ID) )
	{
		while ( (c=getchar()) != '\n' && c != EOF );
		if( strlen(tch->ID) != 10 )
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
			strcpy(tch->password,password1);

			if( strlen(tch->password) < 10 )
				printf("password too simple! please input your password [10-20 bits] again.\n");
			else if ( strlen(tch->password) >20 )
				printf("password should within 10bits and 20 bits, please input your password again.\n");
			else
				break;
		}
		else
		{
			printf("the password isn't the same as the first time!\n");
		}
	}
	free(password1);
	free(password2);

	//gender
	printf("please input your gender [M for man, F for female] : ");
	while ( scanf("%c",&tch->gender) )
	{
		while ( (c=getchar()) != '\n' && c != EOF );
		if ( tch->gender != 'M' && tch->gender != 'F' )
			printf("please input your gender [M for man, F for female] again: ");
		else
			break;
	}

	//title
	printf("please input your title : ");
	while ( scanf("%s",tch->title) )
	{
		while ( (c=getchar()) != '\n' && c != EOF );
		if ( strlen(tch->title) < 1 || strlen(tch->title) > 20 )
			printf("please input your title again: ");
		else
			break;
	}

	//research_area
	printf("please input your research area within 50 characters : ");
	while ( fgets(tch->research_area,50,stdin) )
	{
		if ( strlen(tch->research_area) < 1 )
			printf("input error, please input your research area within 50 characters again : ");
		else
			break;

	}
}

void stuinfo_check(STU * stu)
{
	int c;
	//name
	printf("please input your name [within 20 chars] : ");
	while ( scanf("%s",stu->name) )
	{
		while ( (c=getchar()) != '\n' && c != EOF );
		if ( strlen(stu->name) == 0 || strlen(stu->name) > 20  )
			printf("Input error, please input your name [within 20 chars] again: ");
		else
			break;
	}

	//ID
	printf("please input your ID [10 bits] : ");
	while ( scanf("%s",stu->ID) )
	{
		while ( (c=getchar()) != '\n' && c != EOF );
		if( strlen(stu->ID) != 10 )
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
			strcpy(stu->password,password1);

			if( strlen(stu->password) < 10 )
				printf("password too simple! please input your password [10-20 bits] again.\n");
			else if ( strlen(stu->password) >20 )
				printf("password should within 10bits and 20 bits, please input your password again.\n");
			else
				break;
		}
		else
		{
			printf("the password isn't the same as the first time!\n");
		}
	}
	free(password1);
	free(password2);

	//age
	printf("please input your age : ");
	scanf("%d",&stu->age);
	while ( (c=getchar()) != '\n' && c != EOF );

	//gender
	printf("please input your gender [M for man, F for female] : ");
	while ( scanf("%c",&stu->gender) )
	{
		while ( (c=getchar()) != '\n' && c != EOF );
		if ( stu->gender != 'M' && stu->gender != 'F' )
			printf("please input your gender [M for man, F for female] again: ");
		else
			break;
	}

	//grade
	int option;
	printf("please input yur grade [0,1,2,3] : ");
	while ( scanf("%d",&option) )
	{
	  while ( (c=getchar()) != '\n' && c != EOF );
		if ( option == 0)
		{
			strcpy(stu->grade,"zero");
			break;
		}
		else if ( option == 1 )
		{
			strcpy(stu->grade,"first");
			break;
		}
		else if ( option == 2)
		{
			strcpy(stu->grade,"second");
			break;
		}
		else if ( option == 3)
		{
			strcpy(stu->grade,"third");
			break;
		}
		else
			printf("please input yur grade [0,1,2,3] again : ");
	}
}

//void main()
//{
//	welcome_info();
//	STU * stu = stu_malloc();
//  TCH * tch = tch_malloc();
//	tchinfo_check(tch);
//	stuinfo_check(stu);
//}
