#include "Lobby.h"
#include <iostream>

void game::Lobby::setInitText(Text& text, String str, float xpos, float ypos)
{
	std::cout << "Initializing Text: " << str.toAnsiString() << " at (" << xpos << ", " << ypos << ")\n";
	text.setFont(font);
	text.setFillColor(menu_text_color);
	text.setString(str);
	text.setCharacterSize(size_font);
	text.setPosition(xpos, ypos);
	text.setOutlineThickness(3);
	text.setOutlineColor(border_color);
}

game::Lobby::Lobby(RenderWindow& win, float menux, float menuy, String name[], int index, int sizeFont, int step)
	:mywindow(win), menu_X(menux), menu_Y(menuy), size_font(sizeFont),menu_Step(step)
{
	if (!font.loadFromFile("fonts/Oswald-Regular.ttf")) exit(32);
	max_menu = index;
	mainMenu = new sf::Text[max_menu];

	std::cout << "Initializing Lobby with " << max_menu << " menu items.\n";

	for (int i = 0, ypos = menu_Y; i < max_menu; i++, ypos += menu_Step)
	{
		setInitText(mainMenu[i], name[i], menu_X, ypos);
		std::cout << "Menu item " << i << " initialized: " << name[i].toAnsiString() << "\n";
	}
	mainMenuSelected = 0;
	mainMenu[mainMenuSelected].setFillColor(sf::Color::Yellow);
}

void game::Lobby::draw()
{
	for (int i = 0; i < max_menu; i++)
		mywindow.draw(mainMenu[i]);
}

void game::Lobby::MoveUp() {
	if (max_menu <= 0) {
		std::cerr << "Error: No menu items initialized!\n"; // Handle edge case
		return;
	}

	// Reset the color of the currently selected item
	mainMenu[mainMenuSelected].setFillColor(menu_text_color);

	// Update the selected menu index
	mainMenuSelected = (mainMenuSelected - 1 + max_menu) % max_menu; // Circular decrement

	// Highlight the new selected item
	mainMenu[mainMenuSelected].setFillColor(chose_text_color);

	// Debug output
	std::cout << "MoveUp called: New menu index is " << mainMenuSelected << "\n";
}

void game::Lobby::MoveDown() {
	if (max_menu <= 0) {
		std::cerr << "Error: No menu items initialized!\n"; // Handle edge case
		return;
	}

	// Reset the color of the currently selected item
	mainMenu[mainMenuSelected].setFillColor(menu_text_color);

	// Update the selected menu index
	mainMenuSelected = (mainMenuSelected + 1) % max_menu; // Circular increment

	// Highlight the new selected item
	mainMenu[mainMenuSelected].setFillColor(chose_text_color);

	// Debug output
	std::cout << "MoveDown called: New menu index is " << mainMenuSelected << "\n";
}

void game::Lobby::setColorTextMenu(Color menuColor, Color ChosColor, Color BordColor)
{
	menu_text_color = menuColor;
	chose_text_color = ChosColor;
	border_color = BordColor;

	for (int i = 0; i < max_menu; i++) {
		mainMenu[i].setFillColor(menu_text_color);
		mainMenu[i].setOutlineColor(border_color);
	}

	mainMenu[mainMenuSelected].setFillColor(chose_text_color);
}

void game::Lobby::AlignMenu(int posx)
{
	float nullx = 0;

	for (int i = 0; i < max_menu; i++) {
		switch (posx)
		{
		case 0:
			nullx = 0;
			break;
		case 1:
			nullx = mainMenu[i].getLocalBounds().width;
			break;
		case 2:
			nullx = mainMenu[i].getLocalBounds().width / 2;
			break;
		}

		mainMenu[i].setPosition(mainMenu[i].getPosition().x - nullx, mainMenu[i].getPosition().y);
	}
}
