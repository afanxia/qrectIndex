# qrectIndex
Rectangle index based on implicit geohashed quadtree. Fast and efficient detection of rectangle overlaps.

Prerequisites: GCC 4.7+

I. How to install (CentOS):
		1. wget http://people.centos.org/tru/devtools-1.1/devtools-1.1.repo -O /etc/yum.repos.d/devtools-1.1.repo
		2. yum install devtoolset-1.1-gcc devtoolset-1.1-binutils devtoolset-1.1-gcc-c++
II. How to compile:
		1. scl enable devtoolset-1.1 bash
		2. g++ -std=c++0x -o overlaps *.cpp
		3. exit
III. How to execute:
	usage: overlaps <input> - takes a json file with list of rectangles under "rects" defined as (x,y,w,h)
		
		

