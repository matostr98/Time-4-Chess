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
	if (temp.loadFromFile("wP.png")) {
		TextureMap["wP"]=temp;
	} else std::cout << "why?\n";

	if (temp.loadFromFile("wR.png"))
		TextureMap["wR"]=temp; else std::cout << "why?\n";

	if (temp.loadFromFile("wKn.png"))
		TextureMap["wKn"]=temp; else std::cout << "why?\n";

	if (temp.loadFromFile("wB.png"))
		TextureMap["wB"]=temp; else std::cout << "why?\n";

	if (temp.loadFromFile("wQ.png"))
		TextureMap["wQ"]=temp; else std::cout << "why?\n";

	if (temp.loadFromFile("wK.png"))
		TextureMap["wK"]=temp; else std::cout << "why?\n";
	
	//black
	if (temp.loadFromFile("bP.png"))
		TextureMap["bP"]=temp; else std::cout << "why?\n";

	if (temp.loadFromFile("bR.png"))
		TextureMap["bR"]=temp; else std::cout << "why?\n";

	if (temp.loadFromFile("bKn.png"))
		TextureMap["bKn"]=temp; else std::cout << "why?\n";

	if (temp.loadFromFile("bB.png"))
		TextureMap["bB"]=temp; else std::cout << "why?\n";

	if (temp.loadFromFile("bQ.png"))
		TextureMap["bQ"]=temp; else std::cout << "why?\n";

	if (temp.loadFromFile("bK.png"))
		TextureMap["bK"]=temp; else std::cout << "why?\n";

	//other
	if (temp.loadFromFile("Pionek.png"))
		TextureMap["blue"] = temp; else std::cout << "why?\n";

	if (temp.loadFromFile("high.png"))
		TextureMap["green"] = temp; else std::cout << "why?\n";

	if (temp.loadFromFile("capt.png"))
		TextureMap["red"] = temp; else std::cout << "why?\n";



	if (t_background.loadFromFile("Chessboard.png"))
		background.setTexture(t_background); else std::cout << "why?\n";

	//if (b_texture.loadFromFile("Pionek.png"))
	//	blue.setTexture(b_texture); else std::cout << "why?\n";

	//if (g_texture.loadFromFile("high.png"))
	//	green.setTexture(g_texture); else std::cout << "why?\n";

	//if (r_texture.loadFromFile("capt.png"))
	//	red.setTexture(r_texture); else std::cout << "why?\n";
}

Chessboard::Chessboard() {
	Sprites();
	Initialize();
}
Chessboard::~Chessboard() {}

void Chessboard::Move(sf::Vector2i ActiveCoord, sf::Vector2i CurrentCoord){

}

BoardStatus Chessboard::getBoardStatus(sf::Vector2i coor) {
	return Board[coor.x][coor.y].status;
}

void Chessboard::MakeActiveSprite(sf::Vector2i coord) {
	sf::Sprite temp;
	temp.setTexture(TextureMap["blue"]);

	temp.setPosition(23 + coord.x * 84, 23 + coord.y * 84);
	Board[coord.x][coord.y].rect = temp;
}

void Chessboard::UnmakeActiveSprite(sf::Vector2i coord) {
	sf::Sprite temp;
	temp.setTexture(TextureMap["wP"]);


	temp.setPosition(23 + coord.x * 84, 23 + coord.y * 84);
	Board[coord.x][coord.y].rect = temp;
}

void Chessboard::Initialize() {
	//initialize board status


	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 2; j++) {
			//gdzies tu pojawil sie blad przy wychodzeniu z aplikacji
			Pawn p(PieceColor::Black, {i, j});
			BlackPiecesSet.emplace_back(&p);
			Board[i][j].piece = std::make_shared<Pawn>(p); //ciekawe czy dobrze dziala
			Board[i][j].status = BoardStatus::Occupied;
			sf::Sprite temp;
			temp.setTexture(TextureMap[Board[i][j].piece->getSpriteName()]);
			temp.setPosition(23 + i * 84, 23 + j * 84);
			Board[i][j].rect = temp;
			


		}
		for (int j = 2; j < 6; j++) {
			Board[i][j].status = BoardStatus::Empty;
			Board[i][j].piece = nullptr;
		}
		for (int j = 6; j < 8; j++) {
			Pawn p(PieceColor::White, { i, j });
			BlackPiecesSet.emplace_back(&p);
			Board[i][j].piece = std::make_shared<Pawn>(p); //ciekawe czy dobrze dziala
			Board[i][j].status = BoardStatus::Occupied;
			sf::Sprite temp;
			temp.setTexture(TextureMap[Board[i][j].piece->getSpriteName()]);
			temp.setPosition(23 + i * 84, 23 + j * 84);
			Board[i][j].rect = temp;
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