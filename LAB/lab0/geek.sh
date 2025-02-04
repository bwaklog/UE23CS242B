cd cmds
ls
pwd
(
  mkdir temp1
  mkdir temp1
  rmdir empty_folder
)
mv file1.txt Documents/
touch new_file.txt
cp file1.txt file2.txt
mv file1.txt Documents
rm old_file.txt
chmod 644 file.txt
chown user:group file.txt
ln -s target_file symlink
cat file1.txt file2.txt
head file.txt
tail file.txt
more file.txt
less file.txt
diff file1.txt file2.txt
patch file.txt < changes.diff
ps aux
top
kill <pid>
pkill -9 firefox
killall -9 firefox
renice -n 10 <pid>
nice -n 10 command
pstree
pgrep firefox
jobs
bg <job_id>
fg <job_id>
nohup command &
disown <job_id>
grep "error" logfile.txt
sed 's/old_string/new_string/g' file.txt
awk '{print $1, $3}' data.csv
ping google.com
traceroute google.com
nslookup google.com
dig google.com
host google.com
whois google.com
ssh username@hostname
scp file.txt username@hostname:/path/
ftp hostname
telnet hostname
netstat -tuln
ifconfig
iwconfig wlan0
route -n
arp -a
ss -tuln
hostname
mtr google.com
df -h
du -sh /path/to/directory
crontab -e
