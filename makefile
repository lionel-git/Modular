Modular: main.cpp number_t.cpp number_t.h point_t.cpp point_t.h elliptic_curve.cpp elliptic_curve.h
	g++ -std=c++20 main.cpp number_t.cpp point_t.cpp elliptic_curve.cpp -o Modular

clean:
	rm -f *.o Modular
