mysql_tool:mysql_tool.c mysql_tool.h
	gcc -o mysql_tool mysql_tool.c mysql_tool.h `mysql_config --cflags --libs` -g
