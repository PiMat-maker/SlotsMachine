#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "slotsMachine.h"

class State {
protected:
	SlotsMachine* Machine;
	sf::RenderWindow* Window;
	int PrizeForPreviousSpin;
	sf::RenderWindow* getWindow();
	virtual void drawSlots();
public:
	State(SlotsMachine* machine, sf::RenderWindow* window, int prizeForPreviousSpin);
	int getPrizeForPreviousSpin();
	virtual void run();
};

class StartState : public State {
public:
	StartState(SlotsMachine* machine, sf::RenderWindow* window, int prizeForPreviousSpin);
	void run();
};

class WorkState : public State {
	int Timeout;
public:
	WorkState(SlotsMachine* machine, sf::RenderWindow* window, int prizeForPreviousSpin, int timeout);
	int getTimeout();
	void run();
};

class StopState : public State {
	int ResultPrize;
public:
	StopState(SlotsMachine* machine, sf::RenderWindow* window, int prizeForPreviousSpin);
	int calculatePrize();
	void run();
};