# Makefile

# 定义变量
CC = gcc							#名称
CFLAGS = -Wall -Wextra -std=c11		#编译选项，-Wall 表示显示所有警告，-Wextra 表示显示额外的警告，-std=c11 表示使用 C11 标准编译。

# 默认目标
all: PRNMDTool bin2h

# 编译规则
PRNMDTool: PRNMDTool.c
	$(CC) $(CFLAGS) PRNMDTool.c -o PRNMDTool.exe
bin2h: bin2h.c
	$(CC) $(CFLAGS) bin2h.c -o bin2h.exe

# 清理规则
clean:
	rm -f PRNMDTool.exe
	rm -f bin2h.exe

