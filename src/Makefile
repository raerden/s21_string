CC = gcc
# FLAGS = -Wall -Wextra -Werror -std=c11
FLAGS = -Werror -std=c11
SRC = misc.o s21_string.o s21_strlen.o s21_strstr.o s21_trim.o s21_strtok.o 
TEST_LIBS = -lcheck -lm -lpthread -lsubunit

all: clean main

main: $(SRC)
	$(CC) $(FLAGS) $(SRC) -o main

test: clean
	checkmk tests.check > tests.c
	$(CC) $(FLAGS) tests.c $(TEST_LIBS) -o tests
	./tests

lcov: clean
	checkmk tests.check > tests.c
	$(CC) $(FLAGS) --coverage tests.c $(TEST_LIBS) -o tests
	./tests
	lcov --directory . --capture -o coverage.info
	genhtml --output-directory report --legend coverage.info
	open report/index.html

clean:
	rm -fr report ./main ./tests tests.c *.o *.gcov *.gcda *.gcno coverage.info

mem: all
	valgrind --leak-check=full -s ./main

misc.o: misc.h misc.c
	$(CC) $(FLAGS) -c misc.c

s21_string.o: s21_string.h s21_string.c
	$(CC) $(FLAGS) -c s21_string.c

s21_strlen.o: s21_strlen.c
	$(CC) $(FLAGS) -c s21_strlen.c

s21_strstr.o: s21_strstr.c
	$(CC) $(FLAGS) -c s21_strstr.c

s21_trim.o: s21_trim.c
	$(CC) $(FLAGS) -c s21_trim.c

s21_strtok.o: s21_strtok.c
	$(CC) $(FLAGS) -c s21_strtok.c

# -I.: Указывает компилятору искать заголовочных файлов (файлов с расширением .h) в текущем каталоге (.). Это полезно, если ваши заголовочные файлы (s21_strstr.h) находятся в той же директории, что и исходные файлы .c.
# -lcheck: Сообщает компилятору (точнее, линковщику, который вызывается после компиляции) связать с вашей программой библиотеку libcheck. Библиотека check используется для написания и запуска юнит-тестов. Компилятор сам добавит -lcheck к имени библиотеки (libcheck.so или libcheck.a в зависимости от типа библиотеки).
# -lm: Сообщает линковщику связать с библиотекой libm (Math Library). Она содержит математические функции. Хотя для тестирования строк это не обязательно, иногда check или другие библиотеки могут использовать функции из libm.
# -lpthread: Сообщает линковщику связать с библиотекой libpthread (POSIX Threads). Библиотека check может использовать потоки для управления тестов, поэтому она может быть нужна. (Хотя -lcheck обычно включает -lpthread, явное указание не повредит).
# -lsubunit: Сообщает линковщику связать с библиотекой libsubunit. Это формат для передачи результатов тестов. Библиотека check имеет поддержку вывода результатов в формате Subunit. Этот флаг, скорее всего, является причиной ошибки, которую вы видите. Если библиотека check, которую вы установили, не была собрана с поддержкой Subunit, линковщик не сможет найти функции subunit_test_start, subunit_test_pass и т.д., и выдаст ошибку undefined reference. (Решение - см. предыдущий ответ).
# -o tests: Задает имя выходного исполняемого файла, который будет создан в результате компиляции и линковки. В данном случае это будет файл tests.
# Итог:

# Команда компилирует три исходных файла C (s21_strstr.c, s21_strlen.c, tests.c), использует стандарт C11, включает строгие предупреждений и преобразует их в ошибки. Она ищет заголовочные файлы в текущем каталоге и связывает полученную программу с библиотеками check, m, pthread и subunit, создавая исполняемый файл tests. Проблема, скорее всего, связана с флагом -lsubunit и версией/конфигурацией библиотеки check.