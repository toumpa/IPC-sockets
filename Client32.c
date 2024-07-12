#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 4000

int main(int argc, char const *argv[])
{
	int socket_fd;
	float res;
	struct sockaddr_in server_addr;
	char msg[20] = {"continue"}; // gia na ektelestei h while thn 1h fora 
	char c;
	int num[2];
	int addrlen = sizeof(server_addr);

	if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){ //dhmiourgw to socket
		printf("\n Socket creation error \n");
		return -1;
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	
	if(inet_aton(argv[1], &server_addr.sin_addr) == 0){
		printf("\nInvalid address/Address not supported \n");
		return -1;
	}

	if (connect(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){ //syndeei server/client
		printf("\nConnection Failed \n");
		return -1;
	}
	printf("Connected to server\n");

	while(strcmp(msg, "continue")==0 && strcmp(msg, "exit")!=0){ //oso msg = continue kai != exit tote dwse pali praksh
	
		c = ' '; //character gia sumvolo prakshs
		num[0] = 0;
		num[1] = 0;

		printf("Give a math expression\n");
		scanf("%d", &num[0]);	
		scanf(" %c", &c);
		scanf("%d", &num[1]);
		
		//stelnw ta orismata ths prakshs kai lamvanw to apotelesma apo ton server 
		sendto(socket_fd, num, sizeof(num),  0, (struct sockaddr *)&server_addr, sizeof(server_addr));
		sendto(socket_fd, &c , sizeof(c), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
		recvfrom(socket_fd, &res, 25, 0,(struct sockaddr *)&server_addr, &addrlen);
		
		if((c == '/' && res == 0 && num[0] != 0) || (c != '+' && c != '-' && c != '*' && c != '/')){ //elegxos gia antikanoniko termatismo tou programmatos (diairesh me 0)
			printf("wrong math expression\n");
		}
		else{ //emfanizw apotelesma afou to exw parei apo ton server
			printf("\n%d", num[0]);
			printf(" %c", c);
			printf(" %d", num[1]);
			printf(" = %.2f\n", res);
		}
		do{ // exit or continue
			printf("\nPlease type 'continue' if you want to give another math expression or type 'exit'\n");
			scanf("%s", msg);
		}while(strcmp(msg, "continue")!=0 && strcmp(msg, "exit")!=0);
		
	}
	printf("Client exits\n");
	
	return 0;
}