#!/usr/bin/make -f

# General settings
CFLAGS = -g -std=c99 -Wall -Wextra -pedantic -O0 # Do not touch these flags! 
LDFLAGS = -lm # Mathematical library support
OUTPUT = project
SRC = $(wildcard *.c)

# Directories for input/output operations
IMG_DIR=images
PRED_DIR=output
TEST_DIR=test

# Examples of parameters to give to your program
PARAM1  = --input_filename $(IMG_DIR)/11215-8.pgm --output_filename $(PRED_DIR)/11215-8.pgm --x_0 50 --y_0 75
PARAM3  = $(PARAM1) --reject_criterion 0.5
PARAM4  = $(PARAM3)
PARAM5  = $(PARAM4) --min_size 3
PARAM6  = $(PARAM5) --max_size 40
PARAM7  = $(PARAM6)
PARAM8  = $(PARAM7) --w 1.0
PARAM9  = $(PARAM8)
PARAM10 = $(PARAM9) --s_x 10 --s_y 10
PARAM11 = $(PARAM9) --ns_map $(PRED_DIR)/ns_map.png
PARAM12 = $(PARAM11) --graph $(PRED_DIR)/graph.dot
PARAM13 = $(PARAM12)
PARAM14 = # TODO: Specify the parameters 

$(OUTPUT): $(SRC)
	gcc -o $(OUTPUT) $(SRC) $(CFLAGS) $(LDFLAGS)
	
launch: $(OUTPUT)
	@mkdir -p $(PRED_DIR)
	./project --question 1 $(PARAM1)
	./project --question 3 $(PARAM3)
	./project --question 4 $(PARAM4)
	./project --question 5 $(PARAM5)
	./project --question 6 $(PARAM6)
	./project --question 7 $(PARAM7)
	./project --question 8 $(PARAM8)
	./project --question 9 $(PARAM9)
	./project --question 10 $(PARAM10)
	./project --question 11 $(PARAM11)
	./project --question 12 $(PARAM12)
	./project --question 13 $(PARAM13)
	./project --question 14 $(PARAM14)
	
check: $(OUTPUT)
	@mkdir -p $(TEST_DIR)
	@mkdir -p $(PRED_DIR)
	valgrind ./project --question 1 $(PARAM1) 2> $(TEST_DIR)/question1.val_chk
	valgrind ./project --question 3 $(PARAM3) 2> $(TEST_DIR)/question3.val_chk
	valgrind ./project --question 4 $(PARAM4) 2> $(TEST_DIR)/question4.val_chk
	valgrind ./project --question 5 $(PARAM5) 2> $(TEST_DIR)/question5.val_chk
	valgrind ./project --question 6 $(PARAM6) 2> $(TEST_DIR)/question6.val_chk
	valgrind ./project --question 7 $(PARAM7) 2> $(TEST_DIR)/question7.val_chk
	valgrind ./project --question 8 $(PARAM8) 2> $(TEST_DIR)/question8.val_chk
	valgrind ./project --question 9 $(PARAM9) 2> $(TEST_DIR)/question9.val_chk
	valgrind ./project --question 10 $(PARAM10) 2> $(TEST_DIR)/question10.val_chk
	valgrind ./project --question 11 $(PARAM11) 2> $(TEST_DIR)/question11.val_chk
	valgrind ./project --question 12 $(PARAM12) 2> $(TEST_DIR)/question12.val_chk
	valgrind ./project --question 13 $(PARAM13) 2> $(TEST_DIR)/question13.val_chk
	valgrind ./project --question 14 $(PARAM13) 2> $(TEST_DIR)/question14.val_chk
	
clean:
	rm -f $(OUTPUT) *.o $(TEST_DIR)/*.val_chk
	
.PHONY: clean launch check
