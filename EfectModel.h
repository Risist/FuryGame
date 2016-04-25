#pragma once
#include "EfectUpdateModel.h"
#include "control.h"


inline void loadScript( const string& path, string& constructionScript, bool& loaded)
{
	
	if (loaded == false)
	{
		fstream file(path);
		if (file)
		{
			constructionScript = "";
			while (!file.eof())
			{
				string s;
				getline(file, s);
				if (s != "")
					constructionScript += s + "\n";
			}
		}
		else
		{
			cerr << " Error : fail open the file to load - \"" << path << "\"\n";
		}

		file.close();

		loaded = true;
	}
}

class EfectModel : public EfectUpdateModel
{
public:
	EfectModel(const string& _path = "", sf::Sprite *_connectedTo = nullptr, 
		bool _updateRotation = true, bool _updatePosition = true, bool update = true, float reloadDelay = -1 );
	EfectModel(istream& file, sf::Sprite *_connectedTo = nullptr,
		bool _updateRotation = true, bool _updatePosition = true, bool update = true, float reloadDelay = -1);

	void onInit() override;

	void onDisplay(Camera& cam) override;
	void onUpdate(float dt) override;

	void reloadModel();

	string path;
	istream* stream;
	Model model;
	bool update;

	// to not reload set wait_time to negative value
	Control::Timer timerReload;
};

