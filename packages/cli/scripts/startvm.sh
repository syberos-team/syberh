#!/bin/bash

EMULATOR_DIR=$1
PORT=$2

echo "PORT=$PORT"
if [ "x$2" = "x" ];then
  PORT="5555"
fi


isEmulatorRunning(){
  PID=`pgrep "emulator-x86"`
  if [ "x$PID" = "x" ];then
    return 0
  fi
  return 1
}


isEmulatorRunning
if [ $? -eq 1 ];then
  echo "vm is running"
  exit 0
fi


$EMULATOR_DIR/emulator-x86 "--skin-args" "width=720" "height=1280" "skin.path=$EMULATOR_DIR/skin_conf" "--qemu-args" "-cpu" "qemu64,+ssse3" "-drive" "file=$EMULATOR_DIR/vm-sda.vdi" "-M" "maru-x86-machine" "-m" "2048" "-show-cursor" "-enable-vigs" "-vigs-backend" "gl" "-enable-yagl" "-yagl-backend" "vigs" "-device" "virtio-esm-pci" "-device" "virtio-evdi-pci" "-device" "virtio-keyboard-pci" "-device" "maru-brightness" "-device" "virtio-hwkey-pci" "-device" "virtio-nfc-pci" "-device" "virtio-power-pci" "-device" "virtio-touchscreen-pci,max_point=10" "-device" "virtio-sensor-pci,sensors=accel&geo&gyro&light&proxi" "-device" "virtio-jack-pci,jacks=earjack&charger&usb" "-L" "$EMULATOR_DIR/pc-bios" "-vga" "none" "-kernel" "$EMULATOR_DIR/bzImage" "-boot" "c" "-append" "root=/dev/sda1 console=ttyS0 video=LVDS-1:720x1280-32@60 dpi=2330 ip=10.0.2.16::10.0.2.2:255.255.255.0::eth0:none vm_name=syberos  rootfstype=ext4" "-serial" "stdio" "-net" "user,dhcpstart=10.0.2.16,hostfwd=tcp::$PORT-:22,hostfwd=tcp::10000-:10000,hostfwd=tcp::10001-:10001" "-rtc" "base=utc" "-net" "nic,model=virtio,macaddr=34:17:EB:B0:27:85" "-enable-kvm" &> /dev/null &
echo "startting vm..."

while true 
do
  nport=`echo ""|telnet localhost $PORT 2>/dev/null|grep "\^]"|wc -l`
  if [ $nport -eq 1 ];then
    sleep 5

    isEmulatorRunning
    if [ $? -eq 1 ];then
      echo "vm started!"
      exit 1
    else
      echo "vm startup failed!"
      exit 2
    fi
  fi
  sleep 2
done
