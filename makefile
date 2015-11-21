OBJECT = course_check.o input_info.o register.o mysql_tool.o show_info.o login.o sign.o basic_function.o mem_malloc.o
CC = gcc
CFLAGS = -std=c99 `mysql_config --cflags --libs` -g

# TODO fix the following principles
# How to make mutiple objects with the same principle 

# The entrance of this program
course_check: $(OBJECT)
	$(CC) $^ -o $@ $(CFLAGS)

# Memory allocation function for the struct and enum variable
mem_malloc.o:mem_malloc.c course_check.h
	$(CC) -c $< -o $@ $(CFALGS)

# Basic operation function for student and teacher
basic_function.o:basic_function.c course_check.h
	$(CC) -c $< -o $@ $(CFALGS)

# Sign function for student and teacher
sign.o:sign.c course_check.h
	$(CC) -c $< -o $@ $(CFALGS)

# Login function for student and teacher
login.o:login.c 
	$(CC) -c $< -o $@ $(CFALGS)

# Show menu and user information of student and teacher
show_info.o:show_info.c course_check.h
	$(CC) -c $< -o $@ $(CFALGS)

# The main function
# The top logical structure of this program
course_check.o:course_check.c 
	$(CC) -c $< -o $@ $(CFALGS)

# Input and check user's basic information
input_info.o:input_info.c course_check.h
	$(CC) -c $< -o $@ $(CFALGS)

# The register function for student and teacher
register.o:register.c
	$(CC) -c $< -o $@ $(CFALGS)

# Basic operation function related to mysql database 
mysql_tool.o:mysql_tool.c 
	$(CC) -c $< -o $@ $(CFALGS)

.PHONY:clean cleanall
clean:
	-rm -f $(OBJECT)
cleanall:
	-rm -f $(OBJECT) course_check
