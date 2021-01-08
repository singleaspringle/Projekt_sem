all:
	cc main.c funkcje.c -o wykonaj -lcurl cJSON/cJSON.o  

test:
	./wykonaj qwerty_29 info move move rotate right move explore

reset:
	./wykonaj qwerty_29 reset

memory:
	valgrind ./wykonaj qwerty_29 info move move rotate right move explore