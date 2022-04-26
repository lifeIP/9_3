#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <fstream>
using namespace std;


struct flowers
{
    char s_name[50];
    char s_color[50];
    int s_storage_temperature;
    int s_cost;
    int s_quantity;

};

void print(flowers* f, int count);
int find_temperature(flowers* f, char* flower, int count);
void print_menu();
int load(const char* file, flowers* a);
int sum_castomer(flowers* f, char* flower, int quantity, int count);
void setData(const char* fileName, int size);


int main()
{
    setlocale(LC_ALL, "RUS");

    flowers f[15];
    int count = 0;
    int c = 0;
    char flower[50] = {};
    int q;
    while (true)
    {
        print_menu();
        char ch = _getch();
        switch (ch)
        {
        case '1':
            count = load("TXT.txt", f);
            if (count < 0)
            {
                return 0;
            }
            break;
        case '2':
            print(f, count);
            break;
        case '3':
            cout << "Enter num: ";
            cin >> c;
            setData("TXT.txt", c);
            break;
        case '4':
            cout << "Enter flower name ";
            cin >> flower;
            cout << find_temperature(f, flower, count);
            break;
        case '5':
            cout << "Enter flower name ";
            memset(flower, 0, sizeof(char) * 50);
            cin >> flower;
            cout << "Enter quantity: ";
            cin >> q;
            cout << "All money: " << sum_castomer(f, flower, q, count);
            break;
        case '0':
            return 0;
            break;
        default:
            cout << "Noname command!!!" << endl;
        }
        cout << "..." << endl;
        _getch();
    }

}
void print(flowers* f, int count)
{
    for (int i = 0; i < count; i++)
    {
        cout << "flower #" << i + 1 << endl;
        cout << "flower name " << f[i].s_name << endl;
        cout << "color " << f[i].s_color << endl;
        cout << "storage temperature " << f[i].s_storage_temperature << endl;
        cout << "cost  " << f[i].s_cost << endl;
        cout << "quantity " << f[i].s_quantity << endl;
        cout << endl;
    }
}
int find_temperature(flowers* f, char* flower, int count) {
    int storage_temp;
    for (int i = 0; i < count; i++) {
        if (strncmp(f[i].s_name, flower, 10) == 0) {
            storage_temp = f[i].s_storage_temperature;
        }
    }
    return storage_temp;
}
void print_menu()
{
    cout << endl;
    cout << "1 - Downloading flowers data" << endl;
    cout << "2 - Output data" << endl;
    cout << "3 - Input new data" << endl;
    cout << "4 - Storage temperature" << endl;
    cout << "5 - Get end castomer's information" << endl;
    cout << "0 - Exit" << endl;
    cout << "Enter your answer: ";
}

int load(const char* file, flowers* a)
{
    ifstream f;
    f.open(file);
    if (!f.is_open())
    {
        cout << "File is not open: " << file << endl;
        return -1;
    }

    char buff[100];
    f.getline(buff, 99);
    int count = atoi(buff);

    for (int i = 0; i < count; i++)
    {
        if (f.eof())
        {
            f.close();
            return -1;
        }
        f.getline(a[i].s_name, 49);

        f.getline(a[i].s_color, 49);

        char storage_temperature[49] = {};
        f.getline(storage_temperature, 49);
        a[i].s_storage_temperature = atoi(storage_temperature);

        char cost[49] = {};
        f.getline(cost, 49);
        a[i].s_cost = atoi(cost);

        char quantity[49] = {};
        f.getline(quantity, 49);
        a[i].s_quantity = atoi(quantity);
    }
    f.close();
    return count;
}
int sum_castomer(flowers* f, char* flower, int quantity, int count) {
    int summ;
    for (int i = 0; i < count; i++) {
        if (strncmp(f[i].s_name, flower, 10) == 0) {
            summ = f[i].s_cost * quantity;
        }
    }
    return summ;
}
void setData(const char* fileName, int size) {
    flowers* dataBase = new flowers[size];
    std::ofstream file;
    file.open(fileName, ios::app);
    if (file.is_open()) {
        cout << "Enter flowers detail: " << std::endl;
        for (int i = 0; i < size; i++) {

            cout << "Enter name: " << std::endl;
            std::cin >> dataBase[i].s_name;

            std::cout << "Enter color: " << std::endl;
            std::cin >> dataBase[i].s_color;

            std::cout << "Enter temp storage: " << std::endl;
            std::cin >> dataBase[i].s_storage_temperature;
            for (; dataBase[i].s_storage_temperature < 0 || dataBase[i].s_storage_temperature > 30;) {
                std::cout << "Enter temp storage: " << std::endl;
                std::cin >> dataBase[i].s_storage_temperature;
            }

            std::cout << "Enter cost: " << std::endl;
            std::cin >> dataBase[i].s_cost;
            for (; dataBase[i].s_cost < 0 || dataBase[i].s_cost > 10000;) {
                std::cout << "Enter cost: " << std::endl;
                std::cin >> dataBase[i].s_cost;
            }

            std::cout << "Enter quantity: " << std::endl;
            std::cin >> dataBase[i].s_quantity;
            for (; dataBase[i].s_quantity < 0 || dataBase[i].s_quantity > 1000;) {
                std::cout << "Enter quantity: " << std::endl;
                std::cin >> dataBase[i].s_quantity;
            }


            file << dataBase[i].s_name << std::endl
                << dataBase[i].s_color << std::endl
                << dataBase[i].s_storage_temperature << std::endl
                << dataBase[i].s_cost << std::endl
                << dataBase[i].s_quantity << std::endl;
        }
        file.close();
    }
    else {
        std::cout << "Fatal error! Try again.." << std::endl;
    }
    delete[]dataBase;
}
