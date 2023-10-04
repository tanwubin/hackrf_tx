
all:
	gcc -o tx tx.c -lm -lhackrf -Wno-strict-aliasing

clean:
	rm tx

