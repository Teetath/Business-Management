compile: main.cpp
	 g++ -o main main.cpp



run: monster
	 ./main


clean: monster
	 rm main