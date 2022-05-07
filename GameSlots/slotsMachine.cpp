#include "slotsMachine.h"

Slot::Slot(std::string slotTextureFileName, int xSlotWindowPosition, int lengthSlot,
	int widthSlot, int numberOfUniqueSymbols, int numberOfVisibleSymbols) {
	LengthSlot = lengthSlot;
	WidthSlot = widthSlot;
	NumberOfUniqueSymbols = numberOfUniqueSymbols;
	NumberOfVisibleSymbols = numberOfVisibleSymbols;

	SlotTexture.loadFromFile(slotTextureFileName);

	VisibleSlotPart.setTexture(SlotTexture);
	int startSymbolNumber = rand() % NumberOfUniqueSymbols;
	int symbolLength = calculateSymbolLength();
	CurrentYSlotPosition = startSymbolNumber * symbolLength;
	VisibleSlotPart.setTextureRect(sf::IntRect(CurrentXSlotPosition, CurrentYSlotPosition,
		WidthSlot, WidthSlot * NumberOfVisibleSymbols));
	
	float ySlotWindowPosition = 0;
	VisibleSlotPart.setPosition(xSlotWindowPosition, ySlotWindowPosition);
}
sf::Sprite Slot::getVisibleSlotPart() {
	return VisibleSlotPart;
}
int Slot::getCurrentYSlotPosition() {
	return CurrentYSlotPosition;
}
int Slot::getCurrentSlotSpeed() {
	return CurrentSlotSpeed;
}
int Slot::getNumberOfUniqueSymbols() {
	return NumberOfUniqueSymbols;
}
int Slot::calculateSymbolLength() {
	return LengthSlot / (NumberOfUniqueSymbols + NumberOfVisibleSymbols);
}
void Slot::speedUp(int speedingUp, int slotSpeedInPixelsPerFrameAfterSpeedingUp) {

	if (speedingUp > 0) {
		if (CurrentSlotSpeed + speedingUp <= slotSpeedInPixelsPerFrameAfterSpeedingUp) {
			CurrentSlotSpeed += speedingUp;
		}
		else {
			CurrentSlotSpeed = slotSpeedInPixelsPerFrameAfterSpeedingUp;
		}
	}
	if (speedingUp < 0) {
		if (CurrentSlotSpeed + speedingUp >= slotSpeedInPixelsPerFrameAfterSpeedingUp) {
			CurrentSlotSpeed += speedingUp;
		}
		else {
			CurrentSlotSpeed = slotSpeedInPixelsPerFrameAfterSpeedingUp;
		}
	}

	int shiftSlot = CurrentSlotSpeed;
	int symbolLength = calculateSymbolLength();
	int newYSlotPosition = CurrentYSlotPosition + shiftSlot;

	CurrentYSlotPosition = newYSlotPosition % (LengthSlot - NumberOfVisibleSymbols * symbolLength);
	VisibleSlotPart.setTextureRect(sf::IntRect(CurrentXSlotPosition, CurrentYSlotPosition,
		WidthSlot, WidthSlot * NumberOfVisibleSymbols));
}
void Slot::slowDown(int speedingUp, int slotSpeedInPixelsPerFrameAfterSpeedingUp) {
	speedUp(speedingUp, slotSpeedInPixelsPerFrameAfterSpeedingUp);
}
void Slot::alignSlot() {
	int symbolLength = calculateSymbolLength();
	int shiftSlotForAlign = symbolLength - CurrentYSlotPosition % symbolLength;

	int newYSlotPosition = CurrentYSlotPosition + shiftSlotForAlign;

	CurrentYSlotPosition = newYSlotPosition % (LengthSlot - NumberOfVisibleSymbols * symbolLength);
	VisibleSlotPart.setTextureRect(sf::IntRect(CurrentXSlotPosition, CurrentYSlotPosition,
		WidthSlot, WidthSlot * NumberOfVisibleSymbols));

	CurrentSlotSpeed = 0;
}


SlotsMachine::SlotsMachine(std::string slotImageFileName, int numberOfSlots, int lengthSlotMachineInPixels,
	int widthSlotMachineInPixels, int numberOfUniqueSlotSymbols, int maxSlotSpeedInPixelsPerFrame, int numberOfVisibleSymbols) {
	MaxSlotSpeedInPixelsPerFrame = maxSlotSpeedInPixelsPerFrame;

	int widthSlot = int(widthSlotMachineInPixels / numberOfSlots);
	int lengthSlot = int(lengthSlotMachineInPixels);
	std::vector<Slot*> slots(numberOfSlots);
	for (int i = 0; i < numberOfSlots; ++i) {
		slots[i] = new Slot(slotImageFileName, i * widthSlot, lengthSlot, widthSlot,
			numberOfUniqueSlotSymbols, numberOfVisibleSymbols);
	}
	Slots = slots;
}
std::vector<Slot*> SlotsMachine::getSlots() {
	return Slots;
}
void SlotsMachine::start() {
	int speedingUp = 2;
	for (size_t i = 0; i < Slots.size(); ++i) {
		Slots[i]->speedUp(speedingUp, MaxSlotSpeedInPixelsPerFrame - i * 10);
	}
	for (int j = 0; j < 3; ++j) {
		for (size_t i = 0; i < Slots.size(); ++i) {
			Slots[i]->speedUp(0, MaxSlotSpeedInPixelsPerFrame - i * 10);
		}
	}
}
void SlotsMachine::stop() {
	int speedingUp = -1;
	int minSlotSpeedInPixelsPerFrame = 10;
	bool isSlotSpeedEqualsMin = false;
	while (!isSlotSpeedEqualsMin) {
		for (size_t i = 0; i < Slots.size(); ++i) {
			Slots[i]->slowDown(speedingUp, minSlotSpeedInPixelsPerFrame);
		}
		for(int j = 0; j < 5; ++j){
			for (size_t i = 0; i < Slots.size(); ++i) {
				Slots[i]->slowDown(speedingUp, minSlotSpeedInPixelsPerFrame);
			}
		}
		
		if (Slots[0]->getCurrentSlotSpeed() <= minSlotSpeedInPixelsPerFrame) {
			isSlotSpeedEqualsMin = true;
		}
	}
	
	for (size_t i = 0; i < Slots.size(); ++i) {
		Slots[i]->alignSlot();
	}
	
}