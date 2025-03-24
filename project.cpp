#include <iostream>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <unistd.h>
#include<conio.h>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;
const int N = 9;
string UserName;

int minutes = 0;
int seconds = 0;
int time_payan=0;

struct Bazikonande
{
	string Player;
	int Emtiaz_;
	int Eshtebah_;
	int Sahih;
	int Code_;
	int Start_;
	time_t start_time;
}bz[20];

int KodamBazikon=0;
int CodeBazikoneJari=0;

void timer() {
    while (true) {
        sleep(1000);
        seconds++;

        if (seconds == 60) {
            minutes++;

            if (minutes == time_payan)
			{
                minutes = 0;
            }

            seconds = 0;
        }
    }
}

bool isSafe(int board[N][N], int row, int col, int num)
{
    for (int i = 0; i < N; i++)
    {
    	if (board[row][i] == num)
    	{
    	 return false;
    	}

    }
    for (int i = 0; i < N; i++)
    {
    	 if (board[i][col] == num)
    	 {
    	 	 return false;
    	 }


    }
    int boxRowStart = row - row % 3;
    int boxColStart = col - col % 3;

    for (int i = 0; i < 3; i++)
    {
    	 for (int j = 0; j < 3; j++)
    	 {
    	 	if (board[i + boxRowStart][j + boxColStart] == num)
    	 	{
    	 	 return false;
    	 	}

    	 }

    }
    return true;
}

void printBoard(int grid[N][N]) {

    system("cls");
    cout << "\t\t\t<================================================================================>" << endl;
    cout << "\t\t\t|                             welcome new player                                |" << endl;
    cout << "\t\t\t|                             let's play soduko                                 |" << endl;
    cout << "\t\t\t<================================================================================>" << endl;
    for (int row = 0; row < N; row++)
	{
      for (int col = 0; col < N; col++)
	  {
         if(col == 3 || col == 6)
         {
         cout << " | ";
         }
         cout << grid[row][col] <<" ";
      }

      if(row == 2 || row == 5)
	  {
         cout << endl;
         for(int i = 0; i<N; i++)
         {
         	cout << "---";
         }

      }
      cout << endl;
   }
}


void SaveBoard(int grid[N][N])
 {

    fstream myfile;
   myfile.open("game.txt", ios::out);
    for (int row = 0; row < N; row++)
	{

      for (int col = 0; col < N; col++)
	  {
          myfile <<grid[row][col];

      }
       myfile<<endl;
   }
    myfile.close();

}


bool solveSudoku(int board[N][N], int row, int col)
 {
    if (row == N - 1 && col == N)
    {
      return true;
    }
    if (col == N)
	 {
        row++;
        col = 0;
     }
    if (board[row][col] != 0)
    {
     return solveSudoku(board, row, col + 1);
    }
    for (int num = 1; num <= 9; num++)
	{
        if (isSafe(board, row, col, num))
		 {
            board[row][col] = num;

            if (solveSudoku(board, row, col + 1))
            {
              return true;
            }


            board[row][col] = 0;
        }
    }
    return false;
}

bool isSolvedCompletely(int grid[N][N])
{
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
          if (grid[row][col] == 0)
          {
          	 return false;
          }

        }

    }
    return true;
}

void playGame(int board[N][N]) {
    time_t start_time, current_time;
    double elapsed_time = 0;

    time(&start_time);

    int ch;
    int row, col, num;

    while (true) {
        time(&current_time);
        elapsed_time = difftime(current_time, start_time);

        int minutes = elapsed_time / 60;
        int seconds = (int)elapsed_time % 60;

        cout << "Time left: " << (time_payan * 60 - (int)elapsed_time) / 60 << " minutes "
             << (time_payan * 60 - (int)elapsed_time) % 60 << " seconds." << endl;

        if (elapsed_time >= time_payan * 60) {
            cout << "Time's up! Game over!" << endl;
            break;
        }

        printBoard(board);
        cout << endl << endl;

        if (bz[CodeBazikoneJari].Eshtebah_ >= 5) {
            cout << "you've made 5 mistakes" << endl;
            break;
        }

        cout << "<q For Exit C For Continue" << endl;
        if (getch() == 'q') {
            break;
        }

        cout << "<s For Save" << endl;
        if (getch() == 's') {
            SaveBoard(board);
        }

        cout << "<Esc For Pause C For Continue" << endl;
        if (getch() == 27) {
            cout << "We paused the game - to continue type C" << endl;
            if (getch() == 'C') {
                continue;
            }
        }

        cout << "row: ";
        cin >> row;

        cout << "col: ";
        cin >> col;

        cout << "enter a number: ";
        cin >> num;

        if (row == -1 && col == -1 && num == -1) {
            solveSudoku(board, 0, 0);
            printBoard(board);
            cout << endl;
            cout << "try again" << endl;
            break;
        }

        if (isSolvedCompletely(board))
            break;

        row--;
        col--;
        if (!isSafe(board, row, col, num)) {
            cout << "wrong move - try again" << endl;
            break;
        }

        board[row][col] = num;
    }

    bool solved = true;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 0) {
                solved = false;
                break;
            }
        }
    }

    if (solved) {
        cout << "you won!!" << endl;
        bz[CodeBazikoneJari].Sahih += 1;
        bz[CodeBazikoneJari].Emtiaz_ += 10;
        printBoard(board);
    } else {
        cout << "you failed - try again later" << endl;
        bz[CodeBazikoneJari].Eshtebah_ += 1;
    }
}

int main()
{
    system("color b0");

    string CurrentUser;
    int board[N][N] =
	 {
        {3, 0, 6, 5, 0, 8, 4, 0, 0},
        {5, 2, 0, 0, 0, 0, 0, 0, 0},
        {0, 8, 7, 0, 0, 0, 0, 3, 1},
        {0, 0, 3, 0, 1, 0, 0, 8, 0},
        {9, 0, 0, 8, 6, 3, 0, 0, 5},
        {0, 5, 0, 0, 9, 0, 6, 0, 0},
        {1, 3, 0, 0, 0, 0, 2, 5, 0},
        {0, 0, 0, 0, 0, 0, 0, 7, 4},
        {0, 0, 5, 2, 0, 6, 3, 0, 0}
    };

    cout << "\t\t\t<================================================================================>" << endl;
    cout << "\t\t\t|                            welcome new player                                 |" << endl;
    cout << "\t\t\t|                            let's play sudoku                                  |" << endl;
    cout << "\t\t\t<================================================================================>" << endl;

    while (1)
	 {

        int choice;
      	int c=0;
     	string myText;
        cout << endl << endl;
        cout << "\t\t[0] Create New Player" << endl;
        cout << "\t\t[1] play the game" << endl;
        cout << "\t\t[2] soloution" << endl;
        cout << "\t\t[3] Exit" << endl;
        cout << "\t\t[4] Load Save Game" << endl;
	    cout << "\t\t[5] Jadvale Emtiaz" << endl;
	    cout << "\t\t[6] Change Player" << endl;
        cout << "\t\t please choose an option: "<<endl;
        cin >> choice;

        switch (choice)
		{
				case 0:
             	cout<<"please enter your username :"<<endl;
            	cin>>CurrentUser;
            			bz[KodamBazikon].Player=CurrentUser;
            			bz[KodamBazikon].Code_=KodamBazikon;
            			bz[KodamBazikon].Emtiaz_=0;
            			bz[KodamBazikon].Eshtebah_=0;
            			bz[KodamBazikon].Sahih=0;
            			bz[KodamBazikon].Start_=0;
            		    time(&bz[KodamBazikon].start_time);
            			KodamBazikon++;
            			cout<<"username created"<<endl;
            	break;
            case 6:
            		cout<<"please enter a username :"<<endl;
            	cin>>CurrentUser;
            		for(int k=0;k<KodamBazikon;k++)
            	{
            		if(CurrentUser==bz[k].Player)
            		{

            		cout<<"you chose player "<<bz[k].Code_<<" with username "<<bz[k].Player<<" for the game"<<endl;
                	}

            		else
            		{
            			cout<<"invalid username"<<endl;
            			break;
            		}
            	}
            	break;
            case 1:


            		cout<<"1.easy"<<endl;
            		cout<<"2.medium"<<endl;
            		cout<<"3.hard"<<endl;
            		cin>>c;
            		switch(c)
            		{
            			case 1:
            				time_payan=5;
            				break;
            			case 2:
            				time_payan=3;
            				break;
            			case 3:
            				time_payan=2;
            				break;
            		}
            		playGame(board);
                break;
            case 2:
                if (solveSudoku(board, 0, 0))
                {
                    cout << "solution"<< endl;
                    cout << endl << endl;
                    for (int row = 0; row < N; row++){
                        for (int col = 0; col < N; col++){
                            if(col == 3 || col == 6)
                                cout << " | ";
                            cout << board[row][col] <<" ";
                        }
                        if(row == 2 || row == 5){
                            cout << endl;
                            for(int i = 0; i<N; i++)
                                cout << "---";
                        }
                        cout << endl;
                    }
                    cout << endl;
                    cout << "try again later" << endl;
                }
                else
                    cout << "no solution" << endl;
                break;
            case 3:
                exit(0);

            case 5:
            	time_t endt;
	        	time(&endt);
            	for (int k=0;k<KodamBazikon;k++)
            	{
            		cout<<"Player: "<<bz[k].Player<<" - Code: "<<bz[k].Code_<<endl;
            		cout<<"wrong moves: "<<bz[k].Eshtebah_<<endl;
            		cout<<"right moves: "<<bz[k].Sahih<<endl;
            		cout<<"starting time: "<<ctime(&bz[k].start_time)<<endl;
            		cout<<"total score: "<<bz[k].Emtiaz_<<endl;
            		cout<<"last move: "<<ctime(&endt);
            		cout<<"**************************************"<<endl<<endl;
            	}
            	break;

			 case 4:
                	ifstream MyReadFile("game.txt");
					while (getline (MyReadFile, myText))
					{
						board[N][N]=atoi(myText.c_str());
					}
					MyReadFile.close();
					playGame(board);
               	    break;
        }

}
 getch();
 return 0;

}
