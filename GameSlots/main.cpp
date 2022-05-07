#include <SFML/Graphics.hpp>
#include <iostream>
#include <typeinfo>
#include "slotsMachine.h"
#include "states.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1240, 800), "Slots Machine");

	std::string slotImageFileName = "./../../GameSlots/Images/Slots.png";
	int maxSlotSpeedInPixelsPerFrame = 230;
	int numberOfSlots = 5;
	int lengthSlotMachineInPixels = 800;
	int widthSlotMachineInPixels = 500;
	int numberOfUniqueSlotSymbols = 5;
	int numberOfVisibleSymbols = 3;
	SlotsMachine machine(slotImageFileName, numberOfSlots, lengthSlotMachineInPixels,
		widthSlotMachineInPixels, numberOfUniqueSlotSymbols, maxSlotSpeedInPixelsPerFrame, numberOfVisibleSymbols);
	State* state = &StartState(&machine, &window, 0);

	const int START = 1, WORK = 2, STOP = 3;
	std::map <std::string, int> mapping;
	mapping["class StartState"] = START;
	mapping["class WorkState"] = WORK;
	mapping["class StopState"] = STOP;


	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		state->run();
		std::string classStateName = typeid(*state).name();
		int prize = state->getPrizeForPreviousSpin();

		switch (mapping[classStateName])
		{
		case START: 
			state = &WorkState(&machine, &window, 0, 3000);
			break;
		case WORK:
			state = &StopState(&machine, &window, 0);
			break;
		case STOP:
			state = &StartState(&machine, &window, prize);
			break;
		default:
			std::cout << "State is undefined" << std::endl;
			break;
		}

	}

	return 0;
}