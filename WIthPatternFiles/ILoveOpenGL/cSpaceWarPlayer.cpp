#include "cSpaceWarPlayer.h"



cSpaceWarPlayer::cSpaceWarPlayer() {
	this->meshObject = NULL;
	health = 100.0f;
	isDead = false;
}
cSpaceWarPlayer::~cSpaceWarPlayer() {
	this->meshObject = NULL;
}
void cSpaceWarPlayer::Update(double deltaTime) {


	return;
}

std::string cSpaceWarPlayer::getName(void) {
	return this->name;
}
cMesh* cSpaceWarPlayer::getMeshPointer(void) {
	return this->meshObject;
}
