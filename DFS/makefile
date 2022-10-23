CXX	:= g++-11 -std=c++2a
CXX_FLAGS := -Wunused

dfs: dfs.cpp
	$(CXX) -o dfs dfs.cpp $(CXX_FLAGS)

.PHONY: clean
clean:
	@echo "cleaning..."
	rm dfs
