all: build

build:
	gcc -I../libwebsockets/include server.c -lssl -lcrypto -lcap -o server ../libwebsockets/lib/libwebsockets.a

clean:
	rm server
