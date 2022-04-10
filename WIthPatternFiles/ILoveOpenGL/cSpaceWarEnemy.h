#pragma once
#include "iGameObject.h"
#include "cMesh.h"

class cSpaceWarEnemy : public iGameObject {

public:
	cSpaceWarEnemy();
	virtual ~cSpaceWarEnemy();
	virtual void Update(double deltaTime);
	virtual std::string getName(void);
	virtual cMesh* getMeshPointer(void);
	virtual std::vector<cMesh*> getMeshPointers(void);

	std::string name;
	cMesh* meshObject;
	std::vector<cMesh*> meshObjects;
	int valuecheckAdd;
	int conditionValue;
	int checkConditionValue;
	bool checkEnemyMovementLeft;
	bool checkEnemyMovementRight;
	bool checkEnemyMovementLeftAnim;
	bool checkEnemyMovementRightAnim;
	int getNumberofTime;


};
