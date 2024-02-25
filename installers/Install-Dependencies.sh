#!/bin/bash

sudo apt update -y && sudo apt upgrade -y
sudo apt-get install -y libtins-dev libpcap-dev libssl-dev cmake || sudo apt-get install -y libtins-dev libpcap-dev libssl-dev cmake --fix-missing
sudo ldconfig