#!/usr/bin/expect

set ip [lindex $argv 0]
set port [lindex $argv 1]
set sopid [lindex $argv 2]
set sopFilename [lindex $argv 3]

set timeout 1000
spawn ssh -p $port developer@$ip "/usr/bin/ins-tool -siu /tmp/$sopFilename && rm -f /tmp/$sopFilename"
expect {
  "(yes/no)?" {send "yes\r"; exp_continue}
  "assword:" {send "system\r"}
}
expect eof