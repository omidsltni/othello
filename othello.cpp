#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

void flip_h(char table[], int size, int base, char player){
    int x;
    for (int i=0;i<size;i++){
        x = i*size+size-1;
        if (base <= x && base >= x - size + 1){
            break;
        }
    }
    for (int i = x - size + 1 ; i<=x ; i++){
        if (table[i]==player){
            for (int j=i;j<=x;j++){
                if (table[j]=='E'){
                    break;
                } else if (table[j]==player){
                    for (int q=i;q<=j;q++){
                        table[q]=player;
                    }
                }
            }
        }
    }

}
void flip_v(char table[], int size, int base, char player){
    int x = base%size;
    for (int i=x;i<size*size;i+=size){
        if (table[i]==player){
            for (int j=i;j<size*size;j+=size){
                if (table[j]=='E'){
                    break;
                } else if (table[j]==player){
                    for (int q=i;q<=j;q+=size){
                        table[q]=player;
                    }
                }
            }
        }
    }
}
void flip_d1(char table[], int size, int base, char player){
    
}

string space = "        ";

void load_menu();
void play_game();
void load_game();
void ranking();
void save_game();


void showtable(char table[],int size, int TableSize, string players[], char symbols[]){
    system("clear");
    string player1 = players[0];
    string player2 = players[1];
    char symbol1 = symbols[0];
    char symbol2 = symbols[1];
    int count_pieces1=0,count_pieces2=0;
    for (int i=0;i<TableSize;i++){
        if (table[i]==symbol1){
            count_pieces1++;
        }
    }
    for (int i=0;i<TableSize;i++){
        if (table[i]==symbol2){
            count_pieces2++;
        }
    }

    cout << space <<  "* Othello *" << endl << endl;
	cout << space << "Player 1 : " << player1 << space << "Symbol : " << symbol1 << space << "Pieces : " << count_pieces1 << endl;
	cout << space << "Player 2 : " << player2 << space << "Symbol : " << symbol2 << space << "Pieces : " << count_pieces2 << endl;
	
    int row=0,count=0;
    for (int i=0;i<TableSize;i++){
        int j = row*size + i;
        cout << table[j] << " ";
        count++;
        if (count==size){
            cout << endl;
            count = 0;
        }
    }
    cout << "exit : E" << space << "save : V" << space << "up : W" << space << "down : S" << space << "right : D" << space << "left : A" << endl;
}
void move(int size, char table[],char player,string players[], char symbols[]){
    char choice;
    int base=0;
    int c=0;
    while(choice != '\n'){
        choice = getch();
        if(table[base]=='H'){
            table[base]='E';
        }
        switch(choice){
            case 'e':
                load_menu();
                break;
            case 'v' :
                save_game();
            case 'w':
                base-=size;
                break;
            case 'a':
                base--;
                break;
            case 's':
                base+=size;
                break;
            case 'd':
                base++;
                break;
            case '\n':
                if(table[base]=='E'){
                    table[base]=player;
                    flip_h(table,size,base,player);
                    flip_v(table,size,base,player);
                } else {
                    cout << "invalid" << endl;
                    move(size,table,player,players,symbols);                
                }
                break;
            default:
                cout << "invalid" << endl;
                move(size,table,player,players,symbols);
            }
            if (base<0){
                base += size*size;
            }
            if (base>size*size){
                base -= size*size;
            }
            if(table[base]=='E'){
                table[base]='H';
            } 
            showtable(table,size,size*size,players, symbols);
            c++;
    }
}


int main(){
	system("clear");
	load_menu();
	cout << "HI";
			
		



	
	return 0;
}


void load_menu(){
	
	system("clear");

	char choice;
	cout << "* Othello Game *" << endl << endl;
	cout << "a. New Game" << endl;
	cout << "b. Load Game" << endl;
	cout << "c. Ranking" << endl;
	cout << "d. Exit" << endl;
	choice = getch();
	switch(choice){
		case 'a':
			play_game();
			break;
		case 'b':
			load_game();
			break;
		case 'c':
			ranking();
			break;
		case 'd':
			exit(0);
			break;
		default:
			system("clear");
			cout << "invalid" << endl;
			load_menu();
		}
}


void play_game(){
	system("clear");
	
	cout << "Enter player 1 name :" << endl;
	string player1;
	cin >> player1;
	
	cout << "Choose a symbol between x and o :" << endl;
	char symbol1;
	cin >> symbol1;
	
	cout << "Enter player 2 name :" << endl;
	string player2;
	cin >> player2;
	
	char symbol2;
	if(symbol1 == 'x'){
		symbol2 = 'o';
	}
	else{
		symbol2 = 'x';
	}
	
	
	cout << "Enter the size of the table : " << endl;
	int size;
	cin >> size;
	
	while(size > 12 || size < 4 || size % 2 != 0){
		cout << "Error!" << endl << "press n to enter a valid size (an even number between 4 and 12) or press e to exit" << endl;
		char choice;
		choice = getch();
		
		switch (choice){
			case 'e' :
				load_menu();
				break;
			
			case 'n' :
				cout << "Enter the size of the table : " << endl;
				cin >> size;
				break;
		}
	}
	

	cout << endl;
	int n = size;
    int TableSize = n*n;
    char MainTable[TableSize];
    for (int i=0;i<TableSize;i++){
        MainTable[i]='E';
    }
    int MiddleNumbers[4];
    MiddleNumbers[0]=n*(n/2-1)+(n/2-1);
    MiddleNumbers[1]=n*(n/2-1)+(n/2);
    MiddleNumbers[2]=n*(n/2)+(n/2-1);
    MiddleNumbers[3]=n*(n/2)+(n/2);
    for(int i=0;i<4;i++){
        int x = MiddleNumbers[i];
        if(i%3==0){
            MainTable[x]='x';
        } else {
            MainTable[x]='o';
        }
    }
    string players_name[2] = {player1,player2};
    char player_icon[2] = {symbol1,symbol2};
    int movments=0;
    char player;
    while (movments < size*size){
        if (movments%2==0){
            player = player_icon[0];
        } else {
            player = player_icon[1];
        }
        showtable(MainTable,size,TableSize,players_name,player_icon);
        move(size, MainTable,player,players_name,player_icon);
        movments++;
    }
}
void load_game(){
	system("clear");
	system("ls");
}
void ranking(){
	system("clear");
}


void save_game(){
	string fileName;
	cout << "enter the name of the file :" << endl;
	
	getline(cin, fileName);
	
	std::ofstream ofs(fileName);
}
