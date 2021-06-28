#include <windows.h>
#include <winsock.h>
#include <stdio.h>

#define LOCAL_SERVER_PORT 2018
#define MSG_LENGTH 4096

int main(int argc, char *argv[]) {
  
  int sd, bindSocket, msgReceiveFromClient, msgSendToClient;
  struct sockaddr_in clientAddress; // estrutura do endereço do cliente
  struct sockaddr_in serverAddress; // estrutura do endereço do servidor
  char msg[MSG_LENGTH];
  WSADATA wsaData;
	
  WSAStartup(MAKEWORD(2,1),&wsaData);// Inicia o winsock
  
  /*
  Inicia socket...
  padrão -> (familia protocolo, tipo, protocolo)
  AF_INET -> familia ipv4
  SOCK_DGRAM -> comunicação udp
  */
  sd = socket(AF_INET, SOCK_DGRAM, 0);
 
  if(sd < 0) {
    printf("%s: Nao foi possivel abrir o socket \n",argv[0]);
    exit(1);
  }

  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = htonl(INADDR_ANY); 
  serverAddress.sin_port = htons(LOCAL_SERVER_PORT); 
  
  /* bind (associação do socket a uma porta) */
  bindSocket = bind (sd, (struct sockaddr *) &serverAddress, sizeof(serverAddress));
  
  if(bindSocket < 0) {
    printf("%s: nao foi possivel associar a porta %d \n", argv[0], LOCAL_SERVER_PORT);
    exit(1);
  }

  printf("%s: Aguardando mensagens na porta UDP %u\n", argv[0],LOCAL_SERVER_PORT);

  while(1) {
    memset(msg, 0x0, MSG_LENGTH);
    int clientLength = sizeof(clientAddress);
    msgReceiveFromClient = recvfrom(sd, msg, MSG_LENGTH, 0, (struct sockaddr *) &clientAddress, &clientLength);
    
    if(msgReceiveFromClient < 0){
    	printf("%s: nao foi possivel receber dados \n",argv[0]);
      	continue;
	} 
	
	printf("%s:Recebido de %s:UDP Porta: %u a msg: %s \n", argv[0],inet_ntoa(clientAddress.sin_addr), ntohs(clientAddress.sin_port),msg);
	for(int x = 0; x < strlen(msg); x++)
		msg[x] = toupper(msg[x]);
    
	msgSendToClient = sendto(sd, msg, strlen(msg), 0,(LPSOCKADDR) &clientAddress, sizeof(struct sockaddr));
	if(msgSendToClient < 0){
		printf("Erro ao enviar a mensagem\n");
		closesocket(sd);
		exit(1);
	}
  }

 closesocket(sd);
 WSACleanup();
 return 0;
}

