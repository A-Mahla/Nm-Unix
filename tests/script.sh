#!/bin/bash

rm -rf tests/output
mkdir -p tests/output


moving_ellipsis() {
    local pid=$1
    local message=$2
    local i=1
    while kill -0 $pid &>/dev/null; do
        case $i in
            1) echo -en "$message.\e[0m  " ;;
            2) echo -en "$message..\e[0m " ;;
            3) echo -en "$message...\e[0m" ;;
        esac
        sleep 1
        ((i = (i % 3) + 1))
        echo -en "\r"
    done
}

run_test() {
    local command="$1"
    local directory="$2"
    local custom_output="tests/output/output_custom_nm"
    local libc_output="tests/output/output_libc_nm"

    if [ -e "$directory" ]; then
        echo -e "\n\e[1mRunning nm on files in \e[93m$directory\e[0m\e[0m\n---------------------------------"

        (./ft_nm $command > $custom_output 2>&1) &
        local custom_pid=$!
        moving_ellipsis $custom_pid "\rCustom nm:  \e[94mRunning"
        echo -e "\rCustom nm:  \e[32mCompleted\e[0m"

        (nm $command > $libc_output 2>&1) &
        local libc_pid=$!
        moving_ellipsis $custom_pid "\rSystem nm:  \e[94mRunning"
        echo -e "\rSystem nm:  \e[32mCompleted\e[0m"


        wait $custom_pid
        local custom_exit_code=$?
        wait $libc_pid
        local libc_exit_code=$?


        echo -e "\nComparing custom nm and system nm output:"
        if diff -q "$custom_output" "$libc_output" &>/dev/null && [ "$libc_exit_code" -eq "$custom_exit_code" ] ; then
            echo -e "\e[32mStatus: Succeeded\e[0m"
        else
            diff --unified=3 "$custom_output" "$libc_output" > tests/output/diff_output
			echo "Custom nm exit_code: $custom_exit_code" >> tests/output/diff_output
			echo "System nm exit_code: $libc_exit_code" >> tests/output/diff_output
            echo -e "\e[31mStatus: Failed\e[0m\n"
            echo -e "\e[33mDiff or exit code between custom nm and system nm output for /usr/bin are not the same !"
            echo -e "For more details, check the files in /tests/output.\e[0m"
            exit 1
        fi
    else
        echo -e "\n\e[33mSkipping tests for $directory - Directory not found\e[0m"
    fi
}


# Run the tests
echo -e "\n\e[1;44m\e[97m Automated NM Tests \e[0m\n"

run_test "/usr/bin/docker" "/usr/bin/docker"
run_test "/usr/bin/node" "/usr/bin/node"
run_test "`find /usr/bin | grep -v '/usr/bin/docker\|/usr/bin/node'  | xargs`" "/usr/bin"
run_test "/usr/lib/*" "/usr/lib"
run_test "`find /usr/games | xargs`" "/usr/games"
run_test "`find /usr/include | xargs`" "/usr/include"
run_test "`find /usr/lib32 | grep -v '\.a$' | xargs`" "/usr/lib32"
run_test "`find /usr/lib64 | grep -v '\.a$' | xargs `" "/usr/lib64"
run_test "`find /usr/libx32 | grep -v '\.a$' | xargs`" "/usr/libx32"
run_test "`find /usr/sbin | xargs`" "/usr/sbin"
run_test "`find /usr/local | grep -v '\.a$' | xargs`" "/usr/local"


echo -e "\n\e[1mAll tests completed\e[0m"



