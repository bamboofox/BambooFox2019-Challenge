#!/bin/bash

echo "FLAG{aaaaaaaaaaaaaaaaaaaaa}" > flag1
echo "FLAG{bbbbbbbbbbbbbbbbbbbbb}" > flag2
chmod 0400 flag2
sudo chown root:root .
sudo chmod +s read_flag

sudo apt install apparmor apparmor-utils -y
sudo aa-autodep `pwd`/read_flag
sudo aa-enforce `pwd`/read_flag

