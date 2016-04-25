#include "_Texture.h"
#include "XMLloader.h"

Image _Texture::im;
Color _Texture::clTransparent( 255,255,255 );
vector<_Texture> _Texture::ts(1);



void _Texture::deserializeCont( istream& file)
{
	XMLloader loader;

	loader.nextLine( file );
	string prePath = loader.load("path", "");

	loader.nextLine(file);
	while (loader.str() != "\\")
	{
		addTexture( prePath + loader.load( "path","" ) );

		loader.nextLine(file);
	}
}
void _Texture::deserializeCont(const string& path)
{
	ifstream file(path);
	deserializeCont(file);

	file.close();
}