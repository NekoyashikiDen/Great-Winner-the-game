#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
using namespace std;
int seed,fortune,in,bpool,count;
bool isQuick;
char *filename=(char *)malloc(10);

bool confirm();
void bpset();
int hash(int seed);
void getinf();
void ct(int sec);
void countdown();
int rolldice();
int play();
void game();
bool cos();
bool qcos();
void showinf();
void end();

class Account{
private:
	int UserFt;
	int UserCt;
public:
	Account();
	string Username;
	int GetUserFt() {return UserFt;}
	int GetUserCt() {return UserCt;}
};
Account::Account(){
	cout<<"Please set your name(less than 10 characters): ";
	cin>>Username;
	UserFt=1000;
	UserCt=0;
}

void main(){
	cout<<"***********************************************************************"<<endl;
	cout<<"Welcome to the Great Winner! This is the place for winning your dreams!"<<endl;
	cout<<"***********************************************************************"<<endl<<endl;
	cout<<"Warning: follow the instruction, or I don't know what will happen, either. :)"<<endl;
	while(1){
		if(confirm()==false) break;
		cout<<endl;
		bpool=0;
		bpset();
		showinf();
		while(1){
			game();
			count++;
			if(fortune<=0) break;
			if(bpool<=0||count%20==0) bpset();
			showinf();
			if(isQuick==true){
				if(qcos()==false) break;
			}
			else{
				if(cos()==false) break;
			}
		}
		cout<<"Game over! Your final fortune: "<<fortune<<"$. You have played "<<count<<" turns."<<endl;
	}
	end();
}

bool confirm(){
	char cc;
	isQuick=false;
	while(1){
		cout<<"Load/Create a game/Start a quick game or Quit?(L/C/S/Q): ";
		cin>>cc;
		if(cc=='l'||cc=='L'){
			cout<<"Please input your account name: ";
			cin>>filename;
			ifstream data(filename,ios_base::binary);
			if(data){
				data>>fortune>>count;
				data.close();
				cout<<"Loading complete!";
				break;
			}
			else cout<<"Account not found. :("<<endl;
		}
		else if(cc=='c'||cc=='C'){
			Account NewUser;
			NewUser.Username.copy(filename,NewUser.Username.length(),0);
			fortune=1000;
			count=0;
			*(filename+NewUser.Username.length())='\0';
			ofstream data(filename,ios_base::binary);
			data<<NewUser.GetUserFt()<<' '<<NewUser.GetUserCt();
			data.close();
			cout<<"Data created!";
			break;
		}
		else if(cc=='s'||cc=='S'){
			fortune=1000;
			count=0;
			isQuick=true;
			break;
		}
		else if(cc=='q'||cc=='Q'){
			return false;
		}
	}
	return true;
}

void bpset(){
	srand(time(0));
	do {bpool+=rand()+rand();} while(bpool<=10000);
	cout<<"Bonus pool updated. ";
}

void showinf(){
	cout<<"The current bonus pool: "<<bpool<<"$."<<endl;
	cout<<"Your current fortune: "<<fortune<<"$."<<endl;
}

int hash(int seed){
	srand(time(0));
	for(int i=0;i<seed;i++){
		seed=rand();
	}
	return seed;
}

void getinf(){
	cout<<"Please input a number to start your fortune: ";
	cin>>seed;
	srand(hash(seed));
	cout<<"Please input the prize you want to invest: ";
	while(1){
		cin>>in;
		if(in<50) cout<<"At least 50$ is required: ";
		else if(in>fortune) cout<<"You don't have enough money: ";
		else break;
	}
}

void ct(int sec){
	int t1=clock(),t2;
	while((t2=clock())-t1<(sec*1000));
}

void countdown(){
	cout<<endl;
	for(int i=0;i<3;i++){
		cout<<"Good luck! :) Start in "<<3-i<<"s.";
		ct(1);
		cout<<"\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
	}
}

int rolldice(){
	int dice1,dice2,luck;
	dice1=rand()%6+1;
	dice2=rand()%6+1;
	luck=dice1+dice2;
	cout<<"Dice_1: "<<dice1<<"	Dice_2: "<<dice2<<"	Sum: "<<luck<<endl;
	return luck;
}

int play(){
	double rate=0.007;
	int point=rolldice(),curpnt,bonus;
	cout<<"The point is "<<point<<". Current rate: "<<rate<<endl;
	switch(point){
	case 7:
	case 11:
		bonus=(int)(bpool+in)*rate*4;
		cout<<"You win! Bonus: ("<<bpool<<" + "<<in<<") * "<<rate<<" * 4 = "<<bonus<<"$"<<endl<<endl;
		in+=bonus;
		bpool-=bonus;
		return 0;
	case 2:
	case 3:
	case 12:
		bpool+=in;
		in=0;
		cout<<"Your lose! Bonus: "<<in<<"$"<<endl<<endl;
		return 0;
	}
	while(1){
		rate+=0.007;
		cout<<"Pass, current rate: "<<rate<<endl;
		ct(1);
		curpnt=rolldice();
		if(curpnt==7){
			bpool+=in;
			in=0;
			cout<<"Your lose! Current bonus: "<<in<<"$"<<endl<<endl;
			return 0;
		}
		else if(curpnt==point){
			bonus=(int)(bpool+in)*rate;
			cout<<"You win! Current bonus: ("<<bpool<<" + "<<in<<") * "<<rate<<" = "<<bonus<<"$"<<endl<<endl;
			in+=bonus;
			bpool-=bonus;
			return 0;
		}
	}
}

void game(){
	getinf();
	fortune-=in;
	countdown();
	play();
	fortune+=in;
}

bool cos(){
	char as;
	while(1){
		cout<<"Continue? Or save?(Y/N/S): ";
		cin>>as;
		if(as=='y'||as=='Y') return true;
		else if(as=='n'||as=='N') return false;
		else if(as=='s'||as=='S'){
			ofstream data(filename,ios_base::binary|ios_base::trunc);
			data<<fortune<<' '<<count;
			data.close();
			cout<<"Data saved! ";
		}
	}
}

bool qcos(){
	char as;
	while(1){
		cout<<"Continue?(Y/N): ";
		cin>>as;
		if(as=='y'||as=='Y') return true;
		else if(as=='n'||as=='N') return false;
	}
}

void end(){
	cout<<"Welcome back for your dreams at any time! :)";
	getch();
}