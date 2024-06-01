#include <iostream>
#include <filesystem>
#include <algorithm>
#include <fstream>
#include <string>
using namespace std;
namespace fs = std::filesystem;

static void IdenFInDir(fs::path dir1, fs::path dir2);

int main()
{
    setlocale(LC_ALL, "Russian");
    fs::path dir1, dir2;
    cout << "Введите путь до директории 1:";
    cin >> dir1; // запрашиваем путь к папке 1 у пользователя
    cout << "Введите путь до директории 2:";
    cin >> dir2; // запрашиваем путь к папке 2 у пользователя
    IdenFInDir(dir1, dir2);
    return 0;
}
static void IdenFInDir(fs::path dir1, fs::path dir2)
{
    bool result = true; // флаг

    if (!(fs::exists(dir1) && fs::exists(dir2)) || !fs::is_directory(dir1)) // проверка существования обеих директорий
    {
        cout << "Неверно указаны директории, проверьте еще раз";
    }
    else 
    {
        for (const auto& p1 : fs::directory_iterator(dir1)) // перебираем элемнты директории 1
        {
            for (const auto& p2 : fs::directory_iterator(dir2)) // перебираем элемнты директории 2
            {
                ifstream fin1(p1.path(), ios::binary); // открываем файл p1 в бинарном режиме для чтения
                ifstream fin2(p1.path(), ios::binary); // открываем файл p2 в бинарном режиме для чтения
                if (fin1 && fin2) // если оба файла читаются
                {
                    result = true;
                    char ch1, ch2; // переменные для хранения символов из файлов
                    while (fin2.get(ch1) && fin1.get(ch2)) // пока мы можем прочесть символы из файлов в соответствующие переменные: ch1, ch2
                    { 
                        if (ch1 != ch2) // если символы при чтении разные
                        { 
                            result = false; // файлы не одинаковые
                            break; // прерываем цикл
                        }
                    }
                    if (!fin1.eof() && !fin2.eof()) // если мы не достигли концов файлов
                    { 
                        result = false; // файлы не одинаковые
                    } 
                    if (result) // если файлы одинаковые
                    {
                        cout << p1.path() << " , " << p2.path() << " Равны " << endl; // выводим пути до одинаковых файлов
                    }
                    else 
                    { 
                        continue; // продолжаем поиск
                    }
                }
            }
        }
        if (!result) { cout << "Совпадений не найдено"; }
    }
}