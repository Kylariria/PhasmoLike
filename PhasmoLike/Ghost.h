#pragma once

#include <random>

#include "Character.h"
#include "Room.h"
#include "EvidenceComponent.h"

using namespace std;

enum class GhostType
{
	Spirit,
	Wraith,
	Phantom,
	MAX,
};

class Ghost
{
	Character* character;
	Room* ghostRoom = nullptr;
	GhostType type;
	vector<EvidenceComponent*> evidences;

public:
	Character* GetCharacter() const { return  character; }

public:
	Ghost();
	~Ghost();

private:
	string GetGhostTypeName(const GhostType& _type);
	void Init();
	void InitType();
	void InitGhostRoom();
	void InitEvidences();
	int RandomInRange(const int& _min, const int& _max);
};