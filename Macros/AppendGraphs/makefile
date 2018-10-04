CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g

#################### DEPENDENCIES ####################

CNAF_PATH = /home/DAMPE/ecatanzani/bin/boost_1_67_0
HOME_SERVER_PATH = /home/enrico/boost_1_67_0
LDLIBS = -lboost_filesystem -lboost_system

ifeq ($(shell uname -s),Linux) # LINUX
    ifneq ("$(wildcard $(CNAF_PATH))","")
		CPPFLAGS += -I $(CNAF_PATH)
		LDFLAGS = -L $(CNAF_PATH)/stage/lib/
	else
		CPPFLAGS += -I $(HOME_SERVER_PATH)
		LDFLAGS = -L $(HOME_SERVER_PATH)/stage/lib/
	endif
endif

ifeq ($(shell uname -s),Darwin) # macOS 
        CPPFLAGS += -I /Users/enrico/boost_1_67_0
        LDFLAGS = -L /Users/enrico/boost_1_67_0/stage/lib/
endif

DIPS_INCLUDE = $(shell root-config --cflags)
DIPS_LIBS = $(shell root-config --ldflags) $(shell root-config --libs)

CPPFLAGS+= -I $(DIPS_INCLUDE)
LDFLAGS += $(DIPS_LIBS) 

######################################################

SRCS=SmartAppend.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: tool

tool: $(OBJS)
	$(CXX) $(CPPFLAGS) $(LDFLAGS) -o SAppend $(OBJS) $(LDLIBS)

depend: .depend

.depend: $(SRCS)
	$(RM) ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) *~ .depend

include .depend
