#include "IDirections.h"
#include "VectorsUtils.h"

IDirections::IDirections()
{
	currentAngle = 0.0f;
	forwardVector = Vector2f(0.0f, -1.0f);
	rightVector = Vector2f(1.0f, 0.0f);
}

void IDirections::SetRotation(const int& _newDirection)
{
	currentAngle = _newDirection;
	while (currentAngle >= 360) currentAngle -= 360;
	forwardVector = VectorsUtils::GetVector(currentAngle);
	rightVector = VectorsUtils::GetVector(currentAngle + 90 == 360 ? 0 : currentAngle + 90);
}