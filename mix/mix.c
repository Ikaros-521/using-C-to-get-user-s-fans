#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

void bilibili(char* str);	// 哔哩哔哩
void cnblogs(char* str);	// 博客园
void csdn(char* str);		// CSDN
void gitee(char* str);		// 码云
void github(char* str);		// GitHub
void zhihu(char* str);		// 知乎

int main()
{
	double speed = 1;
	char id_bilibili[20] = {};
	char id_cnblogs[80] = {};
	char id_csdn[40] = {};
	char id_gitee[40] = {};
	char id_github[40] = {};
	char id_zhihu[80] = {};
	FILE* f = NULL;
	// 打开配置文件
	f = fopen("user_info.conf", "r");
	if (f == NULL)
	{
		printf("File user_info.conf access error! press any key to exit \n");
		getch();
		exit(0);
	}
	int i = 0;
	fscanf(f, "speed:%lf\nbilibili:%s\ncnblogs:%s\ncsdn:%s\ngitee:%s\ngithub:%s\nzhihu:%s\n", &speed, id_bilibili, id_cnblogs, id_csdn, id_gitee, id_github, id_zhihu);
	printf("---------- config ----------\nspeed:%lf\nbilibili:%s\ncnblogs:%s\ncsdn:%s\ngitee:%s\ngithub:%s\nzhihu:%s\n---------------------------\n", speed, id_bilibili, id_cnblogs, id_csdn, id_gitee, id_github, id_zhihu);
	speed *= 6e8;
re:	
	// 配置文件必须保证有数据，不需要的函数可以注释掉。
	bilibili(id_bilibili);	// 哔哩哔哩
	cnblogs(id_cnblogs);	// 博客园
	csdn(id_csdn);			// CSDN
	gitee(id_gitee);		// 码云
	//github(id_github);	// GitHub
	zhihu(id_zhihu);		// 知乎
	
	// 循环耗时
	for (i = 0;i < speed;i++);
	// 清屏
	system("cls");
	goto re;
	
	return 0;
}

// 哔哩哔哩
void bilibili(char* str)
{
	//printf("in bilibili");
	char id[20] = {};
	char cmd[100] = {};
	FILE* fp = NULL;
	char buf[4096] = {};
	char fans[10] = {};
	int i = 0;
	strcpy(id, str);
	
	sprintf(cmd ,"..\\wget.exe -q https://api.bilibili.com/x/relation/stat?vmid=%s -O bilibili.txt", id);
	system(cmd);
	fp = fopen("bilibili.txt", "r");
	if (fp == NULL)
	{
		printf("File bilibili.txt access error! press any key to exit \n");
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
		printf("bilibili: %s's number of fans is:%s\n", id, fans);
		memset(buf, 0, sizeof(buf));
		memset(fans, 0, sizeof(fans));
		temp = NULL;
		break;
	}
	fclose(fp);
	fp = NULL;
	memset(cmd, 0, sizeof(cmd));
	sprintf(cmd, "del \"bilibili.txt\"");
	system(cmd);
	memset(cmd, 0, sizeof(cmd));
}

// 博客园
void cnblogs(char* str)
{
	char id[80] = {};
	char cmd[100] = {};
	FILE* fp = NULL;
	char *buf = malloc(4096);
	char fans[10] = {};
	int i = 0;
	strcpy(id, str);
	
	sprintf(cmd ,"..\\wget.exe -q https://www.cnblogs.com/%s/ajax/news.aspx -O cnblogs.txt", id);
	system(cmd);
	fp = fopen("cnblogs.txt", "r");
	if (fp == NULL)
	{
		printf("File cnblogs.txt access error! press any key to exit \n");
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
		memset(buf, 0, sizeof(buf));
		fscanf(fp, "%s", buf);
		sprintf(fans, "%s", buf);
		printf("cnblogs: %s's number of fans is:%s\n", id, fans);
		memset(buf, 0, sizeof(buf));
		memset(fans, 0, sizeof(fans));
		temp = NULL;
		break;
	}
	fclose(fp);
	fp = NULL;
	memset(cmd, 0, sizeof(cmd));
	sprintf(cmd, "del cnblogs.txt");
	system(cmd);
	memset(cmd, 0, sizeof(cmd));
}

// CSDN
void csdn(char* str)
{
	char id[40] = {};
	char cmd[100] = {};
	FILE* fp = NULL;
	char *buf = malloc(4096);
	char fans[10] = {};
	int i = 0;
	strcpy(id, str);
	
	sprintf(cmd ,"..\\wget.exe -q https://blog.csdn.net/%s -O csdn.txt", id);
	system(cmd);
	
	fp = fopen("csdn.txt", "r");
	if (fp == NULL)
	{
		printf("File csdn.txt access error! press any key to exit \n");
		getch();
		exit(0);
	}
	
	i = 0;
	while(1)
	{
		fscanf(fp, "%s", buf);
		char *temp = strstr(buf, "id=\"fan\">");
		if(temp == NULL)
		{
			memset(buf, 0, sizeof(buf));
			continue;
		}
		temp += 9;
		while(1)
		{
			if(temp[i] == '<' || temp[i] == '\0' || temp[i] == '\n')
			{
				break;
			}
			fans[i] = temp[i];
			i++;
		}
		printf("CSDN: %s's number of fans is:%s\n", id, fans);
		memset(buf, 0, sizeof(buf));
		memset(fans, 0, sizeof(fans));
		temp = NULL;
		break;
	}
	fclose(fp);
	fp = NULL;
	memset(cmd, 0, sizeof(cmd));
	sprintf(cmd, "del csdn.txt");
	system(cmd);
	memset(cmd, 0, sizeof(cmd));
}

// 码云
void gitee(char* str)
{
	char id[40] = {};
	char cmd[100] = {};
	FILE* fp = NULL;
	char *buf = malloc(4096);
	char fans[10] = {};
	int i = 0;
	int flag = 0;
	strcpy(id, str);
	
	sprintf(cmd ,"..\\wget.exe -q https://gitee.com/%s/followers -O gitee.txt", id);
	system(cmd);
	
	fp = fopen("gitee.txt", "r");
	if (fp == NULL)
	{
		printf("File gitee.txt access error! press any key to exit \n");
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
		printf("gitee: %s's number of fans is:%s\n", id, fans);
		memset(buf, 0, sizeof(buf));
		memset(fans, 0, sizeof(fans));
		temp = NULL;
		break;
	}
	fclose(fp);
	fp = NULL;
	memset(cmd, 0, sizeof(cmd));
	sprintf(cmd, "del gitee.txt");
	system(cmd);
	memset(cmd, 0, sizeof(cmd));
}

// GitHub
void github(char* str)
{
	char id[40] = {};
	char cmd[100] = {};
	FILE* fp = NULL;
	char *buf = malloc(4096);
	char fans[10] = {};
	int i = 0;
	int flag = 0;
	strcpy(id, str);
	
	sprintf(cmd ,"..\\wget.exe -q  https://github.com/%s -O github.txt", id);
	system(cmd);
	
	fp = fopen("github.txt", "r");
	if (fp == NULL)
	{
		printf("File github.txt access error! press any key to exit \n");
		getch();
		exit(0);
	}
	
	i = 0;
	flag = 0;
	while(1)
	{
		fscanf(fp, "%s", buf);
		
		char *temp = strstr(buf, "hide-sm");
		if(temp == NULL)
		{
			memset(buf, 0, sizeof(buf));
			continue;
		}
		if(flag == 0 || flag == 1 || flag == 2)
		{
			flag++;
			memset(buf, 0, sizeof(buf));
			continue;
		}
		memset(buf, 0, sizeof(buf));
		fscanf(fp, "%s", buf);
		memset(buf, 0, sizeof(buf));
		fscanf(fp, "%s", buf);
		sprintf(fans, "%s", buf);
		printf("GitHub: %s's number of fans is:%s\n", id, fans);
		memset(buf, 0, sizeof(buf));
		memset(fans, 0, sizeof(fans));
		temp = NULL;
		break;
	}
	fclose(fp);
	fp = NULL;
	memset(cmd, 0, sizeof(cmd));
	sprintf(cmd, "del github.txt");
	system(cmd);
	memset(cmd, 0, sizeof(cmd));
}

// 知乎
void zhihu(char* str)
{
	char id[80] = {};
	char cmd[100] = {};
	FILE* fp = NULL;
	char *buf = malloc(4096);
	char fans[10] = {};
	int i = 0;
	int flag = 0;
	strcpy(id, str);
	
	sprintf(cmd ,"..\\wget.exe -q https://www.zhihu.com/people/%s -O zhihu.txt", id);
	system(cmd);
	fp = fopen("zhihu.txt", "r");
	if (fp == NULL)
	{
		printf("File zhihu.txt access error! press any key to exit \n");
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
		printf("zhihu: %s's number of fans is:%s\n", id, fans);
		memset(buf, 0, sizeof(buf));
		memset(fans, 0, sizeof(fans));
		temp = NULL;
		break;
	}
	fclose(fp);
	fp = NULL;
	memset(cmd, 0, sizeof(cmd));
	sprintf(cmd, "del zhihu.txt");
	system(cmd);
	memset(cmd, 0, sizeof(cmd));
}
