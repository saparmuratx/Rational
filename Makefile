src = $(wildcard *.cpp)

CXXFLAGS = -g -std=c++11 -pedantic -Wall -Wextra -Wshadow -D_GLIBCXX_DEBUG -fsanitize=address -fsanitize=undefined
CXXRLSFLAGS = -O2 -std=c++11 -Wall -Wextra -Wshadow -pedantic

main: $(src)
	$(CXX) -o $@ $(CXXFLAGS) $(include) $^

.PHONY: release
release:
	$(CXX) -o main $(CXXRLSFLAGS) $(src)

run:
	./main
redir:
	./main < inp.txt > out.txt
.PHONY: clean
clean:
	rm -f main
	rm -f out.txt
	