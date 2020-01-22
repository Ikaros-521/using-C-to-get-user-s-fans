#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

int main()
{
	char id[20] = {};
	// 输入用户的UID
	printf("Please enter the UID of the user: ");
	scanf("%20s", id);
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
	char filename[40] = {};
	sprintf(filename ,"stat@vmid=%s", id);
re:	
	sprintf(cmd ,"..\\wget.exe -q https://api.bilibili.com/x/relation/stat?vmid=%s", id);
	system(cmd);
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("File access error! press any key to exit \n");
		getch();
		exit(0);
	}
	
	i = 0;
	while(1)
	{
		fscanf(fp, "%s", buf);
		char *temp = strstr(buf, "follower");
		if(temp == NULL)
		{
			memset(buf, 0, sizeof(buf));
			continue;
		}
		temp += 10;
		while(1)
		{
			if(temp[i] == '}' || temp[i] == '\0' || temp[i] == '\n')
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
	sprintf(cmd, "del \"%s\"", filename);
	system(cmd);
	memset(cmd, 0, sizeof(cmd));
	
	for (i = 0;i < speed;i++);
		goto re;
	
	return 0;
}
