all:
	g++ main.cpp -o app.exe -lncurses -DNCURSES_STATIC
run:
	app