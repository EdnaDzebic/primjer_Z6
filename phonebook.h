#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#include <sstream>
#include "list.h"
#include "address.h"

class PhoneBook: public List<Address>
{
	public:
		PhoneBook() = default;
		PhoneBook(std::ifstream& in) { LoadFromFile(in); }
		void LoadFromFile(std::ifstream&);
		void LoadInFile(std::ofstream&) const;
};


void PhoneBook::LoadFromFile(std::ifstream& file)
{
	if(!isEmptyList()) initializeList();

	std::string phone, first_name, last_name;
	while(file>>first_name>>last_name>>phone) {
		Address address(first_name, last_name, phone);	 
		insertLast(address);
	}
	  
}

void PhoneBook::LoadInFile(std::ofstream& file) const
{
	if(isEmptyList()) cout<<"Nothing to save..."<<endl;
	else{
		for(auto it = begin(); it!=end(); it++){
			file<<*it<<endl;
		}
	}	
}

#endif
