#include<stdio.h>
#include<stdlib.h>
#include <WINSOCK2.H>
#include <STDIO.H>
#pragma  comment(lib,"ws2_32.lib")

class file
{
private:
	FILE *f;
	char path_buffer[_MAX_PATH];
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

public:
	FILE * selectfile()
	{
		printf("Enter the file name\n");
		scanf("%s", path_buffer);

		if (f = fopen(path_buffer, "rb"))
		{
			printf("File open success!\n");
			return f;
		}
		else
		{
			printf("The file is not exit, please enter again\n");
			return selectfile();
		}
	}

	char * getFileName()
	{
		_splitpath(path_buffer, drive, dir, fname, ext);
		return strcat(fname, ext);
	}
	FILE * createFile(char *name)
	{
		remove(name);
		if (f = fopen(name, "ab"))
		{
			printf("Create file success\n");

		}
		else
		{
			printf("Create file\n");
		}
		return f;
	}

	bool createDir(char *dir)
	{
		char head[MAX_PATH] = "md ";
		return system(strcat(head, dir));
	}

};
