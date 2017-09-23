#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

//declarations;
char *promptLine(void);
char *getCommandLine(void);
int execCommand(char*);
char **getCommandArgs(char*,int*);
void echo(char**, int);
void exit(void);
void pwd(void);


int main(void){
	while(1){
		printf("%s ", promptLine());
		char* commandline = getCommandLine();
		execCommand(commandline);

		free(commandline);
	}

	return 0;
}


//print promptline;
char *promptLine(void){
	time_t seconds;
	struct tm* localTimeInfo;
	char *timeBuffer = (char*)malloc(sizeof(char) * 10);

	//check memory;
	if(!timeBuffer){
		puts("Failed when try to allocate memory");
		exit(0);
	}
	//get current local time;
	time(&seconds);
	localTimeInfo = localtime(&seconds);

	//set time&bash sign string;
	sprintf(timeBuffer, "%d:%d:%d#",localTimeInfo->tm_hour,
									localTimeInfo->tm_min,
									localTimeInfo->tm_sec);

	return timeBuffer;
}

//read Command Line;
char *getCommandLine(void){
	char *buffer;
    size_t bufsize = 10;
    int charSize;
	buffer = (char *)malloc(bufsize * sizeof(char));
	//check memory;
	if(!buffer){
		puts("Failed when try to allocate memory");
		exit(0);
	}
	charSize = getline(&buffer,&bufsize,stdin);
	//delete '/n' charactor;
	buffer[charSize - 1] = '\0';

	return buffer;
}

//execute command;
int execCommand(char *command){
	//number of arguments;
	int argv = 0;

	char **args = getCommandArgs(command,&argv);

	if(strcmp(args[0],"echo") == 0) echo(args,argv);
	else if(strcmp(args[0],"exit") == 0) exit();
	else if(strcmp(args[0],"pwd") == 0) pwd();
	else if(strcmp(args[0],"\0") == 0) return 0;
	else{
		puts();
		args[argv] = (char*) NULL;
	}

	for(int i = 0; i <= argv; i++) free(args[i]);
	free(args);

	return 1;
}

//split command to arguments;
char **getCommandArgs(char *command,int *pos){
	int bufferSize = 10;
	const char delim[2] = " ";
	char **args = (char**)malloc(bufferSize * sizeof(char**));
	if(!args){
		puts("Failed when try to allocate memory");
		exit(0);
	}
	char *arg;
	//split command to arguments;
	arg = strtok(command,delim);
	while(arg != NULL){
		args[*pos] = arg;
		*pos = *pos + 1;
		arg = strtok(NULL, delim);
	}

	return args;
}

void echo(char** args, int argv){
 	for(int i = 1; i < argv; i++) printf("%s ", args[i]);
 	puts("");	
}

void exit(void){ exit(0);}

void pwd(void){
	char cwd[100];
   	if (getcwd(cwd, sizeof(cwd)) != NULL) fprintf(stdout, "%s\n", cwd);
}

void ls(char **args, int argv){
	return;
}