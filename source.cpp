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
    bool flag_esc = false;
    while(!flag_esc)
    {    
        clear();
        interface(switcher);
        refresh();
        int ch = getch();
        if (ch == DOWN)
        {
            if (switcher != 3)
                switcher += 1;
            else
                switcher = 1;
        }
        if (ch == UP)
        {
            if (switcher != 1)
                switcher -= 1;
            else
                switcher = 3;
        }
        if (ch == ENTER)
        {
            if (switcher == 1)
                Help();

            if (switcher == 2)
                Menu_start_work();
            
            if (switcher == 3)
                flag_esc = true;
        }
    }
    endwin();
    system("clear");
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
    int ch = 0;
    while(ch != ESC)
    {
        clear();

        char str;
        string duplicate_str = "";
        FILE * file = fopen(HELP.c_str(), "r");

        if (file == NULL)
        {
            printw("Для возвращения в меню нажмите Esc\n");
            printw("----------------------------------\n\n");
            printw("Ошибка: не удалось считать файл инструкций!\n");
            printw("Проверьте наличие файла help.txt в рабочей директории программы!");
        }
        else
        {
            int symb;
            while ((symb = fgetc(file)) != EOF) 
            {
                str = (char)symb;
                duplicate_str += str;
            }
            fclose(file);
            printw("%s", duplicate_str.c_str());
        }

        ch = getch();
        refresh();
    }
}

void Menu_start_work()                              // Меню пункта "Начать работу"
{                                                           
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
        choice_input = choose_input_mode(choice_input);     // Выбор режима работы

        if (choice_input == 0)                      // Добавление произведений
        {
            string composition = record_composition();
            if (composition == "")
                continue;
        }
        if (choice_input == 1)                      // Добавление авторов
        {
            record_authors();
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
        if (ch == DOWN)
        {
            if (index == 3)
                index = 0;
            else
                index++;
        }
        if (ch == UP)
        {
            if (index == 0)
                index = 3;
            else 
                index--;
        }
        if (ch == ENTER)                       
            return index;

        if (ch == ESC)
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
        if (ch == DOWN)
        {
            if (index == 3)
                index = 0;
            else
                index++;
        }
        if (ch == UP)
        {
            if (index == 0)
                index = 3;
            else
                index--;
        }
        if (ch == ENTER)                       
            return index;

        if (ch == ESC)
            return -1;
    }
}

string record_composition()                           // Ввод названия произведений
{                                                     // Возвращает пустую строку при нажатии Esc
    bool flag_esc = false; 
    bool empty_flag = false;
    bool symbols_flag = false;
    bool len_flag = false;                              // Диагностические сообщения можно перенести в отдельную функцию с парам-ми - флагами
    bool repeat_flag = false;
    string composition;                                     
    for (int i=0; flag_esc!=true; i++)
    {
        clear();
        printw("Для возвращения нажмите Esc\n");
        printw("---------------------------\n\n");
        if (empty_flag)
        {
            printw("Ошибка! Некорректный ввод!\n");
            empty_flag = false;
        }
        else if (len_flag)
        {
            printw("Ошибка! Строка не должна содержать больше 30 символов!\n");
            len_flag = false;
        }
        else if (symbols_flag)
        {
            printw("Ошибка! Название может содержать только:\n");
            printw("- цифры\n- буквы латинского и русского алфавитов\n- знак пробела в виде разделителя\n\n");
            symbols_flag = false;
        }
        else if (repeat_flag)
        {
            printw("Ошибка! Произведение «%s» уже записано!\n", composition.c_str());
            repeat_flag = false;
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
            {
                if (count_symbols(composition) > 30)
                    len_flag = true;
                else if (composition_symb(composition) == 0)
                {
                    composition = upper_symb(composition);
                    if ((search_composition(composition) == 0) || (search_composition(composition) == -1))
                        add_composition(composition);
                    else
                        repeat_flag = true;
                }
                else 
                    symbols_flag = true;
            }
            else
                empty_flag = true;
        }
    }
    return composition;
}

string input_string(bool* flag_esc)                   // Ввод строки
{                                                     // Возвращает введенную строку при корректном вводе
    string str = "";                                  // При выходе по Esc возвращает пустую строку
    int x, y;
    noecho();
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
                        move(y, x-1);
                        delch();
                    }
                    else                                   
                    {
                        str.erase(str.length()-1, 1);
                        getyx(stdscr, y, x);
                        move(y, x-1);
                        delch();
                    }
                }
                else
                {
                    str.erase(str.length()-1, 1);
                    getyx(stdscr, y, x);
                    move(y, x-1);
                    delch();
                }  
            }
        }
        else if (ch == ESC)              // Выход по ESC
        {
            *flag_esc = true;
            break;
        }              

        else if (ch == ENTER)              // Выход при нажатии Enter
            break;

        else
        {
            str += ch;
            addch(ch);
            if (ch >= 0xC0 && ch <= 0xDF)
            {                                       // если двухбайтовый символ
                int next_ch = getch();              // считываем находящийся в буфере второй байт символа
                str += next_ch;
                addch(next_ch);
            }
        }
    }
    noecho();
    curs_set(0);
    echo();
    return str;
}

int workaround(unsigned char first, unsigned char second) {             // возвращает 1, если это символ кириллицы (2 байтовый)
    // D0 90-BF (А-Я), D0 80-8F (а-п), D1 80-BF (р-я, Ё)                // иначе 0
    if (first == 0xD0 && second >= 0x90 && second <= 0xBF)              // А-Я
        return 1;

    if (first == 0xD0 && second >= 0x80 && second <= 0x8F)              // а-п
        return 1;
    
    if (first == 0xD1 && second >= 0x80 && second <= 0x8F)              // р-я
        return 1;

    if (first == 0xD0 && second == 0x81)                                // Ё
        return 1; 

    if (first == 0xD1 && second == 0x91)                                // ё
        return 1;
        
    return 0;
}

// composition_symb и authors_symb так то можно объединить в одну функцию с каким то параметром
int composition_symb(string composition)                    // Проверка названия произведения на допустимые символы
{                                                           // Возвращает 0 при корректном названии
    string rus_low = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";       // Возвращает 1, если присутствуют недопустимые символы
    string rus_high = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ0123456789.,?!-:; ";
    string eng_high = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string eng_low = "abcdefghijklmnopqrstuvwxyz";
    int length = composition.length();                      
    int invalid_symb = 0;

    if (composition.find("  ") != -1)
        invalid_symb = 1;

    else if ((composition[length-1] == ' ') || (composition[0] == ' '))
        invalid_symb = 1;

    else
    {
        for (int i=0; i<length; i++)
        {
            if ((rus_low.find(composition[i]) == -1) && (rus_high.find(composition[i]) == -1)
                && (eng_high.find(composition[i]) == -1) && (eng_low.find(composition[i]) == -1))
            {
                invalid_symb = 1;
                break;
            }
        }
    }
    
    return invalid_symb;
}

int authors_symb(string author)                 // Проверка имени автора на допустимые символы
{                                               // Возвращает 0 при корректном имени, 1 при некорректном
    string rus_low = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    string rus_high = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ- ";
    string eng_high = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string eng_low = "abcdefghijklmnopqrstuvwxyz";
    int length = author.length();
    int invalid_symb = 0;

    if (author.find("  ") != -1)
        invalid_symb = 1;

    else if ((author[length-1] == ' ') || (author[0] == ' '))
        invalid_symb = 1;

    else
    {
        for (int i=0; i<length; i++)
        {
            if ((rus_low.find(author[i]) == -1) && (rus_high.find(author[i]) == -1)
                && (eng_high.find(author[i]) == -1) && (eng_low.find(author[i]) == -1))
            {
                invalid_symb = 1;
                break;
            }
        }
    }

    return invalid_symb;
}

int file_name_symb(string file_name)                 // Проверка названия файла на допустимые символы
{                                                    // Возвращает 0 при корректном имени, 1 при некорректном
    string error_symb = "\\&;|*?`[]()$<>{}^#/%!\'\"";

    int length = file_name.length();
    int invalid_symb = 0;
    
    for (int i=0; i<length; i++)
    {
        if (error_symb.find(file_name[i]) != -1)
        {
            invalid_symb = 1;
            break;
        }
    }

    return invalid_symb;
}

int numbers_symb(string number)                     // Проверка введенного номера на допустимые символы
{                                                   // Возвращает 0 при корректном номере, иначе возвращает 1
    string numbers = "0123456789";

    int length = number.length();
    int invalid_symb = 0;

    for (int i=0; i<length; i++)
    {
        if (numbers.find(number[i]) == -1)
        {
            invalid_symb = 1;
            break;
        }
    }

    return invalid_symb;
}