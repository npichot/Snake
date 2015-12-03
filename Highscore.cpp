#include "Highscore.h"
using namespace std;
using namespace sf;


/*
Cette fonction permet de récupérer les highscores à partir d'un fichier texte
*/
bool Highscore::loadScores()
{
	//on essaye d'ouvrir le fichier en lecture
	ifstream is("Ressources/Highscore.txt");
	if (!is)
	{
		return false;
	}
	int score;
	string name;

	//On lit les lignes une par une 
	while (scores.size()<3 && (is >> name >> score))
	{
		scores.push_back( pair<string, int>(name, score));
	}

	// close the opened file.
	is.close();
	return true;
}

/*
Cette fonction permet de sauvegarder les highscores
*/
void Highscore::saveScores()
{
	int h = isOneOfTheBest();
	if (h == -1)
		return;
	for (int i = h + 1; i < 3; i++)
		scores[i] = scores[i - 1];

	scores[h] = currentScore;

	ofstream fichier("Ressources/Highscore.txt", ios::out | ios::trunc);
	if (fichier)
	{
		for (int i = 0; i < 3; ++i)
			fichier << scores[i].first << " " << scores[i].second << endl;

		fichier.close();
	}
	else
		return;
	
}

/*
Determine si le score actuel fait partie du top 3
*/
int Highscore::isOneOfTheBest()
{
	for (int i = 0; i < 3; i++)
	{
		if (currentScore.second > scores[i].second)
			return i;
	}
	return -1;
}

/*
Initialise la classe. Crée le fichier highscore s'il n'existe pas.
*/
Highscore::Highscore()
{
	//On vérifie que le fichier existe
	ifstream is("Ressources/Highscore.txt");
	if (!is)
	{
		ofstream fichier("Ressources/Highscore.txt", ios::out | ios::trunc);
		if (fichier)
		{
			for (int i = 0; i < 3; ++i)
				fichier << "Empty " << "0" << endl;

			fichier.close();
		}
		else
			printf("Problème de creation du fichier de Highscores");
	}

	//On charge les scores
	if(!loadScores())
		printf("Problème chargement des Highscores");

	currentScore= pair<string, int>("User", 0);
}


Highscore::~Highscore()
{
}

/*
Actualise le score en fonction de la tile traversée par le serpent.
*/
void Highscore::updateScore(Tiles t, bool reverseMode, bool robotOn)
{
	switch (t)
	{
	case CHERRY:
		currentScore.second++;
		if (reverseMode)
			currentScore.second++;
		if (robotOn)
			currentScore.second++;
		break;
	case BANANA:
		currentScore.second--;
		break;
	case GRAPE:
		currentScore.second = 0;
		break;
	default:
		break;
	}
}

/*
Si l'utilisateur fait partie des highscores, on lui demande son nom
*/
void Highscore::askForName(sf::RenderWindow & window)
{
	if (isOneOfTheBest() != -1)
	{
		RenderWindow nameWindow(VideoMode(600, 75, 32), "Congratulations", Style::None);
		Text text;
		text.setCharacterSize(15);
		Font font;
		font.loadFromFile("Police/arial.ttf");
		text.setFont(font);
		text.setString("Félicitations, vous êtes dans le top 3. Entrez un nom puis appuyez sur Entrée :");
		text.setColor(Color::Red);
		FloatRect fr = text.getLocalBounds();
		text.setPosition((nameWindow.getSize().x - fr.width) / 2, 10);

		Text input;
		input.setFont(font);
		input.setString(currentScore.first);
		input.setCharacterSize(12);
		FloatRect fr2 = input.getLocalBounds();
		input.setPosition(nameWindow.getSize().x - fr2.width, 35);
		input.setColor(Color::Black);


		nameWindow.clear(Color(140, 140, 140, 255));
		nameWindow.draw(input);
		nameWindow.draw(text);
		nameWindow.display();

		while (nameWindow.isOpen())
		{
			Event event;
			while (nameWindow.pollEvent(event))
			{
				if ((event.type == Event::KeyPressed && event.key.code == Keyboard::Return) && currentScore.first.size() > 0)
				{
					saveScores();
					return;
				}
				else if (event.type == Event::TextEntered)
				{
					if (((event.text.unicode < 91) && (event.text.unicode > 64)) || ((event.text.unicode < 123) && (event.text.unicode > 96)))
						if (currentScore.first.size() < 50)
							currentScore.first.push_back(event.text.unicode);
				}
				else if (event.type == Event::KeyPressed && event.key.code == Keyboard::BackSpace)
				{
					if (currentScore.first.size() > 0)
						currentScore.first.pop_back();
				}
			}

			nameWindow.clear(Color(140, 140, 140, 255));
			input.setString(currentScore.first);
			FloatRect fr2 = input.getLocalBounds();
			input.setPosition((nameWindow.getSize().x - fr2.width) / 2, 35);
			nameWindow.draw(input);
			nameWindow.draw(text);
			nameWindow.display();
		}
	}

}

/*
Affiche le score dans la fenêtre de jeu
*/
void Highscore::showCurrentScore(sf::RenderWindow & window)
{
	Font font;
	font.loadFromFile("Police/arial.ttf");
	Text score;
	score.setFont(font);
	score.setString("Score : "+ to_string(currentScore.second));
	score.setCharacterSize(30);
	FloatRect fr = score.getLocalBounds();
	score.setPosition((window.getSize().x - fr.width)/2, 10);
	score.setColor(Color::White);
	window.draw(score);
}
