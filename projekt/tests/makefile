all:
	cc main_test_load.c ../load.c -o test_load -lcurl -lpng ../cJSON/cJSON.o
	cc main_test_response.c ../response.c ../load.c -o test_response -lcurl -lpng ../cJSON/cJSON.o
	cc main_test_map.c ../map.c ../response.c ../load.c -o test_map -lcurl -lpng ../cJSON/cJSON.o
	cc main_test_logic.c ../logic.c ../map.c ../response.c ../load.c -o test_logic -lcurl -lpng ../cJSON/cJSON.o
	cc main_test_image.c ../image.c ../logic.c ../map.c ../response.c ../load.c -o test_image -lcurl -lpng ../cJSON/cJSON.o

test-load:
	./test_load qwerty_29

test-response:
	./test_response qwerty_29

test-map:
	./test_map

test-logic:
	./test_logic qwerty_29

test-image:
	./test_image

load-memory:
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes --track-origins=yes -v ./test_load qwerty_29

response-memory:
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes --track-origins=yes -v ./test_response qwerty_29

map-memory:
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes --track-origins=yes -v ./test_map

logic-memory:
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes --track-origins=yes -v ./test_logic qwerty_29

image-memory:
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes --track-origins=yes -v ./test_image

clean:
	rm mapa_wypisz.txt
	rm derulo.json
	rm mapa.png
	rm test_image
	rm test_logic
	rm test_map
	rm test_response
	rm test_load