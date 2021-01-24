all:
	cc main.c load.c response.c logic.c map.c image.c -o wykonaj -lcurl -lpng cJSON/cJSON.o

test:
	./wykonaj qwerty_29

test-memory:
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes --track-origins=yes -v ./wykonaj qwerty_29 bot

test-seek-wall:
	./wykonaj qwerty_29 test-seek-wall

test-bot:
	./wykonaj qwerty_29 test-bot

test-load-map:
	./wykonaj qwerty_29 test-load-map

test-save-map:
	./wykonaj qwerty_29 test-save-map

test-response:
	./wykonaj qwerty_29 test-response

test-load:
	./wykonaj qwerty_29 test-load

test-reset:
	./wykonaj qwerty_20 reset
