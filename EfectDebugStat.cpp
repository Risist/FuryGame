#include "EfectDebugStat.h"


EfectDebugStat::EfectDebugStat(int _resourceId, bool _f_v2, const string& _description, const Control::Input& _inputCheckAll)
	: resourceId(_resourceId), f_v2(_f_v2), description(_description), inputCheckAll(_inputCheckAll)
{
}


void EfectDebugStat::onUpdate(float dt)
{
	Efect::onUpdate(dt);

	if (inputCheckAll.isReady())
	{
		if ( f_v2 == true)
		{
			cout << description << " position: " << getOwner()->getResourceC_f(resourceId).position << "\n";
			cout << description << " velocity: " << getOwner()->getResourceC_f(resourceId).velocity << "\n";
			cout << description << " force: " << getOwner()->getResourceC_f(resourceId).force << "\n";
			cout << "\n";
			cout << description << " inverseMass: " << getOwner()->getResourceC_f(resourceId).inverseMass << "\n";
			cout << description << " resetVelocity: " << getOwner()->getResourceC_f(resourceId).resetVelocity << "\n";
			cout << description << " resetforce: " << getOwner()->getResourceC_f(resourceId).resetForce << "\n";
			cout << "\n";
		}else
		{
			cout << description << " position: " << getOwner()->getResourceC_v2(resourceId).position << "\n";
			cout << description << " velocity: " << getOwner()->getResourceC_v2(resourceId).velocity << "\n";
			cout << description << " force: " << getOwner()->getResourceC_v2(resourceId).force << "\n";
			cout << "\n";
			cout << description << " inverseMass: " << getOwner()->getResourceC_v2(resourceId).inverseMass << "\n";
			cout << description << " resetVelocity: " << getOwner()->getResourceC_v2(resourceId).resetVelocity << "\n";
			cout << description << " resetforce: " << getOwner()->getResourceC_v2(resourceId).resetForce << "\n";
			cout << "\n";
		}
	}

}
void EfectDebugStat::onInteract(float value, size_t _resourceId, Game::Object* other)
{
	Efect::onInteract(value, _resourceId, other);

	if (f_v2 == true && resourceId == _resourceId)
	{
		cout << "///// onInteract /////\n";
		cout << "with " << other << "\n";
		cout << description << " position: " << getOwner()->getResourceC_f(resourceId).position << "\n";
		cout << description << " velocity: " << getOwner()->getResourceC_f(resourceId).velocity << "\n";
		cout << description << " force: " << getOwner()->getResourceC_f(resourceId).force << "\n";
		cout << "\n";
	}
}

void EfectDebugStat::onInteract(const Vector2D& value, size_t _resourceId, Game::Object* other)
{
	Efect::onInteract(value, _resourceId, other);

	if (f_v2 == false && resourceId == _resourceId)
	{
		cout << "///// onInteract /////\n";
		cout << "with " << (int)other << "\n";
		cout << description << " position: " << getOwner()->getResourceC_v2(resourceId).position << "\n";
		cout << description << " velocity: " << getOwner()->getResourceC_v2(resourceId).velocity << "\n";
		cout << description << " force: " << getOwner()->getResourceC_v2(resourceId).force << "\n";
		cout << "\n";
	}
}