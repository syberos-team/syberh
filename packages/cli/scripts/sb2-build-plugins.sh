#!/usr/bin/expect

set password [lindex $argv 0]
set processNum [lindex $argv 1]
set kchrootPath [lindex $argv 2]
set targetName [lindex $argv 3]
set proPathes [lindex $argv 4]
set qmakeArgs [lindex $argv 5]

set proPathList [split $proPathes ,]

set timeout -1

spawn $kchrootPath "sb2 -t $targetName -R"

expect {
  "sudo" {
    send "$password\r"; exp_continue
  }
  "*" {
    for {set i 0} {$i < [llength $proPathList]} {incr i} {
        set proPath [lindex $proPathList  $i]
        send "/usr/lib/qt5/bin/qmake $proPath -r -spec linux-g++ $qmakeArgs && /usr/bin/make -j$processNum \r"
    }
    send "exit\r"
  }
}
expect eof
