#pragma once
#include "Chessboard.h"
#include <string>
#include <iostream>
#include <fstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


class Game {
private:

	void Setup(const std::string title, const sf::Vector2u& size);
	void Create();
	void Destroy();

	sf::RenderWindow m_window;
	sf::Vector2u m_windowSize;
	std::string m_windowTitle;
	bool m_isDone;

	PieceColor playerTurn;

	bool Active;
	sf::Vector2i ActiveCoord;

	bool promotion;

	Chessboard m_chessboard;
public:
	int cellSize = 84;


	//Constructors
	Game();
	Game(const std::string& title, const sf::Vector2u& size);
	~Game();

	//Main functions
	void HandleInput();
	void Update();
	void Render();

	void BeginDraw();
	void EndDraw();


	//Get
	bool IsDone();
	sf::RenderWindow* GetRenderWindow();
	sf::Vector2u GetWindowSize();


	//Others
	int GetCellNumber(sf::RenderWindow& l_window);
	sf::Vector2i GetCellCoor();
	void OnClickTest();
	PieceID getPromotionPiece();
	void PromotionHandler(PieceColor color, sf::Vector2i CurrentCoordinates);

	//void Draw(sf::Drawable& l_drawable);

	//Window* GetWindow();

};