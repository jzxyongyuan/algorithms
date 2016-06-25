LOG   = ../log/output
BOOST = ../../local/boost/

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
AR  = ar

LIBS     = libalgorithm.a

INCLUDES = stack/*.h \


MODS  = stack \

all : output

compile:
	for module in $(MODS);\
	do\
		make compile -j4 -C $$module;
	done

$(OBJS) : compile


output: $(LIBS)
	rm -rf ./output
	mkdir -p ./output/include
	mkdir -p ./output/lib
	cp -f ${LIBS}     ./output/lib
	for module in $(MODS);\
	do\
		mkdir -p ./output/include/$$module;\
		cp -f $$module/*.h   ./output/include/$$module;\
	done
	rm -f $(LIBS)

$(LIBS) : $(OBJS)
	ar cqs $@ $^

clean:
	rm -fr $(LIBS)
	rm -rf ./output
	make clean -C stack
