
#include "cSpaceWarObjects.h"

#include "cSpaceWarEnemy.h"
#include "cSpaceWarPlayer.h"


cSpaceWarObjects::cSpaceWarObjects() {}
cSpaceWarObjects::~cSpaceWarObjects() {}
cSpaceWarObjects* cSpaceWarObjects::spaceWarFactory = NULL;

cSpaceWarObjects* cSpaceWarObjects::getSpaceWarFactory() {

	if (cSpaceWarObjects::spaceWarFactory == NULL) {

		cSpaceWarObjects::spaceWarFactory = new cSpaceWarObjects();
	}
	return spaceWarFactory;
}

iGameObject* cSpaceWarObjects::makeObject(std::string context) {

	if (context == "enemy") 
	{
		cSpaceWarEnemy* spaceWarEnemys = new cSpaceWarEnemy();
		for (int j = 0; j < 3; j++) {
			int value = -120;
			int value1 = -120;
			int value2 = -120;
			int value3 = -120;
			int locationChange = 1990.0f;
			int height = 0;
			if (j == 1) {
				height = 240;
			}
			else if (j == 2) {
				height = 480;
			}
			
			for (int i = 0; i < 11; i++) {

				cMesh* spaceWarEnemy = new cMesh();
				spaceWarEnemy->scaleXYZ = glm::vec3(1.0f);
				spaceWarEnemy->meshName = "SpaceInvader_I2_block_pose_1.ply";
				spaceWarEnemy->positionXYZ = glm::vec3(700.0f + value - locationChange, 0.0f - height, 0.0f);
				spaceWarEnemy->orientationXYZ.y = 0;
				spaceWarEnemy->wholeObjectDiffuseRGBA = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);;
				spaceWarEnemy->bUseWholeObjectDiffuseColour = true;
				spaceWarEnemy->friendlyName = "first";
				spaceWarEnemys->meshObjects.push_back(spaceWarEnemy);
				value = value - 160;

				cMesh* spaceWarEnemyNextRow = new cMesh();
				spaceWarEnemyNextRow->scaleXYZ = glm::vec3(1.0f);
				spaceWarEnemyNextRow->meshName = "SpaceInvader_I2_block_pose_1.ply";
				spaceWarEnemyNextRow->positionXYZ = glm::vec3(700.0f + value1 - locationChange, 120.0f - height, 0.0f);
				spaceWarEnemyNextRow->orientationXYZ.y = 0;
				spaceWarEnemyNextRow->friendlyName = "first";
				spaceWarEnemys->meshObjects.push_back(spaceWarEnemyNextRow);
				value1 = value1 - 160;

				cMesh* spaceWarEnemyAnimation = new cMesh();
				spaceWarEnemyAnimation->scaleXYZ = glm::vec3(1.0f);
				spaceWarEnemyAnimation->meshName = "SpaceInvader_I2_block_pose_2.ply";
				spaceWarEnemyAnimation->positionXYZ = glm::vec3(700.0f + value2 - locationChange, 0.0f - height, 0.0f);
				spaceWarEnemyAnimation->orientationXYZ.y = 0;
				spaceWarEnemyAnimation->bIsVisible = false;
				spaceWarEnemyAnimation->friendlyName = "second";
				spaceWarEnemys->meshObjects.push_back(spaceWarEnemyAnimation);
				value2 = value2 - 160;

				cMesh* spaceWarEnemyAnimationNextRow = new cMesh();
				spaceWarEnemyAnimationNextRow->scaleXYZ = glm::vec3(1.0f);
				spaceWarEnemyAnimationNextRow->meshName = "SpaceInvader_I2_block_pose_2.ply";
				spaceWarEnemyAnimationNextRow->positionXYZ = glm::vec3(700.0f + value3 - locationChange, 120.0f - height, 0.0f);
				spaceWarEnemyAnimationNextRow->orientationXYZ.y = 0;
				spaceWarEnemyAnimationNextRow->bIsVisible = false;
				spaceWarEnemyAnimationNextRow->friendlyName = "second";
				spaceWarEnemys->meshObjects.push_back(spaceWarEnemyAnimationNextRow);
				value3 = value3 - 160;
			}
			
		}
		return spaceWarEnemys;
	
		
	}
	if (context == "player") {

		

	}
	if (context == "ufo") {

	}
	if (context == "weapon") {
		

	}
	return NULL;
}