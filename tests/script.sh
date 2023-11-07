make && rm -f t1 t2 && ./ft_nm /usr/bin/node >> t1 2>&1 && nm /usr/bin/node >> t2 2>&1 && vimdiff t1 t2

