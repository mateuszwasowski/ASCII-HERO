#include <iostream>
#include <fstream>
#include <conio.h>
#include <vector>
#include <Windows.h>
#include <cstdlib>
#include <ctime>


using namespace std;


void dogtalk(){
	
	system("CLS");
	
    fstream map1, map2, map3, map4,map5, hero_template, hero_save;
    ofstream temp;
    vector <string> save_y_x;
    string temp_line;
    char key;
	
    temp.open( "data/save/temp.txt", ios::in | ios::out | ofstream::trunc);
	hero_save.open( "data/save/hero_save.txt", ios::in | ios::out );
	
	map1.open( "data/animations/dogtalk1.txt", ios::in | ios::out );
	map2.open( "data/animations/dogtalk2.txt", ios::in | ios::out );
	map3.open( "data/animations/dogtalk3.txt", ios::in | ios::out );
	map4.open( "data/animations/dogtalk4.txt", ios::in | ios::out );
	map5.open( "data/animations/dogtalk5.txt", ios::in | ios::out );
	
    if ( hero_save.good() == true ){  //wczytanie hero_save.txt i przygotowanie do zapisu
		
		for ( int  i = 0 ; i < 24 ; i ++){
			
			getline( hero_save , temp_line );
			
			save_y_x.push_back(temp_line);
			
		}
		
		
	}
	else {
		
		cout << "ERROR. Can't open hero_save.txt file!";
		key = getch();
		
	}
	if ( map4.good()== true && map5.good() == true){
		
		for(int j=0 ; j < 4; j++){
			
		
		for(int i = 0; i < 20; i++){
			
			if ( j%2 == 0 ){
			
			getline( map5, temp_line );
			cout << temp_line << endl;
			
			}
			else {
			
				
			getline( map4, temp_line );
			cout << temp_line << endl;
			
			}
			
		}
		
		Sleep(500); //nowa klatka animacji co 300ms
		system("CLS");
		
		//zmienianie klatek 
		
		//zerowanie miejsca w którym jest aktualnie we wczytywanej mapie
		map4.clear();
		map4.seekg( 0, ios::beg );
		map5.clear();
		map5.seekg( 0, ios::beg );
	
		}
		
		
	}
	else{
		cout << "ERROR. Can't open dogtalk4 or dogtalk5 file!";
		key = getch();
		
	}	
	
	if ( map1.good()== true && map2.good() == true && map3.good()==true){
		
		while ( key != 13){  //klawisz enter
			
			// DRUKUJE MAPE
			
			system("CLS");
			
			while(map1.eof() != true){
			
			getline( map1 , temp_line );
			
			cout << temp_line;
			
			if(map1.eof()!=true){
				cout <<endl;
			}
			}
			
			
		    cout << "PRESS ENTER TO CONTINUE!"<<endl;
			
			
			
			//zerowanie miejsca w którym jest aktualnie we wczytywanej mapie
			
			map1.clear();
			map1.seekg( 0, ios::beg );
		
			key = getch(); // pobieranie klawisza
			
			
		}
		
		map1.close();
		key = 0;
		
		while ( key != 13){  //klawisz enter
			
			// DRUKUJE MAPE
			
			system("CLS");
			
			while(map2.eof() != true){
			
			getline( map2 , temp_line );
			
			cout << temp_line;
			
			if(map2.eof()!=true){
				cout <<endl;
			}
			}
			
			
		    cout << "PRESS ENTER TO CONTINUE!"<<endl;
			
			
			
			//zerowanie miejsca w którym jest aktualnie we wczytywanej mapie
			
			map2.clear();
			map2.seekg( 0, ios::beg );
		
			key = getch(); // pobieranie klawisza
			
			
		}
		
		map2.close();
		key = 0;
		
		while ( key != 13){  //klawisz enter
			
			// DRUKUJE MAPE
			
			system("CLS");
			
			while(map3.eof() != true){
			
			getline( map3 , temp_line );
			
			cout << temp_line;
			
			if(map3.eof()!=true){
				cout <<endl;
			}
			}
			
			
		    cout << "PRESS ENTER TO CONTINUE!"<<endl;
			
			
			
			//zerowanie miejsca w którym jest aktualnie we wczytywanej mapie
			
			map3.clear();
			map3.seekg( 0, ios::beg );
		
			key = getch(); // pobieranie klawisza
			
			
		}
		
		map3.close();
		key = 0;
		
		
	}
	else {
		
		cout << "ERROR. Can't open dogtalk1 or dogtalk2 or dogtalk3 file!";
		key = getch();
		
	}
	
	
	// |||||||||||||||||||||||||||||||||||||||||||||||| //zapisywanie zakoñczenie rozmowy herosa w hero_save.txt
				
					hero_save.clear();
					hero_save.seekg( 0, ios::beg );
					hero_save.close();
   					temp.close();
    				remove("data/save/hero_save.txt"); 
    				rename("data/save/temp.txt","data/save/hero_save.txt");
    				hero_save.open( "data/save/hero_save.txt", ios::in | ios:: out );
					temp.open( "data/save/temp.txt", ios::in | ios::out | ofstream::trunc);
					
					for ( int i = 0 ; i < 24 ; i++ ){  
						
						
						
						if ( i == 19 ){
							
							save_y_x[i] = "dogtalk";
							
						}
						
						hero_save << save_y_x[i] <<endl;
					}
					
	// ||||||||||||||||||||||||||||||||||||||||||||||||

	
	
}



