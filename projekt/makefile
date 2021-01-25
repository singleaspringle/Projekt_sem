DEPS = main.c load.c response.c map.c logic.c image.c
LIBS = -lcurl -lpng cJSON/cJSON.o
TESTS = tests/main_test_load.c tests/main_test_response.c tests/main_test_map.c tests/main_test_logic.c tests/main_test_image.c

%.o: %.c
	cc -c $^ -o $@ ${LIBS}

main:
	cc main.c load.c response.c map.c logic.c image.c -o program -Wall --pedantic -lcurl -lpng cJSON/cJSON.o 

tests:
	cd tests &&	cc main_test_load.c ../load.c -o test_load -Wall --pedantic -lcurl -lpng ../cJSON/cJSON.o
	cd tests &&	cc main_test_response.c ../response.c -o test_response -Wall --pedantic -lcurl -lpng ../cJSON/cJSON.o
	cd tests &&	cc main_test_map.c ../map.c -o test_map -Wall --pedantic -lcurl -lpng ../cJSON/cJSON.o
	cd tests &&	cc main_test_logic.c ../logic.c -o test_logic -Wall --pedantic -lcurl -lpng ../cJSON/cJSON.o
	cd tests &&	cc main_test_image.c ../image.c -o test_image -Wall --pedantic -lcurl -lpng ../cJSON/cJSON.o

test_load: tests
	cd tests &&	./test_load qwerty_29

test_response: tests
	/mnt/d/projekty/sem/1dm1103_20z/projekt/tests/test_response qwerty_29

test_map: tests
	/mnt/d/projekty/sem/1dm1103_20z/projekt/tests/test_map

test_logic: tests
	/mnt/d/projekty/sem/1dm1103_20z/projekt/tests/test_logic qwerty_29

test_image: tests
	/mnt/d/projekty/sem/1dm1103_20z/projekt/tests/test_image

test_bot: main
	./program qwerty_29 bot

test_move: main
	./program qwerty_29

clean:
	rm program
	cd tests;
	rm test_load
	rm test_response
	rm test_map
	rm test_logic
	rm test_image
	cd ..;
