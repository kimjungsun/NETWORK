#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include<string.h>
void error_handling(char *message);

int main(int argc, char *argv[])
{
	int sock,sock2;
	struct sockaddr_in serv_addr,serv_addr2;
	char c_message[10], c_message2[10];
	char message[20] = " Well transported!";
	int str_len, str_len2;
	if (argc != 3)
	{
		printf("7.16 / local 각 port 2개 입력해주세용 \n");
		exit(1);
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("192.168.7.16");
	serv_addr.sin_port = htons(atoi(argv[1]));

	memset(&serv_addr2, 0, sizeof(serv_addr2));
	serv_addr2.sin_family = AF_INET;
	serv_addr2.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_addr2.sin_port = htons(atoi(argv[2]));


      for(int i = 0 ; i<10; i++){

	sock = socket(PF_INET, SOCK_STREAM, 0); //소켓을 생성하고 있다.
	sock2 = socket(PF_INET, SOCK_STREAM, 0); //소켓을 생성하고 있다.
	
	if (sock == -1 || sock2 == -1)
		error_handling("socket() error");

	if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
		error_handling("connect() error");
	if (connect(sock2, (struct sockaddr*)&serv_addr2, sizeof(serv_addr2)) == -1)
		error_handling("connect() error");

	str_len = read(sock,c_message, sizeof(c_message) - 1);
	str_len2 = read(sock2,c_message2, sizeof(c_message2) - 1);
	if (str_len == -1)
		error_handling("read()--1 error");
	if (str_len2 == -1)
		error_handling("read()--2 error");
        write(sock,message,sizeof(message));
	strcat(c_message, c_message2);
	printf("Message from both server:%s\n", c_message);
	printf("Message from local server:%s\n", c_message2);
close(sock);
close(sock2);
}	

	return 0;

}



void error_handling(char *message)

{

	fputs(message, stderr);

	fputc('\n', stderr);

	exit(1);

}
