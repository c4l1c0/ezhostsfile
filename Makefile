CC 	= gcc
CFLAGS 	= -I.
LDFLAGS = -lcurl
OBJS 	= main.o getip.o appendhosts.o

ezhostsfile : $(OBJS)
	$(CC) $(LDFLAGS) -o ezhostsfile main.o getip.o appendhosts.o 

main.o : src/main.c
	$(CC) -c -o $@ $(CFLAGS) $^

getip.o : src/include/curl/getip.c
	$(CC) -c -o $@ $(CFLAGS) $^

appendhosts.o : src/include/file/appendhosts.c
	$(CC) -c -o $@ $(CFLAGS) $^

.PHONY = clean
clean :
	rm ezhostsfile $(OBJS)

