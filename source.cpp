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
        choice_operating = choose_operating_mode();         // Выбор режима работы (клавиатура/чтение файла)

        if (choice_operating == -1)
            break;
            
        else if (choice_operating == 0)                     // Выбор режима "Ввод с клавиатуры"
        {
            if (Menu_input_for_keyboard() == -1)
                continue;
        }
    }
}

int Menu_input_for_keyboard()                      // Меню ввода с клавиатуры
{
    int choice_input = 0;
    while(choice_input != -1)
    {
        choice_input = choose_input_mode();     // Выбор режима работы с записями (добавление/удаление)

        if (choice_input == 0)                      // Ввод произведений
        {
            string composition = record_composition();
            if (composition == "")
                continue;
        }
        if (choice_input == 1)                      // Ввод авторов
        {
            string author = record_authors();
            if (author == "")
                continue;
        }
    }
    return choice_input;
}

int choose_operating_mode()                         // Выбор режима работы программы
{                                                   //  Возвращает 0 при выборе "Ввод с клавиатуры",
    int index = 0;                                  // 1 при выборе "Чтение из файла", 2 при выборе "Просмотр записей"
    while(true)                                     // либо возвращает -1 при нажатии Esc
    {    
        clear();
        printw("Для возвращения в меню нажмите Esc\n");
        printw("----------------------------------\n\n");
        printw("Выберите режим работы:\n\n");
        string variants[3] = {"Ввод с клавиатуры", "Чтение из файла", "Просмотр записей"};
        for (int i=0; i<3; i++)
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
            if (index == 2)
                index = 0;
            else
                index++;
        }
        if (ch == 259)
        {
            if (index == 0)
                index = 2;
            else 
                index--;
        }
        if (ch == 10)                       
            return index;

        if (ch == 27)
            return -1;
    }
}

int choose_input_mode()                             // Выбор режима ввода
{                                                   // Возвращает 0 при записи с консоли, 1 при чтении с файла
    int index = 0;                                  // либо возвращает -1 при нажатии Esc
    while(true)
    {    
        clear();
        printw("Для возвращения нажмите Esc\n");
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
    string composition;                                     
    for (int i=0; flag_esc!=true; i++)
    {
        clear();
        printw("Для возвращения нажмите Esc\n");
        printw("---------------------------\n\n");
        if (i>0)
        {
            printw("Произведение «%s» успешно записано\n", composition.c_str());
        }
        printw("Введите название произведения: ");

        composition = input_string(&flag_esc);

        if (flag_esc)
            composition = "";
        
        // добавить проверку на пустую строку
        // для этого можно добавить флаг, при включении который будет срабатывать в условии
    }
    return composition;
}

string record_authors()                               // Ввод авторов
{                                                     // Возвращает пустую строку при нажатии Esc
    bool flag_esc = false; 
    string author;                                     
    for (int i=0; flag_esc!=true; i++)
    {
        clear();
        printw("Для возвращения нажмите Esc\n");
        printw("---------------------------\n\n");
        if (i>0)
        {
            printw("Автор «%s» успешно записан\n", author.c_str());
        }
        printw("Введите автора: ");

        author = input_string(&flag_esc);

        if (flag_esc)
            author = "";
        
        // добавить проверку на пустую строку
        // для этого можно добавить флаг, при включении который будет срабатывать в условии
        // добавить проверку на цифры
    }
    return author;
}

string input_string(bool* flag_esc)                   // Ввод строки
{                                       // Возвращает введенную строку при корректном вводе
    string str = "";                    // При выходе по Esc возвращает пустую строку
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