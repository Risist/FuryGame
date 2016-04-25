#include "Model.h"
#include "_Texture.h"
#include <fstream>

Model::Model( const Texture& ts, const ModelDef& def  )
	: parent(nullptr), childUp(nullptr), childDown(nullptr), sibling(nullptr), // pointners - nullptr for all
	ModelDef(def)
{
	setTexture(ts);
}


Model::~Model() // remove other, connected models with that
{
	if(childDown != nullptr)
		delete childDown;
	if(childUp != nullptr)
		delete childUp;

	if(sibling != nullptr)
		delete sibling;
}

void Model::draw(RenderTarget& target, const  sf::Sprite& father) // display myself and my childs (also siblings)
{
	//if (parent == nullptr)
		//update(father);
	//else update(*parent);

	if( childDown != nullptr)
		childDown->draw( target );

	target.draw( *this );

	if( childUp != nullptr)
		childUp->draw( target );

	if( sibling != nullptr)
		sibling->draw( target );
}
void Model::draw(Camera& target, const  sf::Sprite& father ) // display myself and my childs (also siblings)
{
	//if ( parent == nullptr)
		//update(father);
	//else update(*parent);

	if (childDown != nullptr)
		childDown->draw(target, father);

	target.draw(*this);

	if (childUp != nullptr)
		childUp->draw(target, father);

	if (sibling != nullptr)
		sibling->draw(target, father);
}


void Model::update( const sf::Sprite& parent)
{
	float alfa=((parent.getRotation() + rotAround)* M_PI) /180.f;
	sf::Vector2f v,p(pos.x * parent.getScale().x, pos.y * parent.getScale().y);

	v.x = p.x * cos(alfa) - p.y * sin(alfa);
	v.y = p.x * sin(alfa) + p.y * cos(alfa);

	setRotation(parent.getRotation() + rot);
	setPosition(parent.getPosition() + v + posNoRot);

	sf::Sprite::setScale(	ModelDef::scale.x * parent.getScale().x, 
							ModelDef::scale.y * parent.getScale().y	);

	//setColor( sf::Color( clR, clG, clB, clA ) );
}
void Model::updateAll(const sf::Sprite& father)
{
	if (parent == nullptr)
		update(father);
	else update(*parent);

	if (childDown != nullptr)
		childDown->updateAll(father);

	if (childUp != nullptr)
		childUp->updateAll(father);

	if (sibling != nullptr)
		sibling->updateAll(father);
}


void Model::serialize( ostream& file )
{

}
void Model::deserialize( istream& file )
{
	XMLloader loader;
	loader.nextLine( file );

	deserialize(loader, file);
}
void Model::deserialize( XMLloader& loader, istream& file )
{
	ModelDef::deserialize( loader, ModelDef( Vector2f(), 0, Vector2f(1,1), 0, 255, 255, 255, 255 ) );

	if (childDown != nullptr)
	{
		delete childDown;
		childDown = nullptr;
	}
	if (childUp != nullptr)
	{
		delete childUp;
		childUp = nullptr;
	}

	if (sibling != nullptr)
	{
		delete sibling;
		sibling = nullptr;
	}

	setTexture(  loader.load( "ts", (size_t)0 ) );

	setColor( sf::Color( clR, clG, clB, clA ) );

	loader.nextLine(file);

	while( loader.str() != "\\" )
	{
		bool b = loader.load( "ud", 0 );
		Model *m = new Model();
		
		if( b == 0 )
			addUp( m );
		else
			addDown( m );

		m->deserialize( loader, file );
		
		loader.nextLine(file);
	}
}

void Model::setTexture( size_t id)
{
	setTexture( tsInst[id]);
	idTs = id;
}
