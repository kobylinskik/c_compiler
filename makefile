parser: parser/parser.c lexer/lexer.h structures.h
	gcc -o parse parser/parser.c lexer/lexer.h structures.h