#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/select.h>
#include <sys/types.h>
#include <arpa/inet.h>
#define PORT 4000

int main(int argc, char const *argv[]){

	int server_fd, new_socket; 
	struct sockaddr_in client_addr;
	float res=0;
	int num[2];
	int addrlen = sizeof(client_addr);
	char msg;

	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){	//dhmiourgia socket
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
	
	client_addr.sin_family = AF_INET; // epikoinwnia se oloys toys H/Y
	client_addr.sin_addr.s_addr = INADDR_ANY; 
	client_addr.sin_port = htons(PORT);

	bind(server_fd, (struct sockaddr *)&client_addr, sizeof(client_addr)); //sundesh server kai client
	
	if (listen(server_fd, 10) < 0){ // proetoimazei ton server gia eperxomena aithmata twn clients
		perror("listen");
		exit(EXIT_FAILURE);
	}
	else{
		printf("Listening...");
	}
    printf("\nServer executing...\n");
	while(1){ // trexei gia panta
		if ((new_socket = accept(server_fd, (struct sockaddr *)&client_addr,(socklen_t*)&addrlen)) < 0) {
			perror("accept"); //dexetai enan enan tous clients kai tous 6phretei me th seira
			exit(EXIT_FAILURE);
		}
		//printf("test test\n"); //den douleyei 
		if(fork() != 0){ //parent
		
			while(1){ // 6piretei pollous clients tautoxrona 				
				recvfrom(new_socket, num, sizeof(num), 0,(struct sockaddr *)&client_addr, &addrlen); // dexomaste ta 2 orismata ths prakshs
				recvfrom(new_socket, &msg, 25, 0,(struct sockaddr *)&client_addr, &addrlen); //dexomaste thn praksh

				if( msg == '+'){ //upologizw thn praksh
					res = num[0] + num[1];
				}
				else if( msg == '-'){
					res = num[0] - num[1];
				}
				else if( msg == '*'){
					res = num[0] * num[1];
				}
				else if( msg == '/'){
					if(num[1] != 0){ // elegxos gia diairesh me mhden
						res =(float) num[0] / num[1]; // type-casting apo int se float gia to apotelesma
					}
					else{
						res = 0;
					}
				}			
				sendto(new_socket, &res , 4, 0, (struct sockaddr *)&client_addr, sizeof(client_addr)); //stelnw ston client to apotelesma
			}
		}
	}

	return 0;
}