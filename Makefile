DED_FLAGS_WINDOWS =	-Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline \
					-Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum \
					-Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual \
					-Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 \
					-Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor \
					-Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing \
					-Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

DED_FLAGS_LINUX = -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations \
				  -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts \
				  -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal \
				  -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op \
				  -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self \
				  -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 \
				  -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override \
				  -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast \
				  -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast \
				  -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow \
				  -flto-odr-type-merging -fno-omit-frame-pointer -Wlarger-than=81920 -Wstack-usage=8192 -pie -fPIE -Werror=vla \
				  -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

MODE ?=

UNAME_S := $(shell uname -s)

ifeq ($(OS), Windows_NT)
	FLAGS = $(DED_FLAGS_WINDOWS) -ITreeMemStruct
else
	FLAGS = $(DED_FLAGS_LINUX) -ITreeMemStruct
endif

all: ExecutableFiles/front_end



ExecutableFiles/front_end: ObjectFiles/FrontEnd/FrontEnd.o \
						   ObjectFiles/FrontEnd/LexicalAnalysis.o ObjectFiles/FrontEnd/my_stack.o \
						   ObjectFiles/FrontEnd/Tree.o            ObjectFiles/FrontEnd/TreeDump.o ObjectFiles/FrontEnd/SyntaxAnalysis.o \
						   ObjectFiles/Instruments.o
	@ g++ $(FLAGS) $(MODE) ObjectFiles/FrontEnd/FrontEnd.o \
						   ObjectFiles/FrontEnd/LexicalAnalysis.o ObjectFiles/FrontEnd/my_stack.o \
						   ObjectFiles/FrontEnd/Tree.o            ObjectFiles/FrontEnd/TreeDump.o ObjectFiles/FrontEnd/SyntaxAnalysis.o \
						   ObjectFiles/Instruments.o -o ExecutableFiles/front_end

#               FRONT_END
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
ObjectFiles/FrontEnd/FrontEnd.o: FrontEnd/FrontEnd.cpp FrontEnd/FrontEnd.h  FrontEnd/FrontEndTypes.h
	@ g++ $(FLAGS) $(MODE) -c FrontEnd/FrontEnd.cpp -o ObjectFiles/FrontEnd/FrontEnd.o


# LEXICAL ANALYZE
#~~~~~~~~~~~~~~~~~#
ObjectFiles/FrontEnd/my_stack.o: FrontEnd/LexicalAnalyze/StackMemStruct/my_stack.cpp \
								 FrontEnd/LexicalAnalyze/StackMemStruct/my_stack.h \
								 FrontEnd/FrontEndTypes.h
	@ g++ $(FLAGS) $(MODE) -c FrontEnd/LexicalAnalyze/StackMemStruct/my_stack.cpp -o ObjectFiles/FrontEnd/my_stack.o

ObjectFiles/FrontEnd/LexicalAnalysis.o: FrontEnd/LexicalAnalyze/LexicalAnalysis.cpp \
										FrontEnd/LexicalAnalyze/LexicalAnalysis.h \
										FrontEnd/FrontEndTypes.h
	@ g++ $(FLAGS) $(MODE) -c FrontEnd/LexicalAnalyze/LexicalAnalysis.cpp -o ObjectFiles/FrontEnd/LexicalAnalysis.o
#~~~~~~~~~~~~~~~~~#

# SYNTAX ANALYZE
#~~~~~~~~~~~~~~~~#
ObjectFiles/FrontEnd/Tree.o: FrontEnd/SyntaxAnalyze/TreeMemStruct/Tree.cpp \
							 FrontEnd/SyntaxAnalyze/TreeMemStruct/Tree.h \
							 FrontEnd/SyntaxAnalyze/TreeMemStruct/TreeBase.h
	@ g++ $(FLAGS) $(MODE) -c FrontEnd/SyntaxAnalyze/TreeMemStruct/Tree.cpp -o ObjectFiles/FrontEnd/Tree.o

ObjectFiles/FrontEnd/TreeDump.o: FrontEnd/SyntaxAnalyze/TreeMemStruct/TreeDump.cpp \
								 FrontEnd/SyntaxAnalyze/TreeMemStruct/TreeDump.h \
								 FrontEnd/SyntaxAnalyze/TreeMemStruct/Tree.h \
								 FrontEnd/SyntaxAnalyze/TreeMemStruct/TreeBase.h
	@ g++ $(FLAGS) $(MODE) -c FrontEnd/SyntaxAnalyze/TreeMemStruct/TreeDump.cpp -o ObjectFiles/FrontEnd/TreeDump.o

ObjectFiles/FrontEnd/SyntaxAnalysis.o: FrontEnd/SyntaxAnalyze/SyntaxAnalysis.cpp \
									   FrontEnd/SyntaxAnalyze/SyntaxAnalysis.h \
									   FrontEnd/FrontEndTypes.h
	@ g++ $(FLAGS) $(MODE) -c FrontEnd/SyntaxAnalyze/SyntaxAnalysis.cpp -o ObjectFiles/FrontEnd/SyntaxAnalysis.o
#~~~~~~~~~~~~~~~~#
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#




ObjectFiles/Instruments.o: Instruments/Instruments.cpp Instruments/Instruments.h
	@ g++ $(FLAGS) $(MODE) -c Instruments/Instruments.cpp -o ObjectFiles/Instruments.o



clean:
	rm ObjectFiles/FrontEnd/*.o   ObjectFiles/MiddleEnd/*.o  \
	   ObjectFiles/BackEnd/*.o    ExecutableFiles/front_end  \
	   ObjectFiles/*.o            ExecutableFiles/middle_end \
	   ExecutableFiles/back_end
