#pragma once
#include <string>
using namespace std;
class CurrentUser
{
public:
	void setType(string type);
	void setId(string id);
	void setEmail(string email);
	void setName(string name);
	void clearUserData();

	string getType();
	string getId();
	string getEmail();
	string getName();

	static CurrentUser* getInstance();
private:
	CurrentUser();
	~CurrentUser();
	static CurrentUser* instance;
	string type;
	string id;
	string email;
	string name;
};
