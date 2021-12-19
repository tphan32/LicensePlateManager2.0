CXX=clang++
CXXFLAGS=-std=c++20 -g -fstandalone-debug -Wall -Wextra -w -pedantic -Iincludes/ `pkg-config --cflags --libs opencv` -llept -ltesseract -lsqlite3

exec: bin/exec
tests: bin/tests

bin/exec: obj/main.o obj/LicensePlateManager.o obj/LicensePlateInfo.o obj/LicensePlateScanner.o
	mkdir -p bin
	$(CXX) $(CXXFLAGS) $(INCLUDES) -lc++abi $^ -o $@

obj/main.o: src/main.cc
	mkdir -p obj
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $^ -o $@

obj/LicensePlateManager.o: src/LicensePlateManager.cc
	mkdir -p obj
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $^ -o $@

obj/LicensePlateInfo.o: src/LicensePlateInfo.cc
	mkdir -p obj
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $^ -o $@

obj/LicensePlateScanner.o: src/LicensePlateScanner.cc
	mkdir -p obj
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $^ -o $@

bin/tests: tests/tests.cc obj/catch.o obj/LicensePlateManager.o obj/LicensePlateInfo.o obj/LicensePlateScanner.o
	mkdir -p bin
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

obj/catch.o: tests/catch.cc
	mkdir -p obj
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $^ -o $@

.DEFAULT_GOAL := exec
.PHONY: clean exec tests

clean:
	rm -rf bin/* obj/*