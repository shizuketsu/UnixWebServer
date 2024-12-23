#include <string.h> // functions for strings
#include <stdio.h> // information output
#include <stdlib.h> // standard library
#include <sys/socket.h> // defining and using sockets
#include "../headers/headers.h" // headers responses

char* getFilename(int sd, char* buffer)
{
	char* filename_start = strchr(buffer + 3, ' '); // indicate +3 to start searching after GET
	if(filename_start == NULL)
	{
		send(sd, HEADERS_400, strlen(HEADERS_400), 0);
		return NULL;
	}

	filename_start++; // move one character to the left to skip the space
	filename_start++; // move one character to the left to skip the slash

	char* filename_end = filename_start;
    	while (*filename_end != '\0' && *filename_end != ' ' && strncmp(filename_end, "\r\n", 2) != 0)
	{
        	filename_end++;
    	}

	int filename_length = filename_end - filename_start;
	char* filename = (char*)malloc(filename_length + 1);
	if(filename == NULL)
	{
		perror("Failed to allocate memory for filename");
		free(filename);
		return NULL;
	}

	strncpy(filename, filename_start, filename_length);
	filename[filename_length] = '\0';
	return filename;
}