#include <iostream>
#include <fstream>
#include <conio.h>
#include <vector>
#include <Windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;

string intToStr2(int n)
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


void heroscreen(){
	
	fstream map, hero_save;
	ofstream temp;
	vector <string> cord_y_x;
	vector <string> save_y_x;
	string temp_line;
	int temp_int, int_lvl, int_exp, int_nextexp, select, add_point=0;
	unsigned char key, temp_key;
	bool level_up=false;
	
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

	
	map.open( "data/maps/heroscreen.txt", ios::in | ios::out );
	hero_save.open( "data/save/hero_save.txt", ios::in | ios:: out );
	temp.open( "data/save/temp.txt", ios::in | ios::out | ofstream::trunc);
	
	system ("CLS");
	
	if ( map.good() == true && hero_save.good()== true ){
	
	
	//  WCZYTANIE MAPY Z PLIKU I PRZEPISANIE JEJ NA CORDY PRZY POMOCY VECTORA STRINGOW
		//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		
		for ( int  i = 0 ; i < 24 ; i ++){
			
			getline( hero_save , temp_line );
			
			save_y_x.push_back(temp_line);
			
		}
		
		
		while(map.eof() != true){
			
			getline( map , temp_line );
			
			cord_y_x.push_back(temp_line);
			
		}
		
		temp_line = " ";
		
		cord_y_x.push_back(temp_line); //dodatkowa linia na wszelkie komentarze
	
	
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ drukowanie mapy oraz wczytanie danych
	
		hero_save.clear();
		hero_save.seekg( 0, ios::beg );
	
		for ( int i = 0 ; i < 24 ; i ++ ){
			
			getline(hero_save, temp_line);
			
			
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
				int_lvl = atoi(h.lvl.c_str());
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
				int_exp = atoi(h.exp.c_str());
				
			}
			else if (i == 15){
				h.nextexp = temp_line;
				int_nextexp = atoi(h.nextexp.c_str());
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
		
		if (int_exp >= int_nextexp){
			
			level_up = true;
			int_lvl ++;
			int_nextexp = int_nextexp + (int_lvl*10);
			
			h.lvl = intToStr2 (int_lvl);
			
			save_y_x[9]=h.lvl;
			cord_y_x[4].erase(32, h.lvl.length());
			cord_y_x[4].insert(32, h.lvl);
			
			h.nextexp = intToStr2 (int_nextexp);
			
			save_y_x[15]=h.nextexp;
			
			
		}
	
	
	while ( key != 8 ){
	
			
			
			if (level_up == true){
				
				temp_line = "LEVEL UP! Assign your point!";
				cord_y_x[17].erase(5, temp_line.length());
				cord_y_x[17].insert(5, temp_line);
				cord_y_x[10][23] = '[';
				cord_y_x[10][27] = ']';
				select = 1;
				
				while (key != 8){
					
					// DRUKUJE MAPE
					//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
					
					if (level_up != true){
				
					cord_y_x[10][23] = '-';
					cord_y_x[10][27] = '-';
					cord_y_x[12][23] = '-';
					cord_y_x[12][30] = '-';
					
					}
					
					
					system("CLS");
					
					for( int i = 0 ; i <= 20; i ++){
					
					cout << cord_y_x[i] << endl;
					
					}
					
				
					if (level_up == true){
				
					key = getch();
					
					}
					else break;
					
					
					if ( key == 'w' || key == 'W' ){  
						
						if (select == 2){
						
							select = 1;
							
							cord_y_x[12][23] = '-';  //power
							cord_y_x[12][30] = '-';
							cord_y_x[10][23] = '[';	//hp
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
					
					
					if ( key == 13 ){
						
						if ( select == 1 ){
							
							
							add_point = atoi (h.hp.c_str());
							add_point++;
							
							h.hp = intToStr2 (add_point);
							
							add_point=0;
							
							cord_y_x[10].erase(32, h.hp.length());
							cord_y_x[10].insert(32, h.hp);
							save_y_x[10] = h.hp;
							
							level_up = false;
		
							
						} 
						else {
							


							add_point = atoi (h.power.c_str());
							add_point++;						
			
							h.power = intToStr2 (add_point);
							
							add_point=0;
	
							cord_y_x[12].erase(32, h.power.length());
							cord_y_x[12].insert(32, h.power);
							save_y_x[11] = h.power;	
							
							level_up = false;

				
						}
						
					
						
						
					}
					
					
						
				} // koniec petli while dla wpisywania danych
					
			} //koniec if level_up == true
	
			system("CLS");
					
			temp_line = "Your hero looks marvelous!  ";
			cord_y_x[17].erase(5, temp_line.length());
			cord_y_x[17].insert(5, temp_line);
					
			for( int i = 0 ; i <= 20; i ++){
				
				cout << cord_y_x[i] << endl;
				
			}
				
				
		
			//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			

			key = getch(); // pobieranie klawisza 
		
			if ( key == 'c' || key == 'C'){
				
				// |||||||||||||||||||||||||||||||||||||||||||||||| //zapisywanie herosa w hero_save.txt
				
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
						
						hero_save << save_y_x[i] << endl;
					}
					
					// ||||||||||||||||||||||||||||||||||||||||||||||||		
				
				break;
			
			}
	} // koniec pêtli while
	
}
else {
	
	cout << "ERROR. Can't open heroscreen.txt or hero_save.txt file!";
	key == getch();
	
}

}

