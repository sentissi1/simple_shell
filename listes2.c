#include "shell.h"

/**
 * list_length -A function that gives the length of linked list
 * @p: pointer to first node
 *
 * Return: size of list
 */
size_t list_length(const list_t *p)
{
	size_t j = 0;

	while (p)
	{
		p = p->next;
		j++;
	}
	return (j);
}

/**
 * list_to_str -A  function that returns an array of strings of the linked list
 * @hd: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_str(list_t *hd)
{
	list_t *node = hd;
	size_t x = list_length(hd), y;
	char **strs;
	char *str;

	if (!hd || !x)
		return (NULL);
	strs = malloc(sizeof(char *) * (x + 1));
	if (!strs)
		return (NULL);
	for (x = 0; node; node = node->next, x++)
	{
		str = malloc(_strlen(node->sr) + 1);
		if (!str)
		{
			for (y = 0; y < x; y++)
				free(strs[y]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->sr);
		strs[x] = str;
	}
	strs[x] = NULL;
	return (strs);
}


/**
 * print_list -A function that prints all elements of a list_t linked list
 * @p: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *p)
{
	size_t count = 0;

	while (p)
	{
		_put_input(convert_num(p->nm, 10, 0));
		_putchar(':');
		_putchar(' ');
		_put_input(p->sr ? p->sr : "(null)");
		_put_input("\n");
		p = p->next;
		count++;
	}

	return (count);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = begin_func(node->sr, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index -A function that gets the index of a node
 * @hd: pointer to list head
 * @nde: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *hd, list_t *nde)
{
	size_t j = 0;

	while (hd)
	{
		if (hd == nde)
			return (j);
		hd = hd->next;
		j++;
	}
	return (-1);
}

