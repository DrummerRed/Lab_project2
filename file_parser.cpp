#include "header.h"

void file_reader_interface()                    // Выбор режима "Чтение из файла"
{
    bool flag_esc = false;
    int choice = 0;
    while(!flag_esc)
    {
        bool empty = list_is_empty();
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
                // какая то логика...
                flag_esc = true;
            }
        }
        
        refresh();
    }
}

string file_name_input()                            // Считывание имени файла
{                                                   // Возвращает имя файл, если такой файл существует
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

int file_checker(string file_name)       // Функция проверки существования рабочего файла программы
{                                         // Возвращает 1, если файл с таким именем отсутствует
    ifstream file;                        // 2, если файл пуст
    file.open(file_name);        

    if (!file.is_open())                  // 0, если файл полностью корректен
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