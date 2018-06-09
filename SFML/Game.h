#pragma once
#include "Chessboard.h"
#include "AudioManager.h"
#include "MusicManager.h"
#include <string>
#include <iostream>
#include <fstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class Game {
private:

	void Setup(const std::string title, const sf::Vector2u& size);
	void Create();
	void Destroy();
	void SetupSounds();

	sf::RenderWindow m_window;
	sf::Vector2u m_windowSize;
	std::string m_windowTitle;
	bool m_isDone;

	//audio
	AudioManager audio;
	MusicManager music;

	sf::Font font;
	sf::Text timerWhite;
	sf::Text timerBlack;
	float timerW;
	float timerB;
	sf::Time sub;
	sf::Clock clock;

	//windows
	bool main;
	bool chessboard;
	bool after;


	PieceColor playerTurn;

	bool Active;
	sf::Vector2i ActiveCoord;

	bool promotion;
	sf::Vector2i PromotionCoordinates;

	bool mate;

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
	PieceID getPromotionPiece(sf::Vector2i mousePos);
	void PromotionHandler(PieceColor color, sf::Vector2i TempCoordinates, sf::Vector2i CurrentCoordinates);
	void DisplayTime();
	//void setTime(int t1, int t2);
	void changeTurnTime();
	void updateTime();

};