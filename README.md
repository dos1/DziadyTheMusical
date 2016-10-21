### Dziady The Musical

Dependences (for Debian-based distros):

	sudo apt install liballegro5.2 liballegro-ttf5.2 liballegro-image5.2 liballegro-audio5.2 liballegro-acodec5.2

The game uses CMake as build system, so its building process is pretty typical.

Building dependences:

	sudo apt install liballegro5-dev liballegro-ttf5-dev liballegro-image5-dev liballegro-audio5-dev liballegro-acodec5-dev
	git submodule init
	git submodule update

Compilation:

	mkdir build; cd build
	cmake ..
	make

Running (from top directory):

	build/src/dziadythemusical

Installation (as root):

	make install

https://github.com/dos1/DziadyTheMusical/

Written by Sebastian Krzyszkowiak <dos@dosowisko.net> for Game Jam w Teatrze 2016

Dziady The Musical uses libsuperderpy engine: https://github.com/dos1/libsuperderpy/
