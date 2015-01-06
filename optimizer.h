#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Story
{
	int id;
	int time;
	int score;
	int height;
};

struct TableRow
{
	int total_score;
	int* values;
	int num_ones;
	char* binary_string;
};


int mid_point (int start, int end);
int find_starting_id (int lower_bound, int start_index, int end_index, struct Story** events);
struct TableRow* malloc_table_row (int num_values);
void copy_table_row (struct TableRow* to_copy, struct TableRow* to_return, int num_values);
