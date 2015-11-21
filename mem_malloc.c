/***********************************************************************
 * Filename      : malloc.c
 * Author        : Xingguang wei
 * Email         : jxweixingguang@163.com
 * Create Date   : 2015-11-14
 * Last modified : 2015-11-14 23:37
 * Description   : 
 * ********************************************************************/
#include "course_check.h"

STU * stu_malloc(STU * stu)
{
	stu->ID       = malloc(10 * sizeof(char));
	stu->name     = malloc(20 * sizeof(char));
	stu->password = malloc(20 * sizeof(char));
	stu->age      = 20;
	stu->gender   = 'M';
	stu->grade    = malloc(6 * sizeof(char));
	stu->inlab    = 'Y';

	return stu;
}

TCH * tch_malloc(TCH * tch)
{
	tch->ID            = malloc(10 * sizeof(char));
	tch->name          = malloc(20 * sizeof(char));
	tch->password      = malloc(20 * sizeof(char));
	tch->gender        = 'M';
	tch->title         = malloc(20 * sizeof(char));
	tch->research_area = malloc(50 * sizeof(char));
	tch->inlab         = 'N';

	return tch;
}
