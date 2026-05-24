#include "header.h"

const string HELP = "help.txt";     // Название файла для вкладки "Помощь"

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
                Menu_for_record();
            }
            if (switcher == 3)
            {
                endwin();
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

void Menu_for_record()                              // Меню пункта "Начать работу"
{
    int choice = choose_mode();

    if (choice == -1)
        return;
    else if (choice == 0)
        record_for_console();
}

int choose_mode()                                  // Выбор режима работы программы
{                                                   // Возвращает 0 при записи с консоли, 1 при чтении с файла
    int index = 0;                                  // либо возвращает -1 при нажатии Esc
    while(true)
    {    
        clear();
        printw("Для возвращения в меню нажмите Esc\n");
        printw("----------------------------------\n\n");
        printw("Выберите режим работы:\n\n");
        string variants[2] = {"Ввод с клавиатуры", "Чтение из файла"};
        for (int i=0; i<2; i++)
        {
            if (i == index)
                printw("<< %s >>\n", variants[i].c_str());
            else 
                printw(" %s \n", variants[i].c_str());
        }
        refresh();
        int ch = getch();
        if ((ch == 258) || (ch == 259))
        {
            if (index == 0)
                index = 1;
            else
                index = 0;
        }
        if (ch == 10)                       
            return index;

        if (ch == 27)
            return -1;
    }
}

void record_for_console()
{
    while(true)
    {
        clear();
        printw("Для возвращения в меню нажмите Esc\n");
        printw("----------------------------------\n\n");
        printw("Введите название произведения: ");
        bool flag_esc = false;
        string book = input_string(&flag_esc);

        if (flag_esc)
            return;
        else                ///////
            {printw("%s\n", book.c_str());
                refresh();
            sleep(3);
        }

    }
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