#pragma once
#include "ISerializable.h"
#include <SFML\Graphics.hpp>
#include <vector>

using namespace sf;

class _Texture : public ISerializable, public Texture
{
public:
	_Texture(){}
	_Texture( const string& path )
	{
		deserialize(path);
	}


	void deserialize( const string& path) override
	{
		if( im.loadFromFile(path) )
		{
			im.createMaskFromColor( clTransparent );
			loadFromImage(im);
		}else
		{
			cout << "Fail to open the texture: \"" << path << "\"" << endl;
		}
	}
	void serialize( ostream& file ) override
	{
	}
	void deserialize( istream& file ) override
	{
	}

	static void setClTransparent( const Color& s)
	{
		clTransparent = s;
	}
	static const Color& getClTransparent()
	{
		return clTransparent;
	}
	static vector<_Texture>& instance()
	{
		return ts;
	}
	static _Texture& addTexture( const string& str)
	{
		ts.push_back(_Texture(str) );
		return ts.back();
	}
	static void deserializeCont( istream& file);
	static void deserializeCont(const string& path);
private:
	static Image im;
	static Color clTransparent;
	static vector<_Texture> ts;
};

#define tsInst _Texture::instance()