#  Libft - Printf, Getline and 50+ Utility Functions

![mybadge](https://badgen.net/badge/SKILLS/%20C,%20LIBC,%20LINKED%20LISTS%20/blue?scale=1.2)

#### Extended Implemented C Library with Printf, Getline and 50+ Utility Functions.

🔧 System Requirements:
   - Operating System: Unix-based OS
   - Software: [make](https://www.gnu.org/software/make/), [gcc](https://gcc.gnu.org/)

## Usage
 
To run the command, open your terminal and follow these steps:

  - To create ```libft.a```:
  
      ```shell
      (cd /path/to/project/directory && make)
      ```

   - To compile with ```libft.a```:
  
      ```shell
      (cd /path/to/project/directory && make)
      gcc -o a.out *.o -I </path/to/project/directory>/libft/includes -L /path/to/project/directory -lft
      ```

<br>

## Functions

<br>

### Ft_printf :

   ```C
   # include "ft_printf.h"
   ```

   - [`ft_printf`](libft/ft_printf/ft_printf.c#L112) - ```int	ft_printf(const char *format, ...);```
   - [`ft_dprintf`](libft/ft_printf/ft_dprintf.c#L71) - ```int	ft_dprintf(int fd, const char *format, ...);```

      Types conversions :
        -  [`%c`](libft/ft_printf/ft_print_str_char.c#L22) print a single character.
        -  [`%s`](libft/ft_printf/ft_print_str_char.c#L76) print a string of characters.
        -  [`%p`](libft/ft_printf/ft_print_ptr_pct.c#L44) The void * pointer argument is printed in hexadecimal
        -  [`%d`](libft/ft_printf/ft_print_int.c#L70) print a decimal (base 10) number.
        -  [`%i`](libft/ft_printf/ft_print_int.c#L70) print an integer in base 10.
        -  [`%u`](libft/ft_printf/ft_print_uint.c#L41) print an unsigned decimal (base 10) number.
        -  [`%x`](libft/ft_printf/ft_print_hex.c#L67) print a number in lowercase hexadecimal (base 16).
        -  [`%X`](libft/ft_printf/ft_print_hex.c#L67) print a number in uppercase hexadecimal (base 16).
        -  [`%%`](libft/ft_printf/ft_print_ptr_pct.c#L68) print a percent sign.

      Flag directives (use them between '%' character and the type conversion):
        - [`-`](https://learn.microsoft.com/en-us/cpp/c-runtime-library/format-specification-syntax-printf-and-wprintf-functions?view=msvc-170#flags) left align the result within the given field width.
        - [`+`](https://learn.microsoft.com/en-us/cpp/c-runtime-library/format-specification-syntax-printf-and-wprintf-functions?view=msvc-170#flags) use a sign (+ or -) to prefix the output value if it's of a signed type.
        - [`#`](https://learn.microsoft.com/en-us/cpp/c-runtime-library/format-specification-syntax-printf-and-wprintf-functions?view=msvc-170#flags) When it's used with the o, x, or X format, the # flag uses 0, 0x, or 0X, respectively.
        - [`0`](https://learn.microsoft.com/en-us/cpp/c-runtime-library/format-specification-syntax-printf-and-wprintf-functions?view=msvc-170#flags) If width is prefixed by 0, leading zeros are added until the minimum width is reached.
        - [`blank (' ')`](https://learn.microsoft.com/en-us/cpp/c-runtime-library/format-specification-syntax-printf-and-wprintf-functions?view=msvc-170#flags) use a blank to prefix the output value if it's signed and positive.
        - [`.`](https://learn.microsoft.com/en-us/cpp/c-runtime-library/format-specification-syntax-printf-and-wprintf-functions?view=msvc-170#precision) the precision specification
        - [`\<number\>`](https://learn.microsoft.com/en-us/cpp/c-runtime-library/format-specification-syntax-printf-and-wprintf-functions?view=msvc-170#width) the width specification field.


<br>
   
### Ft_getline :

   ```C
   # include "ft_getline.h"
   ```

   - [`ft_getline`](libft/ft_getline/ft_getline.c#L15) - ```char	*ft_getline(int fd);```

<br>

### Others Functions :

```C
# include "ft_libft.h"
```

#### Functions from `<ctype.h>` library

* [`ft_isascii`](libft/ft_isascii.c)			- test for ASCII character.
* [`ft_isalnum`](libft/ft_isalnum.c)			- alphanumeric character test.
* [`ft_isalpha`](libft/ft_isalpha.c)			- alphabetic character test.
* [`ft_isdigit`](libft/ft_isdigit.c)			- decimal-digit character test.
* [`ft_isprint`](libft/ft_isprint.c)			- printing character test (space character inclusive).
* [`ft_tolower`](libft/ft_tolower.c)			- upper case to lower case letter conversion.
* [`ft_toupper`](libft/ft_toupper.c)			- lower case to upper case letter conversion.

#### Functions from `<stdlib.h>` library

* [`ft_atoi`](libft/ft_atoi.c)		- convert ASCII string to integer.
* [`ft_calloc`](libft/ft_calloc.c)	- memory allocation.

#### Functions from `<string.h>` library

* [`ft_bzero`](libft/ft_bzero.c)		- write zeroes to a byte string.
* [`ft_memset`](libft/ft_memset.c)		- write a byte to a byte string.
* [`ft_memchr`](libft/ft_memchr.c)		- locate byte in byte string.
* [`ft_memcmp`](libft/ft_memcmp.c)		- compare byte string.
* [`ft_memmove`](libft/ft_memmove.c)	- copy byte string.
* [`ft_memcpy`](libft/ft_memcpy.c)		- copy memory area.
* [`ft_strlen`](libft/ft_strlen.c)				- find length of string.
* [`ft_strchr`](libft/ft_strchr.c)				- locate character in string (first occurrence).
* [`ft_strrchr`](libft/ft_strrchr.c)			- locate character in string (last occurence).
* [`ft_strnstr`](libft/ft_strnstr.c)			- locate a substring in a string (size-bounded).
* [`ft_strncmp`](libft/ft_strncmp.c)			- compare strings (size-bounded).
* [`ft_strdup`](libft/ft_strdup.c)				- save a copy of a string (with malloc).
* [`ft_strcat`](libft/ft_strcat.c)		- concatenate strings (s2 into s1).
* [`ft_strncat`](libft/ft_strncat.c)	- concatenate strings (s2 into s1, size-bounded).
* [`ft_strlcpy`](libft/ft_strlcpy.c)			- size-bounded string copying.
* [`ft_strlcat`](libft/ft_strlcat.c)			- size-bounded string concatenation.

#### Non-standard functions

* [`ft_putchar_fd`](libft/ft_putchar_fd.c)		- output a character to given file.
* [`ft_putstr_fd`](libft/ft_putstr_fd.c)		- output string to given file.
* [`ft_putendl_fd`](libft/ft_putendl_fd.c)		- output string to given file with newline.
* [`ft_putnbr_fd`](libft/ft_putnbr_fd.c)		- output integer to given file.
* [`ft_itoa`](libft/ft_itoa.c)					- convert integer to ASCII string.
* [`ft_substr`](libft/ft_substr.c)				- extract substring from string.
* [`ft_strtrim`](libft/ft_strtrim.c)			- trim beginning and end of string with the specified characters.
* [`ft_strjoin`](libft/ft_strjoin.c)			- concatenate two strings into a new string (with malloc).
* [`ft_split`](libft/ft_split.c)				- split string, with specified character as delimiter, into an array of strings.
* [`ft_strmapi`](libft/ft_strmapi.c)			- create new string from modifying string with specified function.

#### Linked list functions

* [`ft_lstnew`](libft/ft_lstnew.c)				- create new list.
* [`ft_lstsize`](libft/ft_lstsize.c)			- count elements of a list.
* [`ft_lstlast`](libft/ft_lstlast.c)			- find last element of list.
* [`ft_lstadd_back`](libft/ft_lstadd_back.c)	- add new element at end of list.
* [`ft_lstadd_front`](libft/ft_lstadd_front.c)	- add new element at beginning of list.
* [`ft_lstdelone`](libft/ft_lstdelone.c)		- delete element from list.
* [`ft_lstclear`](libft/ft_lstclear.c)			- delete sequence of elements of list from a starting point.
* [`ft_lstiter`](libft/ft_lstiter.c)			- apply function to content of all list's elements.
* [`ft_lstmap`](libft/ft_lstmap.c)				- apply function to content of all list's elements into new list.
