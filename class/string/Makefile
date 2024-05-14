# 这里是不能有逗号的
object = test.o string.o

exe:$(object)
	g++ -o exe $(object)

test.o:string.h
string.o:string.h

.PHONY: clean
clean:
	rm exe $(object)
