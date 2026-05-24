#include <iostream>
#include <ncurses.h>
#include <unistd.h>         // Для использования задержки по времени sleep()
using namespace std;


// проверка является ли символ русским двухбайтовым символом
int workaround(unsigned char first, unsigned char second) {             // возвращает 1, если это символ кириллицы (2 байтовый)
    // D0 90-BF (А-Я), D0 80-8F (а-п), D1 80-BF (р-я, Ё)            // иначе 0
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



int main()
{
setlocale(LC_ALL, "ru_RU.UTF-8");

    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    int x, y;
    unsigned char terminals[100] = "";
    printw("Введите строку: ");
    string str = "";
    int pred_ch = 0;            // Для хранения предыдущего символа
    int next_ch;
    bool flag = false;
    while(true)
    {    
        // clear();
        refresh();
        int ch = getch();
        if (ch == KEY_BACKSPACE)
        {
            // if (str != "")           // Первая версия костыля, которая работала только, если строка вся на русском
            // {                        // работала она при помощи булевого флага
            //     if (flag == false)       
            //     {
            //         str.erase(str.length()-1, 1);
            //         getyx(stdscr, y, x);
            //         move(y, x);
            //         delch();
            //     }
            //     else                                    // Если удаляем двухбайтный символ
            //     {
            //         str.erase(str.length()-2, 2);
            //         getyx(stdscr, y, x);
            //         move(y, x);
            //         delch();
            //         // next_ch = 10000;
            //     }
            // }
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
                        // next_ch = 10000;
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
        else if (ch == 27)
        {
            break;
        }
        else if (ch == 10)
            break;

        else
        {
            str += ch;
            pred_ch = ch;
            if (ch >= 0xC0 && ch <= 0xDF)
            {                                       // если двухбайтовый символ
                next_ch = getch();              // считываем находящийся в буфере второй байт символа
                str += next_ch;
                flag = true;
            }
        }


        // if (ch >= 0xC0 && ch <= 0xDF) { // если двухбайтовый символ
        //         int next_ch = getch(); // считываем находящийся в буфере второй байт символа
        //         // проверяем кирилица ли это
        //             if (next_ch >= 0x80 && next_ch <= 0xBF && kostil(ch, next_ch)) 
        //             {
                          
        //             }     
        //             else 
        //                 printw("Unknow symbol");   
        // }


    }
    endwin();

    cout << endl << str << endl;
    // printw("\n %s\n", str.c_str());
    // sleep(5);
    // endwin();
    return 0;
}




    // if (ch >= 0xC0 && ch <= 0xDF) { // если двухбайтовый символ
    //             int next_ch = getch(); // считываем находящийся в буфере второй байт символа
    //             // проверяем кирилица ли это
    //                 if (next_ch >= 0x80 && next_ch <= 0xBF && kostil(ch, next_ch)) 
    //                 {
                          
    //                 }     
    //                 else 
    //                     printw("Unknow symbol");   
    //     }
