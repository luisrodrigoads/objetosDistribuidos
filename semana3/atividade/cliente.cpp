#include <windows.h>
#include <winsock.h>
#include <stdio.h>
#include <string.h>

#define REMOTE_SERVER_PORT 2018
#define MSG_LENGTH 4096
#define SERVIDOR "127.0.0.1"

FILE *fileSendTo, *fileReceiveFrom;

int main() {
  
  int sd, msgReceiveFromServer, msgSendToServer, serverLength;
  struct sockaddr_in clientAddress; 
  struct sockaddr_in remoteServerAddress;
  WSADATA wsaData;
  LPHOSTENT lpHostEntry; 
  char msg[MSG_LENGTH];

  WSAStartup(MAKEWORD(2,1),&wsaData); // inicia o winsock

  lpHostEntry = gethostbyname(SERVIDOR);
  /*
  Inicia socket...
  padrão -> (familia protocolo, tipo, protocolo)
  AF_INET -> familia ipv4
  SOCK_DGRAM -> comunicação udp
  */
  sd = socket(AF_INET,SOCK_DGRAM,0);
  
  if(sd < 0) {
    printf("Nao foi possivel criar o socket com o servidor %s:\n",SERVIDOR);
    exit(1);
  }

  /* bind (associação do socket a uma porta) */
  clientAddress.sin_family = AF_INET;
  clientAddress.sin_addr.s_addr = htonl(INADDR_ANY);
  clientAddress.sin_port = htons(0);
  
  remoteServerAddress.sin_family = AF_INET; 
  remoteServerAddress.sin_addr = *((LPIN_ADDR)*lpHostEntry->h_addr_list);
  remoteServerAddress.sin_port = htons(REMOTE_SERVER_PORT);
  
  if((fileSendTo = fopen("Arquivo.txt","r+")) == NULL){
  	printf("Erro ao abrir Arquivo.txt!");
  }else{
  	fileReceiveFrom = fopen("ArquivoRetorno.txt","w+");
  	while(!feof(fileSendTo)){
  		fgets(msg, MSG_LENGTH, fileSendTo);
  		
  		msgSendToServer = sendto(sd, msg, strlen(msg) + 1, 0, (LPSOCKADDR) &remoteServerAddress, sizeof(struct sockaddr));
  		if(msgSendToServer < 0){
  			printf("Erro ao enviar a mensagem\n");
			closesocket(sd);
			exit(1);	
		}
		printf("Mensagem enviada do cliente para o servidor ->\n %s\n", msg);
		
		memset(msg, 0, strlen(msg));
		serverLength = sizeof(remoteServerAddress);
		msgReceiveFromServer = recvfrom(sd, msg, MSG_LENGTH, 0, (struct sockaddr *) &remoteServerAddress, &serverLength);
		if(msgReceiveFromServer < 0){
			printf("Erro ao receber dados\n");
			continue;
		}
		printf("Mensagem recebida do servidor ->\n %s\n",msg);
		fprintf(fileReceiveFrom, "%s", msg);
		memset(msg, 0, strlen(msg));
	  }
	  fclose(fileSendTo);
	  fclose(fileReceiveFrom);
  }
  system("pause");	
  closesocket(sd);
  return 1;
}
