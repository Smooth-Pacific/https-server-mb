PROJECT     = https-server

BIN         = Bin
SERVER      = Server

all: utopia-server

.PHONY: $(SERVER)
utopia-server: $(BIN) $(SERVER)
	cd $(SERVER) && make release
	cp $(SERVER)/Bin/utopia-server.exe ./Bin/utopia-server.exe

.PHONY: $(BIN)
$(BIN):
	mkdir -p $@

clean:
	cd Server && make clean
	rm -fr Bin/*

extra-clean:
	cd Server && make extra-clean
	rm -fr Bin
