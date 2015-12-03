#ifndef __HIGHSCORE_H__
#define __HIGHSCORE_H__

#include "Map.h"

class Highscore
{
private:
	std::vector<std::pair<std::string, int>> scores;
	std::pair<std::string, int> currentScore;

	bool loadScores();
	void saveScores();
	int isOneOfTheBest();

public:
	Highscore();
	~Highscore();
	void updateScore(Tiles t, bool reverseMode, bool robotOn);
	void askForName(sf::RenderWindow & window);
	void showCurrentScore(sf::RenderWindow & window);
	std::vector<std::pair<std::string, int>> getScores() { return scores; };
	void reset() { currentScore = std::pair<std::string, int>("User", 0); };

};

#endif

