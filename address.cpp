#include "address.h"
#include <string>


const std::string& Address::getPhone() const{
	return _phone;
}

const std::string& Address::getFirstName() const{
	return _first_name;
}

const std::string& Address::getLastName() const{
	return _last_name;
}

Address& Address::setPhone(const std::string& phone){
	_phone = phone;
	return *this;
}

Address& Address::setFirstName(const std::string& first_name){
	_first_name = first_name;
	return *this;
}

Address& Address::setLastName(const std::string& last_name){
	_last_name = last_name;
	return *this;
}


bool Address::operator==(const Address& address) const{
	return _first_name == address._first_name && _last_name == address._last_name;
}
		
bool Address::operator!=(const Address& address) const{
	return _first_name != address._first_name || _last_name != address._last_name;
}
		
bool Address::operator<(const Address& address) const{
	return _first_name + " " + _last_name < address._first_name+ " " + address._last_name;
}

bool Address::operator>(const Address& address) const{
	return _first_name + " " + _last_name > address._first_name+ " " + address._last_name;
}

bool Address::operator<=(const Address& address) const{
	return _first_name + " " + _last_name <= address._first_name+ " " + address._last_name;
}

bool Address::operator>=(const Address& address) const{
	return _first_name + " " + _last_name >= address._first_name+ " " + address._last_name;
}
