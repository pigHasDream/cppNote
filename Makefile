# -----------------------------------------------------
# C++ compiler and options
# -----------------------------------------------------

CXX = g++
STD = -std=c++17
DBG = -g
CXXFLAGS = -Wall -$(STD)

TOP = test
# ----------------------------------------------------
# 1st line with target and denpendency
# 	It tells make to find what needs to be build first 
# 	before building current target.
# 2nd line (must start with tab) is the cmd to execute
#
# By default, first target is the default target.

$(TOP): $(TOP).o
	$(CXX) $(CXXFLAGS) -o $(TOP) $(TOP).o

$(TOP).o: 
	$(CXX) $(CXXFLAGS) -c $(TOP).cpp

clean:
	rm $(TOP) *.o

run: $(TOP)
	./$(TOP)
