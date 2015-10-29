#include <iostream>
#include <fstream>
#include <conio.h>
#include <vector>
#include <Windows.h>
#include <cstdlib>
#include <ctime>

#include "../hdrs/attack.h"
#include "../hdrs/heroscreen.h"
#include "../hdrs/gamefile003.h"


using namespace std;

string intToStr9(int n)
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

void gamefile004(){
	
	fstream map, hero_save, film1;
	ofstream temp;
	vector <string> cord_y_x;
	vector <string> save_y_x;
	string temp_line;
	unsigned char key, temp_key;
	unsigned char hero = '@';
	int hero_y = 0, hero_x = 0, temp_random = 1, fled_int = 0, int_lvl, lvl=0, exp = 0, int_exp=0, popuptext=0, int_nextexp = 0;
	int way;
	
	bool level_up  = false;
	bool killed = false;
	bool fled = false;
	bool talk = false;

	
	map.open( "data/maps/map005.txt", ios::in | ios::out );
	hero_save.open( "data/save/hero_save.txt", ios::in | ios:: out );
	temp.open( "data/save/temp.txt", ios::in | ios::out | ofstream::trunc);
	film1.open( "data/animations/chest.txt", ios::in | ios::out );
	
	system("CLS");
	
	struct stats{
	
		string lvl;  // save_y_x [9]
		string hp; // save_y_x [10]
		string power; // save_y_x [11]
		string dodge; // save_y_x [12]
		string name;  //save_y_x [13] 
		string exp;   //save_y_x [14] 
		string nextexp;  //save_y_x [15] 
		string hero_y;   //save_y_x [16] 
		string hero_x;  //save_y_x [17] 
		string save;   //save_y_x [18] 
		string inventory;  //save_y_x [19] 
	};
	
	stats h;
	
	if ( hero_save.good() == true ){  //wczytanie pozycji hero z pliku hero_save.txt oraz zapisanie aktualnej mapy
		
		for ( int  i = 0 ; i < 24 ; i ++){
			
			getline( hero_save , temp_line );
			
			save_y_x.push_back(temp_line);
			
			if ( i == 18 ){
				save_y_x[i] = "gamefile004";

			}
			else if ( i == 16 ){
				
				hero_y = atoi(temp_line.c_str());
				
			}
			else if ( i == 17 ){
				
				hero_x  = atoi(temp_line.c_str());
				
			}
			else if ( i == 9 ){
				
				lvl = atoi(temp_line.c_str());

			}
			else if ( i == 14){
				exp = atoi(temp_line.c_str());
			}
			else if ( i == 19 ){
				h.inventory = temp_line;
			}
		}
		
		
	}
	else {
		
		cout << "ERROR. Can't open hero_save.txt file!";
		key == getch();
		
	}
	
	if (map.good() == true){
		
			
			
		
		//  WCZYTANIE MAPY Z PLIKU I PRZEPISANIE JEJ NA CORDY PRZY POMOCY VECTORA STRINGOW
		//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		
		while(map.eof() != true){
			
			getline( map , temp_line );
			
			cord_y_x.push_back(temp_line);
			
		}
		
		temp_line = " ";
		
		cord_y_x.push_back(temp_line); //dodatkowa linia na wszelkie komentarze
		
		temp_key = cord_y_x[hero_y][hero_x]; // zapisuje w temp_key znak na którym stoi nasz hero
		
		cord_y_x[hero_y][hero_x] = hero; //wklejenie herosa na mape
		
		//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		
		while ( key != 8 ){  //backspace
		
			if(popuptext == 0){
				
				level_up = false;
				killed = false;
				fled = false;
				
			}
			
			system("CLS");
			
			// DRUKUJE MAPE
			//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			
			
			for( int i = 0 ; i <= 20; i ++){
			
			cout << cord_y_x[i] << endl;
			
			}
			
			//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			
			key = getch(); // pobieranie klawisza 
		   
		    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ KLAWISZ W 
		    
			if ( key == 'w' || key == 'W'){
				
				talk = false;
				
				if ( cord_y_x[hero_y-1][hero_x] == '-' || cord_y_x[hero_y-1][hero_x] == '*' || cord_y_x[hero_y-1][hero_x] == '|' ){
					
					//przemieszczenie herosa
					
					cord_y_x[20] = "Guess, i'll just go north...";
					cord_y_x[hero_y][hero_x] = temp_key;
					hero_y = hero_y-1;
					temp_key = cord_y_x[hero_y][hero_x];
					cord_y_x[hero_y][hero_x] = hero;
					
					// |||||||||||||||||||||||||||||||||||||||||||||||| //zapisywanie pozycji herosa w hero_save.txt
				
					hero_save.clear();
					hero_save.seekg( 0, ios::beg );
					hero_save.close();
   					temp.close();
    				remove("data/save/hero_save.txt"); 
    				rename("data/save/temp.txt","data/save/hero_save.txt");
    				hero_save.open( "data/save/hero_save.txt", ios::in | ios:: out );
					temp.open( "data/save/temp.txt", ios::in | ios::out | ofstream::trunc);
					
					for ( int i = 0 ; i < 24 ; i++ ){ 
						
						if ( i == 16 ){
							
							save_y_x[i] = intToStr9 (hero_y);
							
						}
						else if ( i == 17 ){
							
							//nic siê nie zmienia
							
						}
						
						
						hero_save << save_y_x[i] <<endl;
					}
					
					
					// ||||||||||||||||||||||||||||||||||||||||||||||||
					
					if ( cord_y_x[hero_y][hero_x+1] == 'C' || cord_y_x[hero_y-1][hero_x] == 'C' || cord_y_x[hero_y][hero_x-1] == 'C'){
					
					cord_y_x[20]= "PRESS ENTER TO OPEN CHEST!";
					talk =true;
					}
					
					//dodatkowe warunki
					
					if( temp_key == '*' ){
						
						temp_random = ( rand() % 100) + 0;
						
						if (temp_random < 94){
					
							cord_y_x[20]="I think it's some kind of maze!";
					
						}
						else {
							
							attack();
							
							fled = true;
							popuptext = 4;
							
							hero_save.clear();
							hero_save.seekg( 0, ios::beg );
							
							for ( int i = 0 ; i < 24 ; i++ ){  //sprawdzanie czy zwiêkszy³ siê lvl podczas walki		
								getline(hero_save, temp_line);
								
								if (i == 15){
									
									int_nextexp = atoi(temp_line.c_str());
									save_y_x[15] = temp_line;
									
								}
								if ( i == 14){
									int_exp = atoi(temp_line.c_str());
									save_y_x[14] = temp_line;
								}
							}
							
							if (int_exp > int_nextexp){
								
								lvl = int_lvl;
								level_up=true;
								killed = false;
								fled = false;
								
							}
							else if ( exp < int_exp){
								
								exp = int_exp;
								killed = true;
								fled = false;
								
							}

						
						}	
					}
					else if( temp_key == '|' ){
						
						cord_y_x[20] = "This road seems to go many ways...";
		
					}	
				}
				else if ( cord_y_x[hero_y-1][hero_x] == 'C'){
					
					cord_y_x[20]= "PRESS ENTER TO OPEN CHEST!";
					talk =true;
				}
				else {
					
					cord_y_x[20] = "Hmm, I have to find some other way.";
				
				}
			}
			
			//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ KLAWISZ S 
			
			else if ( key == 's' || key == 'S' ){
				
				talk = false;
				
				if ( cord_y_x[hero_y+1][hero_x] == '-' || cord_y_x[hero_y+1][hero_x] == '*' || cord_y_x[hero_y+1][hero_x] == '|' ){
					
					//przemieszczenie herosa
					
					cord_y_x[20] = "Guess, i'll just go south...";
					cord_y_x[hero_y][hero_x] = temp_key;
					hero_y = hero_y+1;
					temp_key = cord_y_x[hero_y][hero_x];
					cord_y_x[hero_y][hero_x] = hero;
					
					// |||||||||||||||||||||||||||||||||||||||||||||||| //zapisywanie pozycji herosa w hero_save.txt
				
					hero_save.clear();
					hero_save.seekg( 0, ios::beg );
					hero_save.close();
   					temp.close();
    				remove("data/save/hero_save.txt"); 
    				rename("data/save/temp.txt","data/save/hero_save.txt");
    				hero_save.open( "data/save/hero_save.txt", ios::in | ios:: out );
					temp.open( "data/save/temp.txt", ios::in | ios::out | ofstream::trunc);
					
					for ( int i = 0 ; i < 24 ; i++ ){  
						
						
						if ( i == 16 ){	
						
							save_y_x[i] = intToStr9 (hero_y);
							
						}
						else if ( i == 17 ){
							
							//nic siê nie zmienia
							
						}
						
						hero_save << save_y_x[i] <<endl;
					}
					
					// ||||||||||||||||||||||||||||||||||||||||||||||||
					
					if ( cord_y_x[hero_y][hero_x+1] == 'C' || cord_y_x[hero_y+1][hero_x] == 'C' || cord_y_x[hero_y][hero_x-1] == 'C'){
					
					cord_y_x[20]= "PRESS ENTER TO OPEN CHEST!";
					talk =true;
					}
					
					//dodatkowe warunki
					
					if( temp_key == '*' ){
						
						temp_random = ( rand() % 100) + 0;
						
						if (temp_random < 94){
					
							cord_y_x[20]="I think it's some kind of maze!";
					
						}
					    else {
					    	
							attack();
							
							fled = true;
							popuptext = 4;
							
							hero_save.clear();
							hero_save.seekg( 0, ios::beg );
							
							for ( int i = 0 ; i < 24 ; i++ ){  //sprawdzanie czy zwiêkszy³ siê lvl podczas walki								
								getline(hero_save, temp_line);
								
								if (i == 15){
									
									int_nextexp = atoi(temp_line.c_str());
									save_y_x[15] = temp_line;
									
								}
								else if ( i == 14){
									int_exp = atoi(temp_line.c_str());
									save_y_x[14] = temp_line;
								}
							}
							
							if (int_exp > int_nextexp){
								
								lvl = int_lvl;
								level_up=true;
								killed = false;
								fled = false;
								
							}
							else if ( exp < int_exp){
								
								exp = int_exp;
								killed = true;
								fled = false;
								
							}
							
							
						
						}						
					}
					else if( temp_key == '|' ){
						
						cord_y_x[20] = "This road seems to go many ways...";
						
					}	
				}
				else if ( cord_y_x[hero_y+1][hero_x] == 'C'){
					
					cord_y_x[20]= "PRESS ENTER TO OPEN CHEST!";
					talk =true;
				}
				else {
					
					cord_y_x[20] = "Hmm, I have to find some other way.";
				
				}
			}
			
			//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ KLAWISZ A
			
			else if ( key == 'a' || key == 'A'){
				
				talk = false;
				
				if ( cord_y_x[hero_y][hero_x-1] == '-' || cord_y_x[hero_y][hero_x-1] == '*' || cord_y_x[hero_y][hero_x-1] == '|' ){
					
					//przemieszczenie herosa
					
					cord_y_x[20] = "Guess, i'll just go west...";
					cord_y_x[hero_y][hero_x] = temp_key;
					hero_x = hero_x-1;
					temp_key = cord_y_x[hero_y][hero_x];
					cord_y_x[hero_y][hero_x] = hero;
					
					// |||||||||||||||||||||||||||||||||||||||||||||||| //zapisywanie pozycji herosa w hero_save.txt
				
					hero_save.clear();
					hero_save.seekg( 0, ios::beg );
					hero_save.close();
   					temp.close();
    				remove("data/save/hero_save.txt"); 
    				rename("data/save/temp.txt","data/save/hero_save.txt");
    				hero_save.open( "data/save/hero_save.txt", ios::in | ios:: out );
					temp.open( "data/save/temp.txt", ios::in | ios::out | ofstream::trunc);
					
					for ( int i = 0 ; i < 24 ; i++ ){ 
						
						if ( i == 16 ){
							
							//nic siê nie zmienia
							
						}
						else if ( i == 17 ){
							
						    save_y_x[i] = intToStr9 (hero_x);
							
						}
						
						hero_save << save_y_x[i] << endl;
					}
					
					// ||||||||||||||||||||||||||||||||||||||||||||||||
					
					if ( cord_y_x[hero_y][hero_x-1] == 'C' || cord_y_x[hero_y-1][hero_x] == 'C' || cord_y_x[hero_y+1][hero_x] == 'C'){
					
					cord_y_x[20]= "PRESS ENTER TO OPEN CHEST!";
					talk =true;
					}
					
					//dodatkowe warunki
					
					if( temp_key == '*' ){
						
						temp_random = ( rand() % 100) + 0;
						
						if (temp_random < 94){
					
						cord_y_x[20]="I think it's some kind of maze!";
					
						}
						else {	
						attack();
						
						fled = true;
						popuptext = 4;
						
							hero_save.clear();
							hero_save.seekg( 0, ios::beg );
							
							for ( int i = 0 ; i < 24 ; i++ ){  //sprawdzanie czy zwiêkszy³ siê lvl podczas walki								
								getline(hero_save, temp_line);
								
								if (i == 15){
									
									int_nextexp = atoi(temp_line.c_str());
									save_y_x[15] = temp_line;
									
								}
								else if ( i == 14){
									int_exp = atoi(temp_line.c_str());
									save_y_x[14] = temp_line;
								}
							}
							
						if (int_exp > int_nextexp){
								
							lvl = int_lvl;
							level_up = true;
							killed = false;
							fled = false;
								
						}
						else if ( exp < int_exp){
						
							exp = int_exp;
							killed = true;
							fled = false;
								
						}
				
						
						}
					}
					else if( temp_key=='|' ){
						
						cord_y_x[20] = "This road seems to go many ways...";
						
					}
				}
				else if ( cord_y_x[hero_y][hero_x-1] == 'C'){
					
					cord_y_x[20]= "PRESS ENTER TO OPEN CHEST!";
					talk =true;
				}
				else {
					
					cord_y_x[20] = "Hmm, I have to find some other way.";
				
				}
			}
			
			//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ KLAWISZ D			
			
			else if ( key == 'd' || key == 'D' ){
				
				talk = false;
				
				if ( cord_y_x[hero_y][hero_x+1] == '-' || cord_y_x[hero_y][hero_x+1] == '*' || cord_y_x[hero_y][hero_x+1] == '|' ){
					
					//przemieszczenie herosa
					
					cord_y_x[20] = "Guess, i'll just go east...";
					cord_y_x[hero_y][hero_x] = temp_key;
					hero_x = hero_x+1;
					temp_key = cord_y_x[hero_y][hero_x];
					cord_y_x[hero_y][hero_x] = hero;
					
					// |||||||||||||||||||||||||||||||||||||||||||||||| //zapisywanie pozycji herosa w hero_save.txt
				
					hero_save.clear();
					hero_save.seekg( 0, ios::beg );
					hero_save.close();
   					temp.close();
    				remove("data/save/hero_save.txt"); 
    				rename("data/save/temp.txt","data/save/hero_save.txt");
    				hero_save.open( "data/save/hero_save.txt", ios::in | ios:: out );
					temp.open( "data/save/temp.txt", ios::in | ios::out | ofstream::trunc);
					
					for ( int i = 0 ; i < 24 ; i++ ){ 
						
						if ( i == 16 ){
							
							//nic siê nie zmienia
							
						}
						else if ( i == 17 ){
							
							save_y_x[i] = intToStr9 (hero_x);
							
						}
						
						hero_save << save_y_x[i] << endl;
					}
					
					// ||||||||||||||||||||||||||||||||||||||||||||||||
					
					if ( cord_y_x[hero_y][hero_x+1] == 'C' || cord_y_x[hero_y-1][hero_x] == 'C' || cord_y_x[hero_y+1][hero_x] == 'C'){
					
					cord_y_x[20]= "PRESS ENTER TO OPEN CHEST!";
					talk =true;
					}
					
					//dodatkowe warunki				
					
					if( temp_key == '*' ){
						
						temp_random = ( rand() % 100) + 0;
						
						if (temp_random < 94){
					
						cord_y_x[20]="I think it's some kind of maze!";
					
						}
						else {	
						attack();
						
						fled = true;
						popuptext = 4;
						
							hero_save.clear();
							hero_save.seekg( 0, ios::beg );
							
							for ( int i = 0 ; i < 24 ; i++ ){  //sprawdzanie czy zwiêkszy³ siê lvl podczas walki								
								getline(hero_save, temp_line);
								
								if (i == 15){
									
									int_nextexp = atoi(temp_line.c_str());
									save_y_x[15] = temp_line;
									
								}
								else if ( i == 14){
									int_exp = atoi(temp_line.c_str());
									save_y_x[14] = temp_line;
								}
							}
							
						if (int_exp > int_nextexp){
								
							lvl = int_lvl;
							level_up = true;
							killed = false;
							fled = false;
								
						}
						else if ( exp < int_exp){
						
							exp = int_exp;
							killed = true;
							fled = false;
								
						}
				
						
						}
					}
					else if( temp_key == '|' ){
						
						cord_y_x[20] = "This road seems to go many ways...";
						
					}	
				}
				else if ( hero_y == 11 && hero_x+1 == 39 ){
						
					hero_x = hero_x - 38;
					
					
					// |||||||||||||||||||||||||||||||||||||||||||||||| //zapisywanie pozycji herosa w hero_save.txt
				
					hero_save.clear();
					hero_save.seekg( 0, ios::beg );
					hero_save.close();
   					temp.close();
    				remove("data/save/hero_save.txt"); 
    				rename("data/save/temp.txt","data/save/hero_save.txt");
    				hero_save.open( "data/save/hero_save.txt", ios::in | ios:: out );
					temp.open( "data/save/temp.txt", ios::in | ios::out | ofstream::trunc);
					
					for ( int i = 0 ; i < 24 ; i++ ){ 
						
						if ( i == 16 ){
							
							save_y_x[i] = intToStr9 (hero_y);
							
						}
						else if ( i == 17 ){
							
						  save_y_x[i] = intToStr9 (hero_x);
							
						}
						
						
						hero_save << save_y_x[i] <<endl;
					}
					
					
					// ||||||||||||||||||||||||||||||||||||||||||||||||
					
					way = 1;
					
					break;
					
				}
				else if ( cord_y_x[hero_y][hero_x+1] == 'C'){
					
					cord_y_x[20]= "PRESS ENTER TO OPEN CHEST!";
					talk =true;
				}
				else {
					
					cord_y_x[20] = "Hmm, I have to find some other way.";
				
				}
			}
			
			else if ( key == 'c' || key == 'C' ){ //character screen
				
				heroscreen();
				
				hero_save.clear();
				hero_save.seekg( 0, ios::beg );
					
				for ( int i = 0 ; i < 24 ; i++ ){ 						
				getline(hero_save, temp_line);
								
				if (i == 9){
									
				lvl = atoi(temp_line.c_str());
				save_y_x[9] = temp_line;
					
				}
				else if ( i == 11){
					save_y_x[11]= temp_line;
				}
				else if (i == 10 ){
					save_y_x[10]= temp_line;
				}
				else if ( i == 15){
					save_y_x[15]= temp_line;
				}
				}
				
				
			}
			else if (key == 13 && talk == true && film1.good() == true){
				
				key = 0;
				
				while (key != 13){
					
					system("CLS");
						
						for (int i = 0 ; i < 20 ; i ++ ){
							
							getline (film1, temp_line);
							cout << temp_line <<endl;
							
						}
					
						film1.clear();
						film1.seekg( 0, ios::beg );
					
					
					cout << "PRESS ENTER TO GO BACK.";
					
					key = getch();
				}
				
				
				talk = false;
			}
			
			//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			
			while( popuptext != 0 ) {
					
					if (level_up == true){
					
						cord_y_x[20] = "LEVEL UP!!!";
						popuptext--;
						break;
					
					
					}else if (killed == true ){
						
						cord_y_x[20] = "YOU DEFEATED AN ENEMY!";
						popuptext--;
						break;
						
					}
					else if (fled == true) {
						
				
					cord_y_x[20] = "You have successfully fled!";
					popuptext--;
					break; 
					
					}

			}
		
			
			
			
			//opóŸnienie w odswiezaniu ekranu
			if(temp_key == '|'){	
				Sleep(50);		
			}
			else {	
			Sleep(100);
			}
			
		} //koniec funkcji while
		
		map.close();
		
	}//koniec funkcji if(map.good() == true)
	else {
		
	cout << "ERROR. Can't open map005.txt file!";
	key == getch();
	
	}
	
	if (way == 1){
	gamefile003();
	}

	
}



