#include "../s21_string.h"

// функция считывает число с плавающей запятой и представляет его в виде строки
// с учётом флагов и пр.
char* print_float(char* str, Specifiers* data, va_list* args) {
  // f, lf будем получать как double, Lf как long double
  long double f_arg = 0;
  if (data->length == 'L')
    f_arg = va_arg(*args, long double);
  else
    f_arg = (long double)va_arg(*args, double);

  char* str_for_f = S21_NULL;
  bool is_negative = false;
  if (!is_nan_or_inf(f_arg, &str_for_f, &is_negative)) {
    // приводим к положительному значению, запоминаем знак
    if (1 / f_arg < 0) {
      is_negative = true;
      f_arg = -f_arg;
    }
    if (data->spec_char == 'e' || data->spec_char == 'E')
      str_for_f = scientific_notation_handler(data, f_arg);
    else if (data->spec_char == 'g' || data->spec_char == 'G')
      str_for_f = g_spec_handler(data, f_arg);
    else
      str_for_f = make_str_for_float_numb(data, f_arg);

  } else
    nan_inf_special(str_for_f, data, &is_negative);

  str_for_f = wrapper(data, str_for_f, is_negative);

  char* res = str;
  s21_size_t act_len = s21_strlen(str_for_f);
  s21_strncat(str, str_for_f, act_len);
  free(str_for_f);
  res += act_len;
  return res;
}

// вспомогательная функция для обработки e-спецификаторов
char* scientific_notation_handler(Specifiers* data, const long double f_arg) {
  // запись в виде научной нотации опирается на запись строки для дробного
  // числа, но если число мало, то точность нужна больше
  s21_size_t acc = calc_acc(data);
  bool dot_copy = data->dot;
  if (f_arg < 1.0) {
    data->accuracy =
        acc + calc_first_zeroes(f_arg) +
        1;  // увеличиваем точность, пример: 0.00345678 точность 4 -> в записи f
            // будет 0.0035, а нужно получить 3.4568. Чтобы этого достичь, нужно
            // увеличить точность на количество нулей в начале дробной части +1
            // на значение до запятой
    data->dot = true;
  }
  char* str_for_f = make_str_for_float_numb(
      data, f_arg);  // получаем запись числа с нужной точностью (0.0034568)
  data->accuracy = acc;  // возвращаем точность на место
  data->dot = dot_copy;
  return make_str_scientific_notation(data, f_arg, str_for_f);
}

// проверка на not a number и infinity без помощи math.h
bool is_nan_or_inf(long double f_arg, char** str, bool* is_negative) {
  const long double infinity = 1.0 / 0.0;
  if (f_arg == -infinity) {
    *is_negative = true;
    f_arg = -f_arg;
  }

  bool res = false;
  if (f_arg == infinity || f_arg != f_arg) {
    s21_size_t len = 3;
    res = true;
    *str = (char*)calloc(len + 1, sizeof(char));
    (*str)[len] = '\0';
    if (f_arg == infinity)
      s21_strncpy(*str, "inf", len);
    else
      s21_strncpy(*str, "nan", len);
  }
  return res;
}

// Обработка inf, nan. При форматировании не добавляет нули слева, не ставит
// знак +.
void nan_inf_special(const char* str_for_f, Specifiers* data,
                     bool* is_negative) {
  data->zero = 0;
  if (str_for_f[0] == 'n') {
    *is_negative = 0;
    data->plus = 0;
#if defined(__linux__)
    *is_negative = 1;
#endif
  }
}

// возвращает истину, если переданное число так мало, что может быть сравнимо с
// нулём
bool is_0_float(long double num) {
  bool res = false;
  const long double epsilon = 0.00000000000000000000000001;
  if (num < epsilon) res = true;
  return res;
}

// вычисляет максимальную длину массива для записи long double в виде строки с
// учётом спецификаторов
s21_size_t calc_max_strlen_for_fnum(Specifiers* data) {
  const s21_size_t max_ull_len =
      22;  // максимальное число unsigned long long = 18446744073709551615 - 20
           // символов, берём с запасом
  s21_size_t result =
      2 * max_ull_len + 2;  // часть до точки, после точки, точка и знак
  if (data->accuracy > result) result += data->accuracy;
  if (data->width > result) result += data->width;
  return result;
}

// возвращает указатель на выделенную память, в конце строки записывает число с
// учётом точности
char* make_str_for_float_numb(Specifiers* data, const long double f_arg) {
  const s21_size_t max_len = calc_max_strlen_for_fnum(data);
  char* str_for_f =
      (char*)calloc(max_len, sizeof(char));  // для записи числа в качестве
                                             // символов, размер взят с запасом

  // разбиваем число на две части - целую (слева от точки) и дробную - справа от
  // точки
  unsigned long long int_part = (unsigned long long)f_arg;
  s21_size_t accuracy = calc_acc(data);
  // далее записываем в массив 1) целую часть 2) точку 3) дробную часть
  str_for_f[0] = '0';  // резервный первый символ для потенциального округления
  if (!is_0_float(f_arg)) int_to_str(str_for_f, 1, int_part);
  s21_size_t len = s21_strlen(str_for_f);
  if (accuracy) {
    str_for_f[len++] = '.';
    frac_to_str(f_arg, str_for_f, accuracy);
    len += accuracy;
  } else if ((f_arg - int_part) > 0.5)
    round_to_acc(str_for_f, len - 1);
  str_for_f[len] = '\0';
  bool delete_first =
      ((str_for_f[0] == '0') && (len > 1) &&
       (str_for_f[1] != '.'));  // округление не затронуло резервный символ
  if (delete_first) len--;
  char* res_str = (char*)calloc(len + 1, sizeof(char));
  s21_strncpy(res_str, str_for_f + delete_first, len);
  free(str_for_f);
  return res_str;
}

// расчёт точности, то есть необходимого для вывода количества знаков после
// запятой
s21_size_t calc_acc(Specifiers* data) {
  s21_size_t accuracy = 6;  // по умолчанию точность = 6
  if (data->dot)            // точность явно задана
    accuracy = data->accuracy;
  return accuracy;
}

// округление в большую сторону с конца строки, заданного индексом ind
void round_to_acc(char* str, int ind) {
  bool increase = true;
  do  // увеличиваем предыдущий элемент, цикл нужен т.к. может быть число
      // типа 9.99999999
  {
    if (str[ind] >= '0' && str[ind] <= '9')  // в строке может встретиться точка
    {
      increase = false;
      if (str[ind] == '9') {
        str[ind] = '0';
        increase = true;
      } else
        str[ind]++;
    }
    ind--;
  } while (increase && (ind >= 0));
}

// функция записи дробной части числа. Передаётся число, строка, количество
// символов для записи (точность)
void frac_to_str(const long double num, char* str, const s21_size_t acc) {
  long double fraction =
      num - (unsigned long long)num;  // только дробная часть числа (целая = 0)
  const s21_size_t str_len = s21_strlen(str);
  int i = str_len;  // бегунок по переданной строке. Цифры из дробной части
                    // записываем в конец по порядку
  for (; i <= (int)str_len + (int)acc;
       i++)  // идём на 1 порядок больше требуемого количества, чтобы округлить
             // последнее значение
  {
    fraction *= 10;  // следующее число после запятой превращаем в целое
    unsigned long long next_digit = (unsigned long long)fraction % 10;
    str[i] = (next_digit) + '0';  // записываем это число как символ в строку
    fraction -= next_digit;  // зануляем целую часть
  }
  if (str[str_len + acc] >= '5')  // требуется округление
    round_to_acc(str, str_len + acc - 1);
  str[str_len + acc] = 0;  // из дроби брали на один элемент больше для учёта
                           // округления, превращаем его в терминантный нуль
}

// возвращает указатель на выделенную память, записывает число в научной
// нотации, опираясь на строку str_for_f
char* make_str_scientific_notation(Specifiers* data, long double f_arg,
                                   char* str_for_f) {
  s21_size_t accuracy = calc_acc(data);
  char* str_for_e = (char*)calloc(
      accuracy + 7,
      sizeof(
          char));  // 7 = 1 - число до точки, 1 - точка, 1 - "e/Е", 1 - знак
                   // экспоненты 2 - двузначная экспонента, 1 - нуль-терминант
  str_for_e[1] = '.';
  int exponent = 0;
  if (!is_0_float(f_arg)) {
    if (str_for_f[0] > '0')  // число достаточно большое, будем его уменьшать
      exponent = record_e_for_big_value(data, str_for_e, f_arg, &str_for_f);
    else  // str_for_f = 0.***
      exponent = record_e_for_small_value(str_for_e, str_for_f, accuracy);
  } else  // f_arg == 0.0
  {
    str_for_e[0] = '0';
    for (s21_size_t i = 1; i <= accuracy; i++) str_for_e[i + 1] = '0';
  }
  finish_record_sign_notation(data->spec_char, str_for_e, exponent);
  if (str_for_f) free(str_for_f);
  return str_for_e;
}

// запись числа в научной нотации в случае с ненулевой целой частью
int record_e_for_big_value(Specifiers* data, char* str_for_e, long double f_arg,
                           char** str_for_f) {
  s21_size_t accuracy = calc_acc(data);
  s21_size_t int_len = s21_strcspn(*str_for_f, ".");  // длина целой части
  int exponent = int_len - 1;
  if (int_len > 1 &&
      accuracy)  // необходимо скорректировать запись, так как в этом случае
                 // целая часть отнимает часть или всю точность у дробной части
  {
    if (*str_for_f) {
      free(*str_for_f);
      *str_for_f = S21_NULL;
    }
    for (s21_size_t i = 1; i <= int_len - 1; i++)
      f_arg /= 10;  // приводим запись к виду *.******
    *str_for_f = make_str_for_float_numb(data, f_arg);
  }
  str_for_e[0] = (*str_for_f)[0];
  for (s21_size_t f_ind = 1, e_ind = 2; e_ind <= accuracy + 1;
       f_ind++, e_ind++) {
    if ((*str_for_f)[f_ind] == '.') f_ind++;
    str_for_e[e_ind] = (*str_for_f)[f_ind];
  }
  return exponent;
}

// запись числа в научной нотации в случае с нулевой целой частью str_for_f =
// 0.***
int record_e_for_small_value(char* str_for_e, const char* str_for_f,
                             s21_size_t accuracy) {
  int f_ind = 2;  // 0-ой элемент - 0, 1-й - точка
  while (str_for_f[f_ind] == '0')
    f_ind++;  // считаем ведущие нули после запятой
  str_for_e[0] = str_for_f[f_ind++];  // первое ненулевое значение
  int exponent = -(f_ind - 2);
  for (s21_size_t e_ind = 2; e_ind <= (accuracy + 1); e_ind++, f_ind++)
    str_for_e[e_ind] = str_for_f[f_ind];
  return exponent;
}

// дописывает в запись в научной нотации постфикс вида e+05
void finish_record_sign_notation(const char e_spec, char* str_for_e,
                                 int exponent) {
  char buffer[2] = {0};  // для превращения символов в строку
  buffer[0] = e_spec;
  s21_strncat(str_for_e, buffer, 1);
  if (exponent >= 0)
    s21_strncat(str_for_e, "+", 1);
  else {
    s21_strncat(str_for_e, "-", 1);
    exponent *= -1;
  }
  if (exponent < 10)
    s21_strncat(str_for_e, "0", 1);
  else {
    buffer[0] = (exponent / 10) + '0';
    s21_strncat(str_for_e, buffer, 1);
  }
  buffer[0] = (exponent % 10) + '0';
  s21_strncat(str_for_e, buffer, 1);
}

// вычисляет количество первых нулей в дробной части до первого не-нуля
s21_size_t calc_first_zeroes(const long double num) {
  long double fraction =
      num - (unsigned long long)num;  // только дробная часть числа (целая = 0)
  const s21_size_t max = 100;
  s21_size_t counter = 0;
  if (!is_0_float(fraction)) {
    unsigned long long next_digit = 0;
    do {
      fraction *= 10;  // следующее число после запятой превращаем в целое
      next_digit = (unsigned long long)fraction % 10;
      if (next_digit == 0) counter++;
      fraction -= next_digit;  // зануляем целую часть
    } while (counter < max && next_digit == 0);
  }
  return counter;
}

// возвращает значение экспоненты для записи дробного числа в научной нотации
int get_exponent(long double f_arg) {
  int exponent = 0;
  unsigned long long int_part = (unsigned long long)f_arg;
  if (!is_0_float(f_arg)) {
    if (int_part > 0)
      while (int_part /= 10) exponent++;
    else {
      bool zero = true;
      while (zero) {
        exponent--;
        f_arg *= 10;
        if ((unsigned long long)f_arg > 0) zero = false;
      }
    }
  }
  return exponent;
}

// вспомогательная функция для обработки g-спецификаторов
char* g_spec_handler(
    Specifiers* data,
    const long double f_arg) {  // экспоненциальная запись числа в случае если
                                // экспонента <-4 или >=точности
  int exponent = get_exponent(f_arg);
  s21_size_t precision = calc_acc(data);

  // запоминаем точность
  bool dot_copy = data->dot;
  data->dot = true;
  s21_size_t precision_copy = data->accuracy;

  char* str_for_g = S21_NULL;
  if (exponent < -4 ||
      (int)precision <= exponent)  // случай экспоненциальной записи
  {
    if (exponent < 0) data->accuracy = precision - exponent - 1;
    str_for_g = make_str_for_float_numb(
        data, f_arg);  // стандартная запись нужна для научной нотации
    if (!data->hash)   // удаляем конечные нули
    {
      s21_size_t len = s21_strlen(str_for_g);
      s21_size_t deleted = remove_zeroes_after_point(str_for_g);
      if (deleted && exponent > 0) precision = len - deleted;
    }
    data->accuracy = precision - 1;
    data->spec_char = (data->spec_char == 'g') ? 'e' : 'E';
    str_for_g = make_str_scientific_notation(data, f_arg, str_for_g);
  } else  // случай стандартной записи
  {
    data->accuracy = precision - exponent - 1;
    str_for_g = make_str_for_float_numb(data, f_arg);
    if (!data->hash)
      remove_zeroes_after_point(str_for_g);  // удаляем конечные нули
  }
  // возвращаем точку и точность:
  data->dot = dot_copy;
  data->accuracy = precision_copy;
  return str_for_g;
}

// функция затирает конечные нули после точки и саму точку (если после неё нет
// знаков), возвращает количество последних нулей
s21_size_t remove_zeroes_after_point(char* str) {
  s21_size_t counter = 0;
  s21_size_t len = s21_strlen(str);
  s21_size_t ind = len - 1;
  s21_size_t point_ind = s21_strcspn(str, ".");
  bool remove = true;
  while (remove && ind > 0) {
    if (str[ind] == '0' || str[ind] == '.') {
      counter++;
      if (ind >= point_ind) str[ind] = 0;
      ind--;
    } else
      remove = false;
  }
  return counter;
}