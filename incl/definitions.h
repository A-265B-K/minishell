/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   definitions.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ebayat <ebayat@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/25 12:30:07 by ebayat        #+#    #+#                 */
/*   Updated: 2024/11/04 14:08:34 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINITIONS_H
# define DEFINITIONS_H

typedef struct s_token t_token ;

enum e_token_type
{
	OPERATOR,
	REDIRECTION_OPERATOR,
	COMMAND
};

typedef struct s_program
{
	const char	*prompt_symbol;
	char		**envp;
	char		*user_input;
	t_token		*tokens;

	int			fd_in;
	int			fd_out;
}	t_program;

struct s_token
{
	char		*data;
	uint8_t		token_type;

	int			fd_in;
	int			fd_out;

	t_token		*next;
	t_token		*previous;
};


#endif