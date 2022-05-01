#include <iostream>
#include <time.h>
using namespace std;


#define numOfStates 6
#define learningRate 0.9

char s, x;
char goal = 'F';
int R[numOfStates][numOfStates];
int Q[numOfStates][numOfStates];

//give Q-table its inital values
void initQ(){
    for (int i = 1; i <= numOfStates; i++)
    {
        for (int j = 1; j <= numOfStates; j++)
        {
            Q[i][j] = 0;
        }
        
    }
    
}

//give R-table its values
void initR(){
    cout << "enter R values, if there is no path between two states enter -1" << endl;
    for (int i = 1; i <= numOfStates; i++)
    {
        for (int j = 1; j <= numOfStates; j++)
        {
            cin >> R[i][j];
        }
        
    }
    
}


/*
R values in the slides:
-1 -1 -1 -1  0 -1
-1 -1 -1  0 -1 100
-1 -1 -1  0 -1 -1 
-1  0  0 -1  0 -1
 0 -1 -1  0 -1 100
-1  0 -1 -1  0 100 
*/
//using the slides values
void RExample(){
    R[1][1] = R[1][2] = R[1][3] = R[1][4] = R[1][6] = 
    R[2][1] = R[2][2] = R[2][3] = R[2][5] = 
    R[3][1] = R[3][2] = R[3][3] = R[3][5] =R[3][6] = 
    R[4][1] = R[4][4] = R[4][6] =
    R[5][2] = R[5][3] = R[5][5] =
    R[6][1] = R[6][3] = R[6][4] = -1;

    R[1][5] = R[2][4] = R[3][4] = R[4][2] = R[4][3] = R[4][5] = R[5][1] = R[5][4] = R[6][2] = R[6][5] = 0;

    R[2][6] = R[5][6] = R[6][6] = 100;
}

void printTables(){
    cout << "Q: " << endl;
    for (int i = 1; i <= numOfStates; i++)
    {
        for (int j = 1; j <= numOfStates; j++)
        {
            
            cout << Q[i][j] << " ";
            if (Q[i][j] <= 9)
                cout << "  ";
            else if (Q[i][j] <= 99)
                cout << " ";
        }
        cout << endl;
    }
    cout <<"\nR: " <<endl;
    for (int i = 1; i <= numOfStates; i++)
    {
        for (int j = 1; j <= numOfStates; j++)
        {
            if (R[i][j] == 0)
                cout << " ";
            
            
            cout << R[i][j] << " ";
        }
        cout << endl;
    }
}

void QLearning(){
    int row, col, maxRow, maxCol;
    double max;

    //Select initial state by random (s)
    s = rand()%numOfStates + 'A';
    
    //Do while goal not reached
    do
    {
        row = (int)s-64;
        col = rand()%numOfStates+1;

        //Select one possible action (x)
        while (R[row][col] == -1)
        {
            col = rand()%numOfStates+1;
        }
        x = (char) col+64;        

        //Get maximum Q for N(s,x) based on all possible actions
        maxRow = (int)x-64;
        maxCol = 1;
        max = Q[maxRow][maxCol]; 
        maxCol++;
        while (maxCol <= numOfStates)
        {
            if (max < Q[maxRow][maxCol])
                max = Q[maxRow][maxCol];
            
            maxCol++;
        }
        
        //𝑸 (𝒔, 𝒙) = 𝑹 (𝒔, 𝒙) + 𝜸 ∙ 𝑴𝒂𝒙 𝑸(𝑵(𝒔, 𝒙), 𝒂𝒍𝒍 𝒂𝒄𝒕𝒊𝒐𝒏𝒔)
        Q[row][col] = R[row][col] + learningRate * max;

        //Set s=N(s,x)
        s = x; 
    } while (s != goal);

    
}

int main(){
    srand ( time(NULL) );
    initQ();
    RExample();
    cout << "inital tables: "<< endl <<endl;;
    printTables();
    for (int i = 0; i < 50; i++)
        QLearning();
    cout << "\n\nAfter using Q-Learning algorithm: " << endl <<endl;
    printTables();

    return 0;
}