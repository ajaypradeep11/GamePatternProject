#pragma once
#include "cSpaceWarEnemy.h"
#include "cSpaceWarObjects.h"
#include "cWeapon.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

class cGameManager {
public:
	cGameManager();
	~cGameManager();

	void enemyMovements();
	std::vector<cSpaceWarEnemy>* Enemys;
	

private:
	std::vector<std::string > map;
};
