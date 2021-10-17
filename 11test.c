#include <stdio.h>
#include <stdlib.h>

#define ROWS 10
#define COLS 11

#define MAX_Y (ROWS - 1)
#define MAX_X (COLS - 2)

#define BUSY '#'
#define EMPTY 'L'
#define FLOOR '.'

char data[][COLS] = {
		"L.LL.LL.LL",
		"LLLLLLL.LL",
		"L.L.L..L..",
		"LLLL.LL.LL",
		"L.LL.LL.LL",
		"L.LLLLL.LL",
		"..L.L.....",
		"LLLLLLLLLL",
		"L.LLLLLL.L",
		"L.LLLLL.LL"
	};

void print_grid(char grid[][COLS]) {
	printf("\n");
	for (int y=0; y <= MAX_Y; y++) {
		for (int x=0; x <= MAX_X; x++) {
			printf("%c", grid[y][x]);
		}
		printf("\n");
	}
}

void copy_grid(char source[][COLS], char dest[][COLS]) {
	for (int y = 0; y <= MAX_Y; y++) {
		for (int x = 0; x <= MAX_X; x++) {
			dest[y][x] = source[y][x];
		}
	}
}

int are_equal(char first[][COLS], char second[][COLS]) {
	for (int y = 0; y <= MAX_Y; y++) {
		for (int x = 0; x <= MAX_X; x++) {
			if (first[y][x] != second[y][x]) {
				return 0;
			}
		}
	}
	return 1;
}


int count_busy(char grid[][COLS]) {
	int res = 0;
	for (int y = 0; y <= MAX_Y; y++) {
		for (int x = 0; x <= MAX_X; x++) {
			if (grid[y][x] == BUSY) {
				res++;
			}
		}
	}
	return res;
}


int busy_neighbors(char grid[][COLS], int y, int x) {
	int i, j, res = 0;
	i = y - 1; j = x - 1; if (0 <= i     && 0 <= j    ) if (grid[i][j] == BUSY) res++;
	i = y - 1; j = x    ; if (0 <= i                  ) if (grid[i][j] == BUSY) res++;
	i = y - 1; j = x + 1; if (0 <= i     && j <= MAX_X) if (grid[i][j] == BUSY) res++;
	i = y    ; j = x - 1; if (              0 <= j    ) if (grid[i][j] == BUSY) res++;
	i = y    ; j = x + 1; if (              0 <= MAX_X) if (grid[i][j] == BUSY) res++;
	i = y + 1; j = x - 1; if (i <= MAX_Y && 0 <= j    ) if (grid[i][j] == BUSY) res++;
	i = y + 1; j = x    ; if (i <= MAX_Y              ) if (grid[i][j] == BUSY) res++;
	i = y + 1; j = x + 1; if (i <= MAX_Y && 0 <= MAX_X) if (grid[i][j] == BUSY) res++;
	return res;
}

int busy_neighbors2(char grid[][COLS], int y, int x) {
	int i, j, res = 0;
	// North
	for (i = y-1, j = x; i >= 0; i--) {
		if (grid[i][j] == BUSY) {res++; break;}
		if (grid[i][j] == EMPTY) break;
	}
	// South
	for (i = y+1, j = x; i <= MAX_Y; i++) {
		if (grid[i][j] == BUSY) {res++; break;}
		if (grid[i][j] == EMPTY) break;
	}
	// West
	for (i = y, j = x-1; j >= 0; j--) {
		if (grid[i][j] == BUSY) {res++; break;}
		if (grid[i][j] == EMPTY) break;
	}
	// East
	for (i = y, j = x+1; j <= MAX_X; j++) {
		if (grid[i][j] == BUSY) {res++; break;}
		if (grid[i][j] == EMPTY) break;
	}
	// NorthWest
	for (i=y-1, j=x-1; i >= 0 && j >= 0; i--, j--) {
		if (grid[i][j] == BUSY) {res++; break;}
		if (grid[i][j] == EMPTY) break;
	}
	// NorthEast
	for (i=y-1, j=x+1; i >= 0 && j <= MAX_X; i--, j++) {
		if (grid[i][j] == BUSY) {res++; break;}
		if (grid[i][j] == EMPTY) break;
	}
	// SouthWest
	for (i=y+1, j=x-1; i <= MAX_Y && j >= 0; i++, j--) {
		if (grid[i][j] == BUSY) {res++; break;}
		if (grid[i][j] == EMPTY) break;
	}
	// SouthEast
	for (i=y+1, j=x+1; i <= MAX_Y && j <= MAX_X; i++, j++) {
		if (grid[i][j] == BUSY) {res++; break;}
		if (grid[i][j] == EMPTY) break;
	}
	return res;
}

char rules1(char value, int busy_nbs) {
	if (value == EMPTY && busy_nbs == 0) return BUSY;
	if (value == BUSY  && busy_nbs >= 4) return EMPTY;
	return value;
}

char rules2(char value, int busy_nbs) {
	if (value == EMPTY && busy_nbs == 0) return BUSY;
	if (value == BUSY  && busy_nbs >= 5) return EMPTY;
	return value;
}

void conway1(char source[][COLS], char dest[][COLS]) {
	for (int y = 0; y <= MAX_Y; y++) {
		for (int x = 0; x <= MAX_X; x++) {
			dest[y][x] = rules1(source[y][x], busy_neighbors(source, y, x));
		}
	}
}

void conway2(char source[][COLS], char dest[][COLS]) {
	for (int y = 0; y <= MAX_Y; y++) {
		for (int x = 0; x <= MAX_X; x++) {
			dest[y][x] = rules2(source[y][x], busy_neighbors2(source, y, x));
		}
	}
}

int main(int argc, char *argv) {
	char source[ROWS][COLS];
	char other[ROWS][COLS];
	int iter = 0;

	copy_grid(data, source);
	while (!are_equal(source, other)) {
		if (iter % 2 == 0) {
			conway1(source, other);
		} else {
			conway1(other, source);
		}
		iter++;
	}
	printf("Part 1: %d\n", count_busy(other));


	iter = 0;
	while (!are_equal(data, other)) {
		if (iter % 2 == 0) {
			conway2(data, other);
		} else {
			conway2(other, data);
		}
		iter++;
	}
	printf("Part 2: %d\n", count_busy(other));
	return 0;
}

