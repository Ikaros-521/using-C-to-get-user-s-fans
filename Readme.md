## 思路源自
[bilibili](https://www.bilibili.com/video/av84354171)
	
## 支持网站
	CSDN，知乎，博客园，码云，GitHub，bilibili

## 编译
	gcc csdn.c -o csdn

## 运行
	直接运行csdn.exe 或 打开cmd，cd到工作目录，输入 csdn.exe 运行

## 关闭
	ctrl+C

## 相关问题
	1、如果工作目录下有id为名的文件，请把它删除。
	2、如果获取的“知乎”用户设置了隐私权限，那么就获取不到数据，需要手动关闭程序，清楚工作目录下的id为名的文件。
	3、mix即混合版，需要修改配置文件 user_info.conf ，字段信息不能为空，否则会读取出错，导致程序运行不正常。不需要的网址可以在mix.c中注释掉，但配置信息必须填写（随便填一个）。