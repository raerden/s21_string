#ifndef S21_STRING_H
#define S21_STRING_H

#include <stdarg.h>  // для обработки неизвестного количества аргументов
#include <stdbool.h>  // для true/false
#include <stdlib.h>  // для работы с динамической памятью

#define S21_NULL (void*)0
typedef unsigned long int s21_size_t;

void* s21_memchr(const void* str, int c,
                 s21_size_t n);  // Выполняет поиск первого вхождения символа c
                                 // (беззнаковый тип) в первых n байтах строки,
                                 // на которую указывает аргумент str
int s21_memcmp(const void* str1, const void* str2,
               s21_size_t n);  // Cравнивает первые n байтов str1 и str2
void* s21_memcpy(void* dest, const void* src,
                 s21_size_t n);  // Копирует n символов из src в dest
void* s21_memset(
    void* str, int c,
    s21_size_t n);  // Копирует символ c (беззнаковый тип) в первые n символов
                    // строки, на которую указывает аргумент str

char* s21_strncat(
    char* dest, const char* src,
    s21_size_t n);  // Добавляет строку, на которую указывает src, в конец
                    // строки, на которую указывает dest, длиной до n символов
char* s21_strchr(
    const char* str,
    int c);  // Выполняет поиск первого вхождения символа c (беззнаковый тип) в
             // строке, на которую указывает аргумент str
int s21_strncmp(
    const char* str1, const char* str2,
    s21_size_t n);  // Сравнивает не более первых n байтов str1 и str2
char* s21_strncpy(char* dest, const char* src,
                  s21_size_t n);  // Копирует до n символов из строки, на
                                  // которую указывает src, в dest

s21_size_t s21_strcspn(
    const char* str1,
    const char* str2);  // Вычисляет длину начального сегмента str1, который
                        // полностью состоит из символов, не входящих в str2
char* s21_strerror(
    int errnum);  // Выполняет поиск во внутреннем массиве номера ошибки errnum
                  // и возвращает указатель на строку с сообщением об ошибке.
                  // Нужно объявить макросы, содержащие массивы сообщений об
                  // ошибке для операционных систем mac и linux. Описания ошибок
                  // есть в оригинальной библиотеке. Проверка текущей ОС
                  // осуществляется с помощью директив
s21_size_t s21_strlen(const char* str);  // Вычисляет длину строки str, не
                                         // включая завершающий нулевой символ
char* s21_strpbrk(
    const char* str1,
    const char* str2);  // Находит первый символ в строке str1, который
                        // соответствует любому символу, указанному в str2
char* s21_strrchr(
    const char* str,
    int c);  // Выполняет поиск последнего вхождения символа c (беззнаковый тип)
             // в строке, на которую указывает аргумент str
char* s21_strstr(
    const char* haystack,
    const char* needle);  // Находит первое вхождение всей строки needle (не
                          // включая завершающий нулевой символ), которая
                          // появляется в строке haystack
char* s21_strtok(char* str, const char* delim);  // Разбивает строку str на ряд
                                                 // токенов, разделенных delim

int s21_sprintf(char* str, const char* format, ...);
int s21_sscanf(const char* str, const char* format, ...);

void* s21_to_upper(
    const char* str);  // Возвращает копию строки (str), преобразованной в
                       // верхний регистр. В случае какой-либо ошибки следует
                       // вернуть значение NULL.
void* s21_to_lower(
    const char* str);  // Возвращает копию строки (str), преобразованной в
                       // нижний регистр. В случае какой-либо ошибки следует
                       // вернуть значение NULL.
void* s21_insert(
    const char* src, const char* str,
    s21_size_t
        start_index);  // Возвращает новую строку, в которой указанная строка
                       // (str) вставлена в указанную позицию (start_index) в
                       // данной строке (src). В случае какой-либо ошибки
                       // следует вернуть значение NULL.
void* s21_trim(
    const char* src,
    const char*
        trim_chars);  // Возвращает новую строку, в которой удаляются все
                      // начальные и конечные вхождения набора заданных символов
                      // (trim_chars) из данной строки (src). В случае
                      // какой-либо ошибки следует вернуть значение NULL.

// Макросы для определения операционной системы
#if defined(__linux__)
#define S21_ERR_MAX 133
#elif defined(__APPLE__)
#define S21_ERR_MAX 107
#endif

typedef struct {
  char spec_char;  // Символ спецификатора "cdeEfgGosuxXp"
  bool minus;  // Выравнивание по левому краю в пределах заданной ширины
  bool plus;  // Явное указывание знака +/- для чисел
  bool space;  // Резервирует пробел перед выводом
  bool hash;   // Для спецификаторов o,x,X,e,E,f,g,G
  bool zero;  // Заполнить пробелы символом 0 если указан спецификатор ширины
  s21_size_t width;     // Ширина поля для вывода числа
  s21_size_t accuracy;  // точность (количество знаков) после запятой.
  char length;  // длина для типов переменной (l, L, h)
  bool dot;  // Наличие точки в формате вывода (точность числа, количество
             // знаков после зпт)
} Specifiers;

//  Функции s21_parser.c
void specifiers_clean(Specifiers* specs);
bool is_digit(char ch);
s21_size_t scan_int(char** format);
void get_flags(Specifiers* specs, char** format);
void get_width(Specifiers* specs, char** format, va_list* args);
void get_accuracy(Specifiers* specs, char** format, va_list* args);
void get_length(Specifiers* specs, char** format);
void specifiers_parser(Specifiers* specs, char** format, va_list* args);
void flags_conflict(Specifiers* specs);

// Функции для реализации спецификаторов f, e, g, E, G:
bool is_nan_or_inf(long double f_arg, char** str,
                   bool* is_negative);  // проверка на not a number и infinity
                                        // без помощи math.h
void nan_inf_special(const char* str_for_f, Specifiers* data,
                     bool* is_negative);  // выключает флаги форматирования для
                                          // случаев с inf, nan
bool is_0_float(long double num);  // возвращает истину, если переданное число
                                   // так мало, что может быть сравнимо с нулём
void frac_to_str(
    const long double num, char* str,
    const s21_size_t len);  // функция записи дробной части числа. Передаётся
                            // число, строка, количество символов для записи
void round_to_acc(char* str, int ind);  // округление в большую сторону с конца
                                        // строки, заданного индексом ind
s21_size_t calc_max_strlen_for_fnum(
    Specifiers* data);  // вычисляет максимальную длину массива для записи long
                        // double в виде строки с учётом спецификаторов
char* make_str_for_float_numb(
    Specifiers* data,
    const long double
        f_arg);  // возвращает указатель на выделенную память, в конце строки
                 // записывает число с учётом точности
s21_size_t calc_acc(
    Specifiers* data);  // расчёт точности, то есть необходимого для вывода
                        // количества знаков после запятой
char* print_float(
    char* str, Specifiers* data,
    va_list* args);  // функция (основная) считывает число с плавающей запятой и
                     // представляет его в виде строки с учётом флагов и пр.

char* scientific_notation_handler(
    Specifiers* data,
    const long double
        f_arg);  // вспомогательная функция для обработки e-спецификаторов
s21_size_t calc_first_zeroes(
    const long double num);  // вычисляет количество первых нулей в дробной
                             // части до первого не-нуля
char* make_str_scientific_notation(
    Specifiers* data, long double f_arg,
    char* str_for_f);  // возвращает указатель на выделенную память, в конце
                       // строки записывает число в научной нотации
int record_e_for_big_value(
    Specifiers* data, char* str_for_e, long double f_arg,
    char** str_for_f);  // запись числа в научной нотации в случае с ненулевой
                        // целой частью
int record_e_for_small_value(
    char* str_for_e, const char* str_for_f,
    s21_size_t accuracy);  // запись числа в научной нотации в случае с нулевой
                           // целой частью str_for_f = 0.***
void finish_record_sign_notation(
    const char e_spec, char* str_for_e,
    int exponent);  // дописывает в запись в научной нотации постфикс вида e+05

char* g_spec_handler(Specifiers* data,
                     const long double f_arg);  // вспомогательная функция для
                                                // обработки g-спецификаторов
int get_exponent(long double f_arg);  // возвращает значение экспоненты для
                                      // записи дробного числа в научной нотации
s21_size_t remove_zeroes_after_point(
    char*
        str);  // функция затирает конечные нули после точки и саму точку (если
               // после неё нет знаков), возвращает количество последних нулей

// Обработчик спецификаторов o, x, X, p:
char* notation_handler(char* str, long num, Specifiers data);

// Обработка спецификаторов c, s, d, u
char* print_str(char* str, Specifiers* data, va_list* args);
char* print_int(char* str, Specifiers* data, va_list* args);

//  Общие функции common.c
void reverse_str(char* str);
void int_to_str(
    char* str, int ind,
    unsigned long long num);  // записывает переданное целое неотрицательное
                              // число num в строку str начиная с индекса ind
char* wrapper(Specifiers* data, char* str_after_spec,
              bool is_negative);  // применяет форматирование по флагам и ширине
                                  // к переданной строке str_after_spec
void add_sign(Specifiers* data, char* str, int ind,
              bool is_negative);  // добавляет числу знак -/+/пробел (+/пробел -
                                  // в зависимости от флага)
void fill_to_width(
    char* str, int ind, const char filler,
    const s21_size_t signs_to_add);  // добавляет нужное количество символов
                                     // filler в начало строки
s21_size_t wrapper_handler(
    char* str, Specifiers* data, char* str_after_spec,
    bool is_negative);  // Обертка к wrapper. Внутри себя создает строку в куче
                        // и вызывает wrapper
#endif