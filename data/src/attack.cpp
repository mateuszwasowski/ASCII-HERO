#include <iostream>
#include <fstream>
#include <conio.h>
#include <vector>
#include <Windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;

string intToStr4(int n)
{
     string tmp, ret;
     if(n < 0) {
      ret = "-";
      n = -n;
     }
     do {
      tmp += n % 10 + 48;
      n -= n % 10;
     }
     while(n /= 10);
     for(int i = tmp.size()-1; i >= 0; i--)
      ret += tmp[i];
     return ret;
}

void attack(){
	
	fstream map;
	fstream enemy_save, hero_save;
	fstream temp;
	fstream film_1, film_2;
	fstream gameover_1, gameover_2, gameover_3;
	vector <string> cord_y_x;
	vector <string> save_y_x;
	string temp_line;
	unsigned char key;
	int select=0,temp_int=0, temp_random=0;
	int hero_hp=0,hero_power=0,hero_level=0, hero_exp=0, damage=0;
	int enemy_hp=0,enemy_power=0,enemy_dodge=0,enemy_level=0;
	string hero_name="ERROR", enemy_name="ERROR", currentmap;
	
	bool dodged = false;
	
	film_1.open("data/animations/film_attack1.txt", ios::in | ios::out );
	film_2.open("data/animations/film_attack2.txt", ios::in | ios::out );
	
	gameover_1.open("data/animations/gameover1.txt", ios::in | ios::out );
	gameover_2.open("data/animations/gameover2.txt", ios::in | ios::out );
	gameover_3.open("data/animations/gameover3.txt", ios::in | ios::out );
	
	map.open("data/maps/attackmap.txt", ios::in | ios::out );
	hero_save.open("data/save/hero_save.txt", ios::in | ios::out );
	temp.open( "data/save/temp.txt", ios::in | ios::out | ofstream::trunc);
	
	srand( time( NULL ) );

	if (map.good() == true && hero_save.good() == true && film_1.good() == true && film_2.good() == true){
		
		while(map.eof() != true){
			
			getline( map , temp_line );
			
			cord_y_x.push_back(temp_line);
			
		}
		cord_y_x[20]="PRESS ENTER TO SELECT";
		
		
		//+++++++++++++HERO LOAD +++++++++++++++++++++
		
		for(int i=0; i<24; i++){
			
			getline( hero_save , temp_line );
			
			save_y_x.push_back(temp_line);
			
			if(i<7){
				
			cord_y_x[5+i].erase(2,temp_line.length());
			cord_y_x[5+i].insert(2, temp_line);
			
			}
			else if(i==9){
				
				cord_y_x[2].erase(6,temp_line.length());
				cord_y_x[2].insert(6,temp_line);
				
				hero_level = atoi(temp_line.c_str());
		
			}
			else if(i==10){
				
				cord_y_x[3].erase(5,temp_line.length());
				cord_y_x[3].insert(5,temp_line);
				
				hero_hp = atoi(temp_line.c_str());

			}
			else if(i==11){
				hero_power = atoi(temp_line.c_str());
				
			}
			
			else if(i==13){
				hero_name = temp_line;

				cord_y_x[1].erase(2,hero_name.length());
				cord_y_x[1].insert(2,hero_name);
				
			}
			else if(i==14){
				
				hero_exp = atoi(temp_line.c_str());
				
			}
			else if ( i == 18 ){
				 currentmap = temp_line;
							 
			}
		}
		
		if(currentmap == "gamefile000" || currentmap == "gamefile001"){
		enemy_save.open("data/enemies/bunny.txt", ios::in | ios::out );
		}
		else if (currentmap == "gamefile002" ){
		enemy_save.open("data/enemies/bunny1.txt", ios::in | ios::out );
		}
		else if (currentmap == "gamefile005" ){
		enemy_save.open("data/enemies/frogking.txt", ios::in | ios::out );
		}
		else  {
		enemy_save.open("data/enemies/frog.txt", ios::in | ios::out );
		}
		
		if (enemy_save.good()==false){
			cout << "CAN'T OPEN ENEMY FILE!";
			key = getch();
		}
		//+++++++++++++ENEMY LOAD +++++++++++++++++++++
		
		for(int i=0; i<14; i++){
			
			getline( enemy_save , temp_line );
			
			if(i<7){
				
			cord_y_x[5+i].erase(21,16);
			cord_y_x[5+i].insert(21, temp_line);
			
			}
			else if(i==9){
				
				enemy_level = atoi(temp_line.c_str());
				
				cord_y_x[2].erase(26,temp_line.length());
				cord_y_x[2].insert(26,temp_line);
				
			}
			else if(i==10){
				
				enemy_hp = atoi(temp_line.c_str());		
				
				cord_y_x[3].erase(25,temp_line.length());
				cord_y_x[3].insert(25,temp_line);
				
			}
			else if(i==11){
				enemy_power = atoi(temp_line.c_str());
				
			}
			else if(i==12){
				enemy_dodge = atoi(temp_line.c_str());
			}
			else if(i==13){
				enemy_name = temp_line;

				cord_y_x[1].erase(22,enemy_name.length());
				cord_y_x[1].insert(22,enemy_name);

			}
			
		}
		temp_line="";
		
		cord_y_x.push_back(temp_line);
		
		select = 1;
		
		temp_line = "[ATTACK]";
		
		cord_y_x[15].erase(3,temp_line.length());
		cord_y_x[15].insert(3,temp_line);
		
		temp_line = "RUN";
		
		cord_y_x[17].erase(4,temp_line.length());
		cord_y_x[17].insert(4,temp_line);
		
	
		
		/* select:
		1 - ATTACK // PUNCH
		2 - RUN // KICK
		3 - POWER UP
		4 - BACK
		*/
		system("CLS");
		
		// +++++++++++++++++++++++++++++++++++ANIMACJA STARTOWA
		
		for(int j=0 ; j< 16; j++){
			
		for(int i = 0; i < 20;i++){
			if(j%2==0){
			
			getline(film_1, temp_line);
			cout<<temp_line<<endl;
			
			}
			else{
			getline(film_2, temp_line);
			cout<<temp_line<<endl;
			}
		}
		 Sleep(50);
		system("CLS");
			film_1.clear();
			film_1.seekg(0, ios::beg);
			film_2.clear();
			film_2.seekg(0, ios::beg);
		
		}
		
		// +++++++++++++++++++++++++++++++++++++++++++++++++++++
		
		
		while ( key != 8 ){  //backspace
		
			
			system("CLS");
			
			for( int i = 0 ; i <= 20; i ++){
			
			cout << cord_y_x[i]<<endl;
			
			}
			
			if ( cord_y_x[20] == "FAILED TO ESCAPE!"){
				
				cout << "ENEMY ATTACKED " << hero_name<<endl;
				cout << "ENEMY DEALT: " <<enemy_power <<" DAMAGE"<<endl;
					
			}
			
			cord_y_x[20]="PRESS ENTER TO SELECT";
			
		 	key=getch();
			
			if ( key == 'w' || key == 'W'){
				
				if (select == 2){
				
					select = 1;
					
					cord_y_x[15][3]='[';
					cord_y_x[15][10]=']';
					cord_y_x[17][3]='~';
					cord_y_x[17][7]='~';
					
				}
				
			}
			
			else if ( key == 's' || key == 'S'){
				
				if (select == 1){
					select = 2;
					
					cord_y_x[15][3]='~';
					cord_y_x[15][10]='~';
					cord_y_x[17][3]='[';
					cord_y_x[17][7]=']';
					
					
				}
				
			}
			
			/*
			+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			*/
			
			
			else if ( key == 13 && select == 1){  // 13 - enter : carriage return
				
				
				
				
				select = 1;
		
				temp_line = "[ATTACK]";
		
				cord_y_x[15].erase(3,temp_line.length());
				
				temp_int = temp_line.length();
				temp_line = "";
				
				for (int i = 0 ; i < temp_int ; i++ ){
				temp_line = temp_line + '~';
				}
				
				cord_y_x[15].insert(3, temp_line);
				
				temp_line = "RUN";
				
				cord_y_x[17].erase(4,temp_line.length());
				
				temp_int = temp_line.length();
				temp_line = "";
					
				for (int i = 0 ; i < temp_int ; i++ ){
				temp_line = temp_line + '~';
				}
					
				cord_y_x[17].insert(4, temp_line);
				
				temp_line = "[PUNCH]";
				
				cord_y_x[15].erase(3,temp_line.length());
				cord_y_x[15].insert(3,temp_line);
				
				temp_line = "KICK";
				
				cord_y_x[17].erase(4,temp_line.length());
				cord_y_x[17].insert(4,temp_line);
				
				temp_line = "POWER UP";
		
				cord_y_x[15].erase(22,temp_line.length());
				cord_y_x[15].insert(22,temp_line);
				
				temp_line = "BACK";
				
				cord_y_x[17].erase(22,temp_line.length());
				cord_y_x[17].insert(22,temp_line);
				
				while ( key != 8 ){
					
					system("CLS");
			
					for( int i = 0 ; i <= 20; i ++){
					
					cout << cord_y_x[i]<<endl;
					
					}
					cord_y_x[20]="PRESS ENTER TO SELECT";
					
					

					if ( enemy_hp > 0 || hero_hp > 0){
				
					key = getch();
			
					}
					
					
						if ( key == 'w' || key == 'W'){
							
							if (select == 2){
							
								select = 1;
								
								cord_y_x[15][3]='[';
								cord_y_x[15][9]=']';
								cord_y_x[17][3]='~';
								cord_y_x[17][8]='~';
								
								
								
							}
							else if ( select == 3){
								
								select = 2;
								
								cord_y_x[15][21]='~';
								cord_y_x[15][30]='~';
								cord_y_x[17][3]='[';
								cord_y_x[17][8]=']';
								
								
							}
							else if ( select == 4){
								
								select = 3;
								
								cord_y_x[15][21]='[';
								cord_y_x[15][30]=']';
								cord_y_x[17][21]='~';
								cord_y_x[17][26]='~';
								
							}
							
						}
						else if ( key == 's' || key == 'S'){
							
							if (select == 1){
								
								select = 2;
								
								cord_y_x[15][3]='~';
								cord_y_x[15][9]='~';
								cord_y_x[17][3]='[';
								cord_y_x[17][8]=']';
										
							}
							else if (select == 2){
								
								select = 3;
								
								cord_y_x[15][21]='[';
								cord_y_x[15][30]=']';
								cord_y_x[17][3]='~';
								cord_y_x[17][8]='~';
										
							}
							else if (select == 3){
								
								select = 4;
								
								cord_y_x[15][21]='~';
								cord_y_x[15][30]='~';
								cord_y_x[17][21]='[';
								cord_y_x[17][26]=']';
								
										
							}
							
						}
							else if ( key == 13 ){
							
							key = 0;
							
							if (select == 1){
								
								//+++ OBRAZENIA ENEMY
								
								dodged = false;
								
								temp_random = ( rand() % 10) + 0;
								
								if (temp_random > enemy_dodge){
								
								temp_line = intToStr4(enemy_hp);
								
								cord_y_x[3].erase(25,temp_line.length());
								
								temp_int = temp_line.length();
								temp_line = "";
				
								for (int i = 0 ; i < temp_int ; i++ ){
								temp_line = temp_line + '/';
								}
								
								cord_y_x[3].insert(25, temp_line);
								
								enemy_hp = enemy_hp - hero_power;
								
								if (enemy_hp <= 0){
									enemy_hp=0;
									
								}
								
								temp_line = intToStr4(enemy_hp);
								cord_y_x[3].erase(25,temp_line.length());
								cord_y_x[3].insert(25,temp_line);
								
								}
								else {
									
									dodged = true;
									
								}
								
								// +++ OBRAZENIA HERO
								
								
								if (enemy_hp > 0){
								
								temp_line = intToStr4(hero_hp);
								cord_y_x[3].erase(5,temp_line.length());
								
								temp_int = temp_line.length();
								temp_line = "";
				
								for (int i = 0 ; i < temp_int ; i++ ){
								temp_line = temp_line + '/';
								}
								
								cord_y_x[3].insert(5, temp_line);
								
								hero_hp = hero_hp - enemy_power;
								
								if (hero_hp <= 0){
									hero_hp = 0;
									
								}
								
								temp_line = intToStr4(hero_hp);
								
								cord_y_x[3].erase(5,temp_line.length());
								cord_y_x[3].insert(5,temp_line);
								
								}
								system("CLS");
								
								cord_y_x[15][3]='~';
								cord_y_x[15][9]='~';
								
								if (dodged == false ){
									
								cord_y_x[20]="YOU ATTACKED ENEMY";
								}
								else {
								cord_y_x[20]="YOU MISSED!!";
								}	
			
			
								for( int i = 0 ; i <= 20; i ++){
					
								cout << cord_y_x[i]<<endl;
					
								}
								
								if (dodged == false ){
								cout << "YOU DEALT: "<<hero_power<<" DAMAGE!"<<endl;
								}
								else {
									cout << "ENEMY DODGED YOUR ATTACK!"<<endl;
								}
								if (enemy_hp > 0){
								cout << "ENEMY ATTACKED " << hero_name<<endl;
								cout << "ENEMY DEALT: " <<enemy_power <<" DAMAGE"<<endl;
								}
								cout << "PRESS ENTER TO CONTINUE!";
								
								cord_y_x[20]="";
								
								while (key != 13){
									key = getch();
								}
								
								key = 0;
								
								break;
								
							}
							else if (select == 2){
								
								//+++ OBRAZENIA ENEMY
								
								dodged = false;
								
								
								
								temp_random = ( rand() % 10) + 0;
								
								if (temp_random > enemy_dodge){
									
									temp_line = intToStr4(enemy_hp);
								
									cord_y_x[3].erase(25,temp_line.length());
									
									temp_int = temp_line.length();
									temp_line = "";
					
									for (int i = 0 ; i < temp_int ; i++ ){
									temp_line = temp_line + '/';
									}
								
									cord_y_x[3].insert(25, temp_line);
									
								if (temp_random < 7){
									
									enemy_hp = enemy_hp - (0*hero_power);
									damage = (0*hero_power);
								}
								else {
									enemy_hp = enemy_hp - (2*hero_power);
									damage = (2*hero_power);
								}

								if (enemy_hp <= 0){
									enemy_hp=0;
									
								}
								
								temp_line = intToStr4(enemy_hp);
								
								cord_y_x[3].erase(25,temp_line.length());
								cord_y_x[3].insert(25,temp_line);
								
								}else {
									
									dodged = true;
									
								}
								
								// +++ OBRAZENIA HERO
								
								if (enemy_hp > 0){
								
								temp_line = intToStr4(hero_hp);
								cord_y_x[3].erase(5,temp_line.length());
								
								temp_int = temp_line.length();
								temp_line = "";
				
								for (int i = 0 ; i < temp_int ; i++ ){
								temp_line = temp_line + '/';
								}
								
								cord_y_x[3].insert(5, temp_line);
												
								hero_hp = hero_hp - enemy_power;
								
								if (hero_hp <= 0){
									hero_hp = 0;
									
								}
								
								temp_line = intToStr4(hero_hp);
								
								cord_y_x[3].erase(5,temp_line.length());
								cord_y_x[3].insert(5,temp_line);
								}
							
								system("CLS");
								
								cord_y_x[17][3]='~';
								cord_y_x[17][8]='~';
								
								if (dodged == false ){
									
								cord_y_x[20]="YOU ATTACKED ENEMY";
								}
								else {
								cord_y_x[20]="YOU MISSED!!";
								}
			
								for( int i = 0 ; i <= 20; i ++){
					
								cout << cord_y_x[i]<<endl;
					
								}

								if (dodged == false ){
								cout << "YOU DEALT: "<<damage<<" DAMAGE!"<<endl;
								}
								else {
									cout << "ENEMY DODGED YOUR ATTACK!"<<endl;
								}
								if (enemy_hp > 0){
								
								cout << "ENEMY ATTACKED " << hero_name<<endl;
								cout << "ENEMY DEALT: " <<enemy_power <<" DAMAGE"<<endl;
								}
								cout << "PRESS ENTER TO CONTINUE!";
								
								cord_y_x[20]="";
								
								while (key != 13){
									key = getch();
								}
								
								
								break;
								
								
								
							}
							else if (select == 3){
								
								// +++ OBRAZENIA HERO
								
								temp_line = intToStr4(hero_hp);
								cord_y_x[3].erase(5,temp_line.length());
								
								temp_int = temp_line.length();
								temp_line = "";
				
								for (int i = 0 ; i < temp_int ; i++ ){
								temp_line = temp_line + '/';
								}
								
								cord_y_x[3].insert(5, temp_line);
								
								hero_hp = hero_hp - enemy_power;
								
								if (hero_hp <= 0){
									hero_hp = 0;
									
								}
								
								temp_line = intToStr4(hero_hp);
								
								cord_y_x[3].erase(5,temp_line.length());
								cord_y_x[3].insert(5,temp_line);
								
								
								system("CLS");
								
								cord_y_x[20]="YOU ARE POWERING UP!";
								
								cord_y_x[15][21]='~';
								cord_y_x[15][30]='~';
								
								for( int i = 0 ; i <= 20; i ++){
					
								cout << cord_y_x[i]<<endl;
					
								}
								
								cout << "ENEMY ATTACKED " << hero_name<<endl;
								cout << "ENEMY DEALT: " <<enemy_power <<" DAMAGE"<<endl;
								
								cout << "PRESS ENTER TO CONTINUE!";
								
								cord_y_x[20]="";
								
								while (key != 13){
									key = getch();
								}
								
								
								
								hero_power = hero_power+(hero_power/2);
								
								
								break;
								
								
									
							}
							else if ( select == 4){
								
								cord_y_x[17][21]='~';
								cord_y_x[17][26]='~';
								
								break;
							}
							
						}
					
					
					
				}  // koniec petli while1
				
				select = 1;
				
				temp_line = "[PUNCH]";
		
				cord_y_x[15].erase(3,temp_line.length());
				
				temp_int = temp_line.length();
				temp_line = "";
				
				for (int i = 0 ; i < temp_int ; i++ ){
				temp_line = temp_line + '~';
				}
				
				cord_y_x[15].insert(3, temp_line);
				
				temp_line = "KICK";
				
				cord_y_x[17].erase(4,temp_line.length());
				
				temp_int = temp_line.length();
				temp_line = "";
					
				for (int i = 0 ; i < temp_int ; i++ ){
				temp_line = temp_line + '~';
				}
				
				cord_y_x[17].insert(4, temp_line);
				
				temp_line = "POWER UP";
		
				cord_y_x[15].erase(22,temp_line.length());
				
				temp_int = temp_line.length();
				temp_line = "";
				
				for (int i = 0 ; i < temp_int ; i++ ){
				temp_line = temp_line + '~';
				}
				
				cord_y_x[15].insert(22, temp_line);
				
				temp_line = "BACK";
				
				cord_y_x[17].erase(22,temp_line.length());
				
				temp_int = temp_line.length();
				temp_line = "";
					
				for (int i = 0 ; i < temp_int ; i++ ){
				temp_line = temp_line + '~';
				}
				
				cord_y_x[17].insert(22, temp_line);
				
				temp_line = "[ATTACK]";
				
				cord_y_x[15].erase(3,temp_line.length());
				cord_y_x[15].insert(3,temp_line);
				
				temp_line = "RUN";
				
				cord_y_x[17].erase(4,temp_line.length());
				cord_y_x[17].insert(4,temp_line);
				
			}
			
			/*
			+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			*/
			
			else if ( key == 13 && select == 2){  // 13 - enter : carriage return
				
				temp_random = ( rand() % 100) + 0;
						
				if (temp_random < 60){
					
				break;
					
				}
				else {
				
				system ("CLS");
					
				cord_y_x[20]="FAILED TO ESCAPE!";
				
				key = 0;
				
				temp_line = intToStr4(hero_hp);
				cord_y_x[3].erase(5,temp_line.length());
				
				hero_hp = hero_hp - enemy_power;
				
				if (hero_hp <= 0){
					hero_hp = 0;
				}
				
				temp_line = intToStr4(hero_hp);
				
				cord_y_x[3].insert(5,temp_line);
				
				select = 1;
					
					cord_y_x[15][3]='[';
					cord_y_x[15][10]=']';
					cord_y_x[17][3]='~';
					cord_y_x[17][7]='~';
				
				for( int i = 0 ; i <= 20; i ++){
			
				cout << cord_y_x[i]<<endl;
			
				}
				
				if (enemy_hp > 0){
								
								cout << "ENEMY ATTACKED " << hero_name<<endl;
								cout << "ENEMY DEALT: " <<enemy_power <<" DAMAGE"<<endl;
								}
								cout << "PRESS ENTER TO CONTINUE!";
								
				key = 0;				
				while (key != 13){
				key = getch();
				}
				
				}
			}
			
			if ( hero_hp == 0 ){
				
				break;
				
				
			}
			
			if (  enemy_hp == 0 ){
				
				break;
				
			}
			
			

		}
	
		map.close();
		
		if ( hero_hp <= 0 ){
			
			system ("CLS");
			
				if ( gameover_1.good() == true && gameover_2.good() == true && gameover_3.good() == true ){
					
						while ( key != 8){
								
						for(int i = 0; i < 20; i++){
							
							if ( temp_int == 1 ){
							
							getline( gameover_1, temp_line );
							cout << temp_line << endl;
							
							}
							else if( temp_int == 2 || temp_int == 4 ){
								
							getline( gameover_3, temp_line );
							cout << temp_line << endl;
							
							}
							else if( temp_int == 3 ){
								
							getline( gameover_2, temp_line );
							cout << temp_line << endl;
							
							}
						}
						
						Sleep(300); //nowa klatka animacji co 300ms
						system("CLS");
						
						//zmienianie klatek 
						
						if ( temp_int == 1 ){ 
							temp_int = 2;
						}
						else if ( temp_int == 2 ){
							temp_int = 3;	
						}
						else if ( temp_int == 3 ){	
							temp_int = 4;	
						}
						else {
							temp_int = 1;
						}
						
						//zerowanie miejsca w którym jest aktualnie we wczytywanej mapie
						gameover_1.clear();
						gameover_1.seekg( 0, ios::beg );
						gameover_2.clear();
						gameover_2.seekg( 0, ios::beg );
						gameover_3.clear();
						gameover_3.seekg( 0, ios::beg );
						
						}	
	
				}
				else {
					
					cout << "ERROR. Can't open some gameover animation files!";
					key = getch();
	
				}		
			
		}
		else if ( enemy_hp <= 0 ){
			
			key = 0;
			
			while ( key != 13 ){
			
			system ("CLS");
			
			cord_y_x[20]="YOU WON! PRESS ENTER TO CONTINUE!";
			
			for( int i = 0 ; i <= 20; i ++){
			
			cout << cord_y_x[i]<<endl;
			
			}

			key = getch();
		
			}
			
			hero_exp = hero_exp + enemy_level;
			save_y_x[14] = intToStr4(hero_exp);
			
			// |||||||||||||||||||||||||||||||||||||||||||||||| //zapisywanie exp herosa
				
					hero_save.clear();
					hero_save.seekg( 0, ios::beg );
					hero_save.close();
   					temp.close();
    				remove("data/save/hero_save.txt"); 
    				rename("data/save/temp.txt","data/save/hero_save.txt");
    				hero_save.open( "data/save/hero_save.txt", ios::in | ios:: out );
					temp.open( "data/save/temp.txt", ios::in | ios::out | ofstream::trunc);
					
					for ( int i = 0 ; i < 24 ; i++ ){ 
						
						hero_save << save_y_x[i] << endl;
						
					}
					
			// ||||||||||||||||||||||||||||||||||||||||||||||||
				
			system("CLS");
			
		}
		
	
		
	}
	else {
	
	cout << "ERROR. Can't open attackmap.txt or hero_save.txt or enemy file or animation filmattack files!"<<endl;
	key = getch();

	}
	

}
