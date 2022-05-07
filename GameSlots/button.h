#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Button {
public:
	Button(){}
	Button(std::string t, sf::Vector2f size, int charSize, sf::Color bgColor, sf::Color textColor) {
		Text.setString(t);
		Text.setFillColor(textColor);
		Text.setCharacterSize(charSize);

		ButtonShape.setSize(size);
		ButtonShape.setFillColor(bgColor);
	}
	void setFont(sf::Font &font) {
		Text.setFont(font);
	}
	void setBackColor(sf::Color color) {
		ButtonShape.setFillColor(color);
	}
	void setTextColor(sf::Color color) {
		Text.setFillColor(color);
	}
	void setPosition(sf::Vector2f pos) {
		ButtonShape.setPosition(pos);
		float xPos = (pos.x + ButtonShape.getGlobalBounds().width / 3) - (Text.getGlobalBounds().width / 2);
		float yPos = (pos.y + ButtonShape.getGlobalBounds().height / 3) - (Text.getGlobalBounds().height / 2);
		Text.setPosition(xPos, yPos);
	}
	void drawTo(sf::RenderWindow &window) {
		window.draw(ButtonShape);
		window.draw(Text);
	}
	bool isMouseOver(sf::RenderWindow &window) {
		float mouseX = sf::Mouse::getPosition(window).x;
		float mouseY = sf::Mouse::getPosition(window).y;

		float buttonPosX = ButtonShape.getPosition().x;
		float buttonPosY = ButtonShape.getPosition().y;

		float buttonPosWidth = ButtonShape.getPosition().x + ButtonShape.getLocalBounds().width;
		float buttonPosHeight = ButtonShape.getPosition().y + ButtonShape.getLocalBounds().height;

		if (mouseX < buttonPosWidth && mouseX > buttonPosX && mouseY < buttonPosHeight && mouseY > buttonPosY) {
			return true;
		}

		return false;
	}
private:
	sf::RectangleShape ButtonShape;
	sf::Text Text;
};