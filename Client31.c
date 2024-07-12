#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>

#define PORT 4321
#define SIZE 9 //pthseis

void InitA(int A[5][4]);
void changeA(int A[5][4]);

int main(int argc, char *argv[]){

	int clientSocket, A[5][4], seats, id;
	struct sockaddr_in serverAddr;
    float price;

	clientSocket = socket(AF_INET, SOCK_STREAM, 0); //anoigma socket
	if(clientSocket < 0){
		printf("Error in connection.\n");
		exit(1);
	}
	printf("Client Socket is created.\n");

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = INADDR_ANY;

	if(connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0){ //sundew client & server
		printf("Error in connection.\n");
		exit(1);
	}
	printf("Connected to Server.\n");
    
    InitA(A); //arxikopoihsh tou A me -1(opou -1 kamia pthsh)
    changeA(A); //gemisma A 
    send(clientSocket, A, sizeof(A), 0);//stelnw ton A gemato

    for(int i = 0; i < 5; i++){ //5 pelates
        
        printf("\n \033[32;1m Client %d \033[0m\n", i+1); // Emfanish noumero client, 32 = prasino
        printf("Arithmos Eishthriwn    Pthsh           Pthsh            Pthsh \n");
        for(int j = 0; j <4; j++){ //emfanish krathshs tou pelath
            printf(" \t %d \t ", A[i][j]);
        }

        printf("\n \033[31;1m System \033[0m\n");

        if(A[i][0] == 1){ //1 eishthrio
            recv(clientSocket, &seats, sizeof(seats), 0); //pairnoume arithmo eishthriwn
            printf("Available seats %d\n", seats);
            recv(clientSocket, &id, sizeof(id), 0); //pairnoume id pthshs
            if(seats>0){ //an uparxoun diathesimes theseis
                recv(clientSocket, &price , sizeof(price), 0); //pairnw thn timh kai thn emfanizw
                printf("Current ticket price: %.2f \n", price);
                printf("Successful booking tickets for flight %d\n", id);
            }
            else{
                recv(clientSocket, &price , sizeof(price), 0); //thn lamvanw gia na exei kapou na to steilei o server se periptwsh pou den uparxoun alles theseis 
                printf("Unsuccessful booking tickets for flight %d\n", id);
            }
        }
        if(A[i][0] == 2){ //2 eishthria
            recv(clientSocket, &seats, sizeof(seats), 0);
            printf("Available seats %d\n", seats);
            recv(clientSocket, &id, sizeof(id), 0);

            if(seats>0){
                recv(clientSocket, &price , sizeof(price), 0);
                printf("Current ticket price: %.2f \n", price);
                printf("Successful booking tickets for flight %d\n", id);
            }
            else{
                recv(clientSocket, &price , sizeof(price), 0);
                printf("Unsuccessful booking tickets for flight %d\n", id);
            }
            recv(clientSocket, &seats, sizeof(seats), 0);
            printf("Available seats %d\n", seats);
            recv(clientSocket, &id, sizeof(id), 0);
            if(seats>0){
                recv(clientSocket, &price , sizeof(price), 0);
                printf("Current ticket price: %.2f \n", price);
                printf("Successful booking tickets for flight %d\n", id);
            }
            else{
                recv(clientSocket, &price , sizeof(price), 0);
                printf("Unsuccessful booking tickets for flight %d\n", id);
            }
        }
        if(A[i][0] == 3){ //3 eishthria
            recv(clientSocket, &seats, sizeof(seats), 0);
            printf("Available seats %d\n", seats);
            recv(clientSocket, &id, sizeof(id), 0);

            if(seats>0){
                recv(clientSocket, &price , sizeof(price), 0);
                printf("Current ticket price: %.2f \n", price);
                printf("Successful booking tickets for flight %d\n", id);
            }
            else{
                recv(clientSocket, &price , sizeof(price), 0);
                printf("Unsuccessful booking tickets for flight %d\n", id);
            }
            recv(clientSocket, &seats, sizeof(seats), 0);
            printf("Available seats %d\n", seats);
            recv(clientSocket, &id, sizeof(id), 0);
            
            if(seats>0){
                recv(clientSocket, &price , sizeof(price), 0);
                printf("Current ticket price: %.2f \n", price);
                printf("Successful booking tickets for flight %d\n", id);
            }
            else{
                recv(clientSocket, &price , sizeof(price), 0);
                printf("Unsuccessful booking tickets for flight %d\n", id);
            }
            recv(clientSocket, &seats, sizeof(seats), 0);
            printf("Available seats %d\n", seats);
            recv(clientSocket, &id, sizeof(id), 0);
            if(seats>0){
                recv(clientSocket, &price , sizeof(price), 0);
                printf("Current ticket price: %.2f \n", price);
                printf("Successful booking tickets for flight %d\n", id);
            }
            else{
                recv(clientSocket, &price , sizeof(price), 0);
                printf("Unsuccessful booking tickets for flight %d\n", id);
            }
        }
        sleep(1);
    }

	return 0;
}

void InitA(int A[5][4]){ //arxikopoihsh pinaka A

    for(int i=0;i<5;i++){ //arxikopoihsh me -1
        for(int j=0; j<4; j++){
            A[i][j] = -1;
        }
    }
}

void changeA(int A[5][4]){ //gemisma pinaka A
    srand(time(0)); //arxikopoihsh rologiou vash wra ekteleshs
    for(int i = 0; i < 5;i++){ // 5 pelates

        int random=0, random2=0; // random2 = id pthshs , random = arithmos eishthriwn pelath

        random = (rand() %3) + 1;             //dinei orisma apo 1 mexri 3 (eishthria)
        A[i][0] = random; //gemisma 1hs sthlhs me arithmo eishthriwn

        if(random == 1){                    //arithmos eishthriwn = 1
            random2 = rand() %SIZE ;         //vriskei arithmo pthshs 0-9 
            A[i][1] = random2;

        }
        else if(random == 2){
            random2 = rand() %SIZE;
            A[i][1] = random2;
            random2 = rand()%SIZE;
            A[i][2] = random2;
        }
        else if(random == 3){
            random2 = rand() %SIZE;
            A[i][1] = random2;
            random2 = rand()%SIZE;
            A[i][2] = random2;
            random2 = rand() %SIZE;
            A[i][3] = random2;
        }
    }
}