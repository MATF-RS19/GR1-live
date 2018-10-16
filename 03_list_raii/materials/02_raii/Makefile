PROGRAM=02_raii

.PHONY: clean dist

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)

clean:
	-rm *.o $(PROGRAM) *core

