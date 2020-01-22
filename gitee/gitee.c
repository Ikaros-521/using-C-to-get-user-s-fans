#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

int main()
{
	char id[40] = {};
	// 输入用户的ID
	printf("Please enter the ID of the user: ");
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
	sprintf(cmd ,"..\\wget.exe -q https://gitee.com/%s/followers", id);
	system(cmd);
	
	fp = fopen("followers", "r");
	if (fp == NULL)
	{
		printf("File access error! press any key to exit \n");
		getch();
		exit(0);
	}
	
	i = 0;
	flag = 0;
	while(1)
	{
		fscanf(fp, "%s", buf);
		char *temp = strstr(buf, "social-count");
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
		temp += 14;
		while(1)
		{
			if(temp[i] == '<' || temp[i] == '\0' || temp[i] == '\n')
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
	sprintf(cmd, "del followers");
	system(cmd);
	memset(cmd, 0, sizeof(cmd));
	
	for (i = 0;i < speed;i++);
	goto re;
	
	return 0;
}
