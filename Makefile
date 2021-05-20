.PHONY: all
all: format test build

.PHONY: format
format:
	clang-format src/**/*.cpp src/*.cpp -i

.PHONY: build
build:
	mkdir -p build
	cd build && \
	cmake .. && \
	make

.PHONY: run
run:
	cd build && \
	./membot

.PHONY: debug
debug:
	mkdir -p build
	cd build && \
	cmake -DCMAKE_BUILD_TYPE=debug .. && \
	make

.PHONY: valgrind
valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=~/valgrind-out.txt <add command here>


.PHONY: clean
clean:
	rm -rf build
