all: gwd

gwd:
	g++ ./pgd.cpp -o ./pgd

install: gwd
	sudo mv ./pgd /usr/local/bin/pgd