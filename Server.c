#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h> 

#define PORT 4321  // server port 
#define BUFFER_SIZE 1024
#define MAX_SIZE 512
#define LISTEN_QUEUE 20

int main(int argc, char **argv[]) {
	
	int serversocket;
	int bindss;
	int lis;
	int new_serversocket;
	int len;
	int length;
	int send_file;
	char buff[BUFFER_SIZE];
	char filename[MAX_SIZE + 1];
	//set a socket address structure, representing the server's internet address and port
	struct sockaddr_in server_addr;
	bzero(&server_addr, sizeof(server_addr));
	//convert IP and PORT
	server_addr.sin_family = AF_INET; // ipv4
	server_addr.sin_addr.s_addr = htons(INADDR_ANY);
	server_addr.sin_port = htons(PORT);

	serversocket = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in client_addr;
	len = sizeof(client_addr);

	if (serversocket == -1) {
		printf("Fail to create socket.\n");
		exit(1);
	}
	else {
		printf("Create socket succeeded.\n");


	}

	//bind the socket and socket address structure
	bindss = bind(serversocket, (struct sockaddr *)&server_addr, (socklen_t)sizeof(server_addr));
	if (bindss) {
		printf("Server Bind Port: %d Failed!\n", PORT);
		exit(1);

	}
	else {
		printf("Server bind port:[%d]\n", PORT);
	}

	//the server start to provide service to the client
	while (1) {
		//will return a new socket used to communicate with the client connect to the server
		new_serversocket = accept(serversocket, (struct sockaddr*)&client_addr, (socklen_t*)(&len));
		if (new_serversocket <0) {
			printf("Fail to accept server.\n");
			break;
		}
		
		printf("Connected. client ip[%s]:port[%d]\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
		bzero(buff, sizeof(buff));
		if (recv(new_serversocket, buff, BUFFER_SIZE, 0) < 0) {
			printf("Fail to receive data.\n");
			break;
		}
		strncpy(filename, buff, strlen(buff) > MAX_SIZE ? MAX_SIZE : strlen(buff));

		FILE *fp = fopen(filename, "r");
		if (fp == NULL) {
			printf("File cannot open.\n");
		}
		else {
			bzero(buff, BUFFER_SIZE);
			length = fread(buff, sizeof(char), BUFFER_SIZE, fp);
			while (length > 0) {
				send_file = send(new_serversocket, buff, length, 0);
				if (send_file < 0) {
					printf("Fail to send file.\n");
					break;
				}
				bzero(buff, sizeof(buff));
			}
			fclose(fp);
			printf("Finish sending file.\n");
		}
		close(new_serversocket);
	}
	close(serversocket);
	return 0;



} 
