#include "shell.h"

/**
 * add_node -A function that adds a node at the beginning of the list
 * @hd: @ of the pointer to the head node
 * @sr: string domain of node
 * @nm: node index
 *
 * Return: size of list
 */
list_t *add_node(list_t **hd, const char *sr, int nm)
{
	list_t *New_head;

	if (!hd)
		return (NULL);
	New_head = malloc(sizeof(list_t));
	if (!New_head)
		return (NULL);
	_memset_func((void *)New_head, 0, sizeof(list_t));
	New_head->nm = nm;
	if (sr)
	{
		New_head->sr = _str_dupl(sr);
		if (!New_head->sr)
		{
			free(New_head);
			return (NULL);
		}
	}
	New_head->next = *hd;
	*hd = New_head;
	return (New_head);
}

/**
 * add_node_end -A function that adds a node at the End of the linked list
 * @hd: double pointer
 * @sr: string domain of node
 * @nm: node index
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **hd, const char *sr, int nm)
{
	list_t *New_node, *node;

	if (!hd)
		return (NULL);

	node = *hd;
	New_node = malloc(sizeof(list_t));
	if (!New_node)
		return (NULL);
	_memset_func((void *)New_node, 0, sizeof(list_t));
	New_node->nm = nm;
	if (sr)
	{
		New_node->sr = _str_dupl(sr);
		if (!New_node->sr)
		{
			free(New_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = New_node;
	}
	else
		*hd = New_node;
	return (New_node);
}

/**
 * print_list_str -A function that prints only the string elements
 * @p: The pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *p)
{
	size_t j = 0;

	while (p)
	{
		_put_input(p->sr ? p->sr : "(null)");
		_put_input("\n");
		p = p->next;
		j++;
	}
	return (j);
}

/**
 * delete_node_at_index -A function that deletes a given index node
 * @hd: @ of pointer to first node
 * @index: index of node that is going to be deleted delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **hd, unsigned int index)
{
	list_t *node, *previous_node;
	unsigned int j = 0;

	if (!hd || !*hd)
		return (0);

	if (!index)
	{
		node = *hd;
		*hd = (*hd)->next;
		free(node->sr);
		free(node);
		return (1);
	}
	node = *hd;
	while (node)
	{
		if (j == index)
		{
			previous_node->next = node->next;
			free(node->sr);
			free(node);
			return (1);
		}
		j++;
		previous_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list -A function that frees all nodes of a linked list
 * @hd_ptr: @ of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **hd_ptr)
{
	list_t *node, *Next_node, *hd;

	if (!hd_ptr || !*hd_ptr)
		return;
	hd = *hd_ptr;
	node = hd;
	while (node)
	{
		Next_node = node->next;
		free(node->sr);
		free(node);
		node = Next_node;
	}
	*hd_ptr = NULL;
}

