#include <stdlib.h> // standard library
#include <stdio.h> // information output
#include <string.h> // functions for strings

// fn for read file and return its in response
char* getResource(char* filename)
{
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
    free(fullpath); // free memory for fullpath
    if(file == NULL)
    {
        fprintf(stderr, "Failed to open file: %s\n", filename);
        fclose(file);
        return NULL;
    }

    // file size determination
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* resource = (char*)malloc(file_size + 1);
    if(resource == NULL)
    {
        perror("Failed to allocate memory for resource");
        free(resource);
        return NULL;
    }

    if(fread(resource, 1, file_size, file) != file_size)
    {
        perror("Failed to read file");
        fclose(file);
        free(resource);
        return NULL;
    }

    resource[file_size] = '\0';
    fclose(file);
    return resource;
}