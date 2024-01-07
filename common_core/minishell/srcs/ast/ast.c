/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:13:06 by hradoux           #+#    #+#             */
/*   Updated: 2023/03/14 18:27:13 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*					CREATE TREE
 *	créé un AST (arbre synthaxique abstrait) binaire:
 *	c'est une liste chaînée ou chaque node (root dans n'autre cas)
 *	va pouvoir pointer sur 2 nodes (ou roots) et non 1 dans une liste
 *	chainée "classique".
 *	Logique d'éxecution de cette fonction:
 *	- 	lis un str en son entier et retient l'index du dernier && || | rencontré
 *		sachant qu'il y a une precedence entre les symbols : && || < |
 *		donc on veut split d'abord en fonction de && et || puis |
 *	-	dans son "split", les ()) sont prises en compte, mais manque les " et '
 *	Donc pour l'instant, chaque root contient simplement un str correspondant
 *	-	commencant au symbol trouvé si c'est un || && ou |
 *	-	commencant au debut du mot, commande, redirection, fichier si cest pas
 *		une oprande relationnelle (&& || |)
 *	Petit Bonus dans mon AST, les enfants ont un pointer sur l'adresse de
 *	leur pere, permettant ainsi de se déplacer librement dans "l'arbre"
 */

#include "minishell.h"

void	tree_prcdnc(t_tree *root, char *tmp, int index, int prcdnc)
{
	if (!prcdnc)
	{
		root->input = ft_strdup(tmp);
		root->left = NULL;
		root->right = NULL;
	}
	else if (prcdnc > 9)
	{
		root->input = ft_substr_minishell(tmp, index, prcdnc % 3);
		root->left = create_tree(ft_substr_minishell(tmp, 0, index), root);
		root->right = create_tree \
			(ft_substr_minishell(tmp, index + prcdnc % 3, ft_strlen(tmp)
					- (index + prcdnc % 3)), root);
	}
	else
	{
		root->input = ft_substr_brkt_2(tmp, index);
		root->left = create_tree(ft_substr_brkt(tmp, index), root);
		root->right = NULL;
	}
}

void	precedence_modolu3(t_tree *root, char *tmp)
{
	printf("not_bash: parse error near : `%c'\n", *tmp);
	g_status = 258;
	free(root);
}

int	tmp_null(t_tree *father, char *tmp)
{
	if (!tmp || !*tmp)
	{
		printf("not_bash: parse error near : `%s'\n", father->input);
		g_status = 258;
		return (SUCCESS);
	}
	return (ERROR);
}

int	ft_scandale_create_tree(t_tree *root, char *tmp, int index, int prcdnc)
{
	if ((prcdnc % 3) == (int) strlen(tmp))
	{
		precedence_modolu3(root, tmp);
		return (ERROR);
	}
	if (index == -1)
	{
		free(root);
		return (ERROR);
	}
	return (SUCCESS);
}

t_tree	*create_tree(void *input, t_tree *father)
{
	t_tree	*root;
	int		index;
	int		prcdnc;
	char	*tmp;

	root = ft_calloc(sizeof(t_tree), 1);
	if (!root)
		return (NULL);
	tmp = (char *)input;
	if (tmp_null(father, tmp) == SUCCESS)
		return (NULL);
	index = precedence(tmp, &prcdnc);
	if (ft_scandale_create_tree(root, tmp, index, prcdnc) == ERROR)
		return (NULL);
	tree_prcdnc(root, tmp, index, prcdnc);
	root->father = father;
	free(input);
	return (root);
}
