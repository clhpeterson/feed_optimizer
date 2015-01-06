#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getLine.h"

#define TRUE 1
#define FALSE 0

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


int main (int argc, char** argv)
{
	char* line = getLine (stdin);
	int N;
	int W;
	int H;
	char* where_end;
	N = strtol (line, &where_end, 10);
	W = strtol (where_end+1, &where_end, 10);
	H = strtol (where_end+1, &where_end, 10);
	free(line);
	struct Story** events = malloc (N*sizeof (struct Story*));
	int num_stories = 0;
	for (int i = 0; i < N; i++){
		line = getLine (stdin);
		if (line[0] == 'S'){
			int time = strtol (line+2, &where_end, 10);
			int score = strtol (where_end+1, &where_end, 10);
			int height = strtol (where_end+1, &where_end, 10);
			free(line);
			int id = num_stories+1;
			struct Story* new_story = malloc (sizeof (struct Story));
			new_story->id = id;
			new_story->time = time;
			new_story->score = score;
			new_story->height = height;
			events[num_stories] = new_story;
			num_stories++;
		}
		else {
			// reload event
			struct TableRow** table = malloc ((H+1)*sizeof (struct TableRow*));
			int time = strtol (line+2, &where_end, 10);
			free(line);
			int starting_id = find_starting_id (time > W ? time-W : 0, 0, num_stories-1, events);
			int num_events = num_stories-starting_id;
			struct TableRow* zero_row = malloc (sizeof (struct TableRow*));
			zero_row->values = calloc (num_events, sizeof (int));
			zero_row->total_score = 0;
			zero_row->num_ones = 0;
			char* binary_string = malloc ((num_events+1)*sizeof (char));
			for (int i = 0; i < num_events; i++){
				binary_string[i] = '0';
			}
			zero_row->binary_string = binary_string;
			table[0] = zero_row;


			// now we need to create the table. iteratively
			for (int table_row_index = 1; table_row_index < H+1; table_row_index++){
				struct TableRow* current_best = malloc_table_row (num_events);
				copy_table_row (current_best, table[i-1], num_events);
				int current_best_score = current_best->total_score;
				for (int story_id = starting_id; story_id < num_stories; story_id++){
					struct Story* story_of_interest = events[story_id];
					int height = story_of_interest->height;
					if (table_row_index-height < 0){
						continue;
					} else {
						// of_interest can possibly be added to the list
						struct TableRow* table_row_of_interest = table[table_row_index-height];
						if (table_row_of_interest->values[story_id-num_events] == 0){
							// it's not yet in the list and can be added!
							int new_best = FALSE;
							int new_total = table_row_of_interest->total_score + story_of_interest->score;
							if (new_total > current_best_score){
								new_best = TRUE;
							} else if (new_total == current_best_score){
								int old_num_ones = current_best->num_ones;
								int new_num_ones = table_row_of_interest->num_ones + 1;
								if (new_num_ones < old_num_ones){
									new_best = TRUE;
								} else if (new_num_ones == old_num_ones){
									char* temp_binary_string = malloc ((num_events+1)*sizeof (char));
									memcpy (temp_binary_string, table_row_of_interest->binary_string, (num_events+1)*sizeof (char));
									temp_binary_string[story_id-num_events] = '1';
									if (strcmp(temp_binary_string, current_best->binary_string) > 0){
										new_best = TRUE;
									}
									free (temp_binary_string);
								}
							}
							if (new_best == TRUE){
								copy_table_row (current_best, table_row_of_interest, num_events);
								current_best->total_score = new_total;
								current_best->num_ones += 1;
								current_best->values[story_id-num_events] = 1;
								current_best->binary_string[story_id-num_events] = '1';
							}
						}
					}
				}
				table[table_row_index] = current_best;
			}
			printf ("%d %d", table[H]->total_score, table[H]->num_ones);
			int* values = table[H]->values;
			for (int i = 0; i < num_events; i++){
				if (values[i] == 1){
					printf (" %d", starting_id+i);
				}
			}
			printf ("\n");
		}
	}
	return 1;
}


int find_starting_id (int lower_bound, int start_index, int end_index, struct Story** events)
{
	if (end_index < start_index){
		return start_index;
	} else {
		int midpoint = mid_point (start_index, end_index);
		int to_compare = events[midpoint]->time;
		if (to_compare < lower_bound){
			// need to go right
			return find_starting_id (lower_bound, midpoint+1, end_index, events);
		} else if (to_compare > lower_bound){
			// need to go left
			return find_starting_id (lower_bound, start_index, midpoint-1, events);
		} else {
			return midpoint;
		}
	}
}

int mid_point (int start, int end)
{
	return start+((end-start)/2);
}

struct TableRow* malloc_table_row (int num_values)
{
	struct TableRow* to_return = malloc (sizeof (struct TableRow));
	int* new_values = malloc (num_values*sizeof (int));
	char* new_binary_string = malloc ((num_values+1)*sizeof (char));
	to_return->values = new_values;
	to_return->binary_string = new_binary_string;
	return to_return;
}

void copy_table_row (struct TableRow* to_copy, struct TableRow* to_return, int num_values)
{
	memcpy (to_return, to_copy, sizeof (struct TableRow));
	memcpy (to_return->values, to_copy->values, num_values*sizeof (int));
	memcpy (to_return->binary_string, to_copy->binary_string, (num_values+1)*sizeof (char));
}

