#include "CurrentUser.h"

CurrentUser::CurrentUser() {}

CurrentUser::~CurrentUser() {}

void CurrentUser::setType(string type)
{
	this->type = type;
}

void CurrentUser::setId(string id)
{
	this->id = id;
}


void CurrentUser::setEmail(string email)
{
	this->email = email;
}

void CurrentUser::setName(string name)
{
	this->name = name;
}

void CurrentUser::clearUserData()
{
	id = "";
	email = "";
	name = "";
	type = "";
}

string CurrentUser::getType()
{
	return this->type;
}

string CurrentUser::getId()
{
	return this->id;
}

string CurrentUser::getEmail()
{
	return this->email;
}

string CurrentUser::getName()
{
	return this->name;
}

CurrentUser* CurrentUser::instance = NULL;

CurrentUser* CurrentUser::getInstance()
{
	if (instance == NULL) {
		instance = new CurrentUser;
	}
	return instance;
}