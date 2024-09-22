Modular: main.cpp number_t.cpp number_t.h
	g++ -std=c++20 main.cpp number_t.cpp -o Modular

clean:
	rm -f *.o Modular
