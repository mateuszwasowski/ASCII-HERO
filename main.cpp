#include <iostream>
#include <fstream>
#include <conio.h>
#include <vector>
#include <Windows.h>
#include <cstdlib>
#include <ctime>

#include "data/hdrs/newgame000.h"
#include "data/hdrs/gamefile000.h"
#include "data/hdrs/gamefile001.h"
#include "data/hdrs/gamefile002.h"
#include "data/hdrs/gamefile003.h"
#include "data/hdrs/gamefile004.h"
#include "data/hdrs/gamefile005.h"


using namespace std;

int main(){
	
	fstream map, film_1, film_2, film_3, hero_save;
	vector <string> cord_y_x;
	string temp_line;
	unsigned char key;
	int select = 1, temp_int = 1;
	
	map.open( "data/maps/map000.txt", ios::in | ios::out );
	film_1.open( "data/animations/film_newgame1.txt", ios::in | ios::out );
	film_2.open( "data/animations/film_newgame2.txt", ios::in | ios::out );
	film_3.open( "data/animations/film_newgame3.txt", ios::in | ios::out );
	hero_save.open( "data/save/hero_save.txt", ios::in | ios:: out );
	
	struct stats{
	
		string lvl;  // cord_y_x [9]
		string hp; // cord_y_x [10]
		string power; // cord_y_x [11]
		string dodge; // cord_y_x [12]
		string name;  //cord_y_x [13] 
		string exp;   //cord_y_x [14] 
		string nextexp;  //cord_y_x [15] 
		string hero_y;   //cord_y_x [16] 
		string hero_x;  //cord_y_x [17] 
		string save;   //cord_y_x [18] 
		string inventory;  //cord_y_x [19] 
	};
	
	stats h;
	
	
	
	system("CLS");
	
	srand( time( NULL ) );
	
	if ( map.good() == true && film_1.good() == true && film_2.good() == true && film_3.good() == true && hero_save.good() == true ){
		
		//  WCZYTANIE MAPY Z PLIKU I PRZEPISANIE JEJ NA CORDY PRZY POMOCY VECTORA STRINGOW
		//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		
		while(map.eof() != true){
			
			getline( map , temp_line );
			
			cord_y_x.push_back(temp_line);
			
		}
		
		temp_line = "";
		
		cord_y_x.push_back(temp_line); //dodatkowa linia na wszelkie komentarze
		
		
		// ANIMACJA POCZATKOWA GRY
		//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		
		for(int j=0 ; j < 8; j++){
			
		
		for(int i = 0; i < 20; i++){
			
			if ( temp_int == 1 ){
			
			getline( film_1, temp_line );
			cout << temp_line << endl;
			
			}
			else if( temp_int == 2 || temp_int == 4 ){
				
			getline( film_2, temp_line );
			cout << temp_line << endl;
			
			}
			else if( temp_int == 3 ){
				
			getline( film_3, temp_line );
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
		film_1.clear();
		film_1.seekg( 0, ios::beg );
		film_2.clear();
		film_2.seekg( 0, ios::beg );
		film_3.clear();
		film_3.seekg( 0, ios::beg );
		
		}	
		
		//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		// GAME
		
		while ( key != 8 ){ //backspace zamyka 
			
			system("CLS");
		
			// // DRUKUJE MAPE
			//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			
			
			for( int i = 0 ; i <= 20; i ++){
			
			cout << cord_y_x[i] << endl;
			
			}

			key = getch(); // pobieranie klawisza
			
			//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ KLAWISZ W
			
			
			if ( key == 'w' || key == 'W' ){  
				
				if (select == 2){
				
					select = 1;
					
					cord_y_x[9][15] = '-';  //new game
					cord_y_x[9][24] = '-';
					cord_y_x[6][15] = '[';	//continue
					cord_y_x[6][24] = ']';
					
				}
				else if (select == 3){
					select = 2;
					
					cord_y_x[12][17] = '-';	// exit
					cord_y_x[12][22] = '-';
					cord_y_x[9][15] = '[';
					cord_y_x[9][24] = ']';
					
				}
				
			}
			
			//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ KLAWISZ S
			
			else if ( key == 's' || key == 'S'){
				
				if (select == 1){
					select = 2;
					
					cord_y_x[6][15] = '-';
					cord_y_x[6][24] = '-';
					cord_y_x[9][15] = '[';
					cord_y_x[9][24] = ']';
					
					
				}
				else if (select == 2){
					select = 3;
					
					cord_y_x[9][15] = '-';
					cord_y_x[9][24] = '-';
					cord_y_x[12][17] = '[';
					cord_y_x[12][22] = ']';
					
					
				}
				
			}
			
			//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ KLAWISZ ENTER (13)

			else if ( key == 13){  
				
				if(select==1){
					
					for ( int  i = 0 ; i < 24 ; i ++ ){
						
						getline( hero_save, temp_line );
						
						if ( i == 18 ){
							 h.save = temp_line;
							 break;
						}
						
					}
					
					if ( h.save == "gamefile000"){
						
						gamefile000();
						
					}
					else if (h.save == "gamefile001"){
						
						gamefile001();
						
					}
					else if (h.save == "gamefile002"){
						
						gamefile002();
						
					}
					else if (h.save == "gamefile003"){
						
						gamefile003();
						
					}
					else if (h.save == "gamefile004"){
						
						gamefile004();
						
					}
					else if (h.save == "gamefile005"){
						
						gamefile005();
						
					}

				}
				else if (select == 2){
					
					system("CLS");
					newgame000();
					system("CLS");
					break;
					
				}
				else {
					break;
				}
			}

			Sleep(100);
			
		}
		
		map.close();	
		
	}
	else {
		
	cout << "ERROR. Can't open map000.txt or some film_newgame animation file!";
	key = getch();
	
	}

	return 0;
	
}





