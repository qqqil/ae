all:clean event
	@echo "it is good to make test"
event:event.o event_loop.o
	g++ -o $@ $^
%.o:%.cpp
	g++ --std=c++11 -c $<
.PYTHON:clean

clean:
	rm -f *.o event
