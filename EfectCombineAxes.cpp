#include "EfectCombineAxes.h"


EfectCombineAxes::EfectCombineAxes(const string& _inputCode1, const string& _inputCode2, float _scaleInput1, float _scaleInput2)
	: inputCode1(_inputCode1), inputCode2(_inputCode2), scaleInput1(_scaleInput1), scaleInput2(_scaleInput2)
{
}


void EfectCombineAxes::onUpdate(float dt)
{
	float value = getOwner()->keys[inputCode1] * scaleInput1 - getOwner()->keys[inputCode2] * scaleInput2;

	if (value < 0)
	{
		getOwner()->keys[inputCode1] = 0;
		getOwner()->keys[inputCode2] = abs(value);
	}
	else
	{
		getOwner()->keys[inputCode1] = abs(value);
		getOwner()->keys[inputCode2] = 0;
	}
}
