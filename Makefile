CC 	= gcc
CFLAGS 	= -I.
LDFLAGS = -lcurl
OBJS 	= main.o getip.o appendhosts.o search.o deleteline.o

ezhostsfile : $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

main.o : src/main.c
	$(CC) -c -o $@ $(CFLAGS) $^

getip.o : src/include/curl/getip.c
	$(CC) -c -o $@ $(CFLAGS) $^

appendhosts.o : src/include/file/appendhosts.c
	$(CC) -c -o $@ $(CFLAGS) $^

search.o : src/include/file/search.c
	$(CC) -c -o $@ $(CFLAGS) $^

deleteline.o : src/include/file/deleteline.c
	$(CC) -c -o $@ $(CFLAGS) $^

.PHONY = clean
clean :
	rm ezhostsfile $(OBJS)

