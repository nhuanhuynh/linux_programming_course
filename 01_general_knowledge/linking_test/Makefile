
objs:
	gcc -c -o hello_nhuan.o hello_nhuan.c
	gcc -c -o hello_world.o hello_world.c
	gcc -c -o main.o main.c

world: objs
	gcc -o hello_world hello_world.o main.o

nhuan: objs
	gcc -o hello_nhuan hello_nhuan.o main.o

clean:
	rm *.o
