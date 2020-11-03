#!/usr/bin/expect

set ip [lindex $argv 0]
set port [lindex $argv 1]
set sopid [lindex $argv 2]
set appid [lindex $argv 3]

set timeout 1000
spawn ssh -p $port developer@$ip "sdk-invoker 0 $sopid:$appid:uiapp"
expect {
  "(yes/no)?" {send "yes\r"; exp_continue}
  "?assword:" {send "system\r"}
}
interact {         
  timeout 60 {send "\x20"} 
}
expect eof
