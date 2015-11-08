#include "MainTool.h"
#include <iostream>
using namespace std;
using namespace sf;

MainTool::MainTool(sf::Texture t, std::string s)
	:Tool(t, s)
{
}

MainTool::~MainTool()
{
}

bool MainTool::execute(int x0, int y0, int x, int y, Map & map)
{
	if (getName() == "Save")
		saveMap(map);
	return true;
}

void MainTool::saveMap(Map map)
{
	RenderWindow saveWindow(VideoMode(400, 100, 32), "Save Map");
	string inputText;
	bool mouseIsReleased = false;
	int xMouse = 0;
	int yMouse = 0;
	Font font;
	if (!font.loadFromFile("Police/arial.ttf"))
	{
		// TODO erreur...
	}

	while (saveWindow.isOpen())
	{
		saveWindow.clear(Color(200,200,200,255));
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
			}
			else if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
			{
				mouseIsReleased = true;
			}
			else if (event.type == Event::TextEntered)
			{
				if (((event.text.unicode < 91)&& (event.text.unicode > 64))|| ((event.text.unicode < 123) && (event.text.unicode > 96)))
					if(inputText.size()<50)
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
				}
			}
			else if (isCancelClicked(xMouse, yMouse))
				saveWindow.close();

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

void MainTool::buildTheWindow(sf::RenderWindow & window)
{
	Font font;
	if (!font.loadFromFile("Police/arial.ttf"))
	{
		// TODO erreur...
	}
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
	Font font;
	if (!font.loadFromFile("Police/arial.ttf"))
	{
		// TODO erreur...
	}
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
	Font font;
	if (!font.loadFromFile("Police/arial.ttf"))
	{
		// TODO erreur...
	}
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
	ofstream fichier("MapConfig/" + name + ".dat", ios::out | ios::trunc);
	if (fichier)
	{
		for (int i = 0; i < map.getField().size(); ++i)
			for (int j = 0; j < map.getField()[i].size(); ++j)
			{
				fichier << i << " " << j << " " << enumToString.at(map.getTile(i, j)) << endl;
			}

		fichier.close();
	}
	else
		cout << "Erreur écriture !";
}
