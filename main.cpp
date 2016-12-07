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
bool mAttack(char[][SIZE],int,char[][SIZE],int);  //Users turn 
void cAttack(char[][SIZE],int);                //computers turn
void check(char[][SIZE],int);                  //checks if all targets are hit
void disply(char[][SIZE],int);
void clrscr();
//---------------------------------------------------------------<<<<<<<<<<<<<<<
//------Execution Begins Here------------------------------------<<<<<<<<<<<<<<<
//---------------------------------------------------------------<<<<<<<<<<<<<<<
int main(int argc, char** argv) {
    srand(static_cast<unsigned int>(time(0)));
    
    char map1[SIZE][SIZE];            //2d array that will store user data
    char map2[SIZE][SIZE];            //2d array that will store computers actual data
    char map3[SIZE][SIZE];            //2d array that will show computer's data
    char continu='x';
    bool turns;
    
    cout<<"\n         BATTLESHIP GAME\n"<<"       PLACE YOUR BATTLESHIPS:\n";
    
    start(map1,SIZE,map2,SIZE,map3,SIZE);    //initialize and place ships
    disply(map3,SIZE);
    place(map1,SIZE);                  //ask user to place ships on map
    dispMap(map1,SIZE,map2,SIZE);         //display both maps
    disply(map3,SIZE);
    do{
        do{
            turns=mAttack(map2,SIZE,map3,SIZE);     //start from user attack
            dispMap(map1,SIZE,map2,SIZE);     //display both maps
        }
        while(turns==true);
           
        //dispMap(map1,SIZE,map2,SIZE);     //display both maps
        cAttack(map1,SIZE);    //generate random attack from computer & show result
        dispMap(map1,SIZE,map2,SIZE);     //display both maps
        check(map1,SIZE);              //checks if all targets are hit
        cout<<"Enter 'y' to continue or any key to end the game: ";
        cin>>continu;
    }while(continu=='y');
    
    return 0;
}
//******************************************************************************
//*********************** disply **********************************************
//******************************************************************************
//PURPOSE: display map
//******************************************************************************

void disply(char a[][SIZE],int){
    cout<<"\n    a b c d e f g h\n";
    cout<<"   -----------------\n";
    for(int i=1;i<=8;i++){
        cout<<i<<" | ";
        for(int j=1;j<=8;j++){
            cout<<a[i][j]<<" ";
        }
        cout<<"|";
        cout<<endl;
    }
    cout<<"   -----------------\n";
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

bool mAttack(char mapA[][SIZE],int,char mapB[][SIZE],int){
    int x; char y; bool check;
    cout<<"\n\n========================================================\n";
    cout<<"====================YOUR TURN===========================\n";
    cout<<"========================================================\n";
    cout<<"Enter your attack location: ";
    cin>>x>>y;
    if(mapB[x][convert(y)]=='='){
        cout<<"\n--------------TARGET HIT--------------------------\n";
        mapA[x][convert(y)]='X';
        check=true;
    }else{
        cout<<"\n--------------TARGET MISSED-----------------------\n";
        mapA[x][convert(y)]='o';
        check=false;
    }
    return check;
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
    //look for a random position to place a ship:
    int a=rand()%8+1;   //[1,8]
    int b=rand()%5+1;   //must stay b/w [1,5]
    cout<<a<<" "<<b<<endl;
    map_3[a][b]='='; map_3[a][b+1]='='; map_3[a][b+2]='='; map_3[a][b+3]='=';
    
    //--------------------------------------------------------------------------
    //------------->   randomly place 2nd ship:
    do{
        a=rand()%8+1;   //[1,8]
        b=rand()%5+1;   //must stay b/w [1,5]
    }while(map_3[a][b]=='='||map_3[a][b+1]=='='||map_3[a][b+2]=='='||map_3[a][b+3]=='=');
    cout<<a<<" "<<b<<endl;
    map_3[a][b]='='; map_3[a][b+1]='='; map_3[a][b+2]='='; map_3[a][b+3]='=';
    
    //--------------------------------------------------------------------------
    //------------->   randomly place 3rd ship:
    
    do{
        a=rand()%6+1;   //must stay b/w [1,6]
        b=rand()%8+1;   //[1,8]
    }while(map_3[a][b]=='='||map_3[a+1][b]=='='||map_3[a+2][b]=='='||map_3[a+3][b]=='=');
        map_3[a][b]='='; map_3[a+1][b]='='; map_3[a+2][b]='=';

    //--------------------------------------------------------------------------
    //------------->   randomly place 4th ship:
    
    do{
        a=rand()%6+1;   //must stay b/w [1,6]
        b=rand()%8+1;   //[1,8]
    }while(map_3[a][b]=='='||map_3[a+1][b]=='='||map_3[a+2][b]=='='||map_3[a+3][b]=='=');
        map_3[a][b]='='; map_3[a+1][b]='='; map_3[a+2][b]='=';

//--------------------------------------------------------------------------
    //------------->   randomly place 5th ship:
    
    do{
        a=rand()%7+1;   //must stay b/w [1,6]
        b=rand()%8+1;   //[1,8]
    }while(map_3[a][b]=='='||map_3[a+1][b]=='='||map_3[a+2][b]=='=');
        map_3[a][b]='='; map_3[a+1][b]='=';

}
//******************************************************************************
//*********************** place ************************************************
//******************************************************************************
//PURPOSE: ask user to place ships on map
//******************************************************************************

void place(char map1[][SIZE],int){
    int x=0; char y='z';
    //-----------------1st ship------------------------------------------------- 
    //dispMap(map1,SIZE,map1,SIZE);
    disply(map1,SIZE);
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
    clrscr();
    disply(map1,SIZE);
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
    clrscr();
    disply(map1,SIZE);
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
    clrscr();
    disply(map1,SIZE);
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
    clrscr();
    disply(map1,SIZE);
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
        int ret;
    switch(c){
        case 'a': ret=1; break;
        case 'b': ret=2; break;
        case 'c': ret=3; break;
        case 'd': ret=4; break;
        case 'e': ret=5; break;
        case 'f': ret=6; break;
        case 'g': ret=7; break;
        case 'h': ret=8; break;
        default : cout<<error;
    }
    return ret;
}

//******************************************************************************
//*********************** clrscr **********************************************
//******************************************************************************
//PURPOSE: clears out the display
//******************************************************************************

void clrscr(){
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}