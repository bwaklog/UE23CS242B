#!/bin/sh

run() {
  echo "% $1"
  eval "$1"
}

run "mkdir cmds"

(
  run "cd cmds/"
  run "ls"
  run "pwd"
  run "mkdir temp1"
  run "mkdir temp2"
  run "ls"
  run "rmdir temp1"
  run "rmdir temp2"
  run "ls"
)

(
  cd cmds
  run 'echo "foo bar" > temp.txt'
  run 'echo temp.txt'
  run 'mkdir files'
  run 'mv temp.txt files/'

  sleep 2

  run 'cat files/temp.txt > file1.txt'
  run 'cat file1.txt'
  run 'cp file1.txt file2.txt'
  run 'ls'
  run 'rm file2.txt'
  run 'ls'

  run 'chmod 644 file1.txt'

  run 'ls -l'
  run 'chown grogu:everyone file1.txt'
  run 'ls -l'

  run 'mkdir sym'
  run 'ln -s file1.txt sym/'
  run 'ls -l sym/'
)

(
  run 'cd cmds'
  run 'mv files/temp.txt .'
  run 'rm -rf file* sym'
  run 'ls'

  run 'head temp.txt'
  run 'tail temp.txt'
  run 'more temp.txt'
  run 'more temp.txt'
)

# head file.txt
# tail file.txt
# more file.txt
# less file.txt
# diff file1.txt file2.txt
# patch file.txt < changes.diff
# ps aux
# top
# kill <pid>
# pkill -9 firefox
# killall -9 firefox
# renice -n 10 <pid>
# nice -n 10 command
# pstree
# pgrep firefox
# jobs
# bg <job_id>
# fg <job_id>
# nohup command &
# disown <job_id>
# grep "error" logfile.txt
# sed 's/old_string/new_string/g' file.txt
# awk '{print $1, $3}' data.csv
# ping google.com
# traceroute google.com
# nslookup google.com
# dig google.com
# host google.com
# whois google.com
# ssh username@hostname
# scp file.txt username@hostname:/path/
# ftp hostname
# telnet hostname
# netstat -tuln
# ifconfig
# iwconfig wlan0
# route -n
# arp -a
# ss -tuln
# hostname
# mtr google.com
# df -h
# du -sh /path/to/directory
# crontab -e

rm -rf cmds
