CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11
TARGET = main
SRC = s21_strlen.c s21_strstr.c
TEST_LIBS = -lcheck -lm -lpthread
TEST_SRC = tests.c

$(TARGET):
	$(CC) $(FLAGS) $(SRC) -o $(TARGET)

test:
	$(CC) $(FLAGS) $(SRC) $(TEST_SRC) -I. $(TEST_LIBS) -o tests
	./tests

clean:
	rm -f $(TARGET) ./tests