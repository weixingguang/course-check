/***********************************************************************
 * Filename      : search_info.c
 * Author        : Xingguang wei
 * Email         : jxweixingguang@163.com
 * Create Date   : 2015-11-12
 * Last modified : 2015-11-12 20:38
 * Description   : 
 * ********************************************************************/
#include "course_check.h"

//TODO complete this function
int show_signtime_statistic(MYSQL * mysql,char *ID)
{
	int sum = 0;
	char * myorder = malloc( 400*sizeof(char) );
	char *weekday[] = {"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};
	//printf("please input the ID : ");
	//char *ID = malloc( 10*sizeof(char) );
	//scanf("%s",ID);
	int index=0;
	MYSQL_RES * res;
	MYSQL_ROW row;
	for(index=0;index<7;index++)
	{
		sprintf(myorder,"select floor((unix_timestamp(m_out)-unix_timestamp(m_in))/60),floor((unix_timestamp(a_out)-unix_timestamp(a_in))/60),floor((unix_timestamp(n_out)-unix_timestamp(n_in))/60) from student_timetable where ID='%s'and week='%s' and yearweek(date)=yearweek(now())-1",ID,weekday[index]);
		mysql_query(mysql,myorder);
		res = mysql_store_result(mysql);
		row = mysql_fetch_row(res);

		if(row != NULL)
		{
			int index=0;
			for(index=0;index<3;index++)
				if(row[index]!=NULL)
					sum +=atoi(row[index]);
		}
	}
	return sum;
}

void show_signtable(MYSQL * mysql)
{
	char * myorder = malloc( 200*sizeof(char) );
	char *weekday[] = {"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};
	printf("please input the ID : ");
	char *ID = malloc( 10*sizeof(char) );
	scanf("%s",ID);
	int index=0;
	for(index=0;index<7;index++)
	{
		sprintf(myorder,"select week,m_in,m_out,a_in,a_out,n_in,n_out from student_timetable where ID='%s'and week='%s' and yearweek(date)=yearweek(now())-1",ID,weekday[index]);
		mysql_query(mysql,myorder);
		MYSQL_RES * res = mysql_store_result(mysql);
		MYSQL_ROW row = mysql_fetch_row(res);
		if(row != NULL)
		{

			int index=0;
			for(index=0;index<7;index++)
			{
				if(row[index]!=NULL)
					printf("|%-9s",row[index]);
				else
					printf("|%-9s","NULL");
			}
			printf("|\n");
		}
		else
				printf("|%-9s|%-9s|%-9s|%-9s|%-9s|%-9s|%-9s|\n",weekday[index],"NULL","NULL","NULL","NULL","NULL","NULL");
	}

	int sum = show_signtime_statistic(mysql,ID);
	printf("sum time %d hours %d minutes\n",sum/60,sum%60);
}

void show_classtable(MYSQL * mysql)
{
	char *weekday[] = {"Monday","Tuesday","Wednesday","Thursday","Friday"};
	printf("please input the ID : ");
	char * ID = malloc( 10*sizeof(char) );
	scanf("%s",ID);
	char * myorder = malloc( 200*sizeof(char) );
	MYSQL_RES * res;
	MYSQL_ROW row;
  int index=0;
	for(index=0;index<5;index++)
	{
	sprintf(myorder,"select class1,class2,class3,class4,class5,class6,class7,class8,class9,class10,class11 from student_class where ID ='%s' and week ='%s'",ID,weekday[index]);
	mysql_query(mysql,myorder);
  res = mysql_store_result(mysql);
	row = mysql_fetch_row(res);
	printf("%-10s | %-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s%-10s\n",
			weekday[index],row[0],row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8],row[9],row[10]);
	}
	
}

void show_inlab_user(MYSQL * mysql)
{

	int index=0;
	MYSQL_RES * res;
	MYSQL_ROW row;
	char * myorder[2];
	char * user[2];
	user[0]="student";
	user[1]="teacher";
	for (index=0;index<2;index++)
	{
		myorder[index]= malloc( 200*sizeof(char) );
		sprintf(myorder[index],"select name from %s_info where inlab='Y'",user[index]);

		mysql_query(mysql,myorder[index]);
		res = mysql_store_result(mysql);
		printf("<----%s---->\n",user[index]);
			while( (row = mysql_fetch_row(res)) != NULL)
		{
			printf(" %-10s  In Lab\n",row[0]);
		}
	}
}
void change_password(MYSQL * mysql, USER * user)
{
	char c;
	printf("please input the ID:");
	char * ID = malloc( 10 * sizeof(char) );
	char * password1 = malloc( 20 * sizeof(char) );
	char * password2 = malloc( 20 * sizeof(char) );
	scanf("%s",ID);
	printf("please input your new password: ");
	while( (c=getchar()) != '\n' && c != EOF );
	scanf("%s",password1);
	printf("please check your new password again: ");
	while( (c=getchar()) != '\n' && c != EOF );
	scanf("%s",password2);

	char * myorder = malloc( 100 * sizeof(char) );
	if( strcmp(password1,password2) == 0 )
		if( user->ue_flag == 1 )
		sprintf(myorder,"update student_info set password='%s' where ID='%s'",password1,ID);
		else
		sprintf(myorder,"update teacher_info set password='%s' where ID='%s'",password1,ID);

	mysql_query(mysql,myorder);

}

void input_class(MYSQL * mysql,USER * user)
{
	char * class[11];
	int index;
	for(index=0;index<11;index++)
		class[index]= malloc( 30 * sizeof(char));

	char * myorder = malloc(500 * sizeof(char) );
	printf("please input your class by class1[8:00-9:00],class2[9:00-10:00].....class11[8:30-9:30].\n");
	printf("if you don't have class on that time, please input NULL\n");

	char *week[5]={"Monday","Tuesday","Wednesday","Thursday","Friday"};
	for(index=0;index<5;index++)
	{
		printf("please input your class on [%s] like math english physical : ",week[index]);

		scanf("%s%s%s%s%s%s%s%s%s%s%s",class[0],class[1],class[2],class[3],class[4],class[5],
				class[6],class[7],class[8],class[9],class[10]);
		sprintf(myorder,"insert into student_class \
				(ID,week,class1,class2,class3,class4,class5,class6,class7,class8,class9,class10,class11)\
				values('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s')",
				user->ue->stu->ID,week[index],class[0],class[1],class[2],class[3],class[4],class[5],class[6],class[7],class[8],class[9],class[10]);
		mysql_query(mysql,myorder);
	}
}

void search_userinfo(MYSQL * mysql)
{
	char * myorder	= malloc( 200 * sizeof(char) );
	char * name = malloc( 20 * sizeof(char) ); 

	int user_flag = IS_STU;
	printf("[option 0] search student info      [option 1] search teacher info\nInput : ");
	scanf("%d",&user_flag);

	printf("please input the name you want to research: ");
	scanf("%s",name);

	if ( user_flag == IS_STU )
	sprintf(myorder,"select gender,ID,age,grade,inlab from student_info where name='%s' ",name);
	else if ( user_flag == IS_TCH )
	sprintf(myorder,"select gender,ID,age,grade,inlab from teacher_info where name='%s' ",name);

	mysql_query(mysql,myorder);
	MYSQL_RES * res = mysql_store_result(mysql);
	MYSQL_ROW row = mysql_fetch_row(res);
	puts("**********************INFOMATION CARD**************************");
	if ( user_flag == IS_STU )
	{
		printf("   NAME\t: %s\t\t\t\t GENDER\t: %c\n",name,(char)row[0][0]);
		printf("   ID\t: %s\t\t\t GRADE\t: %s\n",row[1],row[3]);
		printf("   AGE\t: %d\t\t\t\t IN_LAB\t: %c\n",atoi(row[2]),row[4][0]);
	}
	else if ( user_flag == IS_TCH )
	{
		printf("   NAME\t: %s\t\t\t\t GENDER\t: %c\n",name,(char)row[0][0]);
		printf("   ID\t: %s\t\t\t GRADE\t: %s\n",row[1],row[3]);
		printf("   AGE\t: %d\t\t\t\t IN_LAB\t: %c\n",atoi(row[2]),row[4][0]);
	}
	puts("***************************************************************");
	mysql_free_result(res);
	free(name);
	free(myorder);
}

