#include "states.h"
#include "button.h"

State::State(SlotsMachine* machine, sf::RenderWindow* window, int prizeForPreviousSpin) {
	Machine = machine;
	Window = window;
	PrizeForPreviousSpin = prizeForPreviousSpin;
}
int State::getPrizeForPreviousSpin() {
	return PrizeForPreviousSpin;
}
void State::run() {
	std::cout << "This is abstract state" << std::endl;
}
void State::drawSlots() {
	SlotsMachine* machine = Machine;
	std::vector<Slot*> slots = Machine->getSlots();
	for (size_t i = 0; i < slots.size(); ++i) {
		sf::Sprite slotSprite = slots[i]->getVisibleSlotPart();
		Window->draw(slotSprite);
	}
}
sf::RenderWindow* State::getWindow() {
	return Window;
}

StartState::StartState(SlotsMachine* machine, sf::RenderWindow* window, int prizeForPreviousSpin) :
	State(machine, window, prizeForPreviousSpin) {

}
void StartState::run() {
	sf::RenderWindow* window = getWindow();
	Button buttonStart("Start", { 200, 50 }, 20, sf::Color::Green, sf::Color::Black);
	buttonStart.setPosition({ 700, 50 });

	Button buttonStop("Stop", { 200, 50 }, 20, sf::Color::Red, sf::Color::Black);
	buttonStop.setPosition({ 700, 250 });

	sf::Font sfui;
	sfui.loadFromFile("./../../GameSlots/Fonts/SFUIText-Regular.ttf");
	buttonStart.setFont(sfui);
	buttonStop.setFont(sfui);

	sf::Text textPrize;
	textPrize.setString("You won: " + std::to_string(PrizeForPreviousSpin));
	textPrize.setFillColor(sf::Color::Cyan);
	textPrize.setCharacterSize(20);
	textPrize.setFont(sfui);
	textPrize.setPosition(400, 500);

	bool isStateStart = true;
	while (window->isOpen() && isStateStart)
	{

		sf::Event event;
		while (window->pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::Closed:
				window->close();
				break;
			case sf::Event::MouseMoved:
				if (buttonStart.isMouseOver(*window)) {
					buttonStart.setBackColor(sf::Color::White);
				}
				else {
					buttonStart.setBackColor(sf::Color::Green);
				}
				if (buttonStop.isMouseOver(*window)) {
					buttonStop.setBackColor(sf::Color::White);
				}
				else {
					buttonStop.setBackColor(sf::Color::Red);
				}
				break;
			case sf::Event::MouseButtonPressed:
				if (buttonStart.isMouseOver(*window)) {
					isStateStart = false;
				}
				break;
			default:
				break;
			}
		}

		window->clear();
		drawSlots();
		buttonStart.drawTo(*window);
		buttonStop.drawTo(*window);
		window->draw(textPrize);
		window->display();
	}
}


WorkState::WorkState(SlotsMachine* machine, sf::RenderWindow* window, int prizeForPreviousSpin, int timeout) :
	State(machine, window, prizeForPreviousSpin) {
	Timeout = timeout;
}
int WorkState::getTimeout() {
	return Timeout;
}
void WorkState::run() {
	sf::RenderWindow* window = getWindow();
	Button buttonStart("Start", { 200, 50 }, 20, sf::Color::Green, sf::Color::Black);
	buttonStart.setPosition({ 700, 50 });

	Button buttonStop("Stop", { 200, 50 }, 20, sf::Color(255, 100, 20), sf::Color::Black);
	buttonStop.setPosition({ 700, 250 });

	sf::Font sfui;
	sfui.loadFromFile("./../../GameSlots/Fonts/SFUIText-Regular.ttf");
	buttonStart.setFont(sfui);
	buttonStop.setFont(sfui);

	sf::Clock clock;
	int timeout = Timeout;
	float workTime = 0;


	bool isStateWork = true;
	while (window->isOpen() && isStateWork)
	{

		float frameTime = clock.getElapsedTime().asMilliseconds();
		clock.restart();
		workTime += frameTime;

		if (workTime > 1500) {
			std::cout << "Button" << std::endl;
			buttonStop.setBackColor(sf::Color::Red);
		}

		std::cout << "Worktime: " << workTime << " " << frameTime << std::endl;

		sf::Event event;
		while (window->pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::Closed:
				window->close();
				break;
			case sf::Event::MouseMoved:
				if (buttonStart.isMouseOver(*window)) {
					buttonStart.setBackColor(sf::Color::White);
				}
				else {
					buttonStart.setBackColor(sf::Color::Green);
				}
				if (buttonStop.isMouseOver(*window)) {
					buttonStop.setBackColor(sf::Color::White);
				}
				else {
					buttonStop.setBackColor(sf::Color::Red);
				}
				break;
			case sf::Event::MouseButtonPressed:
				if (buttonStop.isMouseOver(*window) && workTime > 1500) {
					isStateWork = false;
				}
				break;
			default:
				break;
			}
		}

		Machine->start();

		if (workTime > timeout) {
			isStateWork = false;
		}

		window->clear();
		drawSlots();
		buttonStart.drawTo(*window);
		buttonStop.drawTo(*window);
		window->display();
	}
}


StopState::StopState(SlotsMachine* machine, sf::RenderWindow* window, int prizeForPreviousSpin) : State(machine, window, prizeForPreviousSpin) {
	ResultPrize = 0;
}
int StopState::calculatePrize() {
	std::vector<Slot*> slots = Machine->getSlots();
	int numberOfUniqueSymbols = slots[0]->getNumberOfUniqueSymbols();
	std::vector<int> symbols(numberOfUniqueSymbols, 0);

	std::vector<std::vector<int>> prizeTable{
		{0, 0, 25, 100, 250, 1500},
		{0, 0, 10, 50, 125, 750},
		{0, 0, 0, 30, 100, 500},
		{0, 0, 0, 30, 100, 450},
		{0, 0, 0, 25, 75, 400}
	};

	
	for (size_t i = 0; i < slots.size(); ++i) {
		int symbol = (slots[i]->getCurrentYSlotPosition() / slots[i]->calculateSymbolLength() + 1) % numberOfUniqueSymbols;
		symbols[symbol] += 1;
	}

	int resultPrize = 0;

	for (size_t i = 0; i < numberOfUniqueSymbols; ++i) {
		resultPrize += prizeTable[i][symbols[i]];
	}

	return resultPrize;
}
void StopState::run() {
	sf::RenderWindow* window = getWindow();
	Button buttonStart("Start", { 200, 50 }, 20, sf::Color::Green, sf::Color::Black);
	buttonStart.setPosition({ 700, 50 });

	Button buttonStop("Stop", { 200, 50 }, 20, sf::Color::Red, sf::Color::Black);
	buttonStop.setPosition({ 700, 250 });

	sf::Font sfui;
	sfui.loadFromFile("./../../GameSlots/Fonts/SFUIText-Regular.ttf");
	buttonStart.setFont(sfui);
	buttonStop.setFont(sfui);

	bool isStateStop = true;

	while (window->isOpen() && isStateStop)
	{

		sf::Event event;
		while (window->pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::Closed:
				window->close();
				break;
			case sf::Event::MouseMoved:
				if (buttonStart.isMouseOver(*window)) {
					buttonStart.setBackColor(sf::Color::White);
				}
				else {
					buttonStart.setBackColor(sf::Color::Green);
				}
				if (buttonStop.isMouseOver(*window)) {
					buttonStop.setBackColor(sf::Color::White);
				}
				else {
					buttonStop.setBackColor(sf::Color::Red);
				}
				break;
			default:
				break;
			}
		}

		Machine->stop();
		int prize = calculatePrize();
		PrizeForPreviousSpin = prize;

		sf::Text textPrize;
		textPrize.setString("You won: " + std::to_string(PrizeForPreviousSpin));
		textPrize.setFillColor(sf::Color::Cyan);
		textPrize.setCharacterSize(20);
		textPrize.setFont(sfui);
		textPrize.setPosition(400, 500);

		isStateStop = false;

		window->clear();
		drawSlots();
		buttonStart.drawTo(*window);
		buttonStop.drawTo(*window);
		window->draw(textPrize);
		window->display();
	}
}