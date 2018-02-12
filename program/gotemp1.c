#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

typedef struct
{
    char* morse;
    char* ascii;
} morse_table_t;

void append(char* s, char c)
{
        int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
}

int main()
{
   morse_table_t table[] = {      {".|","A"},
				    {"|...","B"},
				    {"|.|.","C"},
				    {"|..","D"},
				    {".","E"},
				    {"..|.","F"},
				    {"||.","G"},
				    {"....","H"},
				    {"..","I"},
				    {".|||","J"},
				    {"|.|","K"},
				    {".|..","L"},
				    {"||","M"},
				    {"|.","N"},
				    {"|||","O"},
				    {".||.","P"},
				    {"||.|","Q"},
				    {".|.","R"},
				    {"...","S"},
				    {"|","T"},
				    {"..|","U"},
				    {"...|","V"},
				    {".||","W"},
				    {"|..|","X"},
				    {"|.||","Y"},
				    {"||..","Z"},
				    {"......"," "},
				    {"|||||","0"},
				    {".||||","1"},
				    {"..|||","2"},
				    {"...||","3"},
				    {"....|","4"},
				    {".....","5"},
				    {"|....","6"},
				    {"||...","7"},
				    {"|||..","8"},
				    {"||||.","9"},
    };
    int uiofd;
    int configfd;
    int err;
    char buffervalue [1];
    char *s;
    s = (unsigned char *) malloc(500);
    unsigned char *final;
    final = (unsigned char *) malloc(30);
    int i;
    int j;
    unsigned char *buffer;
    buffer = (unsigned char *) malloc(100);
    uiofd = open("/dev/gotemp0", O_RDONLY);
    if (uiofd < 0) {
        perror("gotemp open:");
        return errno;
    }

    for(i = 0;; ++i) { 
        if (i == 0)
	{
        	fprintf(stderr, "Started gotemp driver. Your input:\n");
	}
        err = read(uiofd, buffer, 8);
	sprintf(buffervalue,"%X",buffer[0]);
	switch ( buffervalue[0]) {
		case '0':
		  buffervalue[0] = 'n';
		  break;
		case '1':
		  buffervalue[0] = '.';
		  break;
		case '2':
		  buffervalue[0] = '|';
		  break;
		case '4':
		  buffervalue[0] = ' ';
		  break;
		};

        if (buffervalue[0] != 'n'){
		printf("%c\n",buffervalue[0]);

		if(buffervalue[0] == '|')
		  {
		    append(final, '|');
	 	    //printf("Adding to final. SIZE: %s\n", final);
		  }
	
		if(buffervalue[0] == ' ' || buffervalue[0] == '.')
		  {
		   // printf("Deleting from final!\n");
		    memset(final,0,sizeof(final));
		  }

		if (strlen(final) == 6) 
		  {
		    //printf("Done\n");
		    append(s,buffervalue[0]);
		    append(s,' ');
		    break;
		  }
		append(s,buffervalue[0]);
	}
    }

    char* segment;
    segment = strtok(s, " ");
    while(segment)
    {
        for(i = 0; i<sizeof(table)/sizeof(table[0]); ++i)
        {
            if (!strcmp(segment, table[i].morse)) printf("%s",table    			[i].ascii);
        }
        segment = strtok(NULL, " ");
    }
    
    printf("\n");

    return errno;
}
