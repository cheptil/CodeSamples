TARGET=cachesim
CC=gcc
CFLAGS=-g -Wall
OBJECTS=cachesim.o cache_check.o check_opts_params.o direct_through.o disable_cache.o for_stdout.o global.o parse_arguments.o parse_config.o trace_check.o
all:$(TARGET)
clean:
	rm -f *.o $(TARGET) core 
$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(CFLAGS) $(OBJECTS)
.c.o:
	$(CC) -c $(CFLAGS) $< 

global.o: global.h
direct_through.o: global.h
disable_cache.o: global.h
for_stdout.o: global.h
parse_arguments.o: global.h
cache_check.o: global.h cache_check.h
parse_config.o: global.h parse_config.h
trace_check.o: global.h trace_check.h
check_opts_params.o: global.h cache_check.h trace_check.h
cachesim.o: global.h parse_config.h parse_arguments.h check_opts_params.h disable_cache.h direct_through.h for_stdout.h
