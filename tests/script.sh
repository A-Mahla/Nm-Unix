make && rm -f t1 t2
./ft_nm /usr/bin/* >> t1 2>&1
nm /usr/bin/* >> t2 2>&1
vimdiff t1 t2
