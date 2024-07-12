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
#define SIZE 10

typedef struct Pthseis{
    int flight_id;
    char to_city[50];
    char from_city[50];
    int available_seats; //tyxaia
    float price;
}Pthseis;

void pthseis(Pthseis flights[SIZE]);
void seats(int server_fd, Pthseis flights[SIZE], int k, int Ep[SIZE], float *total,struct sockaddr_in client_addr);

int main(int argc, char *argv[]){

	int sockfd, A[5][4];
	struct sockaddr_in serverAddr;
	int newSocket, i;
	struct sockaddr_in newAddr;
	socklen_t addr_size;
	Pthseis flights[SIZE];

	sockfd = socket(AF_INET, SOCK_STREAM, 0); //dhmiourgia socket
	if(sockfd < 0){
		printf("Error in connection.\n");
		exit(1);
	}
	printf("Server Socket is created.\n");

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT); 
	serverAddr.sin_addr.s_addr = INADDR_ANY; 

	if(bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0){ //sundew server & client
		printf("Error in binding.\n");
		exit(1);
	}
	printf("Bind to port %d\n", PORT);

	if(listen(sockfd, 10) == 0){ //oura aithmatwn 10
		printf("Listening...\n");
	}else{
		printf("Error in listening.\n");
	}

	pthseis(flights); //dhmiourgia listas pthsewn

	while(1){ //gia panta
        //arxikopoihsh metavlhtwn kathe fora pou sundeomaste se neo client
        float total = 0; //sunolika kerdh
        int genplithos = 0; // sunolo krathsewn olwn twn pthsewn
        int genepituxeis = 0; // sunolo epithxhmenwn krathsewn 
        int Ep[SIZE] = {0,0,0,0,0,0,0,0,0}; // pinakas me arithmo apo epituxeis krathseis giak kathe pthsh
        int plithos[SIZE] = {0,0,0,0,0,0,0,0,0,0}; // pinakas me sunoliko arithmo krathsewn 

		newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size); //dexetai enan pelath kathe fora kai ton 6phretei
		if(newSocket < 0){
			exit(1);
		}
		printf("\033[35;1m Client connected from %s\033[0m\n", inet_ntoa(newAddr.sin_addr));

		recv(newSocket, A, sizeof(A), 0); //lamvanome ton pinaka A gemato 
		
        for(int i = 0; i < 5; i++){ //gia 5 pelates

            int k;
            if(A[i][0] == 1){ //an thelei na kleisei 1 eisitirio        
                k = A[i][1]; // k = id pthshs
                seats(newSocket, flights, k, Ep, &total, serverAddr);
            }
            else if(A[i][0] == 2){ //an thelei na kleisei 2 eisitiria

                k = A[i][1];
                seats(newSocket, flights, k, Ep, &total, serverAddr);
                k = A[i][2];
                seats(newSocket, flights, k, Ep, &total, serverAddr);
            }
            else if(A[i][0] == 3){ //an thelei na kleisei 3 eisitiria
                k = A[i][1];
                seats(newSocket, flights, k, Ep, &total, serverAddr);
                k = A[i][2];
                seats(newSocket, flights, k, Ep, &total, serverAddr);
                k = A[i][3];
                seats(newSocket, flights, k, Ep, &total, serverAddr);
            }
        }

        for(int i = 0; i < 5; i++){  // geniko plithos krathsewn
            for(int j = 1; j < 4; j++){ //apo 1 gt den theloume thn 1h sthlh
                if(A[i][j]== 0){               
                    plithos[0] = plithos[0] + 1;
                }
                else if(A[i][j]== 1){
                    plithos[1] = plithos[1] + 1;         
                }
                else if(A[i][j]==2){  
                    plithos[2] = plithos[2] + 1;
                }
                else if(A[i][j]== 3){
                    plithos[3] = plithos[3] + 1;         
                }
                else if(A[i][j]==4){  
                    plithos[4] = plithos[4] + 1;
                }
                else if(A[i][j]== 5){
                    plithos[5] = plithos[5] + 1;         
                }
                else if(A[i][j]==6){  
                    plithos[6] = plithos[6] + 1;
                }
                else if(A[i][j]== 7){
                    plithos[7] = plithos[7] + 1;         
                }
                else if(A[i][j]==8){  
                    
                    plithos[8] = plithos[8] + 1;
                }
                else if(A[i][j]==9){ // oxi else giati exoume kai -1
                    plithos[9] = plithos[9] + 1;
                }          
            }
        }
        sleep(6); //koimatai
        printf("\n \033[36;1m ~FINAL REPORT~ \033[0m\n");  //36 = galazio xrwma
        for(int i = 0; i < SIZE; i++){ //emfanizei plhrofories kathe pthshs
            printf("\n");
            printf(" From : %s \n", flights[i].from_city);
            printf(" To : %s \n", flights[i].to_city);
            printf("%d total requests for flight %d \n", plithos[i], i);
            genplithos = genplithos + plithos[i];
            printf("%d successful requests \n", Ep[i]);
            genepituxeis = genepituxeis + Ep[i];
            int anepitixis = (plithos[i] - Ep[i]);
            printf("%d unsuccessful requests \n", anepitixis);
        }
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("\nTotal count of requests : %d\n", genplithos); //sygkentrwtiko mhnyma
        printf("Total successful requests : %d\n", genepituxeis);
        printf("Total earnings : €%.2f \n", total);
        printf("\033[35;1m Client disconnected from server.\033[0m\n"); //aposundesh pelath
	}
	close(newSocket); //diakoph ths epikoinwnias kai anoigma pali sthn accept!

	return 0;
}

void seats(int server_fd, Pthseis flights[SIZE], int k, int Ep[SIZE], float *total,struct sockaddr_in client_addr){//theeseis
    int p = flights[k].available_seats;
    if (p > 0){ //an uparxoun diathesimes pthseis mpainei sthn if     
        send(server_fd, &p, 4, 0); //stelnw tis diathesimes theseis
        send(server_fd, &k, 4, 0); // -//- to id
        send(server_fd, &flights[k].price , sizeof(flights[k].price), 0); //stelnw thn timh
        flights[k].available_seats --; //meiwnoume ton aritho twn diathesimwn thesewn gia thn pthsh k
        *total = (*total + flights[k].price); //sunolika esoda aeroporikhs etairias
        Ep[k] = Ep[k] + 1; // pinakas me epituxeis krathseis kathe pthshs
    }
    else{
        send(server_fd, &p, 4, 0);
        send(server_fd, &k, 4, 0);
        send(server_fd, &flights[k].price , sizeof(flights[k].price), 0);
    }
}

void pthseis(Pthseis flights[SIZE]){    //dhmiourgei tis pthseis

    srand(time(0)); //arxikopoihsh rologiou vash wra ekteleshs

    int r = 0;

    flights[0].flight_id = 0;
    strcpy(flights[0].from_city, "Athina");
    strcpy(flights[0].to_city, "Thessaloniki");
    flights[0].price = 59.99;
    r = (rand() % 5)+1; // orismata apo 1 mexri 5 gia tis theseis
    flights[0].available_seats = r;

    flights[1].flight_id = 1;
    strcpy(flights[1].from_city, "Ptolemaida");
    strcpy(flights[1].to_city, "Hrakleio");
    flights[1].price = 100.58;
    r = (rand() % 5)+1;
    flights[1].available_seats = r;

    flights[2].flight_id = 2;
    strcpy(flights[2].from_city, "Larissa");
    strcpy(flights[2].to_city, "Axladoxwri");
    flights[2].price = 70.56;
    r = (rand() % 5)+1;    
    flights[2].available_seats = r;

    flights[3].flight_id = 0;
    strcpy(flights[3].from_city, "Katerinh");
    strcpy(flights[3].to_city, "Patra");
    flights[3].price = 44.99;
    r = (rand() % 5)+1; 
    flights[3].available_seats = r;

    flights[4].flight_id = 1;
    strcpy(flights[4].from_city, "Orestiada");
    strcpy(flights[4].to_city, "Kerkyra");
    flights[4].price = 120;
    r = (rand() % 5)+1;
    flights[4].available_seats = r;

    flights[5].flight_id = 2;
    strcpy(flights[5].from_city, "Larnaka");
    strcpy(flights[5].to_city, "Volos");
    flights[5].price = 149.99;
    r = (rand() % 5)+1;    
    flights[5].available_seats = r;

    flights[6].flight_id = 1;
    strcpy(flights[6].from_city, "Naxos");
    strcpy(flights[6].to_city, "Santorinh");
    flights[6].price = 39.99;
    r = (rand() % 5)+1;
    flights[6].available_seats = r;

    flights[7].flight_id = 0;
    strcpy(flights[7].from_city, "Iwannina");
    strcpy(flights[7].to_city, "Kalamata");
    flights[7].price = 34.99;
    r = (rand() % 5)+1; 
    flights[7].available_seats = r;

    flights[8].flight_id = 1;
    strcpy(flights[8].from_city, "Preveza");
    strcpy(flights[8].to_city, "Alexandroupoli");
    flights[8].price = 69.99;
    r = (rand() % 5)+1;
    flights[8].available_seats = r;

    flights[9].flight_id = 2;
    strcpy(flights[9].from_city, "Rhodos");
    strcpy(flights[9].to_city, "Kefalonia");
    flights[9].price = 54.99;
    r = (rand() % 5)+1;    
    flights[9].available_seats = r;
}
