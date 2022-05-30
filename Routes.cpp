#include "Routes.h"

Routes::Routes() {};
Routes::~Routes() {};
Routes* Routes::instance = NULL;
Routes* Routes::getInstance() {
	if (instance == NULL) {
		instance = new Routes();
	}
	return instance;
}