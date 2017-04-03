main:
	g++ -o bin/main src/main.cpp
	cp data/* bin/
clean:
	rm -f bin/*