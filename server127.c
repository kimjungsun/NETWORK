 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>


void error_handling(char *message);
int main(int argc, char *argv[])
{
    char message[20] = "Hello ";
	int sock;
	int clnt_sock;

	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
        int clnt_addr_size = sizeof(clnt_addr);
	int str_len;

	if (argc != 2)
	{
		printf("port 입력해주세요 \n");
		exit(1);
	}
	sock = socket(PF_INET, SOCK_STREAM, 0); //소켓을 생성하고 있다.
	if (sock== -1)
		error_handling("socket() error");
	

	memset(&serv_addr, 0, sizeof(serv_addr));
	

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));


    if(bind(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1){
        printf("bind error\n"); 
        exit(1);
         }
   
       
             listen(sock,5);
     for(int i = 0; i<10;i++){

        if((clnt_sock = accept(sock,(struct sockaddr*)&clnt_addr,&clnt_addr_size))<0)      
            error_handling("accept error");
         write(clnt_sock,message,sizeof(message));
        
        close(clnt_sock);
	}



	close(sock);



	return 0 ; 
}
  

void error_handling(char *message)
{

	fputs(message, stderr);

	fputc('\n', stderr);

	exit(1);

}
