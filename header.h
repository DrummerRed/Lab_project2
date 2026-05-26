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

void Menu_start_work();                              // Меню пункта "Начать работу"
int Menu_input_for_keyboard();                         // Меню ввода с клавиатуры
// int choose_mode();                                  // Выбор режима работы программы
int choose_operating_mode();
int choose_input_mode();
string input_string(bool* flag_esc);                   // Ввод строки
int workaround(unsigned char first, unsigned char second);

string record_composition();                           // Ввод произведений
string record_authors();                               // Ввод авторов