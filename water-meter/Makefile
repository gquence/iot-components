.PHONY: clean all 
PWD = $(shell pwd)
SRCDIR = $(PWD)/src
INCDIR = $(PWD)/include
TARGET = water_meter

INCS := -I $(INCDIR) -I $(PWD)/../gpio_wrapper_lib/include

CXX_SRCS := $(wildcard $(SRCDIR)/*.cpp)
CXX_OBJS := $(CXX_SRCS:$(SRCDIR)/%.cpp=$(SRCDIR)/%.o)

CXXFLAGS := --std=c++17 -g
LDFLAGS := -L../gpio_wrapper_lib -lgpiowrapper -lwiringPi -lfmt -lpthread

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCS) -c $< -o $@

all: $(TARGET)

$(TARGET): $(CXX_OBJS)
	$(CXX) $(CXX_OBJS) $(CXXFLAGS) $(LDPATH) $(LDFLAGS) -o $@

clean:
	rm -f $(SRCDIR)/*.o
	rm -f $(TARGET)
