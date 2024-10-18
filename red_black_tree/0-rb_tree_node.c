#include "rb_tree.h"


/**
 * rb_tree_node - create a new node with given values
 * @parent: new node parent
 * @value: new node value
 * @color: new node color
 *
 * Return: create node or NULL on error
 */
rb_tree_t *rb_tree_node(rb_tree_t *parent, int value, rb_color_t color)
{
	rb_tree new_node = malloc(sizeof(rb_tree));
	if (!new_node)
	{
		printf("Memory error :(");
		return (NULL);
	}

	new_node->parent = parent;
	new_node->n = value;
	new_node->color = color;

	return (new_node);
}


