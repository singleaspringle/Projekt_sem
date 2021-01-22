all:
	cc main.c load.c response.c logic.c map.c -o wykonaj -lcurl cJSON/cJSON.o

test:
	./wykonaj qwerty_29

memory:
	valgrind --leak-check=full ./wykonaj qwerty_29

test-bot:
	./wykonaj qwerty_29 bot

