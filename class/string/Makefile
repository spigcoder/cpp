# 这里是不能有逗号的
object = test.o string.o

exe: $(object)
	@echo "正在进行链接."
	g++ -o exe $(object)

#静态模式<targets ...> : <target-pattern> : <prereq-pattern ...>
$(object): %.o: %.cpp
	@echo 正在编译 $<
	g++ -c $< -o $@

.PHONY: clean
clean:
	-rm exe $(object)
