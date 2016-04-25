#pragma once
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class ISerializable
{
public:
	ISerializable()
	{
	}

	virtual void deserialize( const string& path )
	{
		fstream file(path);
		if( file )
		{
			deserialize( file );
		}else
		{
			cerr << " Error : fail open the file to load - \""<< path <<"\"\n";
		}

		file.close();
	}
	virtual void deserialize(istream& file){}

	virtual void serialize( const string& path )
	{
		fstream file(path);
		if( file )
		{
			serialize( file );
		}else
		{
			cerr << " Error : fail open the file to save - \""<< path <<"\"\n";
		}

		file.close();
	}
	virtual void serialize(ostream& file){}
};

