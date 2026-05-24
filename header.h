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
 

void Menu(char* argv[]);        // Главное меню программы
void interface(int choice);     // Отрисовка интерфейса главного меню программы

void Help();                    // Функция работы пункта меню "Помощь"

void Menu_for_record();                              // Меню пункта "Начать работу"
int choose_mode();                                  // Выбор режима работы программы
string input_string(bool* flag_esc);                   // Ввод строки
int workaround(unsigned char first, unsigned char second);

void record_for_console();