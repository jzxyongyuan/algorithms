LOG       = ../../log/output
ALGORITHM = ../output/

INCLUDEDIR =\
	-I $(LOG)/include\
	-I $(BOOST)/include\
	-I $(ALGORITHM)/include\
	-I ./

LIBDIR =\
	-L $(ALGORITHM)/lib -lalgorithm\
	-L $(LOG)/lib -llog\
	-lpthread -lm -lstdc++ -lcrypto -lrt

GCC = g++

SRCWILD    = $(wildcard *.cpp)
OBJS       = $(patsubst %.cpp, %_release.o, $(SRCWILD))

BINS       = $(patsubst %.cpp, %.bin, $(SRCWILD))
FINAL_BINS = $(patsubst %.cpp, %, $(SRCWILD))

all : clean makebin

CPPFLAGS       = -g -finline-functions -Wall -Winline -pipe -Wno-deprecated -Wunused-variable -DNDEBUG
#CPPFLAGS       = -g -O3 -finline-functions -Wall -Winline -pipe -Wno-deprecated -Wunused-variable -DNDEBUG

compile : $(OBJS)


clean:
	rm -rf $(OBJS)
	rm -rf $(BINS)
	rm -rf $(FINAL_BINS)

%_release.o	: %.cpp
	$(GCC) $(CPPFLAGS) -c $< -o $@ $(INCLUDEDIR)

%.bin  : %_release.o
	$(GCC) -g -o $@ $^ $(LIBDIR) $(INCLUDEDIR)

makebin: $(BINS)
	for bin in $(BINS);\
	do\
		newname=`echo $$bin | sed s/.bin//g`;\
		mv $$bin $$newname;\
	done
