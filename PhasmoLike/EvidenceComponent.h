#pragma once

#include <iostream>
#include <random>

using namespace std;

class EvidenceComponent
{
protected:
	int percent;

public:
	EvidenceComponent(const int& _percent);

private:
	int RandomInRange(const int& _min, const int& _max);

public:
	void TriggerEvidence();
	virtual void Evidence() = 0;
};