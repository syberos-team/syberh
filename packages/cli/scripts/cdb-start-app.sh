#!/usr/bin/expect

set cdbPath [lindex $argv 0]
set cdbDevice [lindex $argv 1]
set sopid [lindex $argv 2]
set appid [lindex $argv 3]

set timeout 1000

spawn $cdbPath -s $cdbDevice shell
expect {
  "developer@" {
    send "exit\r"
    spawn $cdbPath -s $cdbDevice shell "sdk-invoker 0 $sopid:$appid:uiapp"
  }
  "root@" {
    send "su install\r"
    expect "install@" {send "sdk-invoker 0 $sopid:$appid:uiapp\r"}
  }
  
}
expect eof
