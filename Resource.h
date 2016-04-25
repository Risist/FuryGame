#pragma once
#include "utility.h"

typedef float F_t;
/*
Requirements:

T should have defined operators *, += and *= with F_t
and default constructor available
*/
/*
Role:

class used to simulate any kinds of resources
builded on basis of newtons law, 
but can be used with any kinds of resources
like health, rotation, position, money, points, mana ...

supports the second derivate of T
in future may be expand on higher degree

parametrs description:

position - the value of Resource ( position for position, rotation for rotation, hit points for health, amount of money for money ect. )
velocity - how the position is changed every frame ( velocity for position, angular velocity for rotation, regeneretion for health, wage for money ect. )
force - any tries of change position is done by adding the force

mass, inverseMass - describe how easy it is to change the value ( mass for position, momentum for rotation, defense for health ect. )
	there is stored inverseMass instead of mass for one reason
	if mass is equal to 0 it makes no sence
	if inverseMas is equal to 0 creates immovable, inchangeable ect resource

	change to force is counted by multiplaying aplyed force

resetVelocity, resetForce - what happens with left velocity/force? 
	in particualr case resetForce should be equal to 0, then every frame force is stored again from zero
	otherwise it describes how much force left from last frame
	
	resetVelocity works the same
	can be used to simulate friction/dampting
	when equal to 1 there is no friction at all
	when less than 1 and more than 0 it is a dampting
	when less than 0 or more than 1 occurs at weird behaviour, probably useless


*/

enum Param_t
{
	Position,
	Velocity,
	Force,
	None_t
};
enum Param_f
{
	InverseMass,
	ResetVelocity,
	ResetForce,
	None_f
};

template<class T>
class Resource : public ISerializable
{
public:
	Resource( const T& _position = T(), const T& _velocity = T(), const T& _force = T() )
		: resetVelocity(1), resetForce(0), inverseMass(1)
		, position(_position), velocity(_velocity), force(_force)
	{

	}

	
	T& getParam_t(Param_t param)
	{
		switch (param)
		{
		case Position:
			return position;
		case Velocity:
			return velocity;
		case Force:
			return force;
		}
	}
	const T& getParamC_t(Param_t param) const
	{
		switch (param)
		{
		case Position:
			return position;
		case Velocity:
			return velocity;
		case Force:
			return force;
		}
	}

	
	T& getParam_f(Param_f param)
	{
		switch (param)
		{
		case InverseMass:
			return inverseMass;
		case ResetVelocity:
			return resetVelocity;
		case ResetForce:
			return resetForce;
		}
	}
	const F_t& getParamC_f(Param_f param) const
	{
		switch (param)
		{
		case InverseMass:
			return inverseMass;
		case ResetVelocity:
			return resetVelocity;
		case ResetForce:
			return resetForce;
		}
	}


	void serialize(const string& str)
	{
		ISerializable::serialize(str);
	}
	void serialize(ostream& file) override
	{
	}
	void deserialize(const string& str)
	{
		ISerializable::deserialize(str);
	}
	void deserialize(istream& file) override
	{
		XMLloader loader;
		deserialize(loader, file);
	}
	void deserialize(XMLloader& loader, istream& file)
	{
		loader.nextLine(file);

		position = loader.load("position", position);
		velocity = loader.load("velocity", velocity);
		force = loader.load("force", force);

		inverseMass = loader.load("inverseMass", inverseMass);

		resetVelocity = loader.load("resetVelocity", resetVelocity);
		resetForce = loader.load("resetForce", resetForce);
	}

	void addForce(const T& s)
	{
		force += s;
	}

	// update the resource
	// dt param is the time elapsed from last update
	void update(F_t dt = 1)
	{
		velocity += force*inverseMass * dt;
		force *= resetForce;

		position += velocity*dt;
		velocity *= resetVelocity;
	}

	// used to set the mass
	// warring - the s param cant be a zero
	void mass(const F_t& s)
	{
		inverseMass = 1 / s;
	}
	// returns a mass
	F_t mass() const
	{
		return 1 / inverseMass;
	}

	// basic propertites of Resource
	// position is a actual value
	// velocity defines how is changed every second
	// force describes sum of actual efecting forces
	//		a new forces should be added by addForce function
	T position, velocity, force;
	
	// used to define how easy is to change an position
	// value 0 means unchangable resource
	F_t inverseMass;
	// describes how velocity and force is changed after update
	// the resetVelocity parametr is used as dampting ( 0; 1 value)
	// the resetForce parametr describes losing of force ( default = 0 )
	F_t resetVelocity, resetForce;
};

