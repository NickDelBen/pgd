all: gwd

gwd:
	g++ ./pgd.cpp -o ./pgd

install: gwd
	sudo cp ./pgd /usr/local/bin/pgd
