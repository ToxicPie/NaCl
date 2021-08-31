.PRECIOUS: ./p%

%: p%
	ulimit -s unlimited && ./$<
p%: p%.cpp
	g++ -o $@ $< -std=c++17 -Wall -Wextra -Wshadow \
		-fsanitize=address,undefined
