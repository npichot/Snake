#include "MainTool.h"
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
		saveMap();
	return true;
}

void MainTool::saveMap()
{
	RenderWindow saveWindow(VideoMode(400, 100, 32), "Save Map");
	while (saveWindow.isOpen())
	{
		saveWindow.clear(Color(200,200,200,255));
		buildTheWindow(saveWindow);
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
