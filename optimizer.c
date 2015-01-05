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
	int score;
	int* values;
};

int main (int argc, int* argv)
{
	char* line = getLine (stdin);
	int N;
	int W;
	int H;
	char* where_end;
	N = strtol (line, &where_end, 10);
	W = strtol (where_end+1, &where_end, 10);
	H = strtol (where_end+1, &where_end, 10);
	struct Story** events = malloc (N*sizeof (struct Story*));
	int num_stories = 0;
	for (int i = 0; i < N; i++){
		line = getLine (stdin);
		if (line[0] == 'S'){
			int time = strtol (line+2, &where_end, 10);
			int score = strtol (line+1, &where_end, 10);
			int height = strtol (line+1, &where_end, 10);
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
			struct TableRow** table = malloc (H*sizeof (struct TableRow*));
			int time = strtol (line+2, &where_end, 10);
			// need to figure out what story id to start looking from
			// write separate function
			// binary search? yes.
			// need to figure out story id with smallest time such that 
			// time is greater than or equal to time-W. know you've found
			// it if events[id]->time >= time-W but events[id-1]->time < time-W
			int starting_id = find_starting_id (time-W, 0, num_stories-1, events);
		}
	}
}


int find_starting_id (int lower_bound, int start_index, int end_index, struct Story** events)
{
	if (end_index < start_index){
		return start_index;
	} else {
		int midpoint = midpoint (start_index, end_index);
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

int midpoint (int start, int end)
{
	return start+((end-start)/2);
}








