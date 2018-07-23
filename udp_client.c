#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
int main(int argc,char* argv[])
{
	int sock = socket(AF_INET,SOCK_DGRAM,0);
	if(sock<0){
		perror("socket");
		return 2;
	}
	struct sockaddr_in server;
	server.sin_port = htons(atoi(argv[2]));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(argv[1]);
	//客户端不需要绑定端口号
	char buf[1024];
	struct sockaddr_in peer;
	while(1)
	{
		socklen_t len = sizeof(peer);
		printf("please Enter#:");
		fflush(stdout);
		ssize_t _s = read(0,buf,sizeof(buf)-1);

		if(_s>0)
		{
			buf[_s-1] = 0;
			sendto(sock,buf,strlen(buf),0,(struct sockaddr*)&server,sizeof(server));
			ssize_t s = recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&peer,&len);
			if(s>0)
			{
				buf[s] = 0;
				printf("server echo#:%s\n",buf);
			}
		}
	}
	return 0;
}

