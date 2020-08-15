# Adding Flags to my program
CXX=g++
CFlags=-std=c++11 -Wall -pedantic -Wno-long-long
CDebug=-g
BIN=diff
SRC=src
DOC=doc
TMPDIR=.tmp

# Directories
IH=src/InputHandling
FT=src/FileTypes
OH=src/OutputHandling

# Object Files
Objects=$(TMPDIR)/File.o\
		$(TMPDIR)/FileHandler.o\
		$(TMPDIR)/FileType.o\
		$(TMPDIR)/Text.o\
		$(TMPDIR)/Html.o\
		$(TMPDIR)/Binary.o\
		$(TMPDIR)/FileTypeHandler.o\
		$(TMPDIR)/Directory.o\
		$(TMPDIR)/OutputHandler.o\
		$(TMPDIR)/main.o

all: compile

$(BIN): $(Objects)
	$(CXX) $(CFlags) $(Objects) -o $(BIN) $(CDebug)

compile: $(BIN)

run: compile
	./$(BIN)

clean:
	rm -rf $(BIN) $(TMPDIR) $(DOC)

doc:
	doxygen $(SRC)/Doxyfile;

# Extra Functionality -- Counts the total number of lines
count:
	wc -l $(IH)/* $(FT)/* $(OH)/* | tail -1;

# Creating individual binary files and storing them in $(TMP)
$(TMPDIR)/main.o: $(SRC)/main.cpp $(OH)/OutputHandler.h
	mkdir -p $(TMPDIR);\
	$(CXX) $(CFlags) -c $(SRC)/main.cpp -o $(TMPDIR)/main.o $(CDebug) 

$(TMPDIR)/File.o: $(IH)/File.cpp $(IH)/File.h
	mkdir -p $(TMPDIR);\
	$(CXX) $(CFlags) -c $(IH)/File.cpp -o $(TMPDIR)/File.o $(CDebug)

$(TMPDIR)/FileHandler.o: $(IH)/FileHandler.cpp $(IH)/FileHandler.h $(IH)/File.h
	mkdir -p $(TMPDIR);\
	$(CXX) $(CFlags) -c $(IH)/FileHandler.cpp -o $(TMPDIR)/FileHandler.o $(CDebug)

$(TMPDIR)/FileType.o: $(FT)/FileType.cpp $(FT)/FileType.h $(FT)/Text.h $(FT)/Binary.h
	mkdir -p $(TMPDIR);\
	$(CXX) $(CFlags) -c $(FT)/FileType.cpp -o $(TMPDIR)/FileType.o $(CDebug)

$(TMPDIR)/Text.o: $(FT)/Text.cpp $(FT)/Text.h $(FT)/FileType.h
	mkdir -p $(TMPDIR);\
	$(CXX) $(CFlags) -c $(FT)/Text.cpp -o $(TMPDIR)/Text.o $(CDebug)

$(TMPDIR)/Html.o: $(FT)/Html.cpp $(FT)/Html.h $(FT)/Text.h
	mkdir -p $(TMPDIR);\
	$(CXX) $(CFlags) -c $(FT)/Html.cpp -o $(TMPDIR)/Html.o $(CDebug)

$(TMPDIR)/Binary.o: $(FT)/Binary.cpp $(FT)/Binary.h $(FT)/FileType.h
	mkdir -p $(TMPDIR);\
	$(CXX) $(CFlags) -c $(FT)/Binary.cpp -o $(TMPDIR)/Binary.o $(CDebug)

$(TMPDIR)/FileTypeHandler.o: $(FT)/FileTypeHandler.cpp $(FT)/FileTypeHandler.h $(IH)/FileHandler.h
	mkdir -p $(TMPDIR);\
	$(CXX) $(CFlags) -c $(FT)/FileTypeHandler.cpp -o $(TMPDIR)/FileTypeHandler.o $(CDebug)

$(TMPDIR)/Directory.o: $(OH)/Directory.cpp $(OH)/Directory.h $(OH)/OutputHandler.h $(IH)/FileHandler.h
	mkdir -p $(TMPDIR);\
	$(CXX) $(CFlags) -c  $(OH)/Directory.cpp -o $(TMPDIR)/Directory.o $(CDebug)

$(TMPDIR)/OutputHandler.o: $(OH)/OutputHandler.cpp $(OH)/OutputHandler.h $(FT)/FileTypeHandler.h $(IH)/FileHandler.h
	mkdir -p $(TMPDIR);\
	$(CXX) $(CFlags) -c $(OH)/OutputHandler.cpp -o $(TMPDIR)/OutputHandler.o $(CDebug)
