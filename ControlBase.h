#pragma once
#include "ISerializable.h"

namespace Control
{
	class Base : public ISerializable
	{
	public:

		virtual bool isReady()
		{
			return true;
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
		}

		virtual string getName(){ return "Unknown"; }
		//static Base* createNew(const string& str){ return nullptr;  // TODO}

	};
}

