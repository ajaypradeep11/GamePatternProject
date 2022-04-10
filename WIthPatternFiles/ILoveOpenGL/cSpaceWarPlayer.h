#pragma once
#include "iGameObject.h"
#include "cMesh.h"
#include "iWeapon.h"

class cSpaceWarPlayer : public iGameObject {

public:
	cSpaceWarPlayer();
	virtual ~cSpaceWarPlayer();
	virtual void Update(double deltaTime);
	virtual std::string getName(void);
	virtual cMesh* getMeshPointer(void);

	std::string name;
	cMesh* meshObject;
	int health;
	int hitEnemy;
	bool isDead;
	iWeapon* Weapon;

};
