sales:
	gcc -o sales.out sales.c 
	./sales.out ./ex.txt

nfl:
	gcc -o nfl.out nfl.c
	./nfl.out

clean-sales:
	[ ! -e ./sales.out ] || rm ./sales.out 
	[ ! -e ./sales_report.txt  ] || rm ./sales_report.txt

clean-nfl:
	[ ! -e ./nfl.out ] || rm ./nfl.out

clean:
	make clean-sales
	make clean-nfl
