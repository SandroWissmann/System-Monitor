.PHONY: all
all: format test build

.PHONY: format
format:
	#clang-format src/* include/* -i
	find -iname *.h -o -iname *.cpp | xargs clang-format -i
.PHONY: build
build:
	mkdir -p build
	cd build && \
	cmake .. && \
	make

.PHONY: debug
debug:
	mkdir -p build
	cd build && \
	cmake -DCMAKE_BUILD_TYPE=debug .. && \
	make

.PHONY: clean
clean:
	rm -rf build

.PHONY: valgrind
valgrind:
	mkdir -p build
	cd build && \
	cmake -DCMAKE_BUILD_TYPE=debug .. && \
	make
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file="report" ./build/monitor	
