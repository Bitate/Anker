# Anker
## Why Anker ?
Anker is a helper for [Anki](https://apps.ankiweb.net/) with the purpose of facilitating the creation of cards in Anki. Currently, it only serves as a bridge between Anki and [Aboboo](https://www.aboboo.com/). These two softwares are my best friends in learning English language. I highly recommend you guys to try them out :)


Listen a specific dialog over and over again is quite helpful in learning language. Aboboo can help you learn each dialog in detail and also output those dialogs in the form of <mp3, lrc> pair. For example, `12.lrc` - "Can you hold on one second?" correspondes with the `12.mp3`. Open `12.mp3` under resources folder for check.

![Aboboo output audio clips](resources/screenshot_1.png)

 While Anki will remind you to review what you have listened timely, which forms a complete learning process. In my case, I prefer put the audio in the front and corresponding text in the back. It's time-consuming to make each card manually especially you have so many audio clips to learn. Here comes the rescue, Anker will do the legwork for you. 

## Supported Platforms
Windows 10

## How to build ?
1. Install [Qt Creator](https://www.qt.io/product/development-tools) and [CMake](https://cmake.org/download/) for Window 10.
2. `Git clone https://github.com/Bitate/Anker`
3. Open `CMakeLists.txt` ( same folder with README.md ) using Qt Creator.
4. Google how to build CMake project in Qt Creator :-)
## How to run ?
1. Run Anki first (Otherwise, the Anker can not run)
2. Run anker-win32.exe
3. Select deck to be imported. BTW: I have to admit that the UI design is ugly :)

![Select deck](resources/screenshot_2.png)

4. Click "Open Files" button and select all mp3 and lrc files output from Aboboo. Then click "Open" button.

![open mp3 and lrc files](resources/screenshot_3.png)

5. Waiting for importing

6. Done. Remember to review today's cards :)

## A Little More
I'm a newbie in C++ and a life-time learner. Feel free to contact me at papersflyaway@gmail.com or 1660513875@qq.com :)