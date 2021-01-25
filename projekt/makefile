DEPS = main.o load.o response.o map.o logic.o image.o
LIBS = -lcurl -lpng cJSON/cJSON.o 
LIB = load.o response.o map.o logic.o image.o
COMPILER = cc
SDIR = $(PWD)/tests/
all: program
	

program: $(DEPS)
	$(COMPILER) $^ -o $@ $(LIBS)

test-response: tests/main_test_response.o $(LIB)
	$(COMPILER) $^ -o tests/test-response $(LIBS)
	./tests/test-response qwerty_29

test-load: tests/main_test_load.o $(LIB)
	$(COMPILER) $^ -o tests/test-load $(LIBS)
	./tests/test-load qwerty_29

test-logic: tests/main_test_logic.o $(LIB)
	$(COMPILER) $^ -o tests/test-logic $(LIBS)
	./tests/test-logic qwerty_29

test-map: tests/main_test_map.o $(LIB)
	$(COMPILER) $^ -o tests/test-map $(LIBS)
	./tests/test-map 

test-image: tests/main_test_image.o $(LIB)
	$(COMPILER) $^ -o tests/test-image $(LIBS)
	./tests/test-image

memory: program
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes --track-origins=yes -v ./program qwerty_29 bot
	
memory-response: test-response
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes --track-origins=yes -v ./tests/test-response qwerty_29
	
memory-logic: test-logic
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes --track-origins=yes -v ./tests/test-logic qwerty_29

memory-load: test-load
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes --track-origins=yes -v ./tests/test-load qwerty_29

memory-map: test-map
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes --track-origins=yes -v ./tests/test-map 

memory-image: test-image
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes --track-origins=yes -v ./tests/test-image

%.o:%.c
	$(COMPILER) -c $^ -o $@

test-bot: program
	./program qwerty_29 bot

test-move: program
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



