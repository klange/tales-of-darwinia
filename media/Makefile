.PHONY: all clean deploy

all: build build/logo.png

build:
	mkdir build

clean:
	@rm -f build/*

deploy: build/logo.png
	cp build/logo.png ../data/logo.png

build/logo.png: build/_bg.png build/_logo.png
	composite build/_logo.png build/_bg.png build/logo.png

build/_bg.png: bridge.png
	convert bridge.png -blur 0x3 build/_bg.png

build/_logo.png: tales_of_darwinia.svg
	convert -background None tales_of_darwinia.svg -resize 256x192\> -alpha on build/_logo.png

