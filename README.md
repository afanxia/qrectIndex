# qrectIndex
Rectangle index based on implicit geohashed quadtree. Fast and efficient detection of rectangle overlaps.

1. prerequisites: GCC 4.7+
	how to install (CentOS):
		wget http://people.centos.org/tru/devtools-1.1/devtools-1.1.repo -O /etc/yum.repos.d/devtools-1.1.repo
		yum install devtoolset-1.1-gcc devtoolset-1.1-binutils devtoolset-1.1-gcc-c++
2. how to compile:
		scl enable devtoolset-1.1 bash
		g++ -std=c++0x -o overlaps *.cpp
		exit
3. execution:
	usage:
		overlaps <input> - takes a json file with the specified format
		
		

