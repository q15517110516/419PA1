#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h> 
#include <arpa/inet.h> 
#define PORT 4321  // server port 
#define BUFFER_SIZE 1024
#define MAX_SIZE 512

int main(int argc, char **argv) {
	if (argc != 2) {
		printf("Usage: %s <IP Address>\n", argv[0]);
		exit(1);
	}
	int clientsocket;
	int con;
	int write_len;
	int bindss;
	struct sockaddr_in client_addr; // set a socket address structure, representing the client's internet address and port 
	bzero(&client_addr, sizeof(client_addr));
	client_addr.sin_family = AF_INET; //ipv4
	client_addr.sin_addr.s_addr = htons(INADDR_ANY);
	client_addr.sin_port = htons(0);

	clientsocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientsocket == -1) {
		printf("Fail to create socket.\n");
		exit(1);
	}
	else {
		printf("Create socket succeeded.\n");
	}

	//bind the socket and socket address structure
	bindss = bind(clientsocket, (struct sockaddr*)&client_addr, sizeof(client_addr));
	if (bindss) {
		printf("Server Bind Port: %d Failed!\n", PORT);
		exit(1);

	}
	else {
		printf("Server bind port:[%d]\n", PORT);
	}

	struct sockaddr_in server_addr;// set a socket address structure, representing the server's internet address and port
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	//send connection request to the server
	con = connect(clientsocket, (struct sockaddr*)&server_addr, (socklen_t)sizeof(server_addr));
	if (con == -1) {
		printf("Connection with %s failed.\n", argv[1]);
		exit(1);
	}
	else {
		printf("Connection succeeded.\n");

	}

	char filename[MAX_SIZE + 1];
	bzero(filename, sizeof(filename));
	printf("Input file name:\n");
	scanf("%s", filename);

	char buff[BUFFER_SIZE];
	bzero(buff, sizeof(buff));
	strncpy(buff, filename, strlen(filename) > BUFFER_SIZE ? BUFFER_SIZE : strlen(filename));
	send(clientsocket, buff, BUFFER_SIZE, 0); // send the file name to the server

	FILE *fp = fopen(filename, "w");
	if (fp == NULL) {
		printf("File cannot open.\n");
		exit(1);
	}

	//receive data from the server to the buffer
	bzero(buff, sizeof(buff));
	int len = recv(clientsocket, buff, BUFFER_SIZE, 0);

	while (len) {
		if (len < 0) {
			printf("Fail to receive data.\n");
			break;
		}
		if (write_len < len){
			printf("Fail to write file.\n");
			break;
		}
		bzero(buff, BUFFER_SIZE);
			   		 	  
	}
	printf("Finish receiving file from the server.\n");

	//close socket
	fclose(fp);
	close(clientsocket);
	return 0;
}



