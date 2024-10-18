#include "EvidenceComponent.h"

EvidenceComponent::EvidenceComponent(const int& _percent)
{
	percent = _percent;
}

int EvidenceComponent::RandomInRange(const int& _min, const int& _max)
{
	random_device _device;
	mt19937 _random(_device());
	uniform_int_distribution<mt19937::result_type> _distribution(_min, _max);
	return _distribution(_random);
}

void EvidenceComponent::TriggerEvidence()
{
	if (RandomInRange(0, 100) <= percent)
	{
		Evidence();
	}
}
void EvidenceComponent::Evidence()
{
	cout << "Evidence component doesn't override the evidence method" << endl;
}