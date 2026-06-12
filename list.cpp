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

void delete_composition(int index)          /// Стоит допсисать освобождение памяти авторов
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
            if (next_ptr == nullptr)                // Удаление последнего эдемента
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

void viewing_compositions()             // Пока как отладочный принт
{                                       // Добавить удаление
    bool flag_esc = false;
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
            printw("\nДля удаления произведения введите его номер: ");
            string cash = input_string(&flag_esc);
            if (!flag_esc)
            {
                int index = stoi(cash);
                if ((index > 0) && (index <=iterator))
                    delete_composition(index);
            }
                ////else/////////////////

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
    // while(author_ptr != nullptr)
    //     author_ptr = author_ptr->next_ptr;
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

    // author_ptr = new author;
    // author_ptr->name = author_name;
}

void show_list()                            // Вывод всего списка
{     
    int ch = 0;                                  
    while(ch != 27)
    {
        clear();
        printw("Для возвращения нажмите Esc\n");
        printw("---------------------------\n\n");

        composition* ptr = head_ptr;
        int iterator = 0;
        if (ptr == nullptr)
        {
            printw("Записи о произведениях отсутствуют");
        }
        else
        {
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
        }

    ch = getch();
    
    }
}             

void viewing_authors()              // Просмотр и удаление авторов       
{                                       
    bool flag_esc = false;
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

            printw("\nДля удаления автора введите номер его произведения: ");
            string cash = input_string(&flag_esc);
            if (!flag_esc)
            {
                int index = stoi(cash);
                if ((index > 0) && (index <=iterator))
                    delete_composition(index);
            }
            

        }
        refresh();
    }
}

void delete_author(int index)
{
    
}