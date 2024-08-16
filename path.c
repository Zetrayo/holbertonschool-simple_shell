#include "shell.h"

/**
 * add_node_end - adds a new node at the end of a list_t list
 * @head: pointer to pointer to our linked list
 * @str: pointer to string in previous first node
 * Return: address of the new element/node
 */
list_path *add_node_end(list_path **head, char *str)
{
	list_path *tmp;
	list_path *new;

	new = malloc(sizeof(list_path));
	if (!new || !str)
	{
		return (NULL);
	}
	new->dir = str;
	new->p = '\0';
	if (!*head)
	{
		*head = new;
	}
	else
	{
		tmp = *head;
		while (tmp->p)
		{
			tmp = tmp->p;
		}
		tmp->p = new;
	}
	return (*head);
}

/**
 * path_buffer - searches for the PATH
 * @path: its the path
 * Return: returns a singly linked list with the path
 */

list_path *linkpath(char *path)
{
	list_path *head = '\0';
	char *token;
	char *cpath = strdup(path);

	token = strtok(cpath, ":");
	while (token)
	{
		head = add_node_end(&head, token);
		token = strtok(NULL, ":");
	}

	return (head);
}
