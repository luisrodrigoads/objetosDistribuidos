#include <windows.h>
#include <winsock.h>
#include <stdio.h>

#define LOCAL_SERVER_PORT 2018
#define MAX_MSG 100

int main(int argc, char *argv[]) {
  
  int sd, rc, n, cliLen;
  struct sockaddr_in cliAddr, servAddr;
  char msg[MAX_MSG];

  WSADATA wsaData;
  WSAStartup(MAKEWORD(2,1),&wsaData);
  
  sd=socket(AF_INET, SOCK_DGRAM, 0);
 
  if(sd<0) {
    printf("%s: Nao foi possivel abrir o socket \n",argv[0]);
    exit(1);
  }

  servAddr.sin_family = AF_INET;
  servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servAddr.sin_port = htons(LOCAL_SERVER_PORT);
  rc = bind (sd, (struct sockaddr *) &servAddr,sizeof(servAddr));
  
  if(rc<0) {
    printf("%s: nao foi possivel associar a porta %d \n", 
	   argv[0], LOCAL_SERVER_PORT);
    exit(1);
  }

  printf("%s: Aguardando dados na porta UDP %u\n", argv[0],LOCAL_SERVER_PORT);

  while(1) {
    memset(msg,0x0,MAX_MSG);
    cliLen = sizeof(cliAddr);
    n = recvfrom(sd, msg, MAX_MSG, 0, (struct sockaddr *) &cliAddr, &cliLen);
    if(n<0) {
      printf("%s: nao foi possivel receber dados \n",argv[0]);
      continue;
    }
    printf("%s:Recebido de %s:UDP Porta: %u a msg: %s \n", argv[0],inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port),msg);
  }

 closesocket(sd);
 WSACleanup();
return 0;
}

