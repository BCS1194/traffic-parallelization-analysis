default: test

test: road_test.c
	gcc -g -O2 --std=c99 -o test road_test.c

clean:
	rm -f test

