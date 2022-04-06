/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzima <lzima@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:31:41 by lzima             #+#    #+#             */
/*   Updated: 2022/01/11 16:21:47 by lzima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

/**
 * @brief
 * get_next_line
 * 
 * Calling your function get_next_line in a loop will then allow you to read 
 * the text available on the file descriptor one line at a time until the end 
 * of it.
 * 
 * @param
 * File descriptor to read from
 * example: test.txt 
 * 
 * @return
 * Read line: correct behavior
 * (null): nothing else to read or an error occurred
 * 
 * @fn 
 * get_next_line.c
 * 	Write a function which returns a line read from a file descriptor
 * 
 * get_next_line_utils.c
 * 	Useful fonctions from libft
 * 
 * @see
 * 
 * Mandatory part from subject:
 * 
 * • Repeated calls (e.g., using a loop) to your get_next_line() function 
 *  should let you read the text file pointed to by the file descriptor, 
 *  one line at a time.
 * 
 * • Your function should return the line that was read.
 * 	If there is nothing else to read or if an error occurred, it should return NULL.
 * 
 * • Make sure that your function works as expected both when reading a file and 
 * 	when reading from the standard input.
 * 
 * • Please note that the returned line should include the terminating 
 *  '\n' character, except if the end of file was reached and does not end 
 *  with a '\n' character.
 * 
 * • Your header file get_next_line.h must at least contain the prototype of the
 * 	get_next_line() function.
 * 
 * • Add all the helper functions you need in the get_next_line_utils.c file.
 * 
 * @see
 * 
 * Keyterms:
 * 
 * 	fd = file descriptor 0=input ; 1=output ; 2=error ; 3=fd
 * 	BUFFER_SIZE = temporary memory allocation, it's like a waiting room for data
 *  read() = with read, once we use it, we can't go back into what have been readed.
 * 
 * @see
 * 
 * Concept:
 * 
 * All the work of get_next_line is in the change of BUFFER_SIZE.
 * This variable could change and the fonction needs to be resist.
 * 
 * For example: our test.txt is 2 lines = Hello\nWorld\0 (without space)
 * 
 * BUFFER_SIZE will determine how many bytes will be ENOUGH.
 * ___________________________________________________________________________
 * 
 ** 1st case: BUFFER_SIZE = 6
 * 1st read: Hello\n
 * 	return ("Hello\n\0");
 * 2nd read: World\0
 * 	return ("World\0");
 * 3rd read: -
 * 	return ("null");
 * 
 * In this case: BUFFER_SIZE was 6, as much as a line have.
 * Our @fn SEE_THE_MATRIX readed Hello\n, save it into static string
 * and our @fn THE_ONE, found a '\n' at the end of the static string 
 * and return it. Nothing remains between two calls of GNL.
 * _______________________________________________________________________
 * 
 ** 2nd case: BUFFER_SIZE = 5
 * 			 01234	
 * 1st read: Hello
 * 			 0 1234
 * 2nd read: \nWorl
 * 			 0 1
 * 3rd read: d\0
 *
 * In this case : @fn SEE_THE_MATRIX read Hello, but didn't find a '\n'.
 * So, we need to save Hello into a static string (strjoin).
 * 2nd read : read \nWorl then save it to the static string. We find a '\n'
 * in the static string : "Hello\nWorl". So our @fn THE_ONE will :
 * 1 - search for '\n' and dup from the static string, in a new string 
 * 		"Hello\n" and will return it with NEO_LINE.
 * 2 - from the index pointed at '\n', THE_ONE will dup from the static, what
 * 		remains after '\n', so "Worl", to save it for the next call of GNL.
 * 3 - the next time we call get_next_line, it will remember "Worl", and launch
 * 		again @fn SEE_THE_MATRIX. It will read again.
 * >> back to 
 * 1 - @fn SEE_THE_MATRIX search for '\n' by read BUFFER_SIZE 5. 
 * 		It will find only "d\0", so : 
 * 		it didn't read enough bytes, and will activate our switch, 
 * 		named "enough". And save "d/0" in the static string where remain "Worl". 
 * 		So now, static string is : "World\0".
 * 2 - @fn THE_ONE will go though the static string until '\0', and give us our 
 * 		index i : it will be used to dup until '\0' into a new string NEO_LINE 
 * 		and then return it.
 * 
*/
//__________________________________________________________________________ 
// dedicated fonctions

void	see_the_matrix(char **statik, int fd);
// read fd and save it into STATIK

char	*the_one(char **statik);
// return line

char	*get_next_line(int fd);
// call see_the_matrix and the_one
// handle error of fd and free static string (STATIK) and NEO_LINE

//__________________________________________________________________________ 
// libft

char	*ft_strchr(const char *s, int c);
// looks for \n
char	*ft_strjoin(char *s1, char const *s2);
// join read bytes and previews read in a static char
char	*ft_substr(char const *s, unsigned int start, size_t len);
// dup from static string to return a line as requested
// dup from static string to save into static string what remains
char	*ft_strdup(char *s1);
// initialise static string with a \0;
int		ft_strlen(const char *str);
// used in ft_substr to get len of the static string

#endif