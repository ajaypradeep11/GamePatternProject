#pragma once

#include "iGameObject.h"
#include <string>

class cSpaceWarObjects {

public:
	cSpaceWarObjects();
	~cSpaceWarObjects();


	iGameObject* makeObject(std::string context);
	static cSpaceWarObjects* getSpaceWarFactory();

private:
	static cSpaceWarObjects* spaceWarFactory;

};