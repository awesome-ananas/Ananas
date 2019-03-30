CC = gcc
CCFLAG = -Wall --std=c11
PROGRAM = ananas
SRC_PATH = src
OBJ_PATH = obj

SRC = $(foreach x, $(SRC_PATH), $(wildcard $(addprefix $(x)/*,.c*)))
OBJ = $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

default: $(OBJ)
	$(CC) $(CCFLAG) -o $(PROGRAM) $(OBJ)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c*
	$(CC) $(CCFLAG) -c -o $@ $<

.PHONY: clean
clean:
	rm $(OBJ_PATH)/*.o ananas