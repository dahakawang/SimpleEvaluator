all: eval
	./eval script.eval

eval: main.cc
	g++ -std=c++11 -g main.cc -o eval
