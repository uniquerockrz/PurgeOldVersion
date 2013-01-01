all:
	gcc -Wall PurgeOldVersion.c -o PurgeOldVersion

prefix=/usr/local
    
install: PurgeOldVersion
	install -m 0755 PurgeOldVersion $(prefix)/bin
  
    .PHONY: install
