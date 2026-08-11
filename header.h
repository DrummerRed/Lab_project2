#include <iostream>
#include <cstdlib>          // Для использования некоторых системных функций: system(), exit()
#include <ncurses.h>        // Для реализации интерактивного меню
#include <string>
#include <fstream>
#include <unistd.h>         /////
#include <limits.h>         // Для константы максимальной длины пути
#include <iomanip>          // Для вывода информации в табличном виде

// #include <wchar.h>

using namespace std;

struct author;
struct composition;
bool list_is_empty();                        // Проверка списка на содержание элементов
void add_composition(string composition_name);           // Добавление произведений в список
void viewing_compositions();
int search_composition(string composition_name);         // Поиск заданного произведения
void delete_composition(int index);
void add_author(int index, string author_name);                  // Добавление автора
void show_list();                            // Вывод всего списка
void viewing_authors();              // Просмотр и удаление авторов  
void search_authors(int index);                   // Поиск авторов для заданного произведения
int delete_author_interface(composition* ptr);              // Вывод списка авторов произведения для удаления
void delete_author(int index, composition* ptr);         // Удаление авторов
int count_authors(composition* ptr);             // подсчет поличества авторов
void clearing_list();                        // Очистка списка
void output_file_creator(string file_name);                              // Запись списка в файл 
int count_symbols(string str);                   // Подсчет количества символов в строке

void Menu(char* argv[]);        // Главное меню программы
void interface(int choice);     // Отрисовка интерфейса главного меню программы
void Help();                    // Функция работы пункта меню "Помощь"
void Menu_start_work();                              // Меню пункта "Начать работу"
int Menu_input_for_keyboard();                         // Меню ввода с клавиатуры
// int choose_mode();                                  // Выбор режима работы программы
int choose_operating_mode(int index);                  // Выбор режима работы программы
int choose_input_mode(int index);                      // Выбор режима ввода с клавиатуры
string input_string(bool* flag_esc);                   // Ввод строки
int workaround(unsigned char first, unsigned char second);
string record_composition();                           // Ввод произведений
// string record_authors();                               // Ввод авторов
void record_authors();                                      // Ввод авторов (обновленная логика)
void add_author_interface(int index);                       // Интерфейс добавления авторов к произведению
int authors_symb(string author);                 // Проверка имени автора на допустимые символы
int composition_symb(string composition);                    // Проверка названия произведения на допустимые символы

void file_reader_interface();                    // Выбор режима "Чтение из файла"
string file_name_input();                            // Считывание имени файла
int file_checker(string file_name);                // Функция проверки существования рабочего файла программы
int string_counter(string file_name);                    // Подсчет количества строк в файле
int file_parser(string file_name);                       // Парсинг входного файла
void authors_parser(int index, string str);              // парсинг авторов
void interface_of_parsing(string file_name);                     // Функция показа сообщения о завершении парсинга
string file_name_output();                            // Считывание имени выходного файла
void file_creator_interface();                      // Меню создания выходного файла
void output_file_info(string file_name);                     // Вывод информации о записанном файле