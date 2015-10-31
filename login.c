/***********************************************************************
 * Filename      : login.c
 * Author        : Xingguang wei
 * Email         : jxweixingguang@163.com
 * Create Date   : 2015-10-31
 * Last modified : 2015-10-31 19:39
 * Description   : 
 * ********************************************************************/

void welcome_info()
{
	puts("*********************************************************");
	puts("Welcome to course check system!");
	puts("[option 1 ] If you are a new user, please register first.");
	puts("[option 2 ] If you have registered, please login.");
	puts("[option 3 ] EXIT.");
	puts("*********************************************************");
}

int stuinfo_check(STU stu)
{
	//name
	printf("please input your name [within 20 chars] : ");
	while ( scanf("%s",stu.name) )
	{
		if ( strlen(stu.name) == 0 || strlen(stu.name) > 20  )
			printf("Input error, please input your name [within 20 chars] again: ");
		else
			break;
	}

	//ID
	printf("please input your ID [10 bits] : ");
	while ( scanf("%s",stu.ID) )
	{
		if( strlen(stu.ID) != 10 )
			printf("Input error, please input your ID [10 bits] again: ");
		else
			break;
	}

	//password
	char * password1;
	char * password2;
	while ( 1 )
	{
		printf("please input your password [10-20 bits]");
		scanf("%s",password1);
		printf("please confirm your password [10-20 bits] again");
		scanf("%s",password2);

		if( strcmp(password1,password2) == 0 )
		{
			strcpy(stu.password,password1);

			if( strlen(stu.password) < 10 )
				printf("password too simple! please input your password [10-20 bits] again.\n");
			else if ( strlen(stu.password) >20 )
				printf("password should within 10bits and 20 bits, please input your password again.\n");
			else
				break;
		}
		else
		{
			printf("the password isn't the same as the first time!\n");
		}
	}

	//age
	printf("please input your age : ");
	scanf("%d",stu.age);

	//gender
	printf("please input your gender [M for man, F for female] : ");
	while ( scanf("%c",stu.gender) )
	{
		if ( stu.gender != 'M' || stu.gender != 'F' )
			printf("please input your gender [M for man, F for female] again: ");
		else
			break;
	}

	//grade
	int option;
	printf("please input yur grade [0,1,2,3] : ");
	while ( scanf("%d",&option) )
	{
		if ( option == 0)
		{
			strcpy(stu.grade,"zero");
			break;
		}
		else if ( option == 1 )
		{
			strcpy(stu.grade,"first");
			break;
		}
		else if ( option == 2)
		{
			strcpy(stu.grade,"second");
			break;
		}
		else if ( option == 3)
		{
			strcpy(stu.grade,"third");
			break;
		}
		else
			printf("please input yur grade [0,1,2,3] again : ");
	}
}

int stu_register(MYSQL * mysql,STU stu)
{
	int res;
	res = mysql_query(mysql,
			"insert into student_info (ID,name,password,age,gender,grade,inlab) \
			values(stu.ID, stu.name, stu.password, stu.age, stu.gender, stu.grade, stu.inlab )");
	if( res )
	{
		printf("insert into table student_info error %s\n",mysql_error(mysql));
		return 1;
	}

	return 0;
}

int tch_register(MYSQL * mysql,TCH tch)
{
	int res;
	res = mysql_query(mysql,
			"insert into teacher_info (ID,name,password,gender,title,research_area,inlab) \
			values(tch.ID, tch.name, tch.password, tch.gender, tch.title, tch.research_area, tch.inlab)");
	if ( res )
	{
		printf("insert into table teacher_info error %s\n",mysql_error(mysql));
		return 1;
	}

	return 0;
}
