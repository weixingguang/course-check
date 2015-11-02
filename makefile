OBJECT = course_check.o input_info.o register.o mysql_tool.o show_info.o


course_check: $(OBJECT)
	gcc $(OBJECT) -o course_check `mysql_config --cflags --libs` -g

show_info.o:show_info.c course_check.h
	gcc -c show_info.c -o show_info.o -g

course_check.o:course_check.c mysql_tool.h
	gcc -c course_check.c  -o course_check.o  -g

input_info.o:input_info.c course_check.h
	gcc -c input_info.c -o input_info.o -g

register.o:register.c mysql_tool.h
	gcc -c register.c -o register.o -g

mysql_tool.o:mysql_tool.c mysql_tool.h
	gcc -c mysql_tool.c -o mysql_tool.o  -g

.PHONY:clean cleanall
clean:
	rm $(OBJECT)
cleanall:
	rm $(OBJECT) course_check
