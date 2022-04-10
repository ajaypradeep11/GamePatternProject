#include "cSpaceWarEnemy.h"



cSpaceWarEnemy::cSpaceWarEnemy() {
    valuecheckAdd = 0;
    conditionValue = 0;
    checkConditionValue = 0;
    getNumberofTime = 0;
    checkEnemyMovementRight = false;
    checkEnemyMovementLeft = true;
    checkEnemyMovementRightAnim = false;
    checkEnemyMovementLeftAnim = true;
	this->meshObject = NULL;
}
cSpaceWarEnemy::~cSpaceWarEnemy() {
	this->meshObject = NULL;
}
void cSpaceWarEnemy::Update(double deltaTime) {

    getNumberofTime++;
    valuecheckAdd++;
    conditionValue++;
    
    if (valuecheckAdd == 60) {

        if (checkConditionValue % 2 == 1) {
            for (unsigned int index = 0; index != meshObjects.size(); index++)
            {
                if (meshObjects.at(index)->friendlyName == "second") {
                    meshObjects.at(index)->bIsVisible = false;
                }
                else {
                    meshObjects.at(index)->bIsVisible = true;
                }

                if (meshObjects.at(index)->friendlyName == "first") {
                    if (checkEnemyMovementLeft) {
                        meshObjects.at(index)->positionXYZ.x = meshObjects.at(index)->positionXYZ.x + 20;


                    }
                    else if (checkEnemyMovementRight) {
                        meshObjects.at(index)->positionXYZ.x = meshObjects.at(index)->positionXYZ.x - 20;
                    }
                }
                

                //::g_vec_pEnemy.at(index)->positionXYZ.x = ::g_vec_pEnemy.at(index)->positionXYZ.x - 20;
            }

            if ((meshObjects.at(0)->positionXYZ.x > (1000 - 1990.0f))) { //&& ((meshObjects.at(0)->friendlyName == "first"))) {
                checkEnemyMovementLeft = false;
                checkEnemyMovementRight = true;
                if (conditionValue != 55) {
                    conditionValue = conditionValue + 11;
                }
                for (unsigned int index = 0; index != meshObjects.size(); index++)
                {
                    if (meshObjects.at(index)->friendlyName == "first") {

                        meshObjects.at(index)->positionXYZ.y = meshObjects.at(index)->positionXYZ.y - (getNumberofTime * 240);
                    }
                }

            }
            if (checkEnemyMovementRight) {
                if ((meshObjects.at(0)->positionXYZ.x < (400 - 1990.0f))) {
                    checkEnemyMovementLeft = true;
                    checkEnemyMovementRight = false;
                    if (conditionValue != 55) {
                        conditionValue = conditionValue + 11;
                    }
                    for (unsigned int index = 0; index != meshObjects.size(); index++)
                    {
                        if (meshObjects.at(index)->friendlyName == "first") {

                            meshObjects.at(index)->positionXYZ.y = meshObjects.at(index)->positionXYZ.y - (getNumberofTime * 240);

                        }
                    }
                }
                //showUFO = true;

            }
        }
        else {
            for (unsigned int index = 0; index != meshObjects.size(); index++)
            {
                if (meshObjects.at(index)->friendlyName == "second") {
                    meshObjects.at(index)->bIsVisible = true;
                }
                else {
                    meshObjects.at(index)->bIsVisible = false;
                }
                
                if (meshObjects.at(index)->friendlyName == "second") {
                    if (checkEnemyMovementLeftAnim) {
                        meshObjects.at(index)->positionXYZ.x = meshObjects.at(index)->positionXYZ.x + 20;
                        //checkEnemyMovementRight = true;
                    }
                    else if (checkEnemyMovementRightAnim) {
                        meshObjects.at(index)->positionXYZ.x = meshObjects.at(index)->positionXYZ.x - 20;
                        //checkEnemyMovementRight = false;
                    }
                }

                //::g_vec_pEnemy.at(index)->positionXYZ.x = ::g_vec_pEnemy.at(index)->positionXYZ.x - 20;
            }

            if ((meshObjects.at(0)->positionXYZ.x > (1000 - 1990.0f))) {
                checkEnemyMovementLeftAnim = false;
                checkEnemyMovementRightAnim = true;
                if (conditionValue != 55) {
                    conditionValue = conditionValue + 11;
                }
                for (unsigned int index = 0; index != meshObjects.size(); index++)
                {
                    if (meshObjects.at(index)->friendlyName == "second") {

                        meshObjects.at(index)->positionXYZ.y = meshObjects.at(index)->positionXYZ.y - (getNumberofTime * 240);
                    }
                }

            }
            if (checkEnemyMovementRightAnim) {
                if ((meshObjects.at(0)->positionXYZ.x < (400 - 1990.0f))) {
                    checkEnemyMovementLeftAnim = true;
                    checkEnemyMovementRightAnim = false;
                    if (conditionValue != 55) {
                        conditionValue = conditionValue + 11;
                    }
                    for (unsigned int index = 0; index != meshObjects.size(); index++)
                    {
                        if (meshObjects.at(index)->friendlyName == "second") {

                            meshObjects.at(index)->positionXYZ.y = meshObjects.at(index)->positionXYZ.y - (getNumberofTime * 240);
                        }
                    }
                }

            }
        }

        checkConditionValue++;
        valuecheckAdd = 0;

    }
	return;
}

std::string cSpaceWarEnemy::getName(void) {
	return this->name;
}
cMesh* cSpaceWarEnemy::getMeshPointer(void) {
	return this->meshObject;
}

std::vector<cMesh*> cSpaceWarEnemy::getMeshPointers() {
	return this->meshObjects;
}