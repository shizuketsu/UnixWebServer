#include <stdio.h> // information output
#include <stdlib.h> // standard library
#include <sys/socket.h> // defining and using sockets
#include <sys/types.h> // some constansts
#include <arpa/inet.h> // some functions for data conversion
#include <string.h> // functions for strings
#include <unistd.h> // close
#include "./utils/getFilename.c" // function for getting filename from HTTP req
#include "./utils/getResource.c" // function for getting resource from filename
#include "./headers/server.h" // function headers of this project
#include "./headers/headers.h" // headers responses

int main(int argc, char** argv)
{
    printf("Server was started at port %d\n", PORT);

	// creating server socket descriptor
    int ssd = socket(AF_INET, SOCK_STREAM, 0);
    if(ssd == -1)
    {
        perror("Failed to create ssd");
        return 1;
    }

    struct sockaddr_in s_addr;
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(PORT);
    s_addr.sin_addr.s_addr = INADDR_ANY;

    if(bind(ssd, (struct sockaddr*)&s_addr, sizeof(s_addr)))
    {
        perror("Failed to bind ssd");
        return 1;
    }

    // start listen server socket
    if(listen(ssd, MAX_LISTENERS))
    {
        perror("Failed to listen ssd");
        return 1;
    }

    // creating client socket descriptor
    int csd;
    // creating buffer for temporary storage of client data
    char buffer[BUFFER_SIZE];
    // number of bytes received or sent when working with sockets
    ssize_t rec_byte;

    while(1)
    {
        // creating client socket descriptor
        int csd;
        char buffer[BUFFER_SIZE];
        ssize_t rec_byte;
        struct sockaddr_in c_addr;
        socklen_t c_addr_size = sizeof(c_addr);

        // Initialization client server socket
        csd = accept(ssd, (struct sockaddr*)&c_addr, &c_addr_size);
        if(csd == -1)
        {
            perror("Failed to create csd");
            continue;
        }

        memset(buffer, 0, BUFFER_SIZE);

        while(1)
        {
            rec_byte = recv(csd, buffer, BUFFER_SIZE - 1, 0);
            
            if(rec_byte > 0)
			{
                buffer[rec_byte] = '\0';
                handle_req(csd, buffer);
            }
            
            if(rec_byte < 0)
            {
                perror("Failed to receive data");
                break;
            }

            if(rec_byte == 0)
            {
                break; // Connection closed by client
            }
        }

        close(csd);
    }

    close(ssd);
    return 0;
}

// sd is socket descriptor
void handle_req(int sd, char* buffer)
{
	if(sd < 0 || buffer == NULL)
	{
		perror("sd or buffer in handle_req() is undefined");
		return;
	}

	if(strncmp(buffer, "GET ", 4) == 0)
	{
		printf("%s\n", buffer);
		char* filename = getFilename(sd, buffer);
		printf("filename is %s\n", filename);
		char* res = getResource(filename);
		free(filename);
		if(res == NULL)
		{
			send(sd, HEADERS_400, strlen(HEADERS_400), 0);
			return;
		}

		send_res(sd, res, "text/html");
		free(res);
	}

	else
	{
		send(sd, HEADERS_400, strlen(HEADERS_400), 0);
	}
}

// sd is socket descriptor
void send_res(int sd, const char* content, const char* content_type)
{
	char res[BUFFER_SIZE];
	snprintf(res, sizeof(res),
		"HTTP/1.1 200 OK\r\n"
		"Content-Type: %s\r\n"
		"Content-Length: %ld\r\n"
		"Connection: close\r\n"
		"\r\n",
	content_type, strlen(content));

	// sending data
	send(sd, res, strlen(res), 0);
	send(sd, content, strlen(content), 0);
}