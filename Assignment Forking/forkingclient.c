#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
void error_handling(char *message);
// ./server <IP> <port>
#define Buf_SIZE 1024
int main(int argc, char *argv[]){
	int sock;
	char message[Buf_SIZE];
	int str_len;
	struct sockaddr_in ser_adr;

	if (argc !=3){
		printf("Usage : %s <IP> <port>\n",argv[0]);
		exit(1);
	}
	// socket creation
	sock=socket(AF_INET,SOCK_STREAM, 0);
	if(sock==-1)
		error_handling("socket() error");
	memset(&ser_adr,0,sizeof(ser_adr));
	ser_adr.sin_family=AF_INET;
	ser_adr.sin_addr.s_addr=inet_addr(argv[1]);
	ser_adr.sin_port=htons(atoi(argv[2]));
	
	// connection
	
	if(connect(sock,(struct sockaddr*)&ser_adr,sizeof(ser_adr))==-1)
		error_handling("connection() error");
	else
		puts("contion is established....");
	//communication
	while(1)
	{
		fputs("Input message (Q to quit): ", stdout);
		fgets(message,Buf_SIZE,stdin);
		if(!strcmp(message,"q\n")||!strcmp(message,"Q\n"))
			break;
		write(sock,message,strlen(message));
		str_len=read(sock,message, Buf_SIZE-1);
		message[str_len]=0;
		printf("Message from the server : %s ",message);
	}
	close(sock);	
	return 0;
}
void error_handling(char*message){
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
	}
