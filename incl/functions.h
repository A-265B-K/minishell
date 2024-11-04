/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   functions.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ebayat <ebayat@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/25 12:30:07 by ebayat        #+#    #+#                 */
/*   Updated: 2024/11/04 15:06:17 by alkuijte      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H


void 	run_program(t_program *program_data);
void	init_program(t_program *program_data, char **envp);
void	get_user_input(t_program *program_data);

/* -------------------------------------------------------------------------- */
/*                                  Executing                                 */
/* -------------------------------------------------------------------------- */
void	execute_command(t_program *program_data);

// minishell_exit
void	minishell_exit(t_program *program_data);

/* -------------------------------------------------------------------------- */
/*                              Input Processing                              */
/* -------------------------------------------------------------------------- */
void	process_input(t_program *program);


/* -------------------------------------------------------------------------- */
/*                                 Tokenizing                                 */
/* -------------------------------------------------------------------------- */
void	tokenize(t_token *tokens);
t_token	*new_node(char *str);
t_token	*minishell_split(char *str);
void	add_to_back(t_token *node, char *str);

// is_token
int	is_operator_token(char *token);
int	is_redirect_token(char *token);

#endif