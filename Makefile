main: app/src/main/main.c
	gcc -o main.out app/src/main/main.c app/src/lib/env/env.c app/src/lib/list/list.c app/src/lib/cli/list/list.c app/src/lib/input/input.c

