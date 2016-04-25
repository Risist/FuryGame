#pragma once
#include <iostream>
#include <sstream>
#include <string>

using namespace std;
 
class XMLloader
{
public:
	XMLloader()
	{

	}

	const string& str()
	{
		return s;
	}
	void nextLine( istream& stream)
	{
		s = "";
		while (stream.get() != '<');
		{
			string l;
			getline(stream, l, '>');
			s += l;
		}
		//cout << "s = " << s << "\n\n";
	}
	string load( const string& traits, const string& defaultValue = "_undefined" )
	{

		size_t pos = s.find( traits );
		if( pos == string::npos)
			return defaultValue;
		else
		{
			size_t start = s.find( "=", pos ) + 1 ;
			size_t end = s.find(";", start); 
			end = end == string::npos ? s.find( ">", start ) : end;

			return s.substr(start,  end - start );
		}
	}
	template<class Type> Type load( const string& traits, const Type& defaultValue)
	{
		string s = load(traits, "_undefined");

		Type r;
		if( s != "_undefined" )
		{
			stringstream stream( s );
			stream >> r;
		}
		else
			r = defaultValue;
		return r;
	}
	
private:
	string s;

};

/*
< type = coœ; fdfd = dfdf >
< >
< >

*/