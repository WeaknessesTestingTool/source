#include <stdlib.h>
#include <stdio.h>

void manipulate_error(char *errorLog){//char* string){
	char buf[125];

	strcat(buf,"Error occurred on");
	strcat(buf,":");
	strcat(buf,errorLog);

	printf("%s", buf);
}