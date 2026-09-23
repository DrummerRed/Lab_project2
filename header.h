#include <iostream>
#include <cstdlib>          // Для использования некоторых системных функций: system(), exit()
#include <ncurses.h>        // Для реализации интерактивного меню
#include <string>
#include <fstream>
#include <unistd.h>         /////
#include <limits.h>         // Для константы максимальной длины пути
#include <iomanip>          // Для вывода информации в табличном виде
#include <cwchar>
#include <cwctype>

using namespace std;

const int ESC = 27;
const int ENTER = 10;
const int DOWN = 258;
const int UP = 259;
const int LEFT = 260;
const int RIGHT = 261;

struct author;
struct composition;
bool list_is_empty();                                           // Проверка списка на содержание элементов
void add_composition(string composition_name);                  // Добавление произведений в список
void viewing_compositions();
int search_composition(string composition_name);                // Поиск заданного произведения
void delete_composition(int index);
void add_author(int index, string author_name);                 // Добавление автора
// int print_compositions_with_authors(composition* ptr);          // Вывод списка произведений с авторами на консоль
void show_list();                                               // Вывод всего списка
void viewing_authors();                                         // Просмотр и удаление авторов  
void search_authors(int index);                                 // Поиск авторов для заданного произведения
int delete_author_interface(composition* ptr);                  // Вывод списка авторов произведения для удаления
void delete_author(int index, composition* ptr);                // Удаление авторов
int count_authors(composition* ptr);                            // подсчет поличества авторов
void clearing_list();                                           // Очистка списка
string set_number(bool* flag_esc, int* flag_error, void(*callback)(int), int parameter, string* arrow);   // Ввод номера элемента списка
void output_file_creator(string file_name);                     // Запись списка в файл 
int count_symbols(string str);                                  // Подсчет количества символов в строке
int count_elems();                                              // Функция подсчета количества элементов (произведений) списка
int pages_count();                                              // Подсчет количества страниц
string transform_ch(int ch);                                    // Обратботка нажатия стрелок при использовании getch()
int print_compositions_with_authors_2(composition* ptr, int page);       // удалить один из вариантов!!!
string get_composition_and_authors(int index);

void Menu(char* argv[]);                                        // Главное меню программы
void interface(int choice);                                     // Отрисовка интерфейса главного меню программы
void Help();                                                    // Функция работы пункта меню "Помощь"
void Menu_start_work();                                         // Меню пункта "Начать работу"
int Menu_input_for_keyboard();                                  // Меню ввода с клавиатуры
int choose_operating_mode(int index);                           // Выбор режима работы программы
int choose_input_mode(int index);                               // Выбор режима ввода с клавиатуры
string input_string(bool* flag_esc, string* arrows = nullptr);                            // Ввод строки
int workaround(unsigned char first, unsigned char second);
string record_composition();                                    // Ввод произведений
void rec_composition_messages(int* flag_error, string composition, int iterator);    // Вывод диагностических сообщений 
void record_authors();                                          // Ввод авторов (обновленная логика)
void diagnostic_message(int* flag_error, string cash, int deleting = 0);          // Вывод диагностического сообщения на экран
void add_author_interface(int index);                           // Интерфейс добавления авторов к произведению
int allowed_symb(string str, string choice);                    // Проверка названия произведения или имени автора на допустимые символы
int file_name_symb(string file_name);                           // Проверка названия файла на допустимые символы
int numbers_symb(string number);                                // Проверка введенного номера на допустимые символы
string delete_whitespaces(string str);                          // Удаление пробелов в начале и конце строки

void file_reader_interface();                                   // Выбор режима "Чтение из файла"
string file_name_input();                                       // Считывание имени файла
int file_checker(string file_name);                             // Функция проверки существования рабочего файла программы
int string_counter(string file_name);                           // Подсчет количества строк в файле
int file_parser(string file_name);                              // Парсинг входного файла
void authors_parser(int index, string str);                     // Парсинг авторов
void interface_of_parsing(string file_name);                    // Функция показа сообщения о завершении парсинга
string file_name_output();                                      // Считывание имени выходного файла
void file_creator_interface();                                  // Меню создания выходного файла
void output_file_info(string file_name);                        // Вывод информации о записанном файле
string upper_symb(const string& str);                           // Преобразование к верхнему регистру