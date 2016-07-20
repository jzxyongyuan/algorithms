LOG   = ../../log/output

INCLUDEDIR =\
	-I $(LOG)/include\
	-I $(BOOST)/include\
	-I ./

LIBDIR =\
	-L $(LOG)/lib -llog\
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
