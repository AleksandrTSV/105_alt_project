#include "LevelWithTiles.h"

LevelWithTiles::LevelWithTiles(sf::RenderWindow& window, Input& input, GameState& gameState, AudioManager& audio)
	: Scene(window, input, gameState, audio), m_alertText(m_font),
	m_pauseTitle(m_font),
	m_pauseHint(m_font),
	m_resumeLabel(m_font),
	m_menuLabel(m_font),
	m_gameOverTitle(m_font),
	m_gameOverHint(m_font)
{
	GameObject tile;
	std::vector<GameObject> tileSet;

	int num_columns = 20;
	int num_rows = 9;
	int tile_size = 18;      // Visual size of the tile
	int sheet_spacing = 1;   // Gap between tiles


	// Set GameObject size (Scaling up 4x for visibility)
	// 4 * 18 = 3 * 24 = 72 (dino size is 24).
	tile.setSize(sf::Vector2f(tile_size * 4, tile_size * 4));
	tile.setCollisionBox({ { 0,0 }, tile.getSize() });

	for (int i = 0; i < num_columns * num_rows; i++)
	{
		int row = i / num_columns;
		int col = i % num_columns;

		tile.setTextureRect({
			{(tile_size + sheet_spacing) * col, (tile_size + sheet_spacing) * row},
			{tile_size, tile_size} });
		if (col <= 4 || col >= 12) tile.setCollider(true);
		else tile.setCollider(false);
		tileSet.push_back(tile);
	}

	// Add Blank
	tile.setTextureRect({ {0, 0}, {-24, -24} }); // Empty rect for blank
	int b = tileSet.size();
	tile.setCollider(false);
	tileSet.push_back(tile);

	sf::Vector2u mapDimensions{ 40, 8 };
	std::vector<int> tileMap = {
		b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b, b, b, b  , b  , b  , b  , b  , b  , b, b, b, b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  ,
		b  , 131, b  , b  , b  , 131, b  , b  , b  , 131,  21,  22,  23, b, b, b,  21,  22,  22,  22,  22,  23, b, b, b,  21,  22,  22,  23, b  , b  , b  , b  , b  , b  , b  , b  , b  , b  , b  ,
		b  , 131, b  , b  , b  , 131, b  , 21 ,  22, 22 , 121, 122, 123, b, b, b, 121, 122, 122, 122, 122, 123, b, b, b, 121, 122, 122, 123, 22 , 22 , 23 , b  , b  , b  , b  , b  , b  , b  , b  ,
		b  , 131, b  , b  , 21 ,  22, 22 , 121, 122, 122, 121, 122, 123, b, b, b, 121, 122, 122, 122, 122, 123, b, b, b, 121, 122, 122, 123, 122, 122, 123, 22 , 22 , 22 , 22 , 22 , 22 , 22 , 23 ,
		21 ,  22, 22 , 22 , 121, 122, 122, 121, 122, 122, 121, 122, 123, b, b, b, 121, 122, 122, 122, 122, 123, b, b, b, 121, 122, 122, 123, 122, 122, 123, 122, 122, 122, 122, 122, 122, 122, 123,
		121, 122, 122, 122, 121, 122, 122, 121, 122, 122, 121, 122, 123, b, b, b, 121, 122, 122, 122, 122, 123, b, b, b, 121, 122, 122, 123, 122, 122, 123, 122, 122, 122, 122, 122, 122, 122, 123,
		121, 122, 122, 122, 121, 122, 122, 121, 122, 122, 121, 122, 123, b, b, b, 121, 122, 122, 122, 122, 123, b, b, b, 121, 122, 122, 123, 122, 122, 123, 122, 122, 122, 122, 122, 122, 122, 123,
		141, 142, 142, 142, 141, 142, 142, 141, 142, 142, 141, 142, 143, b, b, b, 141, 142, 142, 142, 142, 143, b, b, b, 141, 142, 142, 143, 142, 142, 143, 142, 142, 142, 142, 142, 142, 142, 143
	};
	

	m_tilemap.loadTexture("gfx/tilemap.png");
	m_tilemap.setTileSet(tileSet);
	m_tilemap.setTileMap(tileMap, mapDimensions);
	m_tilemap.setPosition({ 0, 100 });
	m_tilemap.buildLevel();

	tileSet.clear();

	// setup background
	tile_size = 24;
	num_columns = 8;
	num_rows = 3;
	// 24 * 9 = 216, a multiple of 72, the LCM of the player and tile size.
	tile.setSize(sf::Vector2f(tile_size * 9, tile_size * 9));

	for (int i = 0; i < num_columns * num_rows; i++)
	{
		int row = i / num_columns;
		int col = i % num_columns;

		tile.setTextureRect({
			{(tile_size + sheet_spacing) * col, (tile_size + sheet_spacing) * row},
			{tile_size, tile_size} });
		tile.setCollider(false);		// don't collide with background
		tileSet.push_back(tile);
	}

	mapDimensions = { 14,3 };
	tileMap = {
		6,6,6,6,6,6,6,6,6,6,6,6,6,6,
		14,14,14,14,14,14,14,14,14,14,14,14,14,14,
		22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22
	};
	m_bgtilemap.loadTexture("gfx/tilemap-backgrounds.png");
	m_bgtilemap.setTileSet(tileSet);
	m_bgtilemap.setTileMap(tileMap, mapDimensions);
	m_bgtilemap.setPosition({ 0, 0 });
	m_bgtilemap.buildLevel();

	// setup player 
	m_player.setInput(&m_input);
	m_player.setEdges(0, WORLD_SIZE.x);

	//m setup text
	if (!m_font.openFromFile("font/bitcount.ttf")) std::cerr << "no font found";
	m_alertText.setString("Who keeps turning\nthe wind off?");
	m_alertText.setPosition({ 50, 150});
	m_alertText.setCharacterSize(36);
	m_alertText.setFillColor(sf::Color::Black);
	m_promptTimer = PROMPT_TIME;
	if (!m_tileTexture.loadFromFile("gfx/tilemap.png")) std::cerr << "no tile image found";

	// Setup Fireballs
	for (int i = 0; i < 5; i++)
		m_fireballs.push_back(Fireball());

	// Setup Worms
	auto makeWorm = [&](float x, float y, float leftEdge, float rightEdge)
		{
			Worm w;
			w.setPosition({ x, y });
			w.setupPatrol(leftEdge, rightEdge);
			m_worms.push_back(w);
		};
	makeWorm(1300, 109, 1120, 1540);

	// Setup HeratPickups
	for (int i = 0; i < 5; i++)
		m_heartPickups.push_back(HeartPickup());

	//Setup UI for pause----------------------------------------------------
	m_pauseOverlay.setSize({ 432, 432 });
	m_pauseOverlay.setFillColor(sf::Color(0, 0, 0, 150));

	//Title "Pause"
	m_pauseTitle.setFont(m_font);
	m_pauseTitle.setString("PAUSED");
	m_pauseTitle.setCharacterSize(48);
	m_pauseTitle.setFillColor(sf::Color::White);
	m_pauseTitle.setPosition({ 130, 80 });

	//Button "Resume"
	m_resumeButton.setSize({ 216, 56 });
	m_resumeButton.setCollisionBox({ {0, 0}, {216, 56} });
	m_resumeButton.setFillColor(sf::Color(80, 80, 200, 180));

	m_resumeLabel.setFont(m_font);
	m_resumeLabel.setString("Resume");
	m_resumeLabel.setCharacterSize(24);
	m_resumeLabel.setFillColor(sf::Color::White);
	m_resumeLabel.setPosition({ 160, 193 });

	//Button "Menu"
	m_menuButton.setSize({ 216, 56 });
	m_menuButton.setCollisionBox({ {0, 0}, {216, 56} });
	m_menuButton.setFillColor(sf::Color(200, 70, 70, 180));

	m_menuLabel.setFont(m_font);
	m_menuLabel.setString("Main Menu");
	m_menuLabel.setCharacterSize(24);
	m_menuLabel.setFillColor(sf::Color::White);
	m_menuLabel.setPosition({ 145, 273 });

	//Another way to resume
	m_pauseHint.setFont(m_font);
	m_pauseHint.setString("press Escape to resume");
	m_pauseHint.setCharacterSize(16);
	m_pauseHint.setFillColor(sf::Color(255, 255, 255, 130));
	m_pauseHint.setPosition({ 120, 340 });


	// setup flags and end game pos
	m_player.setEndGamePosition({ 24, 325 });
	for (int i = 0; i < 3; i++)
	{
		Flag* new_flag = new Flag();
		new_flag->setSize({ 72,72 });
		new_flag->setPosition({72.f + (i * 288), 100.f});
		new_flag->setTexture(&m_tileTexture);
		new_flag->setup();	// ensure first frame is good.
		m_flags.push_back(new_flag);
	}

	m_lever.setPosition({ 2730, 252 });
	m_lever.setTexture(&m_tileTexture);
	m_lever.setSize({ 72,72 });
	m_lever.setUsed(false);
	m_player.setLeverPosition({ 2730, 252 });
	m_player.setAudio(&m_audio);

	// UI Game Over
	m_gameOverOverlay.setSize({ 432, 432 });
	m_gameOverOverlay.setFillColor(sf::Color(180, 0, 0, 170));

	m_gameOverTitle.setFont(m_font);
	m_gameOverTitle.setString("Game Over!");
	m_gameOverTitle.setCharacterSize(52);
	m_gameOverTitle.setFillColor(sf::Color::White);

	m_gameOverHint.setFont(m_font);
	m_gameOverHint.setString("Press Enter to return\nto the main menu");
	m_gameOverHint.setCharacterSize(22);
	m_gameOverHint.setFillColor(sf::Color(255, 255, 255, 200));
}

void LevelWithTiles::handleInput(float dt)
{
	if (m_input.isPressed(sf::Keyboard::Scancode::Escape))
	{
		m_isPaused = !m_isPaused;
		if (m_isPaused)
			m_audio.pauseAllMusic();
		else
			m_audio.resumeAllMusic();
		return;
	}

	if (m_isPaused)
	{
		sf::Vector2i worldMouse = sf::Vector2i(m_window.mapPixelToCoords(
			sf::Vector2i(m_input.getMouseX(), m_input.getMouseY())
		));

		if (m_input.isLeftMousePressed())
		{
			if (Collision::checkBoundingBox(m_resumeButton, worldMouse))
			{
				m_isPaused = false;
				m_audio.resumeAllMusic();
			}
			else if (Collision::checkBoundingBox(m_menuButton, worldMouse))
			{
				m_isPaused = false;
				m_audio.resumeAllMusic(); // onEnd() will call stopAllMusic() by itself
				m_gameState.setCurrentState(State::MENU);
			}
		}
		return;  // while pausing player can't play
	}

	if (m_isGameOver)
	{
		if (m_input.isPressed(sf::Keyboard::Scancode::Enter)) 
		{
			m_isGameOver = false;
			m_gameState.setCurrentState(State::MENU);
		}
		return;
	}

	m_player.handleInput(dt);
}

void LevelWithTiles::update(float dt)
{
	if (m_isPaused) //if paused, player can't control the dino
	{
		sf::Vector2i worldMouse = sf::Vector2i(m_window.mapPixelToCoords(
			sf::Vector2i(m_input.getMouseX(), m_input.getMouseY())
		));

		m_resumeButton.setFillColor(
			Collision::checkBoundingBox(m_resumeButton, worldMouse)
			? sf::Color(100, 100, 255, 220)
			: sf::Color(80, 80, 200, 180)
		);
		m_menuButton.setFillColor(
			Collision::checkBoundingBox(m_menuButton, worldMouse)
			? sf::Color(255, 90, 90, 220)
			: sf::Color(200, 70, 70, 180)
		);
		return;
	} 

	if (m_flagLeverPulled)
	{
		for (auto& flag : m_flags) flag->update(dt);
	}
	m_lever.update(dt);
	m_player.update(dt);

	std::vector<GameObject>& level = *m_tilemap.getLevel(); // Here are all the tiles you can interact with

	// === FIREBALLS ===
	// Shoot if the player has requested it and there is a free ball
	if (m_player.wantsToShoot())
	{
		for (auto& fb : m_fireballs)
		{
			if (!fb.isAlive())
			{
				sf::Vector2f spawnPos = m_player.getPosition()
					+ sf::Vector2f(m_player.isFacingRight() ? m_player.getSize().x : -64.f,
						m_player.getSize().y * 0.01f);
				fb.launch(spawnPos, m_player.isFacingRight());
				m_audio.playSoundbyName("fire");
				break;
			}
		}
	}
	// We update fireballs and check for collisions with tiles and worms
	for (auto& fb : m_fireballs)
	{
		if (!fb.isAlive()) continue;
		fb.update(dt);

		// Destroy fireball if it goes off the edge of the world
		if (fb.getPosition().x < 0 || fb.getPosition().x > WORLD_SIZE.x)
		{
			fb.setAlive(false);
			continue;
		}

		// Collision with tiles - fireball is being extinguished
		for (auto& t : level)
		{
			if (t.isCollider() && Collision::checkBoundingBox(fb, t))
			{
				fb.setAlive(false);
				break;
			}
		}
		if (!fb.isAlive()) continue;

		// Collision with worms
		for (auto& worm : m_worms)
		{
			if (!worm.isAlive()) continue;
			if (Collision::checkBoundingBox(fb, worm))
			{
				worm.setAlive(false);
				fb.setAlive(false);

				// 30% chance of heart drop
				if (std::rand() % 10 < 3)
				{
					for (auto& hp : m_heartPickups)
					{
						if (!hp.isAlive())
						{
							hp.spawn(worm.getPosition(), &m_tileTexture);
							break;
						}
					}
				}
				break;
			}
		}
	}

	for (auto& t : level)
	{
		if (t.isCollider() && Collision::checkBoundingBox(m_player, t))
		{
			m_player.collisionResponse(t);
		}
	}

	// === WORMS ===
	for (auto& worm : m_worms)
	{
		if (!worm.isAlive()) continue;
		worm.checkEdges(&level);
		worm.update(dt);

		// A worm colliding with tiles
		for (auto& t : level)
		{
			if (t.isCollider() && Collision::checkBoundingBox(worm, t))
				worm.collisionResponse(t);
		}

		// A worm colliding with a player
		if (!m_player.isInvincible() && Collision::checkBoundingBox(m_player, worm))
		{
			m_player.loseLife();
			m_audio.playSoundbyName("hit");
			worm.knockback(m_player.getPosition().x);
		}
	}
	// === HEART PICKUPS ===
	for (auto& hp : m_heartPickups)
	{
		if (!hp.isAlive()) continue;
		hp.update(dt);

		// Falls to the floor
		for (auto& t : level)
		{
			if (t.isCollider() && Collision::checkBoundingBox(hp, t))
				hp.collisionResponse(t);
		}

		// Picked up by the player
		if (Collision::checkBoundingBox(m_player, hp) && m_player.getLives() < 3)
		{
			m_audio.playSoundbyName("healing");
			m_player.gainLife();
			hp.setAlive(false);
		}
	}

	// === HUD ===
	m_hud.update(m_window, m_player.getLives());
	
	// show text if player has dropped very low down
	if (m_promptTimer > 0)
		m_promptTimer -= dt;
	else if (m_alertText.getString() != "")
	{
		// turn off prompt
		m_alertText.setString("");
	}
	else if (m_player.getPosition().y > WORLD_SIZE.y)
	{
		m_alertText.setCharacterSize(24);
		m_alertText.setPosition(m_window.getView().getCenter());
		m_alertText.setString("Press R to reset");
	}
	// show text if the player in lever range
	else if (m_player.inLeverRange())
	{
		m_alertText.setCharacterSize(24);
		m_alertText.setPosition(m_window.getView().getCenter() + sf::Vector2f(-100.f, -150.f));
		m_promptTimer = PROMPT_TIME;
		if (!m_flagLeverPulled)
			m_alertText.setString("Press F to fix\nthe wind");
		else
			m_alertText.setString("Better check\nthose flags");
	}
	else if (m_player.inEndRange())
	{
		m_alertText.setCharacterSize(24);
		m_alertText.setPosition(m_window.getView().getCenter() + sf::Vector2f(-100.f, -150.f));
		m_promptTimer = PROMPT_TIME;
		if (m_flagLeverPulled)
			m_alertText.setString("Good job! Press\nF to end the day");
	}

	if (m_player.getLeverPulled())
	{
		if (!m_flagLeverPulled) m_promptTimer = 0;
		m_flagLeverPulled = true;
		m_lever.setUsed(true);
	}
	else
	{
		m_lever.setUsed(false);
	}
	if (m_player.getGameEndTriggered())
	{		
		m_gameState.setCurrentState(State::MENU);
	}


	// reset if fallen too far
	if (m_player.getPosition().y > 1200)
	{
		m_player.reset();
		m_player.loseLife();
		m_flagLeverPulled = false;
		m_lever.setUsed(false);
		m_audio.stopAllSounds();
		m_audio.playSoundbyName("death");
	}

	if (m_player.getLives() <= 0)
	{
		m_isGameOver = true;
		m_audio.stopAllMusic();	
		return;
	}

	// camera follows player, bounded.
	updateCameraAndBackground();

}

void LevelWithTiles::updateCameraAndBackground()
{
	auto view = m_window.getView();
	sf::Vector2f playerCenter = m_player.getPosition() + m_player.getSize() * 0.5f;

	float halfViewWidth = VIEW_SIZE.x / 2.0f;
	float halfViewHeight = VIEW_SIZE.y / 2.0f;

	float lookahead = 0.f;
	if (m_player.getVelocity().x > 0.5f)
		lookahead = CAM_LOOKAHEAD;
	else if (m_player.getVelocity().x < -0.5f)
		lookahead = -CAM_LOOKAHEAD;

	m_cameraTarget.x = playerCenter.x + lookahead;
	m_cameraTarget.y = playerCenter.y;

	m_cameraTarget.x = std::clamp(m_cameraTarget.x, halfViewWidth, (float)WORLD_SIZE.x - halfViewWidth);
	m_cameraTarget.y = std::clamp(m_cameraTarget.y, halfViewHeight, (float)WORLD_SIZE.y - halfViewHeight);

	// Lerp
	sf::Vector2f currentCenter = view.getCenter();
	sf::Vector2f newCenter = currentCenter + (m_cameraTarget - currentCenter) * CAM_LERP * (1.f / 60.f);

	view.setCenter(newCenter);
	m_window.setView(view);

	m_bgtilemap.setPosition({ newCenter.x - halfViewWidth, 0 });
}

void LevelWithTiles::render()
{
	beginDraw();
	m_bgtilemap.render(m_window);
	m_tilemap.render(m_window);
	m_window.draw(m_lever);
	for (auto& flag : m_flags) m_window.draw(*flag);
	m_window.draw(m_player);
	m_window.draw(m_alertText);

	for (auto& worm : m_worms)
		if (worm.isAlive()) m_window.draw(worm);
	for (auto& fb : m_fireballs)
		if (fb.isAlive()) m_window.draw(fb);
	for (auto& hp : m_heartPickups)
		if (hp.isAlive()) m_window.draw(hp);
	m_hud.render(m_window);

	if (m_isPaused) drawPauseUI();
	if (m_isGameOver) drawGameOverUI();

	endDraw();
}

void LevelWithTiles::drawPauseUI() 
{
	sf::Vector2f center = m_window.getView().getCenter();

	m_pauseOverlay.setPosition(center - sf::Vector2f(216, 216));
	m_pauseTitle.setPosition(center + sf::Vector2f(-95, -140));
	m_resumeButton.setPosition(center + sf::Vector2f(-108, -30));
	m_resumeLabel.setPosition(center + sf::Vector2f(-50, -17));
	m_menuButton.setPosition(center + sf::Vector2f(-108, 50));
	m_menuLabel.setPosition(center + sf::Vector2f(-60, 63));
	m_pauseHint.setPosition(center + sf::Vector2f(-100, 120));


	m_window.draw(m_pauseOverlay);
	m_window.draw(m_resumeButton);
	m_window.draw(m_resumeLabel);
	m_window.draw(m_menuButton);
	m_window.draw(m_menuLabel);
	m_window.draw(m_pauseTitle);
	m_window.draw(m_pauseHint);
}

void LevelWithTiles::drawGameOverUI() 
{
	sf::Vector2f center = m_window.getView().getCenter();

	m_gameOverOverlay.setPosition(center - sf::Vector2f(216, 216));
	m_gameOverTitle.setPosition(center + sf::Vector2f(-130, -80));
	m_gameOverHint.setPosition(center + sf::Vector2f(-100, 20));

	m_window.draw(m_gameOverOverlay);
	m_window.draw(m_gameOverTitle);
	m_window.draw(m_gameOverHint);

}

void LevelWithTiles::onBegin()
{
	m_audio.playMusicbyName("bgm1");

	for (auto& worm : m_worms) worm.setAlive(true);
	for (auto& fb : m_fireballs)  fb.setAlive(false);
	for (auto& hp : m_heartPickups) hp.setAlive(false);
}

void LevelWithTiles::onEnd()
{
	// reset player and level state
	m_player.reset();
	m_flagLeverPulled = false;
	// reset alert text
	m_alertText.setString("Who keeps turning\nthe wind off?");
	m_alertText.setPosition({ 50, 150 });
	m_alertText.setCharacterSize(36);
	m_alertText.setFillColor(sf::Color::Black);
	m_promptTimer = PROMPT_TIME;
	// sfx
	m_audio.stopAllSounds();
	m_audio.stopAllMusic();
	// Game over
	m_isGameOver = false;
	m_player.setLives(3);
}
