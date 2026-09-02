#include "header.h"

struct composition
{
    string name;
    author* author_ptr = nullptr;
    composition* next_ptr = nullptr;
};

struct author
{
    string name;
    author* next_ptr = nullptr;
};

composition* head_ptr = nullptr;            // Глобальный указатель на начало списка

bool list_is_empty()                        // Проверка списка на содержание элементов
{                                           // Возвращает true, если список пуст
    if (head_ptr == nullptr)                // Иначе возвращает false
        return true;
    else
        return false;
}

void add_composition(string composition_name)           // Добавление произведений в список
{
    if (head_ptr == nullptr)
    {
        head_ptr = new composition;
        head_ptr->name = composition_name;
    }
    else 
    {
        composition* ptr = head_ptr;
        while(ptr->next_ptr != nullptr)
        {
            ptr = ptr->next_ptr;
        }
        ptr->next_ptr = new composition;
        ptr = ptr->next_ptr;
        ptr->name = composition_name;
    }
}

void delete_composition(int index)          /// Стоит дописать освобождение памяти авторов
{
    composition* ptr = head_ptr;
    composition* next_ptr;
    composition* prev_ptr;

    if (index == 1)                         // Удаление 1го элемента
    {
        next_ptr = ptr->next_ptr;
        head_ptr = next_ptr;
        delete ptr;
    }
    else
    {
        for (int i=1; i<index; i++)
        {
            if (i == 1)
            {
                ptr = ptr->next_ptr;
                prev_ptr = head_ptr;
            }
            else
            {
                ptr = ptr->next_ptr;
                prev_ptr = prev_ptr->next_ptr;
            }
        }
        next_ptr = ptr->next_ptr;
        if (next_ptr == nullptr)                // Удаление последнего элемента
        {
            prev_ptr->next_ptr = nullptr;
            delete ptr;
        }
        else                                    // Удаление элемента из середины списка
        {
            prev_ptr->next_ptr = next_ptr;
            delete ptr;
        }
    }
    
}

void clearing_list()                    // Очистка списка
{
    int first_elem = 1;

    while(list_is_empty() == false)
        delete_composition(first_elem);
}

void record_authors()                               // Ввод авторов (обновленная логика)
{                                       
    bool flag_esc = false;
    bool flag_empty = false;
    bool flag_error = false;        // сократить код!
    while(!flag_esc)
    {
        clear();
        printw("Для возвращения нажмите Esc\n");
        printw("---------------------------\n\n");

        composition* ptr = head_ptr;
        
        if (ptr == nullptr)
        {
            printw("Записи о произведениях отсутствуют, добавление недоступно!");
            int ch = getch();
            if (ch == 27)
                break;
        }
        else
        {
            int iterator = print_compositions_with_authors(ptr);

            if (flag_empty)
            {
                printw("\nОшибка! Введена пустая строка!");
                flag_empty = false;
            }
            if (flag_error)
            {
                printw("\nОшибка! Некорректный ввод!");
                flag_error = false;
            }

            printw("\nДля добавления автора введите номер его произведения: ");
            string cash = input_string(&flag_esc);
            if (!flag_esc)
            {
                if (cash == "")
                    flag_empty = true;
                else
                {
                    try
                    {
                        int index = stoi(cash);
                        if ((index > 0) && (index <= iterator))
                            add_author_interface(index);
                        else
                            flag_error = true;
                    }
                    catch(...)
                    {
                        flag_error = true;
                    }
                }
            }
        }
        refresh();
    }
}

void viewing_compositions()             // Пока как отладочный принт
{                                       
    bool flag_esc = false;
    bool flag_empty = false;
    bool flag_error = false;            // сократить код!
    while(!flag_esc)
    {
        clear();
        printw("Для возвращения нажмите Esc\n");
        printw("---------------------------\n\n");

        composition* ptr = head_ptr;
        int iterator = 0;
        if (ptr == nullptr)
        {
            printw("Записи о произведениях отсутствуют");
            int ch = getch();
            if (ch == 27)
                break;
        }
        else
        {
            while(ptr != nullptr)
            {
                iterator++;
                string name = ptr->name;
                printw("%d. %s\n", iterator, name.c_str());
                ptr = ptr->next_ptr;
            }
            if (flag_empty)
            {
                printw("\nОшибка! Введена пустая строка!");
                flag_empty = false;
            }
            if (flag_error)
            {
                printw("\nОшибка! Некорректный ввод!");
                flag_error = false;
            }

            printw("\nДля удаления произведения введите его номер: ");
            string cash = input_string(&flag_esc);
            if (!flag_esc)
            {
                if (cash == "")
                    flag_empty = true;
                else 
                {
                    try
                    {
                        int index = stoi(cash);
                        if ((index > 0) && (index <=iterator))
                            delete_composition(index);
                        else
                            flag_error = true;
                    }
                    catch(...)
                    {
                        flag_error = true;
                    }
                }
            }
        }
        refresh();
    }
}

int search_composition(string composition_name)                 // Поиск заданного произведения
{                                                               // Возвращает 0, если список не задан (Элементы отсутствуют)
    if (head_ptr == nullptr)                                    // Если элемент найден, возврощает порядковый номер элемента в списке
        return 0;                                               // Если элемент в списке не найден, возвращает -1
    else
    {
        bool item_find = false;
        composition* ptr = head_ptr;
        int iterator = 0;
        while(ptr != nullptr)
        {
            iterator++;
            string name = ptr->name;
            if (name == composition_name)
            {
                item_find = true;
                break;
            }
            else
                ptr = ptr->next_ptr;
        }
        if (item_find)
            return iterator;
        else
            return -2;                                          // Произведение не найдено в списке
    }
}

void add_author(int index, string author_name)                  // Добавление автора
{
    composition* ptr = head_ptr;

    for (int i=1; i<index; i++)
        ptr = ptr->next_ptr;
    
    author* author_ptr = ptr->author_ptr;
    if (author_ptr == nullptr)
    {
        ptr->author_ptr = new author;
        ptr->author_ptr->name = author_name;
    }
    else
    {
        while(author_ptr->next_ptr != nullptr)
            author_ptr = author_ptr->next_ptr;
        author_ptr->next_ptr = new author;
        author_ptr->next_ptr->name = author_name; 
    }
}

void add_author_interface(int index)                // Интерфейс добавления авторов к произведению
{
    bool flag_esc = false;
    bool symbol_flag = false;  
    bool len_flag = false;                               
    while(!flag_esc)
    {
        composition* ptr = head_ptr;
        for (int i=1; i<index; i++)
            ptr = ptr->next_ptr;

        author* author_ptr = ptr->author_ptr;

        if (index > 0)
        {
            clear();
            printw("Для возвращения нажмите Esc\n");
            printw("---------------------------\n\n");
            printw("Произведение: %s\n", ptr->name.c_str());
            
            if (author_ptr == nullptr)
                printw("Авторы: не указаны");
            else
            {
                printw("Авторы: ");
                while(author_ptr != nullptr)
                {
                    printw("%s", author_ptr->name.c_str());
                    author_ptr = author_ptr->next_ptr;
                    if (author_ptr != nullptr)
                        printw(", ");
                }
            }
            printw("\n\n");

            if (symbol_flag)
            {
                symbol_flag = false;
                printw("Ошибка! Имя автора может содержать только буквы латинского и русского алфавитов!\n");
            }
            else if (len_flag)
            {
                len_flag = false;
                printw("Ошибка! Строка не должна содержать больше 40 символов!\n");
            }

            printw("Введите автора: ");
            string author = input_string(&flag_esc);

            if (flag_esc)
                author = "";
            else if (author != "")
            {
                if (count_symbols(author) > 40)
                    len_flag = true;
                else if (authors_symb(author) == 0)
                    add_author(index, author);
                else 
                    symbol_flag = true;
            }
        }
        refresh();
    }
}

int print_compositions_with_authors(composition* ptr)          // Вывод списка произведений с авторами на консоль
{                                                              // Возвращает значение количества произведений в списке
    int iterator = 0;
    while(ptr != nullptr)
    {
        iterator++;
        string composition_name = ptr->name;
        printw("%d. %s", iterator, composition_name.c_str());

        author* author_ptr = ptr->author_ptr;
        int number = 0;
        while(author_ptr != nullptr)
        {
            number++;
            string author_name = author_ptr->name;
            if (number == 1)
                printw(" - %s", author_name.c_str());
            else
                printw(", %s", author_name.c_str());

            author_ptr = author_ptr->next_ptr;
        }
        ptr = ptr->next_ptr;
        printw("\n");
    }
    return iterator;
}

void show_list()                            // Вывод всего списка на экран
{     
    int ch = 0;                                  
    while(ch != 27)
    {
        clear();
        printw("Для возвращения нажмите Esc\n");
        printw("---------------------------\n\n");

        composition* ptr = head_ptr;
        
        if (ptr == nullptr)
            printw("Записи о произведениях отсутствуют");

        else
            print_compositions_with_authors(ptr);

    ch = getch();
    }
}             

void viewing_authors()              // Просмотр и удаление авторов       
{                                       
    bool flag_esc = false;
    bool flag_empty = false;
    bool flag_error = false;        
    while(!flag_esc)
    {
        clear();
        printw("Для возвращения нажмите Esc\n");
        printw("---------------------------\n\n");

        composition* ptr = head_ptr;

        if (ptr == nullptr)
        {
            printw("Записи о произведениях отсутствуют");
            int ch = getch();
            if (ch == 27)
                break;
        }
        else
        {
            int iterator = print_compositions_with_authors(ptr);

            if (flag_empty)
            {
                printw("\nОшибка! Введена пустая строка!");
                flag_empty = false;
            }
            if (flag_error)
            {
                printw("\nОшибка! Некорректный ввод!");
                flag_error = false;
            }

            printw("\nДля удаления автора введите номер его произведения: ");
            string cash = input_string(&flag_esc);
            if (!flag_esc)
            {
                if (cash == "")
                    flag_empty = true;
                else
                {
                    try
                    {
                        int index = stoi(cash);
                        if ((index > 0) && (index <= iterator))
                            search_authors(index);
                        else
                            flag_error = true;
                    }
                    catch(...)
                    {
                        flag_error = true;
                    }
                }
            }
        }
        refresh();
    }
}

void search_authors(int index)                   // Поиск авторов для заданного произведения
{
    int count_authors = 0;
    composition* ptr = head_ptr;

    for (int i=1; i<index; i++)
        ptr = ptr->next_ptr;
    
    delete_author_interface(ptr);
}

int delete_author_interface(composition* ptr)              // Вывод списка авторов произведения для удаления
{ 
    bool flag_esc = false;
    bool flag_empty = false;
    bool flag_error = false;                // сократить код!
    while(!flag_esc)
    {
        author* author_ptr = ptr->author_ptr;
        int authors = count_authors(ptr);
        clear();
        printw("Для возвращения нажмите Esc\n");
        printw("---------------------------\n\n");

        if (authors == 0)
        {
            printw("У данного произведения отсутствуют авторы.");
            int ch = getch();
            if (ch == 27)
                break;
        }
        else
        {
            author* tmp_author_ptr = author_ptr;
            for (int i=1; i<=authors; i++)
            {
                string author_name = tmp_author_ptr->name;
                printw("%d. %s\n", i, author_name.c_str());

                if (i != authors)
                    tmp_author_ptr = tmp_author_ptr->next_ptr;
            }
            if (flag_empty)
            {
                printw("\nОшибка! Введена пустая строка!");
                flag_empty = false;
            }
            if (flag_error)
            {
                printw("\nОшибка! Некорректный ввод!");
                flag_error = false;
            }

            printw("\nДля удаления желаемого автора введите его номер: ");
            string cash = input_string(&flag_esc);
            if (!flag_esc)
            {
                if (cash == "")
                    flag_empty = true;
                else
                {
                    try
                    {
                        int index = stoi(cash);
                        if ((index > 0) && (index <= authors))
                            delete_author(index, ptr);
        
                        else
                            flag_error = true;
                    }
                    catch(...)
                    {
                        flag_error = true;
                    }
                }
            }
        }
    }

    return 0; /////////////
}

void delete_author(int index, composition* ptr)         // Удаление авторов
{
    author* author_ptr = ptr->author_ptr;
    author* next_author_ptr;
    author* prev_author_ptr;

    if (index == 1)                                     // Удаление первого элемента
    {
        next_author_ptr = ptr->author_ptr->next_ptr;
        ptr->author_ptr = next_author_ptr;
        delete author_ptr;
    }
    else
    {
        for (int i=1; i<index; i++)
        {
            prev_author_ptr = author_ptr;
            author_ptr = author_ptr->next_ptr;
        }

        next_author_ptr = author_ptr->next_ptr;
        if (next_author_ptr == nullptr)                 // Удаление последнего элемента
        {
            prev_author_ptr->next_ptr = nullptr;
            delete author_ptr;
        }
        else                                            // Удаление элемента из середины
        {
            prev_author_ptr->next_ptr = next_author_ptr;
            delete author_ptr;
        }

    }
}

int count_authors(composition* ptr)             // подсчет поличества авторов
{
    int count_authors = 0;
    author* author_ptr = ptr->author_ptr;
    if (author_ptr == nullptr)
        count_authors = 0;
    else
    {
        while(author_ptr != nullptr)
        {
            count_authors++;
            author_ptr = author_ptr->next_ptr;
        }
    }
    return count_authors;
}

void output_file_creator(string file_name)                              // Запись списка в файл              
{
    const int MAX_NAME_LEN = 33;         // + 2 скобки + еще один пробел
    ofstream file;
    file.open(file_name);
    if (file.is_open())
    {
        composition* ptr = head_ptr;

        while(ptr != nullptr)
            {
                string composition_name = ptr->name;
                int length_str = count_symbols(composition_name);
                // file << "[" << composition_name << "]";                         /// старый вариант
                file << "[" << upper_symb(composition_name) << "]";
                file << string(MAX_NAME_LEN - length_str, ' ');

                author* author_ptr = ptr->author_ptr;
                while(author_ptr != nullptr)
                {
                    string author_name = author_ptr->name;
                    
                    // file << " " << author_name;             /// изменил вместо комментариев (старый вариант)
                    file << " " << upper_symb(author_name);

                    author_ptr = author_ptr->next_ptr;
                }
                ptr = ptr->next_ptr;
                if (ptr != nullptr)
                    file << endl;
            }
    }
}

int count_symbols(string str)                   // Подсчет количества символов в строке
{
    int count = 0;
    
    for (int i=0; i < str.length(); i++)
    {
        if (i < str.length() - 1)
        {
            unsigned char first = str[i];
            unsigned char second = str[i+1];

            if (workaround(first, second) == 1)
                i++;
        }

        count++;
    }

    return count;
}