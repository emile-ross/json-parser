#include "header.h"

void *scalloc(struct memory_layout_node *node, size_t n, size_t size)
{
	struct memory_layout_node *last_node = NULL;

	void *ptr = NULL;
	if (size <= 0)
	{
		fprintf(stderr, "Invalid scalloc() call with size %lu\n", (unsigned long)size);
		if (node != NULL)
			sfree(node);
		exit(EXIT_FAILURE);
	}

	ptr = calloc(n, size);	/* allocate memory */
	if (ptr == NULL)
	{
		fprintf(stderr, "scalloc() fn failed to allocated memory of size %lu on the heap\n", (unsigned long)size);
		if (node != NULL)
			sfree(node);
		exit(EXIT_FAILURE);
	}

	if (node != NULL)
	{
		last_node = get_last_node(node);
		last_node->next_node = smalloc(NULL, sizeof(struct memory_layout_node));
		if (last_node->next_node == NULL)
		{
			fprintf(stderr, "smalloc() failed inside scalloc() function\n"
					"(failed to allocate memory for memory handling)\n");
			sfree(node);
			exit(EXIT_FAILURE);
		}
		last_node->next_node->allocated = True;
		last_node->next_node->ptr = ptr;
		last_node->next_node->next_node = NULL;
	}
	return ptr;	/* return pointer to buffer */
}

void *smalloc(struct memory_layout_node *node, size_t size)
{
	struct memory_layout_node *last_node = NULL;

	void *ptr = NULL;
	if (size <= 0)
	{
		fprintf(stderr, "Invalid malloc() call with size %lu\n", (unsigned long)size);
		if (node != NULL)
			sfree(node);
		exit(EXIT_FAILURE);
	}

	ptr = malloc(size);	/* allocate memory */
	if (ptr == NULL)
	{
		fprintf(stderr, "malloc() fn failed to allocated memory of size %lu on the heap\n", (unsigned long)size);
		if (node != NULL)
			sfree(node);
		exit(EXIT_FAILURE);
	}

	if (node != NULL)
	{
		last_node = get_last_node(node);
		last_node->next_node = malloc(sizeof(struct memory_layout_node));
		if (last_node->next_node == NULL)
		{
			fprintf(stderr, "malloc() failed inside smalloc() function\n"
					"(failed to allocate memory for memory handling)\n");
			sfree(node);
			exit(EXIT_FAILURE);
		}
		last_node->next_node->allocated = True;
		last_node->next_node->ptr = ptr;
		last_node->next_node->next_node = NULL;
	}
	return ptr;	/* return pointer to buffer */
}

void *srealloc(struct memory_layout_node *node, void *ptr, size_t size)
{
	struct memory_layout_node *last_node = NULL;
	struct memory_layout_node *cur = NULL;
	void *old_ptr = ptr;
	if (size <= 0)
	{
		fprintf(stderr, "Invalid realloc() call with size %lu\n", (unsigned long)size);
		sfree(node);
		exit(EXIT_FAILURE);
	}

	ptr = realloc(ptr, size);	/* allocate memory */

	if (ptr == NULL)
	{
		fprintf(stderr, "realloc() fn failed to allocated memory of size %lu on the heap\n", (unsigned long)size);
		if (node != NULL)
			sfree(node);
		exit(EXIT_FAILURE);
	}

	if (node != NULL)
	{
		for (cur = node; cur != NULL; cur = cur->next_node)
		{
			if (cur->allocated && old_ptr != NULL && cur->ptr == old_ptr)
			{
				cur->ptr = ptr;
				return ptr;
			}
		}
		last_node = get_last_node(node);
		last_node->next_node = malloc(sizeof(struct memory_layout_node));
		if (last_node->next_node == NULL)
		{
			fprintf(stderr, "malloc() failed inside realloc() function\n");
			sfree(node);
			exit(EXIT_FAILURE);
		}
		last_node->next_node->allocated = True;
		last_node->next_node->ptr = ptr;
		last_node->next_node->next_node = NULL;
	}
	return ptr;	/* return pointer to buffer */
}

/* free every single node in the linked list */
void sfree(struct memory_layout_node *node)
{
	struct memory_layout_node *cur = node;
	struct memory_layout_node *next = NULL;

	while (cur != NULL)
	{
		next = cur->next_node;

		if (cur->allocated)
		{
			free(cur->ptr);
		}
		free(cur);
		cur = next;
	}
}

struct memory_layout_node *get_last_node(struct memory_layout_node *node)
{
	struct memory_layout_node *cur = node;

	while (cur->next_node != NULL)
	{
		cur = cur->next_node;
	}
	return cur;
}
