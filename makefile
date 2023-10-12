sales:
	gcc -o sales.out sales.c 
	./sales.out ./ex.txt

clean-sales:
	rm ./sales.out ./sales_report.txt

clean:
	make clean-sales