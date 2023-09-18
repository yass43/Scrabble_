# Macros
CC = gcc
CFLAGS = -std=c99 --pedantic -Wall -Wextra -Wmissing-prototypes

ALL = sb_list sb_hash sb_trie sb_fast

# Object files
%.o: %.c $(wildcard *.h)
	$(CC) $(CFLAGS) -c -o $@ $<

# Executables
all: $(ALL)

sb_list: main.o LinkedList.o ListScrabble.o
sb_hash: main.o LinkedList.o HashTable.o DictScrabble.o
sb_trie: main.o LinkedList.o Trie.o DictScrabble.o
sb_fast: main.o LinkedList.o Trie.o TrieScrabble.o

$(ALL):
	$(CC) $(CFLAGS) -o $@ $^

# Phony
.PHONY: all clean run

clean:
	rm -f $(ALL) *.o

run: $(ALL)
	./sb_list
	./sb_hash
	./sb_trie
	./sb_fast
