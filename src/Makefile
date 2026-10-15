MAKEFLAGS += -r
.PHONY: all clean extern
.SUFFIXES: .c .o .d
SRC := $(shell find . -path ./src -prune -o -type f -name "*.c" -print)
OBJ := $(patsubst %.c, %.o, $(SRC))
DEP := $(patsubst %.c, %.d, $(SRC))

EXT := cmacs.h
WGET := wget -qc --show-progress -t 3 --waitretry=3

CFLAGS ?= -O3 -fno-plt -pipe -flto=auto
CFLAGS += -D_GNU_SOURCE=1 -D_REENTRANT -pthread -fwrapv -fms-extensions -Wall -Wvla -Wno-parentheses -Wno-microsoft -I$(CURDIR) -I$(CURDIR)/extern -I$(CURDIR)/include
LDFLAGS ?= -Wl,-O1
LDFLAGS += -L$(CURDIR)/lib
LDLIBS += -lm -lpthread

all: main

main: $(OBJ)
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $@

%.o: %.c
	$(COMPILE.c) $< -o $@

clean:
	$(RM) -- $(OBJ) $(DEP) main

-include $(DEP)
%.d: %.c $(EXT)
	$(COMPILE.c) -MM $< -o $@

extern: $(EXT)
	install -d $@

cmacs.h:
	@$(WGET) -O $@ https://raw.github.com/ArcanusNEO/cmacs/master/cmacs.h || ($(RM) $@ && false)

.SECONDARY: $(OBJ)
