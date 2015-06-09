#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "phonebook.h"

using namespace std;

int printMenu();
void addNewItem(PhoneBook& phonebook);
void loadFromFile(PhoneBook& phonebook);
void saveInFile(PhoneBook& phonebook);
int getFileSize();

int main() {

	PhoneBook phonebook;

	int choice;
	bool added_new = false, already_loaded = false, saved_in_file = false;
	int file_size;
	
	do{

		choice = printMenu();

		switch(choice){

			case 1:				
			file_size = getFileSize();
			
			if(file_size > 0 && !already_loaded){
			
			cout<<"Something is already stored in file. Do you want to load it? Y/N:";
			char answer;
			cin>>answer;
			if(answer == 'Y') {				
				loadFromFile(phonebook);
			}
			}
			already_loaded = true;									
			added_new = true;
			saved_in_file = false;
			addNewItem(phonebook);			
			break;
			case 2:
			loadFromFile(phonebook);
			already_loaded = true;				
			break;
			case 3:
			phonebook.mergeSort();
			saveInFile(phonebook);
			saved_in_file = true;
			break;
			case 4:
			cout<<"You have following items in your list (before sort):"<<endl;
			phonebook.print();
			phonebook.mergeSort();
			cout<<"You have following items in your list (after sort):"<<endl;			
			phonebook.print();
			cout<<endl;
			break;
			case 0:
			cout<<"Ending program..."<<endl;
			break;
			
		}

	}while(choice != 0);
	if(added_new && !saved_in_file){
		cout<<"You have unsaved changes here. Do you want to save them? Y/N:";
		char answer;
		cin>>answer;
		if(answer == 'Y') {
			phonebook.mergeSort();
			saveInFile(phonebook);
		}
	}
	cout<<"Goodbye..."<<endl;
	return 0;
}

int getFileSize() {	
	std::ifstream is ("phonebook.txt", std::ifstream::binary);
	int length = 0;
	if (is) {	    
	    is.seekg (0, is.end);
	    length = is.tellg();	   
	    is.close();
	}
	return length;
}

void addNewItem(PhoneBook& phonebook){
	string phone, first_name, last_name;
	cout<<"Please enter data"<<endl;
	cout<<"Phone"<<endl;
	cin>>phone;
	cout<<"First name"<<endl;
	cin>>first_name;
	cout<<"Last name"<<endl;
	cin>>last_name;
	
	Address address(first_name, last_name, phone);
	phonebook.insertLast(address);
	cout<<"Successfully added new item into phonebook."<<endl;
}

void loadFromFile(PhoneBook& phonebook){
	
	ifstream file("phonebook.txt");
	
	if (file.is_open())
	{
		phonebook.LoadFromFile(file);
		file.close();
	}
	else{
		cout<<"Cannot opet file...Maybe file does not exist yet?"<<endl;
	}

	
}

void saveInFile(PhoneBook& phonebook){
	
	ofstream file("phonebook.txt");

	if (file.is_open())
	{
		phonebook.LoadInFile(file);
		file.close();
	}
	else{
		cout<<"Cannot opet file..."<<endl;
	}
}

int printMenu() {

	int choice;
	cout<<"Please choose one of the following options:"<<endl;
	cout<<"1 Add new item to phonebook"<<endl;
	cout<<"2 Load data from file"<<endl;
	cout<<"3 Store data from memory to file"<<endl;
	cout<<"4 Print current list"<<endl;
	cout<<"0 End program"<<endl;

	cin>>choice;
	return choice;

}
