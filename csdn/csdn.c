#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

int main()
{
	char id[40] = {};
	// 输入博主的ID
	printf("Please enter the ID of the blogger: ");
	scanf("%40s", id);
	double speed = 1;
	// 循环间隔(s)
	printf("Please enter the display cycle interval(s): ");
	scanf("%lf", &speed);
	speed *= 6e8;
	char cmd[100] = {};
	FILE* fp = NULL;
	char *buf = malloc(4096);
	char *temp = NULL;
	char fans[10] = {};
	int i = 0;
re:	
	sprintf(cmd ,"..\\wget.exe -q https://blog.csdn.net/%s", id);
	system(cmd);
	
	fp = _popen("type csdn.txt | findstr user-profile-statistics-num 2>null", "r");
	if (fp == NULL)
	{
		printf("File access error! press any key to exit \n");
		getch();
		exit(0);
	}
	
	i = 0;
	while(1)
	{
		int size = fread(buf, 1, 4096, fp);
		if(size <= 0)
		{
			printf("CSDN error!\n");
			return;
		}
		temp = strstr(buf, "user-profile-statistics-num");
		if(temp == NULL)
		{
			printf("CSDN error!\n");
			return;
		}
		temp += 45;
		temp = strstr(temp, "user-profile-statistics-num");
		if(temp == NULL)
		{
			printf("CSDN error!\n");
			return;
		}
		temp += 45;
		temp = strstr(temp, "user-profile-statistics-num");
		if(temp == NULL)
		{
			printf("CSDN error!\n");
			return;
		}
		temp += 45;
		temp = strstr(temp, "user-profile-statistics-num");
		if(temp == NULL)
		{
			printf("CSDN error!\n");
			return;
		}
		temp += 45;
		while(1)
		{
			if(temp[i] == '<' || temp[i] == '\0' || temp[i] == '\n')
			{
				break;
			}
			fans[i] = temp[i];
			i++;
		}
		printf("CSDN    :%s\n", fans);
		memset(buf, 0, sizeof(buf));
		memset(fans, 0, sizeof(fans));
		temp = NULL;
		break;
	}
	_pclose(fp);
	fp = NULL;
	memset(cmd, 0, sizeof(cmd));
	sprintf(cmd, "del %s", id);
	system(cmd);
	memset(cmd, 0, sizeof(cmd));
	
	for (i = 0;i < speed;i++);
	goto re;
	
	return 0;
}
