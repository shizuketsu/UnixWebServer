#ifndef HTTP
#define HTTP

void send_res(int sd, const char* content, const char* content_type);
void handle_req(int sd, char* buffer);

#endif
