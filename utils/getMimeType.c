#include <string.h> // functions for strings
#include <stdlib.h> // standard library

char* getMimeType(char* filename)
{
    char* extension = strrchr(filename, '.');
    if (extension == NULL) return "application/octet-stream"; // Default MIME type

    if (strcmp(extension, ".html") == 0 || strcmp(extension, ".htm") == 0) return "text/html";
    else if (strcmp(extension, ".css") == 0) return "text/css";
    else if (strcmp(extension, ".js") == 0) return "text/javascript";
    else if (strcmp(extension, ".jpg") == 0 || strcmp(extension, ".jpeg") == 0) return "image/jpeg";
    else if (strcmp(extension, ".png") == 0) return "image/png";
    else if(strcmp(extension, ".gif") == 0) return "image/gif";
    else if (strcmp(extension, ".ico") == 0) return "image/x-icon";
    else if (strcmp(extension, ".woff") == 0) return "font/woff";
    else if (strcmp(extension, ".woff2") == 0) return "font/woff2";
    else if (strcmp(extension, ".ttf") == 0) return "font/ttf";
    else return "application/octet-stream"; // Default MIME type
}