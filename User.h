#pragma once
#include <string>
#include <iostream>

using namespace std;
class User
{
protected :
	string id;
	string name;
	string email;
	string password;

	virtual void loginUser();
	virtual void createUser();
	virtual void deleteUser();
	virtual void userLogout();

public : 
	virtual void setId(string id);
	virtual void setName(string name);
	virtual void setEmail(string email);
	virtual void setPassword(string password);

	virtual string getId();
	virtual string getName();
	virtual string getEmail();
	virtual string getPassword();
};

