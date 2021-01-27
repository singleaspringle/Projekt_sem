DEPS = main.o load.o response.o map.o logic.o image.o
LIBS = -lcurl -lpng cJSON/cJSON.o 
LIB = load.o response.o map.o logic.o image.o
COMPILER = cc
SDIR = $(PWD)/tests/
all: program response load logic map image
	

program: $(DEPS)
	$(COMPILER) $^ -o $@ $(LIBS)

response: tests/main_test_response.o $(LIB)
	$(COMPILER) $^ -o tests/test-response $(LIBS)

test-response: response
	./tests/test-response qwerty_29

load: tests/main_test_load.o $(LIB)
	$(COMPILER) $^ -o tests/test-load $(LIBS)

test-load: load
	./tests/test-load qwerty_29

logic: tests/main_test_logic.o $(LIB)
	$(COMPILER) $^ -o tests/test-logic $(LIBS)

test-logic: logic
	./tests/test-logic qwerty_29

map: tests/main_test_map.o $(LIB)
	$(COMPILER) $^ -o tests/test-map $(LIBS)

test-map: map
	./tests/test-map 

image: tests/main_test_image.o $(LIB)
	$(COMPILER) $^ -o tests/test-image $(LIBS)

test-image: image
	./tests/test-image

memory: program
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes --track-origins=yes -v ./program qwerty_29
	
memory-response: response
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes --track-origins=yes -v ./tests/test-response qwerty_29
	
memory-logic: logic
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes --track-origins=yes -v ./tests/test-logic qwerty_29

memory-load: load
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes --track-origins=yes -v ./tests/test-load qwerty_29

memory-map: map
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes --track-origins=yes -v ./tests/test-map 

memory-image: image
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes --track-origins=yes -v ./tests/test-image

%.o:%.c
	$(COMPILER) -c $^ -o $@

test: program
	./program qwerty_29

clean:
	rm program
	rm *.o
	rm $(SDIR)*.o
	rm $(SDIR)test-load
	rm $(SDIR)test-logic
	rm $(SDIR)test-response
	rm $(SDIR)test-map
	rm $(SDIR)test-image
	rm $(SDIR)derulo.json
	rm $(SDIR)mapa.png
	rm $(SDIR)mapa_wypisz.txt