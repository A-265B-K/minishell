/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_token.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ebayat <ebayat@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/26 14:42:31 by ebayat        #+#    #+#                 */
/*   Updated: 2024/10/20 16:52:01 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"


int	is_operator_token(char *token);
int	is_redirect_token(char *token);

int	is_operator_token(char *token)
{
	if (strlen(token) == 1)
	{
		if (!strcmp(token, ";") || !strcmp(token, "&") || !strcmp(token, "|"))
			return (1);
		if (!strcmp(token, ">") || !strcmp(token, "<"))
			return (1);
	}
	if (strlen(token) == 2)
	{
		if (!strcmp(token, "&&") || !strcmp(token, "||"))
			return (2);
		if (!strcmp(token, ">>") || !strcmp(token, "<<"))
			return (2);
	}

	return (0);
}

int	is_redirect_token(char *token)
{
	if (strlen(token) == 1)
		if (!strcmp(token, ">") || !strcmp(token, "<"))
			return (1);
	if (strlen(token) == 2)
		if (!strcmp(token, ">>") || !strcmp(token, "<<"))
			return (2);

	return (0);
}

// ? '&' and ';' are not actually required by the subject. Double check needed.
// ? Should this also check for other operator tokens that we don't use?

// // TEST
// int main(void)
// {
// 	char str1[] = "&";
// 	char str2[] = "&&";
// 	char str3[] = "&&&";

// 	char str4[] = "b&";
// 	char str5[] = "bee|t";

// 	if (is_operator_token(str1))
// 		printf("1. true\n");
// 	if (is_operator_token(str2))
// 		printf("2. true\n");
// 	if (is_operator_token(str3))
// 		printf("3. true\n");
// 	if (is_operator_token(str4))
// 		printf("4. true\n");
// 	if (is_operator_token(str5))
// 		printf("5. true\n");


// }