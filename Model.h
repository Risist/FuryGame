#pragma once
#include "ISerializable.h"
#include "ModelDef.h"
#include <vector>
#include "Camera.h"

#include "utility.h"

using namespace sf;


class Model : public sf::Sprite, public ISerializable, public ModelDef
{
public:
	Model( const Texture& ts = Texture(), const ModelDef& def = ModelDef(Vector2f(),0, Vector2f(1,1), 0,255,255,255,255) );
	~Model();

	void draw(RenderTarget& target, const sf::Sprite& father = sf::Sprite() );
	void draw(Camera& cam, const sf::Sprite& father = sf::Sprite() );

	void update()
	{
		if( parent != nullptr)
			update(*parent);
		else
			update( Sprite() );
	}
	void update( const sf::Sprite& parent);
	void updateAll()
	{
		if (parent != nullptr)
			updateAll(*parent);
		else
			updateAll(Sprite());
	}
	void updateAll(const sf::Sprite& parent);

	void initAllModels( vector<Model*>& all )
	{
		all.push_back(this);

		
		if( childDown != nullptr )
			childDown->initAllModels( all );

		if( childUp != nullptr )
			childUp->initAllModels( all );
		
		if( sibling != nullptr )
			sibling->initAllModels( all );

	}


	// initializing process functions

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

	void setTexture( const sf::Texture& ts)
	{
		Sprite::setTexture(ts,true);
		setOrigin( getTextureRect().width/2, getTextureRect().height/2 );
	}
	void setTexture(size_t id);

	void addUp( Model *s)
	{
		if( childUp == nullptr )
		{
			childUp = s;
			childUp->parent = this;
		}
		else
			childUp->addSibling(s);
	}
	void addDown( Model *s)
	{
		if( childDown == nullptr )
		{
			childDown = s;
			childDown->parent = this;
		}
		else
			childDown->addSibling(s);
	}

//private:
	sf::Sprite *parent;
	Model *childUp, *childDown, *sibling;
	size_t idTs;
	void addSibling( Model *s )
	{
		if(sibling == nullptr )
		{
			sibling = s;
			sibling->parent = parent;
		}
		else
			sibling->addSibling(s);
	}

	void setColorAll( const Color& cl)
	{
		clR = cl.r;
		clG = cl.g;
		clB = cl.b;
		clA = cl.a;
		setColor(Color(clR, clG, clB, clA));

		if (childUp != nullptr)
			childUp->setColorAll(cl);
		if (childDown != nullptr)
			childDown->setColorAll(cl);
		if (sibling != nullptr)
			sibling->setColorAll(cl);
	}
	void setColorAll_R( float s)
	{
		clR = s;
		setColor(Color(clR, clG, clB, clA));

		if (childUp != nullptr)
			childUp->setColorAll_R(s);
		if (childDown != nullptr)
			childDown->setColorAll_R(s);
		if (sibling != nullptr)
			sibling->setColorAll_R(s);
	}
	void setColorAll_G( float s)
	{
		clG = s;
		setColor(Color(clR, clG, clB, clA));

		if (childUp != nullptr)
			childUp->setColorAll_G(s);
		if (childDown != nullptr)
			childDown->setColorAll_G(s);
		if (sibling != nullptr)
			sibling->setColorAll_G(s);
	}
	void setColorAll_B( float s)
	{
		clB = s;
		setColor(Color(clR, clG, clB, clA));

		if (childUp != nullptr)
			childUp->setColorAll_B(s);
		if (childDown != nullptr)
			childDown->setColorAll_B(s);
		if (sibling != nullptr)
			sibling->setColorAll_B(s);
	}
	void setColorAll_A( float s)
	{
		clA = s;
		setColor(Color(clR, clG, clB, clA));

		if (childUp != nullptr)
			childUp->setColorAll_A(s);
		if (childDown != nullptr)
			childDown->setColorAll_A(s);
		if (sibling != nullptr)
			sibling->setColorAll_A(s);
	}
};

