#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <stdbool.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#define BUFFER_SIZE 1024

#define SERVER_FAMILY AF_INET
#define SERVER_PORT 4567
#define SERVER_ADDR INADDR_ANY

void config_server(SOCKADDR_IN *addr_server)
{
    addr_server->sin_family = SERVER_FAMILY;
    addr_server->sin_port = htons(SERVER_PORT);
    //addr_server->sin_addr.S_un.S_addr = SERVER_ADDR;
    addr_server->sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
}

int main(int argc, char *argv[]) {
	
	WSADATA WSAData;
	char receBuf[BUFFER_SIZE];
    char Response[BUFFER_SIZE];
    int r_sento = 0;
    
    printf("Server start\n");
    
    if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0){
        printf("init error\n");
        exit(1);
    }
    SOCKET sockServer = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);//AF_INET = IPv4;SOCK_STREAM=¦³§Ç; 
    if (sockServer == INVALID_SOCKET){
        printf("Failed socket() \n");
        return 0;
    }
    
    SOCKADDR_IN addr_Server;
    config_server(&addr_Server);
    if (bind(sockServer, (SOCKADDR *)&addr_Server, sizeof(addr_Server)) == SOCKET_ERROR){ 
        printf("Failed socket() %d \n", WSAGetLastError());
        return 0;
    }
    
    SOCKADDR_IN addr_Clt;
    int fromlen = sizeof(addr_Clt);
    while (true){
        int last = recvfrom(sockServer, receBuf, sizeof(receBuf), 0, (SOCKADDR *)&addr_Clt, &fromlen);
        printf("-------------------------\n");
        printf("last:%d\n", last);
        if (last > 0){                         
            receBuf[last] = '\0'; 
            if (strcmp(receBuf, "bye") == 0){
                printf("client disconnect...\n");
                printf("Response client data:%s\n", receBuf);
        		r_sento = sendto(sockServer, receBuf, strlen(receBuf), 0, (SOCKADDR *)&addr_Clt, sizeof(SOCKADDR));
                closesocket(sockServer);
                system("pause");
                return 0;
            }
            else{
                printf("receive data(%s):%s\n", inet_ntoa(addr_Clt.sin_addr), receBuf);
            }
        }
        
        printf("Response client data:%s\n", receBuf);
        r_sento = sendto(sockServer, receBuf, strlen(receBuf), 0, (SOCKADDR *)&addr_Clt, sizeof(SOCKADDR));
        printf("return :%d\n", r_sento);
        printf("-------------------------\n");
    }
    
    closesocket(sockServer);

    WSACleanup();
    
	system("pause");
	return 0;
}
