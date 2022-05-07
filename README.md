# Game Slots

### Files locations
SFML package - C++ frameworks <br>
.exe - x64/Debug/GameSlots.exe

### Building

Building was made with VS Studio builder. <br><br>

![image](https://user-images.githubusercontent.com/54264954/167255802-fe41ca9b-1bd7-4ec0-9269-6f335ee64b22.png)
At first add to the properties the absolute path to the SFML package folder. <br>
As you can see on the screenshot we write in the field "Additional including files catalogues" path to the include folder of SFML package.

![image](https://user-images.githubusercontent.com/54264954/167256126-94f5147c-06b4-4a2a-905c-bff893bb80ba.png)
Then add ( SFML_DYNAMIC;_MBCS;%(PreprocessorDefinitions) ) to the preprocessor properties in the field "Preprocessor's Definitions".

![image](https://user-images.githubusercontent.com/54264954/167256119-2da12e58-9e84-482a-b8df-a5ea764df4dc.png)
Now go to the linker properties. Here write down the absolute path to the SFML lib folder in the field "Additional libraries catalogues".

![image](https://user-images.githubusercontent.com/54264954/167256225-b3e33fbd-0337-445b-9b30-ace8275aa1d6.png)
Finally go to the input properties. Add next string to the field "Additional dependencies":
sfml-graphics-d.lib;sfml-window-d.lib;sfml-system-d.lib;sfml-audio-d.lib;kernel32.lib;user32.lib;gdi32.lib;winspool.lib;comdlg32.lib;advapi32.lib;shell32.lib;ole32.lib;oleaut32.lib;uuid.lib;odbc32.lib;odbccp32.lib
