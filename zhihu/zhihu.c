#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

int main()
{
	char id[80] = {};
	// 输入用户的主页ID
	printf("Please enter the homepage ID of the user: ");
	scanf("%40s", id);
	double speed = 1;
	// 循环间隔(s)
	printf("Please enter the display cycle interval(s): ");
	scanf("%lf", &speed);
	speed *= 6e8;
	char cmd[100] = {};
	FILE* fp = NULL;
	char *buf = malloc(4096);
	char fans[10] = {};
	int i = 0;
	int flag = 0;
re:	
	sprintf(cmd ,"..\\wget.exe -q https://www.zhihu.com/people/%s", id);
	system(cmd);
	fp = fopen(id, "r");
	if (fp == NULL)
	{
		printf("File access error! press any key to exit \n");
		getch();
		exit(0);
	}
	
	flag = 0;
	i = 0;
	while(1)
	{
		fscanf(fp, "%s", buf);
		char *temp = strstr(buf, "title=\"");
		if(temp == NULL)
		{
			memset(buf, 0, sizeof(buf));
			continue;
		}
		if(flag == 0 || flag == 1)
		{
			flag++;
			memset(buf, 0, sizeof(buf));
			continue;
		}
		temp += 7;
		while(1)
		{
			if(temp[i] == '"' || temp[i] == '\0' || temp[i] == '\n')
			{
				break;
			}
			fans[i] = temp[i];
			i++;
		}
		printf("%s's number of fans is:%s\n", id, fans);
		memset(buf, 0, sizeof(buf));
		memset(fans, 0, sizeof(fans));
		temp = NULL;
		break;
	}
	fclose(fp);
	fp = NULL;
	memset(cmd, 0, sizeof(cmd));
	sprintf(cmd, "del %s", id);
	system(cmd);
	memset(cmd, 0, sizeof(cmd));
	
	for (i = 0;i < speed;i++);
	goto re;
	
	return 0;
}
