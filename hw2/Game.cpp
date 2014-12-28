#include "Game.h"

#include <vector>
#include <string>

#include "GameConfig.h"
#include "FilesManager.h"
#include "ScreenManager.h"
#include "GameScreenBuilder.h"
#include "GameOverScreen.h"
#include "GameScreen.h"
#include "MenuScreen.h"

unsigned Game::_nextLevelId;

void Game::startLevel()
{
	std::string nextLevelFileName("");
	bool found = false;

	//Get closest-level file
	{
		std::vector<std::string> fileNames = FilesManager::getFileNames();

		//Get ID per SPG file
		std::vector<unsigned> ids;
		{
			for(std::vector<std::string>::iterator fileName = fileNames.begin();
				fileName != fileNames.end(); ++fileName)
			{
				const std::string filePath = GameConfig::getLevelsPath() +  *fileName;

				unsigned id;
				if(FilesManager::getScreenId(filePath, id))
				{
					ids.push_back(id);
				}
				else
				{
					fileName = fileNames.erase(fileName);
					--fileName;
				}
			}
		}

		unsigned closestIdIndex = 0;
		for(unsigned i = 0; i < ids.size(); ++i)
		{
			if(ids[i] >= Game::_nextLevelId)
			{
				if(found == false)
				{
					found = true;
					closestIdIndex = i;
				}
				else if(ids[i] <= ids[closestIdIndex])
				{
					closestIdIndex = i;
				}
			}
		}

		if(found)
		{
			Game::_nextLevelId = ids[closestIdIndex];
			nextLevelFileName = fileNames[closestIdIndex];
		}
	}

	if(found)
	{
		const std::string levelFile = GameConfig::getLevelsPath() + nextLevelFileName;

		GameScreenBuilder builder;
		builder.loadFromFile(levelFile);
		if(builder.isValid())
		{
			ScreenManager::add(builder.build());
		}
		else
		{
			Game::startNextLevel(); //Retry with another ID
		}
	}
	else
	{
		MenuScreen * congratulationsScreen = new MenuScreen();
		congratulationsScreen->append("Congratulations!");
		congratulationsScreen->append("You may receive the \"Challanger\" bedge");
		congratulationsScreen->append(" by subscribing to our Facebook page!");

		//TODO: Append a high-score board

		ScreenManager::add(congratulationsScreen);
	}
}

void Game::start()
{
	Game::_nextLevelId = 0;

	Game::startLevel();
}

void Game::startNextLevel()
{
	++Game::_nextLevelId;

	Game::startLevel();
}

void Game::gameOver()
{
	ScreenManager::add(new GameOverScreen());
}
