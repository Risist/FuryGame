#include "Animation.h"



AnimationSteap::State AnimationSteap::update( Model& model, float step, float speed)
{
	State state = inRange;
	if( step + speed >= stepMax )
		state = above;
	/*{
		speed = steapMax - steap;
		state = above;
	}*/
	else if( step + speed < stepMin )
		state = under;
		/*{
		speed = steapMin - steap;
		state = under;
	}*/
	model += (*this) * ( ::clamp(speed+ step, stepMin, stepMax) - step);
	model.setColor( sf::Color( model.clR, model.clG, model.clB, model.clA ) );

	return state;
}


void AnimationSteap::serialize( ostream& file )
{

}
void AnimationSteap::deserialize( istream& file )
{
	XMLloader loader;
	loader.nextLine( file );

	deserialize(loader, file);
}
void AnimationSteap::deserialize( XMLloader& loader, istream& file )
{
	stepMin = loader.load( "stepMin", -99990.f );
	stepMax = loader.load( "stepMax", 99990.f );
	idModel = loader.load( "model", 0 );
	
	ModelDef::deserialize( loader);
}


void Animation::serialize( ostream& file )
{

}
void Animation::deserialize( istream& file )
{
	XMLloader loader;
	loader.nextLine(file);

	
	stepMin = loader.load( "stepMin", 0.f );
	stepMax = loader.load( "stepMax", 100.f );
	step = loader.load( "step", stepMin );
	speed = loader.load( "speed", 1.f );

	loader.nextLine(file);
	while( loader.str() != '\\' )
	{
		part.push_back( AnimationSteap(loader,file) );

		loader.nextLine(file);
	}
}

void Animation::deserialize( const string& str, vector<Model*>& model )
{
	fstream file(str);
	if( file )
	{
		deserialize( file, model );
	}else
	{
		cerr << " Error : fail open the file to load - \""<< str <<"\"\n";
	}

	file.close();
}
void Animation::deserialize( istream& file, vector<Model*>& model )
{
	XMLloader loader;
	loader.nextLine(file);

	
	stepMin = loader.load( "stepMin", 0.f );
	stepMax = loader.load( "stepMax", 100.f );
	speed = loader.load( "step", stepMin );
	float _speed = loader.load( "speed", 1.f );

	loader.nextLine(file);
	while( loader.str() != '\\' )
	{
		part.push_back( AnimationSteap(loader,file) );

		loader.nextLine(file);
	}

	update(model);
	speed = _speed;
}