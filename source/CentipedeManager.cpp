#include "CentipedeManager.h"
#include "CentipedeSegment.h"
#include <iostream>
#include "CentipedeGame.h"

CentipedeManager::CentipedeManager() {

	gameHandle = nullptr;
}

void CentipedeManager::bindToGame(CentipedeGame *handle) {
	gameHandle = handle;
}

void CentipedeManager::calculateEntryX() {
	do {
		entryX = rand() % 30;
	} while (CentipedeGame::isMushroomCell(entryX, 0));
}

bool CentipedeManager::beginSpawn(unsigned int frame, unsigned int _speed, unsigned int _length) {

	bool status;

	if (done) {

		done = false;

		calculateEntryX();
		entryTime = frame;
		speed = _speed;
		haveSpawned = 0;
		length = _length;

		status = true;
	}
	else
		status = false;

	return status;
}

void CentipedeManager::update() {
	if (!done) {
        if (CentipedeGame::clock % speed == 0) {
            segments.push_back(gameHandle->spawnObject<CentipedeSegment>(entryX, 0));
            if (++haveSpawned >= length)
                done = true;
        }
	} else {
	    //verify segments
	    for (int i = 0; i < segments.size(); ++i) {
	        if (segments[i].use_count() < 2) {
                segments.erase(segments.begin() + i);
                --i;
	        }
	    }
	}

}

void CentipedeManager::placeSegment() {
}
