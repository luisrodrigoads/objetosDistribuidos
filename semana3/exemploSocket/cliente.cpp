#include <windows.h>
#include <winsock.h>
#include <stdio.h>
#include <string.h>

#define REMOTE_SERVER_PORT 2018
#define MAX_MSG 100
#define SERVIDOR "127.0.0.1"


int main() {
  
  int sd, rc, i;
  struct sockaddr_in cliAddr, remoteServAddr;
  WSADATA wsaData;
  LPHOSTENT lpHostEntry; 
  char mensagem[20];
   
  WSAStartup(MAKEWORD(2,1),&wsaData);

  lpHostEntry = gethostbyname(SERVIDOR);
  
  /* cira??o do socket */
  sd = socket(AF_INET,SOCK_DGRAM,0);
  
  if(sd<0) {
    printf("Nao foi possivel criar o socket com o servidor %s:\n",SERVIDOR);
    exit(1);
  }

  /* bind */
  cliAddr.sin_family = AF_INET;
  cliAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  cliAddr.sin_port = htons(0);
  
  remoteServAddr.sin_family = AF_INET;
  remoteServAddr.sin_addr = *((LPIN_ADDR)*lpHostEntry->h_addr_list);
										
  remoteServAddr.sin_port = htons(REMOTE_SERVER_PORT);	


  int fim = 10000000;
  
  for(i=1;i<fim;i++) {
      
   sprintf(mensagem,"Enviando mensagem Nro: %d",i);
   system("pause");
  
   rc = sendto(sd, mensagem, strlen(mensagem)+1, 0,(LPSOCKADDR) &remoteServAddr, sizeof(struct sockaddr));
  	if(rc<0) {
	  printf("%s: Nao foi possivel enviar valor %d \n",i,i-1);
      closesocket(sd);
      exit(1);
    }
  }
  closesocket(sd);
  return 1;

}
