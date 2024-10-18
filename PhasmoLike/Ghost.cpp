#include "Ghost.h"
#include "EMFEvidenceComponent.h"
#include "SpiritBoxEvidenceComponent.h"
#include "WritingEvidenceComponent.h"
#include "DOTsEvidenceComponent.h"
#include "UltravioletEvidenceComponent.h"

Ghost::Ghost()
{
	character = new Character("Player", Vector2f(0.0f, 0.0f), Vector2f(50.0f, 50.0f), "Resources/Images/Player/idle.png");
	character->SetOriginAtMiddle();
	Init();
}
Ghost::~Ghost()
{
	for (EvidenceComponent* _component : evidences)
		delete _component;
}

string Ghost::GetGhostTypeName(const GhostType& _type)
{
	string _names[] = {"Spirit", "Wraith", "Phantom"};
	return _names[(int)_type];
}

void Ghost::Init()
{
	InitGhostRoom();
	InitType();
	InitEvidences();
}
void Ghost::InitType()
{
	type = (GhostType)RandomInRange(0, (int)GhostType::MAX - 1);
	cout << "[GHOST DEBUG]>>> Ghost type is: " << GetGhostTypeName(type) << endl;
}
void Ghost::InitGhostRoom()
{
	// TODO
}
void Ghost::InitEvidences()
{
	vector<vector<EvidenceComponent*>> _evidences = {
		{ new EMFEvidenceComponent(), new SpiritBoxEvidenceComponent(), new WritingEvidenceComponent() }, // Spirit ==> EMF Spirit Writing
		{ new EMFEvidenceComponent(), new SpiritBoxEvidenceComponent(), new DOTsEvidenceComponent() }, // Wraith ==> EMF Spirit DOTs
		{ new SpiritBoxEvidenceComponent(), new UltravioletEvidenceComponent(), new DOTsEvidenceComponent()}, // Phantom ==> Spirit Ultraviolet DOTs
	};
	for (int _index = 0; _index < 3; _index++)
		evidences.push_back(_evidences[(int)type][_index]);
}

int Ghost::RandomInRange(const int& _min, const int& _max)
{
	random_device _device;
	mt19937 _random(_device());
	uniform_int_distribution<mt19937::result_type> _distribution(_min, _max);
	return _distribution(_random);
}
