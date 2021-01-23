all:
	cc main.c load.c response.c logic.c map.c -o wykonaj -lcurl cJSON/cJSON.o

test:
	./wykonaj qwerty_29

memory:
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes --track-origins=yes -v ./wykonaj qwerty_29 bot

test-bot:
	./wykonaj qwerty_29 bot

