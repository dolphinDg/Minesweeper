main: main.cpp Board.cpp Menu.cpp Application.cpp Game.cpp Options.cpp signal_slot.cpp Rating.cpp
	g++ -lncurses -std=gnu++14 -g -Wall main.cpp Options.cpp Board.cpp Menu.cpp Application.cpp Game.cpp signal_slot.cpp Rating.cpp -o exec -I.