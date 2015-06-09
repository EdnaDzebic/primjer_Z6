#ifndef _ADDRESS_H
#define _ADDRESS_H

#include <iostream>
#include <string>

class Address {

	public:
		Address() = default;
		Address(const Address& address) {			
			this->_first_name = address._first_name;
			this->_last_name = address._last_name; 
			this->_phone = address._phone;
		}
		Address( const std::string& first_name, const std::string& last_name, const std::string& phone) :  _first_name(first_name), _last_name(last_name), _phone(phone) {};

		const std::string& getPhone() const;
		const std::string& getFirstName() const;
		const std::string& getLastName() const;
		

		Address& setPhone(const std::string& phone);
		Address& setFirstName(const std::string& first_name);
		Address& setLastName(const std::string& last_name); 
		
		friend std::ostream& operator<< (std::ostream& out, const Address& address){		
			out<<address._first_name<<" "<<address._last_name<<" "<<address._phone;	
			return out;	
		}

		bool operator==(const Address& address) const;
		bool operator!=(const Address& address) const;
		bool operator<(const Address& address) const;
		bool operator>(const Address& address) const;
		bool operator<=(const Address& address) const;
		bool operator>=(const Address& address) const;

	private:
		
		std::string _phone;
		std::string _first_name;
		std::string _last_name;
};

#endif
