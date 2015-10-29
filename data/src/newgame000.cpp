#include <iostream>
#include <fstream>
#include <conio.h>
#include <vector>
#include <Windows.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstdio>


#include "../hdrs/gamefile000.h"

using namespace std;

string intToStr1(int n)
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

void newgame000(){
	
	fstream map0, map1, map2, hero_template;
	ofstream hero_save;
	char key;
	
	vector <string> cord_y_x;
	string temp_line;
	int temp_int=0, select = 1, add_point = 0;
	
	hero_template.open( "data/maps/hero_template.txt", ios::in | ios::out );
	hero_save.open( "data/save/hero_save.txt", ios::in | ios::out | ofstream::trunc );//trunc przy otwarciu usuwa zawartosc pliku hero_save.txt
	
	map0.open( "data/maps/newgame000.txt", ios::in | ios::out );
	map1.open( "data/maps/newgame001.txt", ios::in | ios::out );
	map2.open( "data/maps/newgame002.txt", ios::in | ios::out );
	
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
	
	
	if (map0.good() == true){				
		
		
		//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ NEWGAME000
		
		while ( key != 13){  //klawisz enter
		
			system("CLS");
			
			// DRUKUJE MAPE
			
			while(map0.eof() != true){
			
			getline( map0 , temp_line );
			
			cout << temp_line;
			
			if(map0.eof()!=true){
				cout <<endl;
			}
			
			}
			
			//zerowanie miejsca w którym jest aktualnie we wczytywanej mapie
			
			map0.clear();
			map0.seekg( 0, ios::beg );
			
			cout << "PRESS ENTER TO CONTINUE.";
			
			key = getch(); // pobieranie klawisza
			
			
		}
		
		map0.close();
		key = 0;
		system("CLS");
		
	}	//koniec funkcji if(map1.good() == true)
	else {
		
	cout << "ERROR. Can't open newgame000.txt file!";
	key = getch();
	
	}
		
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ NEWGAME001 IMIÊ!
	
	if ( map1.good() == true ){
		
		while ( key != 13){  //klawisz enter
			
			// DRUKUJE MAPE
			
			while(map1.eof() != true){
			
			getline( map1 , temp_line );
			
			cout << temp_line;
			
			if(map1.eof()!=true){
				cout <<endl;
			}
			}
			
			if(temp_int==1){
				cout << "THE NAME YOU PICKED IS TOO LONG!"<<endl;
				temp_int=0;
			}
			
			//zerowanie miejsca w którym jest aktualnie we wczytywanej mapie
			
			map1.clear();
			map1.seekg( 0, ios::beg );
			
			cout << "ENTER NAME:";
			
			cin >> temp_line;
			
			if (temp_line.length() > 13){
				
				system("CLS");
				temp_int=1;
				continue;
				
			}
			else{
				
				h.name = temp_line;
				cout << "PRESS ENTER TO CONFIRM YOUR NAME.";
			}
		
			key = getch(); // pobieranie klawisza
			
			
		}
		
		map1.close();
		key = 0;
	
	} //koniec funkcji if(map2.good() == true)
	else {
		
	cout << "ERROR. Can't open newgame001.txt file!";
	key = getch();
	
	}
	
	
		//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ NEWGAME002
	
	if ( map2.good() == true && hero_template.good()== true ){
		
		//  WCZYTANIE MAPY Z PLIKU I PRZEPISANIE JEJ NA CORDY PRZY POMOCY VECTORA STRINGOW
		//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		
		
		while(map2.eof() != true){
			
			getline( map2 , temp_line );
			
			cord_y_x.push_back(temp_line);
			
		}
		
		temp_line = " ";
		
		cord_y_x.push_back(temp_line); //dodatkowa linia na wszelkie komentarze
		
		
		
		for ( int i = 0 ; i < 24 ; i ++ ){
			
			getline(hero_template, temp_line);
			
			if ( i == 0 ){
				
				cord_y_x[6].erase(5, temp_line.length());
				cord_y_x[6].insert(5, temp_line);
				
			}
			else if ( i == 1 ){
				
				cord_y_x[7].erase(5, temp_line.length());
				cord_y_x[7].insert(5, temp_line);
				
			}
			else if ( i == 2 ){
				
				cord_y_x[8].erase(5, temp_line.length());
				cord_y_x[8].insert(5, temp_line);
				
			}
			else if ( i == 3 ){
				
				cord_y_x[9].erase(5, temp_line.length());
				cord_y_x[9].insert(5, temp_line);
				
			}
			else if ( i == 4 ){
				
				cord_y_x[10].erase(5, temp_line.length());
				cord_y_x[10].insert(5, temp_line);
				
			}
			else if ( i == 5 ){
				
				cord_y_x[11].erase(5, temp_line.length());
				cord_y_x[11].insert(5, temp_line);
				
			}
			else if ( i == 6 ){
				
				cord_y_x[12].erase(5, temp_line.length());
				cord_y_x[12].insert(5, temp_line);
			
			}
			else if ( i == 9){
				h.lvl = temp_line;
				cord_y_x[4].erase(32, h.lvl.length());
				cord_y_x[4].insert(32, h.lvl);
				temp_int = atoi(h.lvl.c_str());
			}
			else if (i == 10){
				h.hp = temp_line;
				cord_y_x[10].erase(32, h.hp.length());
				cord_y_x[10].insert(32, h.hp);
			}
			else if (i == 11){
				h.power = temp_line;
				cord_y_x[12].erase(32, h.power.length());
				cord_y_x[12].insert(32, h.power);
			}
			else if (i == 12){
				h.dodge = temp_line;
			}
			else if (i == 13){
				
				cord_y_x[4].erase(10,h.name.length());
				cord_y_x[4].insert(10, h.name);
		
			}
			else if (i == 14){
				
				h.exp = temp_line;
				cord_y_x[6].erase(32, h.exp.length());
				cord_y_x[6].insert(32, h.exp);
				
			}
			else if (i == 15){
				h.nextexp = temp_line;
			}
			else if (i == 16){
				h.hero_y = temp_line;
			}
			else if (i == 17){
				h.hero_x = temp_line;
			}
			else if (i == 18){
				h.save = temp_line;
			}
			else if (i == 19){
				h.inventory = temp_line;
			}
			
		}
		
		//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		temp_int++;
		
		while ( temp_int != 0){  //null
			
			system("CLS");
			// DRUKUJE MAPE
			cord_y_x[20] = "PRESS ENTER TO ASSIGN WHEN SELECTED";
			
			for( int i = 0 ; i <= 20; i ++){
			
			cout << cord_y_x[i] << endl;
			
			}
			
			
			if (temp_int == 1){  //TU JEST JAKIS ERROR, NIE WIEM O CO CHODZI, DLATEGO TEMP_INT++ PRZED WHILE!!!
				break;
			}
			else{
			
			key = getch();			 // pobieranie klawisza
			
			}
			
			if ( key == 'w' || key == 'W' ){  
				
				if (select == 2){
				
					select = 1;
					
					cord_y_x[12][23] = '-';  //new game
					cord_y_x[12][30] = '-';
					cord_y_x[10][23] = '[';	//continue
					cord_y_x[10][27] = ']';
					
				}
				
			}
			
			//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ KLAWISZ S
			
			else if ( key == 's' || key == 'S'){
				
				if (select == 1){
					select = 2;
					
					cord_y_x[10][23] = '-';
					cord_y_x[10][27] = '-';
					cord_y_x[12][23] = '[';
					cord_y_x[12][30] = ']';
					
					
				}
				
			}
			
			//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ KLAWISZ ENTER!!!
			
			else if ( key == 13 ){
				
				if ( select == 1 ){
					
					cord_y_x[10].erase(32, h.hp.length());
					
					temp_int --;
					add_point = atoi (h.hp.c_str());
					add_point++;
					
					h.hp = intToStr1 (add_point);

					add_point=0;
					
					cord_y_x[10].insert(32, h.hp);
					
				} 
				else {
					
					cord_y_x[12].erase(32, h.power.length());
					
					temp_int --;
					add_point = atoi (h.power.c_str());
					add_point++;
				
					h.power = intToStr1 (add_point);
				
					add_point=0;
					cord_y_x[12].insert(32, h.power);
					
				}
				
				
			}
			
			
			
		} // koniec petli while
		

		map2.close();
	
	}
	else {
		
		cout << "ERROR. Can't open newgame002.txt or hero_template.txt file!";
		key = getch();
		
	}
	
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ ZAPISANIE DANYCH DO hero_save.txt
	
	
	if ( hero_save.good() == true && hero_template.good()== true ){
	
		hero_template.clear();
		hero_template.seekg( 0, ios::beg );
	
		for ( int i = 0 ; i < 24 ; i++){
		
		getline ( hero_template, temp_line );
		
		if ( i == 10 ){
		
		hero_save << h.hp << endl;
		
		}
		else if ( i == 11){
		
		hero_save << h.power<< endl;
		
		}
		else if ( i == 13 ){
		
		hero_save << h.name << endl;
		
		}
		else{
		
		hero_save << temp_line << endl;
		
		}
	}
		hero_save.close();
		hero_template.close();
	
	}
	else {
		
		cout << "ERROR. Can't open hero_save.txt or hero_template.txt file";
		key = getch();
		
	}
	
	key = 0;
	cout << "PRESS ENTER TO START YOUR ADVENTURE!"<<endl;
	cout << "PRESS C WHEN IN GAME TO ACCESS CHARACTER SCREEN";
	
	while ( key != 13){
		
		key = getch();
		
	}
	
	gamefile000();
	
}



