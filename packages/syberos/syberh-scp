#!/usr/bin/expect

set upload_path [lindex $argv 0]

if {"$upload_path" == ""} {
  puts "Need argv: upload file path"
  exit 1
}

set timeout 1000
spawn scp $upload_path developer@192.168.100.100:/tmp
expect {
  "(yes/no)?" {send "yes\r"; exp_continue}
  "password:" {send "system\r"}
}
expect eof
