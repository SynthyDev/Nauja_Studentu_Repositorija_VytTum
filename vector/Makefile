CXX = g++
CXXFLAGS = -O3 -std=c++17 -Wall

TARGET = programa

SRC = versija_v1.cpp funk.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	del /f /q $(TARGET).exe 2>nul || rm -f $(TARGET)