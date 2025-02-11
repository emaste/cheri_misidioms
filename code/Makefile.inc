CHERIBASE ?= ${HOME}/cheri
SSHPORT ?= 0

.PHONY: all clean

.c:
	${CC} ${CFLAGS} -o $@ $<

TARGETS = narrow narrow_realloc narrow_widen privesc privesc2 undef unrepresentable_length

all: ${TARGETS}

all-copyexec: ${TARGETS:%=copyexec-%}

copyexec-%: %
	scp -P $(SSHPORT) $< root@127.0.0.1:/root
	ssh -p $(SSHPORT) root@127.0.0.1 -t '/root/$<'

clean:
	rm -f ${TARGETS}
