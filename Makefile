PROJECT     = https-server

BIN         = Bin
SERVER      = Server

all: $(SERVER)

.PHONY: server
$(SERVER): $(BIN)
	cd $(SERVER) && make
	cp $(SERVER)/Bin/utopia-server.exe ./Bin/utopia-server.exe

$(BIN):
	mkdir -p $@

clean:
	cd server && make clean
	rm -fr Bin/*

extra-clean:
	cd server && make extra-clean
	rm -fr Bin
