#pragma once
#include "Model.h"

class AnimationSteap : public ModelDef, public ISerializable
{
public:
	AnimationSteap( )
	{

	}
	AnimationSteap( XMLloader& loader, istream& file )
	{
		deserialize( loader, file );
	}
	AnimationSteap( const string& str )
	{
		deserialize(str);
	}


	enum State
	{
		under,
		inRange,
		above
	};
	State update( Model& model, float step, float speed = 1 );
	State update( vector<Model*>& model, float step, float speed = 1 )
	{
		return update( *model[idModel], step,  speed);
	}


	void serialize( const string& str)
	{
		ISerializable::serialize(str);
	}
	void serialize( ostream& file ) override;
	void deserialize( const string& str)
	{
		ISerializable::deserialize(str);
	}
	void deserialize( istream& file ) override;

	void deserialize( XMLloader& loader, istream& file);
	
	bool isInRange(float steap)
	{
		return steap >= stepMin && steap <= stepMax;
	}

private:
	float stepMin, stepMax;
	int idModel;
};

class Animation : public ISerializable
{
public:
	Animation(){}
	Animation(const string& path)
	{
		deserialize(path);
	}

	// update functions
	void update( vector<Model*>& model )
	{
		for( auto it = part.begin(); it != part.end(); ++it )
			if (it->isInRange(step) )
				it->update(model, step, speed);
		
		step += speed;
	}
	void update( vector<Model*>& model, float _speed )
	{
		swap( _speed, speed);
		update(model);
		swap( _speed, speed);
	}
	// returns true when in range
	bool updateInRange( vector<Model*>& model, float speed )
	{
		if( inRange(stepMin, stepMax, speed ) )
		{
			update(model, speed);
			return true;
		}
		
		/*if( steap >= steapMax)
			update(model, steapMax-speed > 0 ? steapMax - speed : 0 );
		else if( steap <= steapMin)
			update(model, steapMin-speed > 0 ? steapMin - speed : 0 );*/
		
		return false;
	}
	bool updateInRange(vector<Model*>& model )
	{
		if( inRange(stepMin, stepMax, speed ) )
		{
			update(model);
			return true;
		}
		return false;
	}
	AnimationSteap::State updateReturn(vector<Model*>& model )
	{
		update( model );
		if( !inRange( stepMin, stepMax) )
		{
			speed *= -1;
			return step >= stepMax ? AnimationSteap::above : AnimationSteap::under;
		}	
		return AnimationSteap::inRange;
	}

	// initialize
	void serialize( const string& str)
	{
		ISerializable::serialize(str);
	}
	void serialize( ostream& file ) override;
	void deserialize( const string& str)
	{
		ISerializable::deserialize(str);
	}
	void deserialize( istream& file ) override;
	
	void deserialize( const string& str, vector<Model*>& model );
	void deserialize( istream& file, vector<Model*>& model );
	
	// utility
	float getStep() const
	{
		return step;
	}
	float getStepMin() const
	{
		return stepMin;
	}
	float getStepMax() const
	{
		return stepMax;
	}

	bool inRange() const
	{
		return inRange(stepMin, stepMax);
	}
	bool inRange(float speed) const
	{
		return inRange(stepMin, stepMax, speed);
	}
	bool inRange( float steapMin, float steapMax) const
	{
		return step >= steapMin && step <= steapMax;
	}
	bool inRange( float steapMin, float steapMax, float speed) const
	{
		return step + speed >= steapMin && step + speed <= steapMax;
	}
	void reset()
	{
		step = 0;
		speed = abs(speed);
	}
	bool side() const
	{
		return speed > 0;
	}

	float getSpeed() const
	{
		return speed;
	}

	float getLenght()
	{
		return stepMax - stepMin;
	}
	float getPercentStep()
	{
		return (step - stepMin) / getLenght();
	}

//private:
	vector<AnimationSteap> part;
	float step, speed, stepMin, stepMax;
};

