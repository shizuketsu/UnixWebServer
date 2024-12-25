#include <stdlib.h> // standard library
#include <stdio.h> // information output
#include <string.h> // functions for strings
#include "getMimeType.c" // function for getting mime type

typedef struct {
    char* data;
    size_t size;
    char* mime_type;
} resource_t;

// fn for read file and return its in response
resource_t* getResource(char* filename)
{
    resource_t* resource = (resource_t*)malloc(sizeof(resource_t));

    char* fullpath = (char*)malloc(strlen("./public/") + strlen(filename) + 1);
    if(fullpath == NULL)
    {
        perror("Failed to allocate memory for fullpath");
        free(fullpath);
        return NULL;
    }

    strcpy(fullpath, "./public/");
    strcat(fullpath, filename);

    FILE *file = fopen(fullpath, "r");
    if(file == NULL)
    {
        fprintf(stderr, "Failed to open file: %s\n", filename);
        fclose(file);
        return NULL;
    }

    free(fullpath); // free memory for fullpath

    // file size determination
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* data = (char*)malloc(file_size + 1);
    if(data == NULL)
    {
        perror("Failed to allocate memory for data resource");
        free(data);
        return NULL;
    }

    if(fread(data, 1, file_size, file) != file_size)
    {
        perror("Failed to read file");
        fclose(file);
        free(data);
        return NULL;
    }

    fclose(file);

    resource->data = data;
    resource->size = file_size;
    resource->mime_type = getMimeType(filename);

    return resource;
}

void freeResource(resource_t* resource)
{
    if(resource != NULL) 
    {
        free(resource->data);
    }
}