#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define CHAR_O 'O'
#define CHAR_N 'N'

typedef struct MY_MOVE
{
    int i;
    int j;
    int direction;
}myMove;


const int rowCount = 7;
const int colCount = 7;
const int possibleMoves = 4;

string moveDirection[possibleMoves] = {"UP" , "DOWN" , "RIGHT" , "LEFT"};

int rowMoves[possibleMoves] = {-1 , 1 , 0 , 0};
int colMoves[possibleMoves] = {0 , 0 , 1 , -1};

char board[rowCount][colCount];
vector<myMove> steps;


void give_position(vector<vector<string> > &position)
{
    char positionIndex[2] = {'A','1'};

    for (int i = 0 ; i < position.size() ; i++)
    {
        positionIndex[1] = '1';
        for (int j  = 0 ; j < position[i].size() ; j++)
        {
            position[i][j].push_back(positionIndex[0]);
            position[i][j].push_back(positionIndex[1]);
            positionIndex[1]++;
        }
        positionIndex[0]++;
    }
}

void move_pieces(int row , int col , int move , char firstChar , char secondChar)
{
    int new_row = row + 2*rowMoves[move];
    int new_col = col + 2*colMoves[move];

    int delete_row = row + rowMoves[move];
    int delete_col = col + colMoves[move];
  
    board[row][col] = firstChar;
    board[delete_row][delete_col] = firstChar;
    board[new_row][new_col] = secondChar;
}

bool find_way()
{
    myMove temp;
    int sum = 0;
    for (int i = 0; i < rowCount ; i++)
    {
        for (int j = 0; j < colCount ; j++)
        {
            if (board[i][j] == 'N')
                sum++;
        }
    }
    if (sum == 1 && board[3][3] == 'N')
        return true;

    for (int i = 0; i < rowCount ; i++)
    {
        for (int j = 0; j < colCount ; j++)
        {
            if (board[i][j] != 'N')
                continue;

            for (int move = 0; move < possibleMoves; move++)
            {
                int new_row = i + 2*rowMoves[move];
                int new_col = j + 2*colMoves[move];

                int delete_row = i + rowMoves[move];
                int delete_col = j + colMoves[move];

                if (board[new_row][new_col] != 'O' || board[delete_row][delete_col] != 'N')
                    continue;

                move_pieces(i,j,move,CHAR_O,CHAR_N);
                temp.i = i;
                temp.j = j;
                temp.direction = move;
                steps.push_back(temp);
                if(find_way())
                    return true;
                move_pieces(i,j,move,CHAR_N,CHAR_O);
                steps.pop_back();
            }
        }
    }
    return false;
}

void solve()
{
    vector<vector<string> > position(rowCount , vector<string> (colCount));
    give_position(position);

    if(find_way())
    {
        for (int i = 0; i < steps.size(); i++)
        {
            cout << position[steps[i].i][steps[i].j] << " ";
            cout << moveDirection[steps[i].direction] << endl;
        }
    }
    else
    {
        cout << "Loser";
    }
}


int main()
{
    char input;
    for (int i = 0 ; i < rowCount; i++)
    {
        for (int j  = 0 ; j < colCount ; j++)
        {
            cin >> input;
            board[i][j] = input;
        }
    }

    solve();

    return 0;
}

