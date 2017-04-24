default: test

test: test_user_file_io_cars_roads.c
	gcc -g -O2 --std=c99 -Wall -o test test_user_file_io_cars_roads.c

clean:
	rm -f test

