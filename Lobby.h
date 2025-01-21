#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace sf;

namespace game {
	
	class Lobby {

		float menu_X;
		float menu_Y;
		int menu_Step;
		int max_menu;
		int size_font;
		int mainMenuSelected;
		int index;
		Font font;
		Text* mainMenu;

		Color menu_text_color = Color::White;
		Color chose_text_color = Color::Yellow;
		Color border_color = Color::Black;

		void setInitText(Text& text, String str, float xpos, float ypos);

		RenderWindow& mywindow;

	public:

		Lobby(RenderWindow& win, float menux, float menuy, String name[], int index, int sizeFont = 60, int step = 80);

		~Lobby() {
			delete[] mainMenu;
			mainMenu = nullptr; // Nullify pointer to avoid dangling references
			std::cout << "Deleted mainMenu array.\n";
		}

		void draw();
		void MoveUp();
		void MoveDown();
		void setColorTextMenu(Color menuColor, Color ChosColor, Color BordColor);
		void AlignMenu(int posx);
		int getSelectedMenuNumber() {
			return mainMenuSelected;
		}
	};
}