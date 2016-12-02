/* 
 * File:   main.cpp
 * Author: Hatim, Muhamamd
 * Created on: december,1st.2016
 * Purpose: Battleship Game
 */

//System Libraries
#include <iostream>     //Input/Output objects
#include <iomanip>      //formats text
#include <cstdlib>      //Random number seed
#include <ctime>        //Seed the random number generator

using namespace std;    //Name-space used in the System Library

//User Libraries
//Global constants
const int SIZE=10;      //size of the array

//---------Function prototypes--------------------------------------------------
void dispMap(char[][SIZE],int,char[][SIZE],int);              //displays maps
void start(char[][SIZE],int,char[][SIZE],int,char[][SIZE],int);//initializes maps 
void place(char[][SIZE],int);          //asks user to place the battleships on map
int convert(char);                  //converts 'char' -> 'int' for use in arrays
void mAttack(char[][SIZE],int,char[][SIZE],int);  //Users turn 
void cAttack(char[][SIZE],int);                //computers turn
void check(char[][SIZE],int);                  //checks if all targets are hit

//------------------------------------------------------------------------------
//------Execution Begins Here---------------------------------------------------
//------------------------------------------------------------------------------
int main(int argc, char** argv) {
    srand(static_cast<unsigned int>(time(0)));
    
    char map1[SIZE][SIZE];            //2d array that will store user data
    char map2[SIZE][SIZE];            //2d array that will store computers actual data
    char map3[SIZE][SIZE];            //2d array that will show computer's data
    char continu='x';
 
    
    cout<<"\n         BATTLESHIP GAME\n"<<"       PLACE YOUR BATTLESHIPS:\n";
    
    start(map1,SIZE,map2,SIZE,map3,SIZE);    //initialize and place ships
    place(map1,SIZE);                  //ask user to place ships on map
    dispMap(map1,SIZE,map2,SIZE);         //display both maps
    
    do{
        mAttack(map2,SIZE,map3,SIZE);     //start from user attack  
        dispMap(map1,SIZE,map2,SIZE);     //display both maps
        cAttack(map1,SIZE);    //generate random attack from computer & show result
        dispMap(map1,SIZE,map2,SIZE);     //display both maps
        check(map1,SIZE);              //checks if all targets are hit
        cout<<"Enter 'y' to continue or any key to end the game: ";
        cin>>continu;
    }while(continu=='y');
    
    return 0;
}


//******************************************************************************
//*********************** cAttcak **********************************************
//******************************************************************************
//PURPOSE: (computer's attack):  GENERATE A RANDOM ATTACK
//******************************************************************************
void cAttack(char mapA[][SIZE],int){
    int xComp=rand()%8+1,
        yComp=rand()%8+1;
    cout<<"Hit enter to continue\n";
    cin.get();
    cin.ignore();
cout<<"\n\n========================================================\n";
    cout<<"==================== COMPUTERS TURN ====================\n";
    cout<<"========================================================\n";
        cout<<"\nComputers Chose location: ("<<xComp<<",";
    switch(yComp){
        case 1:cout<<"a)";break;
        case 2:cout<<"b)";break;
        case 3:cout<<"c)";break;
        case 4:cout<<"d)";break;
        case 5:cout<<"e)";break;
        case 6:cout<<"f)";break;
        case 7:cout<<"g)";break;
        case 8:cout<<"h)";
    }
    if(mapA[xComp][yComp]=='='){
        cout<<"\n--------------TARGET HIT--------------------------\n";
        mapA[xComp][yComp]='X';
    }else{
        cout<<"\n--------------TARGET MISSED-----------------------\n";
        mapA[xComp][yComp]='o';        
    }
}
//******************************************************************************
//*********************** dispMap **********************************************
//******************************************************************************
//PURPOSE: DISPLAYS BOTH MAP ON THE SCREEN 
//******************************************************************************

void dispMap(char a[][SIZE],int rowSizea, char b[][SIZE],int rowsizeb){
    cout<<"\n    a b c d e f g h             a b c d e f g h\n";
    cout<<"   -----------------           -----------------\n";
    for(int i=1;i<=8;i++){
        cout<<i<<" | ";
        for(int j=1;j<=8;j++){
            cout<<a[i][j]<<" ";}
        cout<<"|";
        cout<<right<<setw(8)<<i<<" | ";
        for(int j=1;j<=8;j++){
            cout<<b[i][j]<<" ";            
        }
        cout<<"|"<<endl;
    }
    cout<<"   -----------------           -----------------\n";
}
//******************************************************************************
//*********************** mAttack **********************************************
//******************************************************************************
//PURPOSE: ASKS THE USER FOR ATTACK LOCATION
//******************************************************************************

void mAttack(char mapA[][SIZE],int,char mapB[][SIZE],int){
    int x; char y;
    cout<<"\n\n========================================================\n";
    cout<<"====================YOUR TURN===========================\n";
    cout<<"========================================================\n";
    cout<<"Enter your attack location: ";
    cin>>x>>y;
    if(mapB[x][convert(y)]=='='){
        cout<<"\n--------------TARGET HIT--------------------------\n";
        mapA[x][convert(y)]='X';
    }else{
        cout<<"\n--------------TARGET MISSED-----------------------\n";
        mapA[x][convert(y)]='o';        
    }
}
//******************************************************************************
//*********************** start ************************************************
//******************************************************************************
//PURPOSE: initializes and place ships
//******************************************************************************

void start(char map_1[][SIZE],int,char map_2[][SIZE],int,char map_3[][SIZE],int){
    for(int i=1;i<=8;i++){
        for(int j=1;j<=8;j++){
            map_1[i][j]='.';
            map_2[i][j]='.';
            map_3[i][j]='.';
        }
    }
    map_3[1][2]='='; map_3[1][3]='='; map_3[1][4]='='; map_3[1][5]='=';
    map_3[3][5]='='; map_3[3][6]='='; map_3[3][7]='='; map_3[3][8]='=';
    map_3[4][2]='='; map_3[5][2]='='; map_3[6][2]='=';
    map_3[6][8]='='; map_3[7][8]='='; map_3[8][8]='=';
    map_3[5][5]='='; map_3[6][5]='=';
}
//******************************************************************************
//*********************** place ************************************************
//******************************************************************************
//PURPOSE: ask user to place ships on map
//******************************************************************************

void place(char map1[][SIZE],int){
    int x=0; char y='z';
    //-----------------1st ship------------------------------------------------- 
    dispMap(map1,SIZE,map1,SIZE);
    cout<<"\nWhere do you want to place a horizontal battleship(4 units long)? \n";
    do{
        cout<<"Enter the digit value between[1-8]: ";
        cin>>x;
    }while(x>9||x<1);
    do{
        cout<<"enter the alphabet value between [a-e]: ";
        cin>>y;
    }while(!(y=='a'||y=='b'||y=='c'||y=='d'||y=='e'));
    map1[x][convert(y)]='=';
    map1[x][convert(y)+1]='=';
    map1[x][convert(y)+2]='=';
    map1[x][convert(y)+3]='=';
    
    //-----------------2nd ship------------------------------------------------- 
    dispMap(map1,SIZE,map1,SIZE);
    x=0; y='z';
    cout<<"\nwhere do you want to place a horizontal battleship(4 units long)? \n";
    do{
        cout<<"Enter the digit value between[1-8]: ";
        cin>>x;
    }while(x>9||x<1);
    do{
        cout<<"enter the alphabet value between [a-e]: ";
        cin>>y;
    }while(!(y=='a'||y=='b'||y=='c'||y=='d'||y=='e'));
    map1[x][convert(y)]='=';
    map1[x][convert(y)+1]='=';
    map1[x][convert(y)+2]='=';
    map1[x][convert(y)+3]='=';
    //-----------------3rd ship------------------------------------------------- 
    dispMap(map1,SIZE,map1,SIZE);
    x=0; y='z';
    cout<<"\nwhere do you want to place a verticle battleship(3 units long)? \n";
    do{
        cout<<"Enter the digit value between[1-6]: ";
        cin>>x;
    }while(x>6||x<1);
    do{
        cout<<"enter the alphabet value between [a-h]: ";
        cin>>y;
    }while(!(y=='a'||y=='b'||y=='c'||y=='d'||y=='e'||y=='f'||y=='g'||y=='h'));
    map1[x][convert(y)]='=';
    map1[x+1][convert(y)]='=';
    map1[x+2][convert(y)]='=';
    //-----------------4th ship------------------------------------------------- 
    dispMap(map1,SIZE,map1,SIZE);
    x=0; y='z';
    cout<<"\nwhere do you want to place a verticle battleship(3 units long)? \n";
    do{
        cout<<"Enter the digit value between[1-6]: ";
        cin>>x;
    }while(x>6||x<1);
    do{
        cout<<"enter the alphabet value between [a-h]: ";
        cin>>y;
    }while(!(y=='a'||y=='b'||y=='c'||y=='d'||y=='e'||y=='f'||y=='g'||y=='h'));
    map1[x][convert(y)]='=';
    map1[x+1][convert(y)]='=';
    map1[x+2][convert(y)]='=';
    //-----------------5th ship------------------------------------------------- 
    dispMap(map1,SIZE,map1,SIZE);
    x=0; y='z';
    cout<<"\nwhere do you want to place a verticle battleship(2 units long)? \n";
    do{
        cout<<"Enter the digit value between[1-7]: ";
        cin>>x;
    }while(x>7||x<1);
    do{
        cout<<"enter the alphabet value between [a-h]: ";
        cin>>y;
    }while(!(y=='a'||y=='b'||y=='c'||y=='d'||y=='e'||y=='f'||y=='g'||y=='h'));
    map1[x][convert(y)]='=';
    map1[x+1][convert(y)]='=';
    
}
//******************************************************************************
//*********************** check ************************************************
//******************************************************************************
//PURPOSE: checks if all targets are hit
//******************************************************************************

void check(char map_3[][SIZE],int){
    if(map_3[1][2]!='='&& map_3[1][3]!='='&& map_3[1][4]!='='&& map_3[1][5]!='='&&
       map_3[3][5]!='='&& map_3[3][6]!='='&& map_3[3][7]!='='&& map_3[3][8]!='='&&
       map_3[4][2]!='='&& map_3[5][2]!='='&& map_3[6][2]!='='&&
       map_3[6][8]!='='&& map_3[7][8]!='='&& map_3[8][8]!='='&&
       map_3[5][5]!='='&& map_3[6][5]!='='){
        cout<<"\n\n=======================================================\n"
                <<"===========ALL TARGETS HAVE BEEN HIT===================\n"
                <<"=======================================================\n";

    }
}

//******************************************************************************
//*********************** convert **********************************************
//******************************************************************************
//PURPOSE: converts a character value into an integer
//******************************************************************************

int convert(char c){
	string error="\nError in conversion\n";
    switch(c){
        case 'a': return 1; break;
        case 'b': return 2; break;
        case 'c': return 3; break;
        case 'd': return 4; break;
        case 'e': return 5; break;
        case 'f': return 6; break;
        case 'g': return 7; break;
        case 'h': return 8; break;
    }
    cout<<error;
    return 0;
}
