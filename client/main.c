#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <stdbool.h>
#include <windows.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define BUFFER_SIZE 1024

#define SERVER_FAMILY AF_INET
#define SERVER_PORT 4567
#define SERVER_ADDR "127.0.0.1"

static char s_receBuf[BUFFER_SIZE];
static char s_sendBuf[BUFFER_SIZE];

void config_server(SOCKADDR_IN *addr_server)
{
    addr_server->sin_family = SERVER_FAMILY;
    addr_server->sin_port = htons(SERVER_PORT);
    addr_server->sin_addr.S_un.S_addr = inet_addr(SERVER_ADDR);
}

int main(int argc, char *argv[]) {
	
	SOCKET sock_Client; 
    WSADATA WSAData;
    int max_retry = 10;
    int i = 0;
    int last = 0;
    int check_status = -1;
	
	printf("Client start\n");
	
	if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0){
        printf("init error");
        return -1;
    } 
    
    sock_Client = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); 

    SOCKADDR_IN addr_server; 
    config_server(&addr_server);

    SOCKADDR_IN sock;
    int len = sizeof(sock);
    
    while (true){
    	printf("-----------------------\n");
        printf("please input send data:");
        scanf("%s", s_sendBuf);
        sendto(sock_Client, s_sendBuf, strlen(s_sendBuf), 0, (SOCKADDR *)&addr_server, sizeof(SOCKADDR));
        last = recvfrom(sock_Client, s_receBuf, sizeof(s_receBuf), 0, (SOCKADDR *)&sock, &len);
        printf("last:%d,%s\n", last, s_receBuf);
        if (last > 0){
            s_receBuf[last] = '\0'; 
            if (strcmp(s_receBuf, "bye") == 0){
            	printf("receive server data:%s\n", s_receBuf);
            	printf("exit code = 0\n");
                printf("server disconnect\n");
                check_status = 0;
                break;
            }else{
                printf("receive server data:%s\n", s_receBuf);
                printf("exit code = 0\n");
                check_status = 1;
            }
        }else{
        	for(i=0 ; i<max_retry ; i++){
        		printf("Retry to send data to server.\n");
        		printf("Retry time = %d\n",i+1);
        		sendto(sock_Client, s_sendBuf, strlen(s_sendBuf), 0, (SOCKADDR *)&addr_server, sizeof(SOCKADDR));
        		last = recvfrom(sock_Client, s_receBuf, sizeof(s_receBuf), 0, (SOCKADDR *)&sock, &len);
        		if (last > 0){
        			s_receBuf[last] = '\0'; 
        			if (strcmp(s_receBuf, "bye") == 0){
        				printf("receive server data:%s\n", s_receBuf);
        				printf("exit code = 0\n");
        				printf("server disconnect\n");
        				check_status = 0;
                		break;
					}else{
						printf("receive server data:%s\n", s_receBuf);
						printf("exit code = 0\n");
						check_status = 1;
						break;
					}
				}else{
					Sleep(500);
				}
				if(i == max_retry-1){
					printf("exit code = 1\n");
				}
			}
		}
		if(check_status == 0){
			break;
		}
    }

    closesocket(sock_Client);
    WSACleanup();
    
    system("pause");
	return 0;
}
