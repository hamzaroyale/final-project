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
#include <fstream>

using namespace std;    //Name-space used in the System Library

//User Libraries
//Global constants
const int SIZE=10;      //size of the array

//---------Function prototypes--------------------------------------------------
void dispMap(char[][SIZE],int,char[][SIZE],int);              //displays maps
void start(char[][SIZE],int,char[][SIZE],int,char[][SIZE],int);//initializes maps 
void place(char[][SIZE],int);          //asks user to place the battleships on map
int convert(char);                  //converts 'char' -> 'int' for use in arrays
bool mAttack(char[][SIZE],int,char[][SIZE],int,int&);  //Users turn 
void cAttack(char[][SIZE],int,bool &,bool &,bool &,bool &,int &,int &,bool&);//computers turn
int check(char[][SIZE],int,char[][SIZE],int);                  //checks if all targets are hit
void disply(char[][SIZE],int);
void clrscr();
void intro();
void highscr(int*,int);
//---------------------------------------------------------------<<<<<<<<<<<<<<<
//------Execution Begins Here------------------------------------<<<<<<<<<<<<<<<
//---------------------------------------------------------------<<<<<<<<<<<<<<<
int main(int argc, char** argv) {
    srand(static_cast<unsigned int>(time(0)));
    
    char map1[SIZE][SIZE];            //2d array that will store player's data
    char map2[SIZE][SIZE];            //2d array that will store computers actual data
    char map3[SIZE][SIZE];            //2d array that will show computer's data
    char continu='x';
    bool turns,tryAgn=false;
    int num_scr=10;
    int mScore=0;                       //players score
    int count=0;
    fstream iFile;
    int scores[num_scr];
    int temp;
    //these help computer determine where to attack next; once a target is found
    bool up=false,down=false,left=false,right=true; 
    
    int tFoundX=0, tFoundY=0;
    
    iFile.open("file.txt");

    while(! iFile.eof()){
        iFile>>temp;
        //cout<<"count: "<<count<<" "<<temp<<endl;
        scores[count]=temp;
        count++;
    }
    highscr(scores,SIZE);
    intro();        //display game title
    cout<<"                             Hit enter to continue\n";
    cin.get();
    cout<<"\n\n\n\n-------------------------------------------------------------"
            <<"\n                PLACE YOUR BATTLESHIPS:\n"
            <<"-------------------------------------------------------------\n";
    
    start(map1,SIZE,map2,SIZE,map3,SIZE);//initialize and place ships
    place(map1,SIZE);              //ask user to place ships on map
    dispMap(map1,SIZE,map2,SIZE);  //display both maps
    disply(map3,SIZE);             //shows enemy ships(for testing purpose only)
    do{
        // this loop repeats as long as targets are being hit 
        do{
            turns=mAttack(map2,SIZE,map3,SIZE,mScore); //start from user attack
            dispMap(map1,SIZE,map2,SIZE);       //display both maps
        }
        while(turns==true);                     //check if target was hit/missed
        
        cAttack(map1,SIZE,up,down,left,right,tFoundX, tFoundY,tryAgn);    //generate random attack from computer & show result
        dispMap(map1,SIZE,map2,SIZE);     //display both maps

        check(map1,SIZE,map3,SIZE);              //checks if all targets are hit
        
        cout<<"\nEnter 'x' to end the game \nOr any key and hit enter to continue: ";
        cin>>continu;
    }while(continu!='x');
//    cout<<endl<<mscore<<endl;
    //oFile<<mScore<<endl;
    //oFile.close();
    iFile.close();

    return 0;
}
//******************************************************************************
//*********************** disply ***********************************************
//******************************************************************************
//PURPOSE: display map
//******************************************************************************

void disply(char a[][SIZE],int){
    cout<<"\n                    a b c d e f g h\n";
    cout<<"                   -----------------\n";
    for(int i=1;i<=8;i++){
        cout<<"                "<<i<<" | ";
        for(int j=1;j<=8;j++){
            cout<<a[i][j]<<" ";
        }
        cout<<"|";
        cout<<endl;
    }
    cout<<"                   -----------------\n";
}

//******************************************************************************
//*********************** cAttcak **********************************************
//******************************************************************************
//PURPOSE: (computer's attack):  GENERATE A RANDOM ATTACK
//arguments: an array, 4-bool values and 2-int 
//******************************************************************************
void cAttack(char mapA[][SIZE],int, bool &u,bool &d,bool &l,bool &r,int &x,int &y,bool & tryAgn){
        bool temp;
        int xComp, yComp;
        int rCount=1, lCount=1, uCount=1, dCount=1;

        do{
        cout<<"Hit enter to continue\n";
        cin.ignore();
        cin.get();
        
        if(temp==false && tryAgn==false){
        //test (in this loop) to make sure a different location is chosen 
            do{
                cout<<"making a random attack";
                xComp=rand()%8+1,       //[1,8]
                yComp=rand()%8+1;       //[1,8]
            }while(mapA[xComp][yComp]=='o'||mapA[xComp][yComp]=='X');
        }
        else{
            //if(temp==true || tryAgn==true){
                cout<<"guessing an attack location";                
                if(r==true){
                    yComp=y+rCount;  //attack one position to right
                    rCount++;
                }
                else if(l==true){
                    yComp=y-lCount;
                    xComp=x;
                    lCount++;
                }
                else if(u==true){
                    yComp=y;
                    xComp=x-uCount;
                    uCount++;
                }
                else if(d==true){
                    yComp=y;
                    xComp=x+dCount;
                    dCount++;
                }
        }
        cout<<endl<<"yComp= "<<yComp<<endl;
        cout<<endl<<"xComp= "<<xComp<<endl;
        cout<<endl<<"temp= "<<temp<<endl;
        cout<<endl<<"l= "<<l<<endl;
        cout<<endl<<"try= "<<tryAgn<<endl;
        
        cout<<"\n\n========================================================\n";
        cout<<"==================== COMPUTERS TURN ====================\n";
        cout<<"========================================================\n";

        
        cout<<"\n  -->  Computers Chose location: ("<<xComp<<",";

        switch(yComp){                  //convert number val -> alphabet[a,h]
            case 1:cout<<"a)";break;
            case 2:cout<<"b)";break;
            case 3:cout<<"c)";break;
            case 4:cout<<"d)";break;
            case 5:cout<<"e)";break;
            case 6:cout<<"f)";break;
            case 7:cout<<"g)";break;
            case 8:cout<<"h)";
        }
        
        
        //check if target is hit:
        if(mapA[xComp][yComp]=='='){
            cout<<"\n--------------TARGET HIT--------------------------\n";
            mapA[xComp][yComp]='X';
            disply(mapA,SIZE);
            temp=true;
            tryAgn=true;
            if(x==0){
                x=xComp;
                y=yComp;
            }
        }
        else{
            cout<<"\n--------------TARGET MISSED-----------------------\n";
            mapA[xComp][yComp]='o';
            temp=false;
            
            //these conditions make sure the direction is voided if target is missed
            if(r==true && tryAgn==true){
                r=false;
                l=true;
            }
            else if(l==true && tryAgn==true){
                l=false;
                u=true;
            }
            else if(u==true && tryAgn==true){
                u=false;
                d=true;
            }
            else if(d==true && tryAgn==true){
                d=false;
                r=true;
                tryAgn=false;
                //this makes sure that in the next hit, the orignal location is saved
                x=0;
            }
        }
    }while(temp==true);
   
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

bool mAttack(char mapA[][SIZE],int,char mapB[][SIZE],int,int&scr){
    int x; char y; bool check;
    cout<<"\n\n========================================================\n";
    cout<<"====================YOUR TURN===========================\n";
    cout<<"========================================================\n";
    
    do{
        cout<<"Enter attack location: ";
        cin>>x;
    }while(x>9||x<1);
    
    do{
        cin>>y;
    }while(!(y=='a'||y=='b'||y=='c'||y=='d'||y=='e'||y=='f'||y=='g'||y=='h'));
    
    
    if(mapB[x][convert(y)]=='='){
        cout<<"\n--------------TARGET HIT--------------------------\n";
        mapA[x][convert(y)]='X';
        check=true;
        scr+=10;
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
    map_3[a][b]='='; map_3[a][b+1]='='; map_3[a][b+2]='='; map_3[a][b+3]='=';
    
    //--------------------------------------------------------------------------
    //------------->   randomly place 2nd ship:
    do{
        a=rand()%8+1;   //[1,8]
        b=rand()%5+1;   //must stay b/w [1,5]
    }while(map_3[a][b]=='='||map_3[a][b+1]=='='||map_3[a][b+2]=='='||map_3[a][b+3]=='=');
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
    disply(map1,SIZE);
    cout<<"\nWhere do you want to place a horizontal battleship(4 units long)? \n";
    
    do{
        cout<<"Enter the digit value between[1-8]: ";
        cin>>x;
    }while(x>8||x<1);
    
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

int check(char map_1[][SIZE],int,char map_3[][SIZE],int){
    bool all_1=true,all_3=true;
    int temp=0;
    for(int i=1;i<9;i++){
        for(int j=1;j<9;j++){
            if(map_1[i][j]=='='){
                all_1=false;
            }
            if(map_3[i][j]=='='){
                all_3=false;
            }
        }
    }
    if(all_1==true){
        temp=1;
        cout<<"\n------------------COMPUTER WON-------------------------\n";
        cout<<"\n\n=======================================================\n"
                <<"===========ALL TARGETS HAVE BEEN HIT===================\n"
                <<"=======================================================\n";
    }
    else if(all_3==true){
        temp=3;
        cout<<"\n---------------------YOU WON-------------------------\n";
        cout<<"\n\n=======================================================\n"
                <<"===========ALL TARGETS HAVE BEEN HIT===================\n"
                <<"=======================================================\n";
    }
    return temp;
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


void intro(){
     cout<<endl<<
",-----.    ,---. ,--------.,--------.,--.   ,------. ,---.  ,--.  ,--.,--.,------. \n"<<  
"|  |) /_  /  O  \'---.  .--''--.  .--'|  |   |  .---''   .-' |  '--'  ||  ||  .--. ' \n"<< 
"|  .-.  ||  .-.  |  |  |      |  |   |  |   |  `--, `.  `-. |  .--.  ||  ||  '--' | \n"<<
"|  '--' /|  | |  |  |  |      |  |   |  '--.|  `---..-'    ||  |  |  ||  ||  | --' \n"<<  
"`------' `--' `--'  `--'      `--'   `-----'`------'`-----' `--'  `--'`--'`--'"<<endl;
 }

void highscr(int *a,int size){
    for(int i=0;i<SIZE-1;i++){
        for(int j=i+1;j<SIZE;j++){
            if(*(a+j)>*(a+i)){
                *(a+j)=*(a+j)^*(a+i);
                *(a+i)=*(a+j)^*(a+i);
                *(a+j)=*(a+j)^*(a+i);
            }
        }
    }
    //-------------------------------
    cout<<"HIGHSCORE:\n";
    for(int i=0;i<SIZE;i++){
        cout<<setw(2)<<i+1<<"."<<setw(4)<<*(a+i)<<endl;
    }
}