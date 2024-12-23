#ifndef SERVER
#define SERVER

#define PORT 3002
#define MAX_LISTENERS 10
#define BUFFER_SIZE 1024

void send_res(int sd, const char* content, const char* content_type);
void handle_req(int sd, char* buffer);

#endif
