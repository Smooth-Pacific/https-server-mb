PROJECT     = https-server

SERVER      = Server
CLIENT      = Client

BIN         = Bin

all: $(SERVER) $(CLIENT)

.PHONY: server
$(SERVER): $(BIN)
	cd $(SERVER) && make
	cp $(SERVER)/Bin/server.exe ./Bin/server.exe

.PHONY: client
$(CLIENT): $(BIN)
	cd $(CLIENT) && make
	cp $(CLIENT)/Bin/client.exe ./Bin/client.exe

$(BIN):
	mkdir -p $@

clean:
	cd server && make clean
	cd client && make clean
	rm -fr Bin/*

extra-clean:
	cd server && make extra-clean
	cd client && make extra-clean
	rm -fr Bin
