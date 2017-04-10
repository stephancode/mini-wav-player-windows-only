#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <time.h>
#include <stdio.h>
#include <Windows.h>
#include <MMSystem.h>

enum TYPE {	infinite, stopped };
std::vector<std::string> get_files(std::string);
void choose_song(std::string, std::string*, TYPE type);
void selection_song(std::string*);
void selection_menu(std::string*);
void shuffle_and_listen(std::string*, TYPE type);

int main(){
	
	srand(time(NULL));
	char song_name[20];
	char folder[20];
	char full_name[40];
	
	std::cout << "Insert the name of the songs folder(put \\* at the end): ";
	std::cin.get(folder, sizeof(folder));

	std::string sfolder = std::string(folder);

	selection_menu(&sfolder);
	
	
	return 0;
}

void selection_menu(std::string* folder){
	
	int menu_option = 0;
	std::cout << "1. Choose a song manually.\n";
	std::cout << "2. Listen a random song but only one(you will return to this menu afterwards).\n";
	std::cout << "3. Listen a random song one after another(infinite).\n";
	std::cout << "-> Choose an option: ";
	std::cin >> menu_option;
	
	switch(menu_option){
		case 1:
			selection_song(folder);
			break;
		case 2:
			shuffle_and_listen(folder, stopped);
			break;
		case 3:
			shuffle_and_listen(folder, infinite);
			break;
		default:
			std::cout << "Invalid option!";
			selection_menu(folder);
			break;
	}
	
}

void shuffle_and_listen(std::string* folder, TYPE type){
	std::vector<std::string> file_names = get_files(*folder);
	int rand_song = rand() % (file_names.size() - 1) + 1;
	choose_song(file_names[rand_song], folder, type);
}

void selection_song(std::string* folder){
	unsigned int option = 0;

	std::vector<std::string> file_names = get_files(*folder);
	
	for(int i = 1; i < file_names.size(); i++){
		std::cout << i << " " << file_names[i] << std::endl;
	}

	std::cout << "-> Choose your poison!(#): ";
	std::cin >> option;
	choose_song(file_names[option], folder, stopped);
}

void choose_song(std::string song_name, std::string* folder, TYPE type){
	std::string tmp_folder = *folder;
	tmp_folder.erase(tmp_folder.length() - 1, tmp_folder.length() - 0);
	std::string full_name = tmp_folder + song_name;
	LPSTR name = (char*)(full_name.c_str());
	std::cout << song_name << " is now playing, Enjoy!";
	PlaySound(name, NULL, SND_SYNC);
	Sleep(2000);
	printf("\n   ==================    \n");
	if(type == stopped) selection_menu(folder);
	else shuffle_and_listen(folder, infinite);
}

std::vector<std::string> get_files(std::string folder) {

	std::vector<std::string> files;
	WIN32_FIND_DATA fileData;
	HANDLE hFind;


	if ( !((hFind = FindFirstFile(folder.c_str(), &fileData)) == INVALID_HANDLE_VALUE) ) {
		while(FindNextFile(hFind, &fileData)) {
			files.push_back(fileData.cFileName);
		}
	}
 

	FindClose(hFind);
	return files;

}

 
