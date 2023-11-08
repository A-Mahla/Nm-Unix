make && rm -f output_custom_nm output_libc_nm
./ft_nm /usr/bin/* >> output_custom_nm 2>&1
nm /usr/bin/* >> output_libc_nm 2>&1
./ft_nm /usr/lib/* >> output_custom_nm 2>&1
nm /usr/lib/* >> output_libc_nm 2>&1
./ft_nm /usr/games/* >> output_custom_nm 2>&1
nm /usr/games/* >> output_libc_nm 2>&1
./ft_nm /usr/include/* >> output_custom_nm 2>&1
nm /usr/include/* >> output_libc_nm 2>&1
./ft_nm `find /usr/lib32 | grep -v '\.a$' | xargs`  >> output_custom_nm 2>&1
nm `find /usr/lib32 | grep -v '\.a$' | xargs`  >> output_libc_nm 2>&1
./ft_nm `find /usr/lib64 | grep -v '\.a$' | xargs`  >> output_custom_nm 2>&1
nm `find /usr/lib64 | grep -v '\.a$' | xargs`  >> output_libc_nm 2>&1
./ft_nm /usr/libexec/* >> output_custom_nm 2>&1
nm /usr/libexec/* >> output_libc_nm 2>&1
./ft_nm `find /usr/libx32 | grep -v '\.a$' | xargs`  >> output_custom_nm 2>&1
nm `find /usr/libx32 | grep -v '\.a$' | xargs`  >> output_libc_nm 2>&1
./ft_nm /usr/sbin/* >> output_custom_nm 2>&1
nm /usr/sbin/* >> output_libc_nm 2>&1
./ft_nm `find /usr/local | grep -v '\.a$' | xargs`  >> output_custom_nm 2>&1
nm `find /usr/local | grep -v '\.a$' | xargs`  >> output_libc_nm 2>&1
vimdiff output_custom_nm output_libc_nm
