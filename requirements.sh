#!/bin/bash -e
# Install all pcl (https://github.com/PointCloudLibrary/pcl) deps.
# Verified on Ubuntu 16.04.4.

# Install ubuntu packages
sudo apt-get update -y

sudo apt-get install cmake git wget libeigen3-dev libflann-dev libvtk5-dev libboost-all-dev libusb-1.0-0-dev libqhull-dev libpcap0.8-dev -y

# Install metslib 0.5.3
wget http://www.coin-or.org/download/source/metslib/metslib-0.5.3.tgz
tar zxvf metslib-0.5.3.tgz
cd metslib-0.5.3/
./configure
make -j9
sudo make install
cd ..
rm -rf metslib-0.5.3*

echo "Done installing pcl deps"

git clone https://github.com/PointCloudLibrary/pcl.git
cd pcl
mkdir build
cd build
cmake ..
make -j2
sudo make -j2 install
cd ..
rm -rf pcl

echo "Done installing pcl"

git clone https://github.com/strawlab/python-pcl.git
cd python-pcl
pip install --upgrade pip
pip install cython==0.25.2
pip install numpy

python setup.py build_ext -i
python setup.py install

echo "Done installing pcl python"


