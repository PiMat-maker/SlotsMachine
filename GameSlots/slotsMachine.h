#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

class Slot {
	sf::Sprite VisibleSlotPart;
	sf::Texture SlotTexture;
	const int CurrentXSlotPosition = 0;
	int CurrentYSlotPosition;
	int LengthSlot;
	int WidthSlot;
	int NumberOfUniqueSymbols;
	int NumberOfVisibleSymbols = 3;
	int CurrentSlotSpeed = 0;
public:
	Slot(std::string slotTextureFileName, int xSlotFramePosition, int lengthSlot,
		int widthSlot, int numberOfSymbols, int numberOfVisibleSymbols);
	sf::Sprite getVisibleSlotPart();
	int getCurrentYSlotPosition();
	int getCurrentSlotSpeed();
	int getNumberOfUniqueSymbols();
	int calculateSymbolLength();
	void speedUp(int speedingUp, int slotSpeedInPixelsPerFrameAfterSpeedingUp);
	void slowDown(int speedingUp, int slotSpeedInPixelsPerFrameAfterSlowingDown);
	void alignSlot();
};

class SlotsMachine {
	int MaxSlotSpeedInPixelsPerFrame;
	std::vector<Slot*> Slots;
public:
	SlotsMachine(std::string slotImageFileName, int numberOfSlots, int lengthSlotMachineInPixels,
		int widthSlotMachineInPixels, int numberOfUniqueSlotSymbols, int maxSlotSpeedInPixelsPerFrame,
		int numberOfVisibleSymbols);
	std::vector<Slot*> getSlots();
	void start();
	void stop();
};