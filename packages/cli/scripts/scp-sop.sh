#!/usr/bin/expect

set ip [lindex $argv 0]
set port [lindex $argv 1]
set sopPath [lindex $argv 2]

set timeout 1000
spawn scp -P $port $sopPath developer@$ip:/tmp
expect {
  "(yes/no)?" {send "yes\r"; exp_continue}
  "assword:" {send "system\r"}
}
expect eof