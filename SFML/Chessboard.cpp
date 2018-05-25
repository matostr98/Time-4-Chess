#include "Chessboard.h"


void Chessboard::Sprites() {
	

	/*if (b_texture.loadFromFile("Pionek.png"))
		blue.setTexture(b_texture); else std::cout << "why?\n";

	if (g_texture.loadFromFile("high.png"))
		green.setTexture(g_texture); else std::cout << "why?\n";

	if (r_texture.loadFromFile("capt.png"))
		red.setTexture(r_texture); else std::cout << "why?\n";*/

	sf::Texture temp;
	//white
	if (temp.loadFromFile("wP.png"))
		SpriteMap["wP"].setTexture(temp); else std::cout << "why?\n";

	if (temp.loadFromFile("wR.png"))
		SpriteMap["wR"].setTexture(temp); else std::cout << "why?\n";

	if (temp.loadFromFile("wKn.png"))
		SpriteMap["wKn"].setTexture(temp); else std::cout << "why?\n";

	if (temp.loadFromFile("wB.png"))
		SpriteMap["wB"].setTexture(temp); else std::cout << "why?\n";

	if (temp.loadFromFile("wQ.png"))
		SpriteMap["wQ"].setTexture(temp); else std::cout << "why?\n";

	if (temp.loadFromFile("wK.png"))
		SpriteMap["wK"].setTexture(temp); else std::cout << "why?\n";
	
	//black
	if (temp.loadFromFile("bP.png"))
		SpriteMap["bP"].setTexture(temp); else std::cout << "why?\n";

	if (temp.loadFromFile("bR.png"))
		SpriteMap["bR"].setTexture(temp); else std::cout << "why?\n";

	if (temp.loadFromFile("bKn.png"))
		SpriteMap["bKn"].setTexture(temp); else std::cout << "why?\n";

	if (temp.loadFromFile("bB.png"))
		SpriteMap["bB"].setTexture(temp); else std::cout << "why?\n";

	if (temp.loadFromFile("bQ.png"))
		SpriteMap["bQ"].setTexture(temp); else std::cout << "why?\n";

	if (temp.loadFromFile("bK.png"))
		SpriteMap["bK"].setTexture(temp); else std::cout << "why?\n";

	//other
	if (t_background.loadFromFile("Chessboard.png"))
		background.setTexture(t_background); else std::cout << "why?\n";

	if (b_texture.loadFromFile("Pionek.png"))
		blue.setTexture(b_texture); else std::cout << "why?\n";

	if (g_texture.loadFromFile("high.png"))
		green.setTexture(g_texture); else std::cout << "why?\n";

	if (r_texture.loadFromFile("capt.png"))
		red.setTexture(r_texture); else std::cout << "why?\n";
}

Chessboard::Chessboard() {
	Sprites();
	Initialize();
}
Chessboard::~Chessboard() {}

BoardStatus Chessboard::getBoardStatus(sf::Vector2i coor) {
	return Board[coor.x][coor.y].status;
}

void Chessboard::MakeActiveSprite(sf::Vector2i coord) {
	green.setPosition(23 + coord.x * 84, 23 + coord.y * 84);
	Board[coord.x][coord.y].rect = green;
}

void Chessboard::UnmakeActiveSprite(sf::Vector2i coord) {
	blue.setPosition(23 + coord.x * 84, 23 + coord.y * 84);
	Board[coord.x][coord.y].rect = blue;
}

void Chessboard::Initialize() {
	//initialize board status


	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 2; j++) {
			Board[i][j].status = BoardStatus::Occupied;
			blue.setPosition(23 + i * 84, 23 + j * 84);
			Board[i][j].rect = blue;

		}
		for (int j = 2; j < 6; j++) {
			Board[i][j].status = BoardStatus::Empty;
			Board[i][j].piece = nullptr;
		}
		for (int j = 6; j < 8; j++) {
			Board[i][j].status = BoardStatus::Occupied;
			blue.setPosition(23 + i * 84, 23 + j * 84);
			Board[i][j].rect = blue;
		}
	}
}

void Chessboard::Render(sf::RenderWindow & l_window) {

	l_window.draw(background);
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (Board[i][j].status != BoardStatus::Empty)
				l_window.draw(Board[i][j].rect);
		}
	}

}