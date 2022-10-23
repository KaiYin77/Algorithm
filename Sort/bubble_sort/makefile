CXX	:= g++-11 -std=c++2a
CXX_FLAGS := -Wunused

main: main.cpp
	$(CXX) -o main main.cpp $(CXX_FLAGS)

.PHONY: clean
clean:
	@echo "cleaning..."
	rm main
