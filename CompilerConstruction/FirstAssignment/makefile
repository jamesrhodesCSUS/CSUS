all: Parser Scanner AST ST
	gcc BabyC.tab.o lex.yy.o driver.o ast.o symbol_table.o -o bcc

AST: ast.o driver.o

Scanner: BabyC.lex
	flex BabyC.lex
	gcc -c lex.yy.c

ST: symbol_table.o

Parser: BabyC.y
	bison -d BabyC.y
	gcc -c BabyC.tab.c

%.o: %.c
	gcc -c $<
