
vmc: mc.c
	${CC} -o vmc mc.c

clean:
	rm -f vmc
	@echo "All clean!"