all:
	cc main.c funkcje.c -o wykonaj -lcurl cJSON/cJSON.o  

test:
	./wykonaj qwerty_29

memory:
	valgrind --leak-check=full ./wykonaj qwerty_29