course_check:course_check.o mysql_tool.o
	gcc course_check.o mysql_tool.o -o course_check `mysql_config --cflags --libs` -g

course_check.o:course_check.c mysql_tool.h
	gcc -c course_check.c  -o course_check.o  -g
mysql_tool.o:mysql_tool.c mysql_tool.h
	gcc -c mysql_tool.c -o mysql_tool.o  -g

clean:
	rm mysql_tool.o course_check.o course_check
