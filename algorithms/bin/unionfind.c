#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct union_state {
	int num_components;
	int num_ids;
	int *ids;
	int *sizes;
};

typedef struct union_state * union_state_p;

struct union_algorithm
{
	int (*_connected)(union_state_p, int, int);
	void (*_connect)(union_state_p, int, int);
};

typedef struct union_algorithm * union_algorithm_p;

// quick find

int qf_find(union_state_p state, int p)
{
	return state->ids[p];
}

int qf_connected(union_state_p state, int p, int q)
{
	return qf_find(state, p) == qf_find(state, q);
}

void qf_connect(union_state_p state, int p, int q)
{
	// ids of p and q
	int pid = qf_find(state, p);
	int qid = qf_find(state, q);

	// if they're already part of the same component do nothing
	if(pid == qid)
	{
		return;
	}

	// set all pid and qid's equal
	for(int i = 0 ; i < state->num_ids; i++)
	{
		if(state->ids[i] == pid)
		{
			state->ids[i] = qid;
		}
	}

	// we got a component
	state->num_components--;
}

// quick union
int qu_find(union_state_p state, int p)
{
	while(p != state->ids[p])
	{
		p = state->ids[p];
	}

	return p;
}

void qu_connect(union_state_p state, int p, int q)
{
	int i = qu_find(state, p);
	int j = qu_find(state, q);

	if(i == j)
	{
		return;
	}

	state->ids[i] = j;

	state->num_components--;
}

int qu_connected(union_state_p state, int p, int q)
{
	return qu_find(state, p) == qu_find(state, q);
}

// weighted quick union

void wqu_connect(union_state_p state, int p, int q)
{
	int i = qu_find(state, p);
	int j = qu_find(state, q);

	if(i == j)
	{
		return;
	}

	if(state->sizes[i] < state->sizes[j])
	{
		state->ids[i] = j;
		state->sizes[j] += state->sizes[i];
	}
	else
	{
		state->ids[j] = i;
		state->sizes[i] += state->sizes[j];
	}

	state->num_components--;
}

union_state_p run_union(union_algorithm_p algorithm, char *filename)
{	
	printf("processing file: %s\n", filename);

	FILE *handle = fopen(filename, "rt");

	if (handle == NULL)
	{
		perror ("Error opening file");
		return NULL;
	}

	union_state_p state = (union_state_p)calloc(1, sizeof(struct union_state));
	fscanf(handle, "%d", &state->num_ids);
	printf("reading num sites: %d\n", state->num_ids);

	state->ids = calloc(state->num_ids, sizeof(int));
	state->sizes = calloc(state->num_ids, sizeof(int));
	state->num_components = state->num_ids;
	
	for(int i = 0 ; i < state->num_ids ; i++)
	{
		state->ids[i] = i;
		state->sizes[i] = 1;
	}

	int p = 0;
	int q = 0;
	while(fscanf(handle, "%d %d", &p, &q) > 0)
	{
		if(algorithm->_connected(state, p, q))
		{
			continue;
		}

		algorithm->_connect(state, p, q);
	}

	fclose(handle);
	return state;
}

void free_union_state(union_state_p state)
{
	free(state->ids);
	free(state);
}

union_algorithm_p create_quick_find()
{
	union_algorithm_p algo = (union_algorithm_p)malloc(sizeof(struct union_algorithm));
	algo->_connect = qf_connect;
	algo->_connected = qf_connected;
	return algo;
}

union_algorithm_p create_quick_union()
{
	union_algorithm_p algo = (union_algorithm_p)malloc(sizeof(struct union_algorithm));
	algo->_connect = qu_connect;
	algo->_connected = qu_connected;
	return algo;
}

union_algorithm_p create_weighted_quick_union()
{
	union_algorithm_p algo = (union_algorithm_p)malloc(sizeof(struct union_algorithm));
	algo->_connect = wqu_connect;
	algo->_connected = qu_connected;
	return algo;
}

union_algorithm_p create_algorithm(char *name)
{
	if(strncmp(name, "qf", 5) == 0)
	{
		return create_quick_find();
	}
	else if(strncmp(name, "qu", 5) == 0)
	{
		return create_quick_union();
	}
	else if(strncmp(name, "wqu", 5) == 0)
	{
		return create_weighted_quick_union();
	}
	else
	{
		return NULL;
	}
}

int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		printf("Usage: ./unionfind quickfind <filename>\n");
		return 1;
	}

	char *algorithm_name = argv[1];
	char *filename = argv[2];

	union_algorithm_p algorithm = create_algorithm(algorithm_name);
	if(algorithm == NULL)
	{
		printf("unknown algorithm: %s\n", algorithm_name);
		return 1;
	}

	union_state_p state = run_union(algorithm, filename);

	if(state == NULL)
	{
		printf("couldn't create state\n");
		return 1;
	}

	printf("Found %d components\n", state->num_components);
	
	free_union_state(state);
	free(algorithm);

	return 0;
}