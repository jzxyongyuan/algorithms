LOG   = ../../log/output
BOOST = ../../../local/boost/

INCLUDEDIR =\
	-I $(LOG)/include\
	-I $(BOOST)/include\
	-I ./

LIBDIR =\
	-L $(LOG)/lib -llog\
	-L $(BOOST)lib \
	-lboost_log_setup\
	-lboost_log\
	-lboost_iostreams\
	-lboost_filesystem\
	-lboost_system\
	-lboost_thread\
	-lpthread -lm -lstdc++ -lcrypto -lrt

GCC = g++

SRCWILD    = $(wildcard *.cpp)
OBJS       = $(patsubst %.cpp, %_release.o, $(SRCWILD))

all : clean compile

CPPFLAGS       = -g -finline-functions -Wall -Winline -pipe -Wno-deprecated -Wunused-variable -DNDEBUG
#CPPFLAGS       = -g -O3 -finline-functions -Wall -Winline -pipe -Wno-deprecated -Wunused-variable -DNDEBUG

compile : $(OBJS)


clean:
	rm -rf $(OBJS)

%_release.o	: %.cpp
	$(GCC) $(CPPFLAGS) -c $< -o $@ $(INCLUDEDIR)
