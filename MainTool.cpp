#include "MainTool.h"
#include <iostream>
using namespace std;
using namespace sf;

string MainTool::checkMap(Map & map)
{
	vector<pair<int, int>> freeSpace;
	vector<vector<bool>> mapMask;
	bool headFound = false;
	vector<pair<int, int>> stack;
	int countProofedTiles = 0;

	for (int i = 0; i < map.getGameField().size(); i++)
	{
		vector<bool> init;
		for (int j = 0; j < map.getGameField()[0].size(); j++)
		{
			init.push_back(false);
				if (map.getTile(i, j) == EMPTY)
					freeSpace.push_back(pair<int, int>(i, j));
				else if (map.getTile(i, j) >= 20 && map.getTile(i, j) <= 23)
				{
					if (headFound)
						return "Vous ne devez placer qu'une seule tête !";

					headFound = true;
					freeSpace.push_back(pair<int, int>(i, j));
					stack.push_back(pair<int, int>(i, j));
				}
		}
		mapMask.push_back(init);
	}

	if (!headFound)
		return "Vous devez placer une tête !";

	if (freeSpace.size() < 2)
		return "Vous devez placer des espaces libres !";

	//Parcours du graphe à partir de la tête pour voir si tout les espaces sont accessibles.
	while (stack.size()>0)
	{
		int i = stack[stack.size()-1].first, j = stack[stack.size()-1].second;
		stack.pop_back();

		if (mapMask[i][j])
			continue;

		mapMask[i][j] = true;
		countProofedTiles++;

		if (i > 0)
			if (!mapMask[i - 1][j] && map.getTile(i - 1, j) == EMPTY)
				stack.push_back(pair<int, int>(i - 1, j));

		if (i < map.getGameField().size()-1)
			if (!mapMask[i + 1][j] && map.getTile(i + 1, j) == EMPTY)
				stack.push_back(pair<int, int>(i + 1, j));

		if (j > 0)
			if (!mapMask[i][j - 1] && map.getTile(i, j - 1) == EMPTY)
				stack.push_back(pair<int, int>(i, j - 1));

		if (j < map.getGameField()[0].size() - 1)
			if (!mapMask[i][j + 1] && map.getTile(i, j + 1) == EMPTY)
				stack.push_back(pair<int, int>(i, j + 1));
	}

	if (freeSpace.size() != countProofedTiles)
		return "Tout les espaces libres ne sont pas accessibles";

	return "OK";
}

MainTool::MainTool(sf::Texture t, std::string s)
	:Tool(t, s)
{
	!font.loadFromFile("Police/arial.ttf");
}

MainTool::~MainTool()
{
}

bool MainTool::execute(int x0, int y0, int x, int y, Map & map)
{
	if (getName() == "Save")
		saveMap(map);
	else if (getName() == "Quit")
		return false;
	return true;
}

void MainTool::saveMap(Map map)
{
	string check = checkMap(map);
	if (check!="OK")
	{
		RenderWindow errorWindow(VideoMode(600, 75, 32), "Erreur");
		while (errorWindow.isOpen())
		{
			errorWindow.clear(Color(140, 140, 140, 255));
			Text text;
			text.setCharacterSize(25);
			text.setFont(font);
			text.setString(check);
			text.setColor(Color::Red);
			FloatRect fr = text.getLocalBounds();
			text.setPosition((errorWindow.getSize().x - fr.width) / 2, 12.5);
			errorWindow.draw(text);
			errorWindow.display();

			Event event;
			while (errorWindow.pollEvent(event))
			{
				if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
				{
					errorWindow.close();
					return;
				}
			}
		}
	}
	else
	{
		RenderWindow saveWindow(VideoMode(400, 100, 32), "Save Map");
		string inputText;
		bool mouseIsReleased = false;
		int xMouse = 0;
		int yMouse = 0;

		while (saveWindow.isOpen())
		{
			saveWindow.clear(Color(200, 200, 200, 255));
			buildTheWindow(saveWindow);

			Event event;
			while (saveWindow.pollEvent(event))
			{
				// fermeture de la fenêtre lorsque l'utilisateur le souhaite
				if (event.type == Event::Closed)
					saveWindow.close();
				else if (event.type == Event::MouseMoved)
				{
					xMouse = Mouse::getPosition(saveWindow).x;
					yMouse = Mouse::getPosition(saveWindow).y;
				}
				else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
				{
					xMouse = Mouse::getPosition(saveWindow).x;
					yMouse = Mouse::getPosition(saveWindow).y;
					break;
				}
				else if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
				{
					mouseIsReleased = true;
					break;
				}
				else if (event.type == Event::TextEntered)
				{
					if (((event.text.unicode < 91) && (event.text.unicode > 64)) || ((event.text.unicode < 123) && (event.text.unicode > 96)))
						if (inputText.size() < 50)
							inputText.push_back(event.text.unicode);
				}
				else if (event.type == Event::KeyPressed && event.key.code == Keyboard::BackSpace)
				{
					if (inputText.size() > 0)
						inputText.pop_back();
				}
			}

			if (mouseIsReleased)
			{
				if (isSaveClicked(xMouse, yMouse))
				{
					if (inputText.size() > 0)
					{
						writeConfig(inputText, map);
						saveWindow.close();
						return;
					}
				}
				else if (isCancelClicked(xMouse, yMouse))
				{
					saveWindow.close();
					return;
				}

				mouseIsReleased = false;
			}

			Text input;
			input.setFont(font);
			input.setString(inputText);
			input.setCharacterSize(12);
			input.setPosition(15, 37);
			input.setColor(Color::Black);
			saveWindow.draw(input);

			saveWindow.display();
		}
	}
}

void MainTool::buildTheWindow(sf::RenderWindow & window)
{
	Text title;
	title.setFont(font);
	title.setString("Entre le nom de la Map que vous voulez sauvegarder :");
	title.setCharacterSize(12);
	title.setColor(sf::Color::Black);
	title.setPosition(10, 10);
	window.draw(title);

	RectangleShape inputTextZone;
	inputTextZone.setFillColor(Color::White);
	inputTextZone.setOutlineThickness(1);
	inputTextZone.setOutlineColor(Color::Black);
	inputTextZone.setSize(Vector2f(380, 22));
	inputTextZone.setPosition(10, 32);
	window.draw(inputTextZone);

	Text ok;
	ok.setFont(font);
	ok.setString("Sauver");
	ok.setCharacterSize(12);
	ok.setColor(sf::Color::Black);
	FloatRect fro = ok.getLocalBounds();

	Text cancel;
	cancel.setFont(font);
	cancel.setString("Annuler");
	cancel.setCharacterSize(12);
	cancel.setColor(sf::Color::Black);
	FloatRect frc = cancel.getLocalBounds();

	ok.setPosition((400 - 50 - fro.width - frc.width) / 2, 70);
	cancel.setPosition((400 - 40 - fro.width - frc.width) / 2 + 30 + fro.width, 70);

	RectangleShape buttonOk;
	buttonOk.setFillColor(Color(200, 200, 200, 255));
	buttonOk.setOutlineThickness(1);
	buttonOk.setOutlineColor(Color::Black);
	buttonOk.setSize(Vector2f(fro.width + 10, fro.height + 10));
	buttonOk.setPosition(ok.getPosition().x - 5, ok.getPosition().y);
	window.draw(buttonOk);

	RectangleShape buttonCancel;
	buttonCancel.setFillColor(Color(200, 200, 200, 255));
	buttonCancel.setOutlineThickness(1);
	buttonCancel.setOutlineColor(Color::Black);
	buttonCancel.setSize(Vector2f(frc.width + 10, frc.height + 10));
	buttonCancel.setPosition(cancel.getPosition().x - 5, cancel.getPosition().y);
	window.draw(buttonCancel);

	window.draw(ok);
	window.draw(cancel);
}

bool MainTool::isSaveClicked(int x, int y)
{
	Text ok;
	ok.setFont(font);
	ok.setString("Sauver");
	ok.setCharacterSize(12);
	FloatRect fro = ok.getLocalBounds();

	Text cancel;
	cancel.setFont(font);
	cancel.setString("Annuler");
	cancel.setCharacterSize(12);
	FloatRect frc = cancel.getLocalBounds();

	ok.setPosition((400 - 50 - fro.width - frc.width) / 2, 70);

	RectangleShape buttonOk;
	buttonOk.setSize(Vector2f(fro.width + 10, fro.height + 10));
	buttonOk.setPosition(ok.getPosition().x - 5, ok.getPosition().y);

	if (buttonOk.getGlobalBounds().contains(x, y))
		return true;
	else
		return false;
}

bool MainTool::isCancelClicked(int x, int y)
{
	Text ok;
	ok.setFont(font);
	ok.setString("Sauver");
	ok.setCharacterSize(12);
	FloatRect fro = ok.getLocalBounds();

	Text cancel;
	cancel.setFont(font);
	cancel.setString("Annuler");
	cancel.setCharacterSize(12);
	FloatRect frc = cancel.getLocalBounds();

	cancel.setPosition((400 - 40 - fro.width - frc.width) / 2 + 30 + fro.width, 70);

	RectangleShape buttonCancel;
	buttonCancel.setSize(Vector2f(frc.width + 10, frc.height + 10));
	buttonCancel.setPosition(cancel.getPosition().x - 5, cancel.getPosition().y);

	if (buttonCancel.getGlobalBounds().contains(x, y))
		return true;
	else
		return false;
}

void MainTool::writeConfig(string name, Map map)
{
	//Write dat file
	ofstream fichier("MapConfig/" + name + ".dat", ios::out | ios::trunc);
	if (fichier)
	{
		for (int i = 0; i < map.getGameField().size(); ++i)
			for (int j = 0; j < map.getGameField()[i].size(); ++j)
			{
				fichier << i << " " << j << " " << map.getTile(i, j) << endl;
			}

		fichier.close();
	}
	else
		cout << "Erreur écriture !";
}
