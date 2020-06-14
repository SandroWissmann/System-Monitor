.PHONY: format
format:
	#clang-format src/* include/* -i
	find -iname *.h -o -iname *.cpp | xargs clang-format -i