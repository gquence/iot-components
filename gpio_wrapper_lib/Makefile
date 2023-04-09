.PHONY: clean all 
PWD = $(shell pwd)
SRCDIR = $(PWD)/src
INCDIR = $(PWD)/include
TARGET = libgpiowrapper.a

INCS := -I $(INCDIR) -I $(PWD)/../wiringOP/wiringPi

CXX_SRCS := $(wildcard $(SRCDIR)/*.cpp)
CXX_OBJS := $(CXX_SRCS:$(SRCDIR)/%.cpp=$(SRCDIR)/%.o)

CXXFLAGS ?= -g -O3
CXXFLAGS += --std=c++17
LDFLAGS := -lfmt -lwiringPi -lpthread

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCS) -c $< -o $@

all: $(TARGET)

$(TARGET): $(CXX_OBJS)
	ar -rcs $@ $(CXX_OBJS)

clean:
	rm -r $(SRCDIR)/*.o
	rm -r $(TARGET)
