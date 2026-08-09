#include "header.h"

const string HELP = "help.txt";     // Название файла для вкладки "Помощь"
const int OPERATING_MODE = 1;       // Флаг для режима работы
const int INPUT_MODE = 2;           // Флаг для режима ввода

void Menu(char* argv[])         // Главное меню программы
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);                // выключение курсора

    int switcher = 1;
    while(true)
    {    
        clear();
        interface(switcher);
        refresh();
        int ch = getch();
        if (ch == 258)
        {
            if (switcher != 3)
                switcher += 1;
            else
                switcher = 1;
        }
        if (ch == 259)
        {
            if (switcher != 1)
                switcher -= 1;
            else
                switcher = 3;
        }
        if (ch == 10)
        {
            if (switcher == 1)
            {
                Help();
            }
            if (switcher == 2)
            {
                Menu_start_work();
            }
            if (switcher == 3)
            {
                endwin();
                system("clear");
                exit(0);
            }
        }
    }
    endwin();
}

void interface(int choice)      // Отрисовка интерфейса главного меню программы
{
    switch(choice)
    {
        case 1:
        printw(" \t\t<< Помощь >>\n \t\tНачать работу\n \t\tВыход");            // либо начать запись
        break;
        case 2:
        printw(" \t\tПомощь\n \t\t<< Начать работу >>\n \t\tВыход");
        break;
        case 3:
        printw(" \t\tПомощь\n \t\tНачать работу\n \t\t<< Выход >>");
        break;
    }
}

void Help()             // Функция работы пункта меню "Помощь"
{
    def_prog_mode();                    // Сохраняем режим ncurses
    endwin();                           // Временно выключаем ncurses
    system("clear");
    char str;
    string duplicate_str = "";
    FILE * file = fopen(HELP.c_str(), "r");

    if (file == NULL)
    {
        printf("Ошибка: не удалось считать файл инструкций!\n");
        exit(0);
    }
    int symb;
    while ((symb = fgetc(file)) != EOF) 
    {
        str = (char)symb;
        duplicate_str += str;
    }
    fclose(file);
    reset_prog_mode();                  // Восстанавливаем режим
    clear();
    printw("%s", duplicate_str.c_str());
    refresh();
    int ch = 0;
    while((int)ch != 27)
    {
        ch = getch();
    }
}

void Menu_start_work()                              // Меню пункта "Начать работу"
{                                                           // Для того чтобы не выходить сразу вменю из второго выбора можно организовать цикл
    int choice_operating = 0;
    while(choice_operating != -1)
    {
        choice_operating = choose_operating_mode(choice_operating);         // Выбор режима работы (клавиатура/чтение файла)

        if (choice_operating == -1)
            break;
            
        else if (choice_operating == 0)                     // Выбор режима "Ввод с клавиатуры"
        {
            if (Menu_input_for_keyboard() == -1)
                continue;
        }

        else if (choice_operating == 1)                     // Выбор режима "Чтение из файла"
        {
            file_reader_interface();                    
        }

        else if (choice_operating == 2)                     // Выбор режима "Сохранение в файл"
        {
            file_creator_interface();                  
        }

        else if (choice_operating == 3)                     // Выбор режима "Просмотр записей"
        {
            show_list();
        }
    }
}

int Menu_input_for_keyboard()                      // Меню ввода с клавиатуры
{
    int choice_input = 0;
    while(choice_input != -1)
    {
        choice_input = choose_input_mode(choice_input);     // Выбор режима работы с записями (добавление/удаление)

        if (choice_input == 0)                      // Добавление произведений
        {
            string composition = record_composition();
            if (composition == "")
                continue;
        }
        if (choice_input == 1)                      // Добавление авторов
        {
            string author = record_authors();
            if (author == "")
                continue;
        }
        if (choice_input == 2)                      // Просмотр и удаление произведений 
        {
            viewing_compositions();
        }
        if (choice_input == 3)                      // Просмотр и удаление авторов
        {
            viewing_authors();
        }
    }
    return choice_input;
}

int choose_operating_mode(int index)                // Выбор режима работы программы
{                                                   // Возвращает 0 при выборе "Ввод с клавиатуры",
    while(true)                                     // 1 при выборе "Чтение из файла", 2 при выборе "Сохранение в файл"
    {                                               // 3 при выборе "Просмотр записей", -1 при нажатии Esc
        clear();
        printw("Для возвращения в меню нажмите Esc\n");
        printw("----------------------------------\n\n");
        printw("Выберите режим работы:\n\n");
        string variants[4] = {"Ввод с клавиатуры", "Чтение из файла", "Сохранение в файл", "Просмотр записей"};
        for (int i=0; i<4; i++)
        {
            if (i == index)
                printw("<< %s >>\n", variants[i].c_str());
            else 
                printw(" %s \n", variants[i].c_str());
        }
        refresh();
        int ch = getch();
        if (ch == 258)
        {
            if (index == 3)
                index = 0;
            else
                index++;
        }
        if (ch == 259)
        {
            if (index == 0)
                index = 3;
            else 
                index--;
        }
        if (ch == 10)                       
            return index;

        if (ch == 27)
            return -1;
    }
}

int choose_input_mode(int index)                    // Выбор режима ввода с клавиатуры
{                                                   // Возвращает 0 при выборе "Добавление произведений"
    while(true)                                     // 1 при выборе "Добавление авторов"
    {                                               // 2 при выборе "Просмотр и удаление произведений
        clear();                                    // 3 при выборе "Просмотр и удаление авторов"
        printw("Для возвращения нажмите Esc\n");    // либо возвращает -1 при нажатии Esc
        printw("---------------------------\n\n");
        printw("Выберите:\n\n");
        string variants[4] = {"Добавление произведений", "Добавление авторов", "Просмотр и удаление произведений", "Просмотр и удаление авторов"};
        for (int i=0; i<4; i++)
        {
            if (i == index)
                printw("<< %s >>\n", variants[i].c_str());
            else 
                printw(" %s \n", variants[i].c_str());
        }
        refresh();
        int ch = getch();
        if (ch == 258)
        {
            if (index == 3)
                index = 0;
            else
                index++;
        }
        if (ch == 259)
        {
            if (index == 0)
                index = 3;
            else
                index--;
        }
        if (ch == 10)                       
            return index;

        if (ch == 27)
            return -1;
    }
}

string record_composition()                           // Ввод названия произведений
{                                                     // Возвращает пустую строку при нажатии Esc
    bool flag_esc = false; 
    bool flag_error = false;
    string composition;                                     
    for (int i=0; flag_esc!=true; i++)
    {
        clear();
        printw("Для возвращения нажмите Esc\n");
        printw("---------------------------\n\n");
        if (flag_error)
        {
            printw("Ошибка! Некорректный ввод!\n");
            flag_error = false;
        }
        else if (i>0)
        {
            printw("Произведение «%s» успешно записано\n", composition.c_str());
        }
        printw("Введите название произведения: ");

        composition = input_string(&flag_esc);

        if (flag_esc)
            composition = "";
        
        else
        {
            if (composition != "")
                add_composition(composition);
            else
                flag_error = true;
        }
    }
    return composition;
}

string record_authors()                               // Ввод авторов
{                                                     // Возвращает пустую строку при нажатии Esc
    bool flag_esc = false; 
    bool item_find = true;
    string author;  
    string composition;                                   
    for (int i=0; flag_esc!=true; i++)
    {
        int index;
        clear();
        printw("Для возвращения нажмите Esc\n");
        printw("---------------------------\n\n");
        if (i>0)
        {
            if (item_find)
                printw("Автор «%s» успешно записан\n", author.c_str());
            else
            {
                printw("Данное произведение не найдено!\n");
                item_find = true;
            }
        }

        printw("Укажите произведение, к которому хотите добавить автора: ");
        composition = input_string(&flag_esc);
        if (flag_esc)
        {
            author = "";
            break;
        }
        else
            index = search_composition(composition);

        if (index > 0)
        {
            clear();
            printw("Для возвращения нажмите Esc\n");
            printw("---------------------------\n\n");
            printw("Введите автора: ");
            author = input_string(&flag_esc);
            add_author(index, author);
        }
        else
        {
            item_find = false;          // Произведение не найдено
            continue;
        }

        if (flag_esc)
            author = "";
        
        // добавить проверку на пустую строку
        // для этого можно добавить флаг, при включении который будет срабатывать в условии
        // добавить проверку на цифры
    }
    return author;
}

string input_string(bool* flag_esc)                   // Ввод строки
{                                                     // Возвращает введенную строку при корректном вводе
    string str = "";                                  // При выходе по Esc возвращает пустую строку
    int x, y;
    echo();
    curs_set(1);
    while(true)
    {
        refresh();          /////////
        int ch = getch();
        if (ch == KEY_BACKSPACE)                // Удаление символа
        {
            if (str != "")
            {
                int len = str.length();
                if (len > 1)
                {
                    unsigned char first =  str[len - 2];
                    unsigned char second = str[len - 1];

                    if (workaround(first, second) == 1)       
                    {
                        str.erase(str.length()-2, 2);
                        getyx(stdscr, y, x);
                        move(y, x);
                        delch();
                    }
                    else                                   
                    {
                        str.erase(str.length()-1, 1);
                        getyx(stdscr, y, x);
                        move(y, x);
                        delch();
                    }
                }
                else
                {
                    str.erase(str.length()-1, 1);
                    getyx(stdscr, y, x);
                    move(y, x);
                    delch();
                }  
            }
        }
        else if (ch == 27)              // Выход по ESC
        {
            *flag_esc = true;
            break;
        }              

        else if (ch == 10)              // Выход при нажатии Enter
            break;

        else
        {
            str += ch;
            if (ch >= 0xC0 && ch <= 0xDF)
            {                                       // если двухбайтовый символ
                int next_ch = getch();              // считываем находящийся в буфере второй байт символа
                str += next_ch;
            }
        }
    }
    noecho();
    curs_set(0);
    return str;
}

int workaround(unsigned char first, unsigned char second) {             // возвращает 1, если это символ кириллицы (2 байтовый)
    // D0 90-BF (А-Я), D0 80-8F (а-п), D1 80-BF (р-я, Ё)                // иначе 0
    // А-Я
    if (first == 0xD0 && second >= 0x90 && second <= 0xBF) return 1;
    // а-п
    if (first == 0xD0 && second >= 0x80 && second <= 0x8F) return 1;
    // р-я
    if (first == 0xD1 && second >= 0x80 && second <= 0x8F) return 1;
    if (first == 0xD0 && second == 0x81) return 1; // Ё
    if (first == 0xD1 && second == 0x91) return 1; // ё
    return 0;
}