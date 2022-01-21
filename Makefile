game:
	clang++ Main6.cpp -o play -I/usr/local/include -D_THREAD_SAFE -L/usr/local/lib -lSDL2 -lSDL2_Image -lSDL2_ttf

run:
	./play