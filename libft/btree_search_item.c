/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_search_item.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 07:55:23 by mamartin          #+#    #+#             */
/*   Updated: 2021/10/03 18:39:10 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	*btree_search_item(t_btree *root, void *data_ref,
		int (*cmpf)(void *, void *))
{
	void	*item;

	if (!root)
		return (0);
	item = btree_search_item(root->left, data_ref, cmpf);
	if (item != 0)
		return (item);
	if ((*cmpf)(root->item, data_ref) == 0)
		return (root->item);
	item = btree_search_item(root->right, data_ref, cmpf);
	if (item != 0)
		return (item);
	return (0);
}
