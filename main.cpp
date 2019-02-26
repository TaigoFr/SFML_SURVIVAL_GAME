#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "Global.h"

struct mywindow {
	sf::RenderWindow window;
	MyShape cursor;
	MyShape ground;
	MyShape dollarSign;
	sf::Text text;
	sf::Font font;
	sf::SoundBuffer buffer;
	sf::Sound bullet_sound;
	sf::Sound numbers;
	sf::Sound start;
};

bool GameLoop(mywindow &w);
bool GameOver(mywindow &w);
static void DisplayText(std::string str, int number, unsigned characterSize, sf::Color color, float positionX, float positionY, mywindow &w);
void sleep(sf::Clock &clock, float wait);


void setUpWindow(mywindow &w) {
	w.window.create(sf::VideoMode((unsigned)screenWidth, (unsigned)screenHeight), "StickMan Fight");
	w.window.clear(sf::Color::Black);
	w.window.setMouseCursorVisible(false);
	w.window.setPosition(sf::Vector2i(0, 0));

	w.cursor.setFile("cursor.png", sW*0.08f, sH*0.08f);
	w.cursor.setOrigin(0,0);
	w.ground.setFile("ground_cut.png", sW*0.5f, sH*0.5f);
	w.ground.setPosition(screenWidth / 2.f, screenHeight / 2.f);
	w.dollarSign.setFile("dollarSign.png", sW*0.09f, sH*0.09f);
	w.dollarSign.setPosition(sW*15, sH*62);

	w.font.loadFromFile("5.ttf");
	w.text.setFont(w.font);
}

int main(){
	
	mywindow w;
	setUpWindow(w);

	while(GameOver(w) && GameLoop(w));
	//while(GameLoop(w) && GameOver(w));
	
	return 0;
}


bool GameLoop(mywindow &w) {
	w.buffer.loadFromFile("bulletsound3.wav");
	w.bullet_sound.setBuffer(w.buffer);
	w.bullet_sound.setVolume(5);

	Player player(sW*300, sH*300);

	int bot_number = 0;

	Bot bots[max_bots];

	float frame_count_shot = player.getPeriodD();
	float frame_count_bot = Bot::getPeriodD();

	sf::Clock clock;
	sf::Event event;

	/*Button button(80, 50, sf::Color::Black, 100, 30);
	button.setText("Damage", sf::Color::Red, 15, "5.ttf");
	button.setSubText(200, sf::Color::Red, 10);*/

	const int buttons_number = 4;
	Button button[buttons_number];
	std::string texts[buttons_number] = { "Damage", "BPS", "Regenerate", "Armor" };
	//int initial_price[buttons_number] = { (int)(10*Bot::getHealth0()), (int)(10 * Bot::getHealth0()), 2*(int)(Figure::getMaxHealth() / Bot::getDamage0()), (int)(10 * Bot::getHealth0()) };
	int (*func[buttons_number])(Player&, int) = { Player::increaseDamage, Player::increaseBPS, Player::Regenerate, Player::increaseArmor };
	float button_Width = sW*94;

	for (int i = 0; i < buttons_number; i++) {

		button[i].setUp(button_Width, sH*40.f, sf::Color::Black, (float)(sW*350 + (button_Width + sW*30) * i), sH*30.f);
		button[i].setText(texts[i], sf::Color::Red, (int)(sH*15), "5.ttf");
		button[i].setSubText(200, sf::Color::Red, (int)(sH*10));
		button[i].setFunction(func[i]);
	}

	bool mouse_button_clicked = false;

	bool game_pause = false;

	bool space_released = false;

	while (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))) {

		clock.restart();
		w.window.pollEvent(event);
		if (space_released && (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))) {
			game_pause = !game_pause;
			space_released = false;
		}
		if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Space)) space_released = true;

		if (!game_pause) {
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && (player.getX() >= (player.getSize().x / 2) + boundary_x))				player.move(-1., 0.);
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && (player.getX() <= screenWidth - player.getSize().x / 2 - boundary_x))	player.move(1., 0.);
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && (player.getY() >= (player.getSize().y / 2) + boundary_y))				player.move(0., -1.);
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && (player.getY() <= screenHeight - player.getSize().y / 2 - boundary_x))	player.move(0., 1.);

			for (int i = 0; i < max_bots; i++)
				if (player.collide(bots[i])) return true;  //after draws not to show a black screen when player dies before returning to main()

			for (int i = 0; i < max_bots; i++)
				bots[i].move(player.getX(), player.getY());

			player.move_shots();


			if (frame_count_bot >= Bot::getPeriodD() / delay) {
				bots[bot_number++].setUp();
				frame_count_bot = 0;

				if (bot_number == max_bots) bot_number = 0;
			}
			frame_count_bot++;

			if ((sf::Mouse::isButtonPressed(sf::Mouse::Left)) && (frame_count_shot >= player.getPeriodD() / delay)) {
				player.setUpShot((float)sf::Mouse::getPosition(w.window).x, (float)sf::Mouse::getPosition(w.window).y, player.getX(), player.getY());
				w.bullet_sound.play();
				frame_count_shot = 0;
			}

			frame_count_shot++;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			mouse_button_clicked = true;

		if (upgrade) {
			w.window.pollEvent(event);
			if (mouse_button_clicked && (event.type == sf::Event::MouseButtonReleased) && (event.mouseButton.button == sf::Mouse::Left)) {
				mouse_button_clicked = false;
				int i = isClicked(button, buttons_number, sf::Mouse::getPosition(w.window));
				if (i >= 0)	button[i].Upgrade(player);
			}
		}

		w.window.clear(sf::Color::Black);


		w.window.draw(w.ground);

		player.draw(w.window);
		player.drawShots(w.window);

		int digitsS = player.getScore() ? 1 + (int)log10(player.getScore()) : 0;
		int digitsM = player.getMoney() ? 1 + (int)log10(player.getMoney()) : 0;
		DisplayText("", player.getScore(), (int)(sH*35), sf::Color::Black, sW*(110.f + 10.f*digitsS), sH*10.f, w);
		DisplayText("Score:", 0, (int)(sH*30), sf::Color::Black, sW*50.f, sH*10.f, w);
		DisplayText("", player.getMoney(), (int)(sH*20), sf::Color::Yellow, sW*(35.f + 5.f*digitsM), sH*54.f, w);

		if (upgrade)
			for (int i = 0; i < buttons_number; i++) button[i].draw(w.window);

		for (int i = 0; i < max_bots; i++) {
			bots[i].draw(w.window);
		}

		w.cursor.setPosition((float)sf::Mouse::getPosition(w.window).x, (float)sf::Mouse::getPosition(w.window).y);
		w.window.draw(w.cursor);

		w.window.draw(w.dollarSign);

		if (game_pause) DisplayText("PAUSE", 0, (int)(sH*60), sf::Color(0, 0, 0, 150), screenWidth / 2, screenHeight / 2, w);


		w.window.display();

		sleep(clock, delay);

		w.window.pollEvent(event);
		if (event.type == sf::Event::Closed)
			break;
	}

	w.window.close();
	return false;
} 


bool GameOver(mywindow &w) {
	static bool start = true;
	static std::string text = "Press SPACE to start or ESC to quit to MENU";
	
	Bot::setPeriodD(Bot::getPeriod0());

	Shot::setDamageD(Shot::getDamage0());
	Bot::setDamageD(Bot::getDamage0());

	Shot::setHealthD(Shot::getHealth0());
	Bot::setHealthD(Bot::getHealth0());

	if(start) w.window.draw(w.ground);

	if(!start) DisplayText("GAME OVER", 0, (int)(sH*40), sf::Color::Blue, (float)(screenWidth / 2), (float)(screenHeight / 4), w);
	DisplayText(text, 0, (int)(sH*24), sf::Color::Black, (float)(screenWidth / 2), (float)(screenHeight / 3) + sH*20, w);
	DisplayText("Use SPACE to PAUSE during the game", 0, (int)(sH*24), sf::Color::Black, (float)(screenWidth / 2), (float)(screenHeight / 3 + sH*70), w);
	w.window.display();

	sf::Event event;

	while (1) {
		w.window.pollEvent(event);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || (event.type == sf::Event::Closed && sf::Mouse::isButtonPressed(sf::Mouse::Left))) {//event closed is being triggered after game over
			w.window.close();
			return false;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			break;
		}
	}
	w.window.clear(sf::Color::Black);

	int size_max = (int)(sH*2100);
	float frame_step = 40.f; //ms
	float frame_weight = 1000.f; //ms
	float size_step = frame_step / frame_weight * size_max;
	sf::Clock clock;

	MyShape number_i[3];
	number_i[0].setFile("1.png");
	number_i[1].setFile("2.png");
	number_i[2].setFile("3.png");

	w.buffer.loadFromFile("countdown.wav");
	w.numbers.setBuffer(w.buffer);

	for (int number = 2; number >= 0; number--) {
		w.numbers.play();
		for (float size = 0; size <size_max; size+= size_step) {
			clock.restart();
			w.window.clear(sf::Color::Black);
			w.window.draw(w.ground);
			number_i[number].setSize(size, size);
			number_i[number].setOrigin(sf::Vector2f(size / 2, size / 2));
			number_i[number].setPosition(sf::Vector2f(screenWidth/2, screenHeight/2));
			w.window.draw(number_i[number]);
			//DisplayText("3", number, size, sf::Color::Blue, (float)(screenWidth / 2.f), (float)(screenHeight / 2.f), w);
			w.window.display();
			sleep(clock, frame_step);
		}
	}

	w.buffer.loadFromFile("finalcountdown.ogg");
	w.start.setBuffer(w.buffer);
	w.start.play();

	if (start) {
		start = false;
		text = "Press SPACE to restart or ESC to quit to MENU";
	}

	sf::sleep(sf::milliseconds(200));
	return  true;
}

static void DisplayText(std::string str, int number, unsigned characterSize, sf::Color color, float positionX, float positionY, mywindow &w) {

	/*if (str == "") 
		w.text.setString(std::to_string(number));
	else 
		w.text.setString(str);*/

	w.text.setString((str == "" )? std::to_string(number):str);

	w.text.setCharacterSize(characterSize);
	w.text.setOrigin(w.text.getGlobalBounds().width / 2, w.text.getGlobalBounds().height / 2);
	w.text.setFillColor(color);
	w.text.setPosition(positionX, positionY);

	w.window.draw(w.text);
}

void sleep(sf::Clock &clock, float wait) {

	if (wait - clock.getElapsedTime().asMilliseconds() <= 0) {
		if (print)
			std::cout << "WARNING: INCREASE DELAY TO MORE THAN " << clock.getElapsedTime().asMilliseconds() << " ms" << std::endl;
	}
	else
		sf::sleep(sf::milliseconds((sf::Int32)wait - clock.getElapsedTime().asMilliseconds()));
	
}