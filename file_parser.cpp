#include "header.h"

void file_reader_interface()                    // Выбор режима "Чтение из файла"
{
    bool flag_esc = false;
    int choice = 0;
    while(!flag_esc)
    {
        bool empty = list_is_empty();               // Проверка списка на содержание элементов
        clear();

        if (empty == false)
        {
            printw("Внимание! Список содержит записи. ");
            printw("При чтении файла они будут удалены.\n");
            printw("Желаете продолжить?\n\n");

            string array[2] = {"Да", "Нет"};
            if (choice == 0)
                printw("<< %s >>\n  %s", array[0].c_str(), array[1].c_str());
            else
                printw("  %s\n<< %s >>", array[0].c_str(), array[1].c_str());

            int ch = getch();
            if ((ch == 258) || (ch == 259))
            {
                if (choice == 0)
                    choice = 1;
                else
                    choice = 0;
            }
            
            if (ch == 10)
            {
                if (choice == 0)
                    clearing_list();
                else
                    flag_esc = true;
            }
        }
        else
        {
            string file_name = file_name_input();
            if (file_name == "")
                flag_esc = true;
            else
            {
                interface_of_parsing(file_name);
                flag_esc = true;
            }
        }
        
        refresh();
    }
}

string file_name_input()                            // Считывание имени файла
{                                                   // Возвращает имя файла, если такой файл существует
    bool flag_esc = false;                          // При выходе по ESC возвращает пустую строку
    int checker = 0;
    string file_name;
    while(!flag_esc)
    {
        clear();
        printw("Для возвращения нажмите Esc\n");
        printw("---------------------------\n\n");

        if (checker == 1)
            printw("Ошибка! Файл с данным названием отсутствует!\n");
        else if (checker == 2)
            printw("Ошибка! Данный файл пуст!\n");
        printw("Введите имя файла: ");

        file_name = input_string(&flag_esc);
        if (file_name.find(".txt") == -1)
            file_name.append(".txt");

        if (flag_esc)
            file_name = "";
        else
        {
            checker = file_checker(file_name);
            
            if (checker == 0)
                flag_esc = true;
        }
    }
    return file_name;
}

int file_checker(string file_name)          // Функция проверки существования рабочего файла программы
{                                           // Возвращает 1, если файл с таким именем отсутствует
    ifstream file;                          // 2, если файл пуст
    file.open(file_name);                   // 0, если файл полностью корректен

    if (!file.is_open())                  
        return 1;
    else                                    // Добавить проверку на структуру файла
    {
        int flag;       
        string str;
        getline(file, str);

        if (str == "")
            flag = 2;
        else
            flag = 0;

        file.close();
        return flag;
    }
}

int string_counter(string file_name)                    // Подсчет количества строк в файле
{                                                       // Возвращает количество строк
    string buffer;                                      // При ошибке открытия файла возвращает -1
    int counter = 0;    

    ifstream file;
    file.open(file_name);
    if (!file.is_open())                  
        counter = -1;
    else
    {
        while(getline(file, buffer))
            counter++;
        file.close();
    }
    return counter;             // А нужна ли эта функция вообще???
}

int file_parser(string file_name)                       // Парсинг входного файла
{                                                       // Возвращает 1 при ошибке открытия файла
    ifstream file;                                      // Возвращает 2 при некорректной структуре файла
    file.open(file_name);                               // Возвращает 0 при успешном завершении

    if (!file.is_open())                  
        return 1;
    else
    {
        string str;
        string composition;
        string author;
        int compos_counter = 0;
        while(getline(file, str))
        {
            compos_counter++;

            if (str[0] == '[')
            {
                int len = str.length();
                for (int i=0; i<len; i++)
                {
                    if (str[i] == ']')
                    {
                        composition = str;
                        composition.erase(i, (len-i));
                        composition.erase(0, 1);

                        author = str;
                        author.erase(0, i+1);
                        break;
                    }
                }
                add_composition(composition);
                
                if (len > author.length())                  // Если автор присутствует
                {
                    for (int i=0; ; i++)       // Удаление пробелов
                    {
                        if (author[i] != ' ')
                        {
                            author.erase(0, i);
                            break;
                        }
                    }
                    authors_parser(compos_counter, author);
                }
            }
            else
                return 2;      // неправильная структура файла
        }
        return 0;          
    }
}

void authors_parser(int index, string str)              // парсинг авторов
{
    string author;
    while(str != "")
    {
        author = str;
        int i = 0;
        for (; i<author.length(); i++)
        {
            if ((str[i] == ' '))
            {
                author.erase(i, author.length()-i);
                i++;
                break;
            }
        }
        
        add_author(index, author);
        str.erase(0, i);

        // printw("%ld\n", str.length());           // Отладочный принт
        // refresh();
        // sleep(3);
    }
}

void interface_of_parsing(string file_name)                     // Функция показа сообщения о завершении парсинга
{
    int result = file_parser(file_name);
    int ch = 0;
    while(ch != 27)
    {
        clear();
        printw("Для возвращения нажмите Esc\n");
        printw("---------------------------\n\n");

        if (result == 0)
            printw("Файл успешно считан");
        else if (result == 1)
            printw("Ошибка! Не удалось открыть файл");
        else if (result == 2)
            printw("Ошибка! Файл имеет некорректную структуру! Отредактируйте данный файл или выберите другой");

        ch = getch();
        refresh();
    }
}

string file_name_output()                            // Считывание имени выходного файла
{                                                   // Возвращает имя файл, если такое имя корректно
    bool flag_esc = false;                          // При выходе по ESC возвращает пустую строку
    int checker = 1;
    bool empty_flag = false;
    string file_name;
    while(!flag_esc)
    {
        clear();
        printw("Для возвращения нажмите Esc\n");
        printw("---------------------------\n\n");

        if (checker != 1)
        {
            printw("Ошибка! Файл с данным названием уже существует! Выберите другое имя файла!\n");
            checker = 1;
        }
        else if (empty_flag)
        {
            printw("Ошибка ввода! Введите имя файла!\n");
            empty_flag = false; 
        }
        
        printw("Введите имя файла: ");

        file_name = input_string(&flag_esc);
        if (file_name.find(".txt") == -1)
            file_name.append(".txt");

        if (flag_esc)
            file_name = "";
        else
        {
            if (file_name == ".txt")
                empty_flag = true;
            else
            {
                checker = file_checker(file_name);
                
                if (checker == 1)
                    flag_esc = true;
            }
        }
    }
    return file_name;
}

void file_creator_interface()                      // Меню создания выходного файла
{
    bool empty = list_is_empty();               // Проверка на пустоту списка
    bool flag_esc = false;

    while(!flag_esc)
    {
        clear();
        printw("Для возвращения нажмите Esc\n");
        printw("---------------------------\n\n");

        if (empty)                              // Список пуст
        {
            printw("Записи о произведениях отсутствуют, сохранение недоступно");
            int ch = getch();
            if (ch == 27)
                flag_esc = true;
        }
        else
        {
            string file_name = file_name_output();

            if (file_name != "")
            {
                output_file_creator(file_name);
                flag_esc = true;
                output_file_info(file_name);
            }
            else
                flag_esc = true;
        }
    }
}

void output_file_info(string file_name)                     // Вывод информации о записанном файле
{
    clear();
    printw("Для возвращения нажмите Esc\n");
    printw("---------------------------\n\n");
    
    char absolute_path[PATH_MAX];
    string dir_name = "";
    if (realpath(file_name.c_str(), absolute_path))       // Преобразует относительный путь в абсолютный
    {
        printw("Данные были успешно записаны в файл\n\n");
        printw("Имя файла:\t%s\n", file_name.c_str());
        printw("Путь до файла:\t%s", absolute_path);
    }
    else 
        printw("Ошибка! Файл не был загружен!\n");

    int ch = 0;
    while(ch != 27)
        ch = getch();
}