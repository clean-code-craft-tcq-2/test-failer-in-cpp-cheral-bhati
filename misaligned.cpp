#include <iostream>
#include <assert.h>
#include <string.h>

const char* majorColor[] = { "White", "Red", "Black", "Yellow", "Violet" };
const char* minorColor[] = { "Blue", "Orange", "Green", "Brown", "Slate" };

int numberOfMajorColor = sizeof(majorColor) / sizeof(majorColor[0]);
int numberOfMinorColor = sizeof(minorColor) / sizeof(minorColor[0]);
int maxNumberofColorPairs = numberOfMajorColor * numberOfMinorColor;

int lengthOflongestMajorColor = 0;

int formatCounterStub = 0;
int printCounterStub = 0;

void setlengthofLogestMajorColor()
{
	size_t maxLength = strlen(majorColor[0]);
	for (int i = 1; i < numberOfMajorColor; i++)
	{
		if (strlen(majorColor[i]) > maxLength)
			maxLength = strlen(majorColor[i]);
	}
	lengthOflongestMajorColor = static_cast<int>(maxLength);
}

int computePairId(int majorColorIndex, int minorColorIndex)
{
	return (majorColorIndex * 5 + minorColorIndex + 1);
}

std::string formatColorPairEntry(int majorColorIndex, int minorColorIndex) {
	int pairId = computePairId(majorColorIndex, minorColorIndex);
	std::string pairIdString = std::to_string(pairId); 
	std::string majorColorEntry = majorColor[majorColorIndex];
	std::string minorColorEntry = minorColor[minorColorIndex];
	std::string seperator = " | ";
	std::string space_char = " ";
	if (pairId < 10)
	{
		pairIdString = pairIdString + space_char;
	}
	for (int i = strlen(majorColor[majorColorIndex]); i < lengthOflongestMajorColor; i++)
	{
		majorColorEntry = majorColorEntry + space_char;
	}
	std::string formattedColorPairEntry = pairIdString + seperator + majorColorEntry + seperator + minorColorEntry;
	return formattedColorPairEntry;
}

void printOnConsole(std::string ColorPairEntry)
{
	std::cout << ColorPairEntry << std::endl;
}

std::string formatterStub(int majorColorIndex, int minorColorIndex)
{
	formatCounterStub++;
	int pairId = computePairId(majorColorIndex, minorColorIndex);
	std::string pairIdString = std::to_string(pairId);
	std::string majorColorEntry = majorColor[majorColorIndex];
	std::string minorColorEntry = minorColor[minorColorIndex];
	std::string seperator = " | ";
	std::string space_char = " ";
	if (pairId < 10)
	{
		pairIdString = pairIdString + space_char;
	}
	for (int i = strlen(majorColor[majorColorIndex]); i < lengthOflongestMajorColor; i++)
	{
		majorColorEntry = majorColorEntry + space_char;
	}
	std::string formattedColorPairEntry = pairIdString + seperator + majorColorEntry + seperator + minorColorEntry;
	return formattedColorPairEntry;

}

void printerStub(std::string ColorPairEntry)
{
	printCounterStub++;
	std::cout << "PrinterStub "<< ColorPairEntry << std::endl;
}

int printColorMap(std::string(*formatColorPairEntryFunc)(int, int), void(*printOnConsoleFunc)(std::string)) {
	int i = 0, j = 0;
	setlengthofLogestMajorColor();
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			std::string ColorPairEntry = formatColorPairEntryFunc(i, j);
			printOnConsoleFunc(ColorPairEntry);
		}
	}
	return i * j;
}

void testColorPairEntry(std::string actualColorPairEntry, std::string expectedColorPairEntry)
{
	assert(expectedColorPairEntry.compare(actualColorPairEntry) == 0);
}

int main() {
	int result = printColorMap(&formatColorPairEntry, &printOnConsole);
	assert(result == 25);
	//asert to check if fomatter and printer functions are called for each pair
	printColorMap(&formatterStub, &printerStub);
	assert(formatCounterStub == maxNumberofColorPairs);
	assert(printCounterStub == maxNumberofColorPairs);
	assert(formatCounterStub == printCounterStub);
	//assert to check if the pairs are formatted in expected format
	testColorPairEntry(formatColorPairEntry(0, 0), "1  | White  | Blue");
	testColorPairEntry(formatColorPairEntry(0, 2), "3  | White  | Green");
	testColorPairEntry(formatColorPairEntry(1, 1), "7  | Red    | Orange");
	testColorPairEntry(formatColorPairEntry(1, 4), "10 | Red    | Slate");
	testColorPairEntry(formatColorPairEntry(2, 2), "13 | Black  | Green");
	testColorPairEntry(formatColorPairEntry(2, 3), "14 | Black  | Brown");
	testColorPairEntry(formatColorPairEntry(3, 0), "16 | Yellow | Blue");
	testColorPairEntry(formatColorPairEntry(3, 2), "18 | Yellow | Green");
	testColorPairEntry(formatColorPairEntry(4, 2), "23 | Violet | Green");
	testColorPairEntry(formatColorPairEntry(4, 4), "25 | Violet | Slate");
	std::cout << "All is well (maybe!)\n";
	return 0;
}
