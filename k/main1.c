#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *pathTickets = "tickets.txt";
const char *pathAccounts = "acc.txt";
struct Ticket //Структура для билета
{
    int trainNumber; //Номер поезда
    char station[50]; //Название конечного пункта
    char date[20]; //Дата
    int H1, M1, //Время отбытия
        H2, M2; //Время прибытия
    int cost; //Стоимость билета в копейках
    int ticketsSold; //Кол-во проданных билетов
    int ticketsAvailable; //Кол-вобилетов всего
};
struct Account //Структура для аккаунта
{
    char login[20]; //Поле логина
    char password[20]; //Поле пароля
    char role[10]; //Поле роли
};
int logIn(struct Account *acc, struct Account *accs, int count) //Функция входа в аккаунт
{
    strcpy(acc->role, ""); //Обнуление роли
    for (int i = 0; i < count; i++) //Цикл до конца аккаунтов
    {
        if (strcmp(acc->login, &accs[i].login) == 0 && strcmp(acc->password, &accs[i].password) == 0)//Проверка логина и пароля
        {
            strcpy(acc->role, &accs[i].role); //Сохранение роли
            printf("Role: %s.\n", acc->role); //Вывод роли на экран
            break; //Выход из цикла
        }
    }
    return 0;
}
int loadAccounts(struct Account *accs) //Чтение аккаунтов из файла
{
    FILE *f1; //Файл
    if ((f1 = fopen(pathAccounts, "r+")) == NULL) //Открытие файла , если файл не удалось открыть                                              
    {                                                          //то возвращается NULL
        printf("Cannot open file.\n");
        exit(1);
    }
    int i = 0; //Перемнная для подсчёта количества аккаунтов
    while (!feof(f1)) //Цикл для чтения до конца файла
    {
        char constr[80]; //Временная переменная для чтения
        char *p = constr; //Временная переменная для чтения
        fgets(p, 80, f1); //Чтение строки
        if (p[strlen(p) - 1] == '\n') //Удаление символа перехода на новую строку
            p[strlen(p) - 1] = '\0';
        char *str[80];
        strcpy(str, constr);
        char *token = strtok(str, ";"); //Разделение строки по символу ";"
        strcpy(&accs[i].login, token); //Чтение логина из файла
        token = strtok(NULL, ";"); //Чтение в строке до следующего символа ";"
        strcpy(&accs[i].password, token); //Чтение пароля из файла
        token = strtok(NULL, ";"); //Чтение в строке до следующего символа ";"
        strcpy(&accs[i].role, token); //Чтение роли из файла
        i++; //Подсчёт аккаунтов
    }
    fclose(f1); //Закрытие файла
    return i; //Возвращаем кол-во аккаунтов
}
int loadTickets(struct Ticket *t) //Чтение билетов из файла
{
    FILE *f1; //Файл
    if ((f1 = fopen(pathTickets, "r+")) == NULL) //Открытие файла
    {
        printf("Cannot open file.\n");
        exit(1);
    }
    int i = 0; //Перемнная для подсчёта количества билетов
    while (!feof(f1)) //Цикл чтения до конца файла
    {
        char constr[80];
        char *p = constr;
        fgets(p, 80, f1);
        if (p[strlen(p) - 1] == '\n')
            p[strlen(p) - 1] = '\0';
        char *str[80];
        strcpy(str, constr);
        char *token = strtok(str, ";"); //Разделение строки по символу ";"
        char *pp[80];
        strcpy(pp, token);
        t[i].trainNumber = atoi(pp);
        token = strtok(NULL, ";");
        strcpy(&t[i].station, token);
        token = strtok(NULL, ";");
        strcpy(&t[i].date, token);
        token = strtok(NULL, ";");
        strcpy(pp, token);
        t[i].H1 = atoi(pp);
        token = strtok(NULL, ";");
        strcpy(pp, token);
        t[i].M1 = atoi(pp);
        token = strtok(NULL, ";");
        strcpy(pp, token);
        t[i].H2 = atoi(pp);
        token = strtok(NULL, ";");
        strcpy(pp, token);
        t[i].M2 = atoi(pp);
        token = strtok(NULL, ";");
        strcpy(pp, token);
        t[i].cost = atoi(pp);
        token = strtok(NULL, ";");
        strcpy(pp, token);
        t[i].ticketsSold = atoi(pp);
        token = strtok(NULL, ";");
        strcpy(pp, token);
        t[i].ticketsAvailable = atoi(pp);
        i++;
    }
    fclose(f1); //Закрытие файла
    return i; //Возвращаем кол-во билетов
}
int printTicket(struct Ticket t) //Вывод билетов на экран
{
    printf("Train number: %d, ", t.trainNumber);
    printf("Station: %s, ", t.station);
    printf("Time: %s, %d:%d, Time2: %d:%d\n", t.date, t.H1, t.M1, t.H2, t.M2);
    printf("Cost: %.2f BYN, ", t.cost/100.0);
    printf("Sold: %d/%d\n", t.ticketsSold, t.ticketsAvailable);
    return 0;
}
int printAcc(struct Account acc) //Вывод аккаунта на экран
{
    printf("Login: %s, ", acc.login);
    printf("Password: %s, ", acc.password);
    printf("Role: %s.\n", acc.role);
    return 0;
}
int saveAccounts(int count, struct Account accs[]) //Сохранение аккаунтов в файл
{
    FILE *f2; //Переменая файла
    f2 = fopen(pathAccounts, "w+"); //Открытие файла
    for (int i = 0; i < count; i++) //Цикл на все аккаунты
    {
        char buf[80];//Временная переменная
        sprintf(buf, "%s;%s;%s", accs[i].login, accs[i].password, accs[i].role); //Формирование строки с данными об аккаунте в переменную buf
        fputs(buf, f2); //Сохренение строки buf в файл
        if (i + 1 < count) //Добавление перехода на новую строку
            fputs("\n", f2);
    }
    fclose(f2); //Закрытие файла
}
int saveTickets(int count, struct Ticket t[]) //Сохранение билетов в файл
{
    FILE *f2; //Переменая файла
    f2 = fopen(pathTickets, "w+"); //Открытие файла
    for (int i = 0; i < count; i++) //Цикл на все билеты
    {
        char buf[80]; //Временная переменная
        sprintf(buf, "%d;%s;%s;%d;%d;%d;%d;%d;%d;%d", t[i].trainNumber, t[i].station, t[i].date,
                t[i].H1, t[i].M1, t[i].H2, t[i].M2,
                t[i].cost, t[i].ticketsSold, t[i].ticketsAvailable); //Формирование строки с данными о билете в переменную buf
        fputs(buf, f2); //Сохренение строки buf в файл
        if (i + 1 < count) //Добаление перехода на новую строку
            fputs("\n", f2);
    }
    fclose(f2); //Закрытие файла
}
int addAccount(int count, struct Account *accs) //Добавление аккаунта
{
    printf("Enter login:\n"); //Запрос логина
    scanf("%s", accs[count].login); //Ввод логина
    printf("Enter parol:\n"); //Запрос пароля
    scanf("%s", accs[count].password); //Ввод пароля
    int p = 3;
    while (p > 2 || p < 1)
    {
        printf("Enter role: 1-admin, 2-user\n"); //Запрос роли
        scanf("%d", &p); //Ввод роли
        if (p == 1)
            strcpy(accs[count].role, "admin");
        if (p == 2)
            strcpy(accs[count].role, "user");
    }
    printf("Account has been added!\n"); //Вывод сообщения об успешном добавлении аккаунта
}
int addTicket(int count, struct Ticket *t) //Добавление билета
{
    printf("Enter the number of train:\n"); //Запрос номера поезда
    scanf("%d", &t[count].trainNumber); //Ввод номера поезда
    printf("Enter the last station:\n"); //Запрос станции
    scanf("%s", t[count].station); //Ввод станции
    printf("Enter the date:\n"); //Запрос даты
    scanf("%s", t[count].date); //Ввод даты
    printf("Enter the hour1:\n"); //Запрос часа отбытия
    scanf("%d", &t[count].H1); //Ввод часа отбытия
    printf("Enter the min1:\n"); //Запрос минут отбытия
    scanf("%d", &t[count].M1); //Ввод минут отбытия
    printf("Enter the hour2:\n"); //Запрос часа прибытия
    scanf("%d", &t[count].H2); //Ввод часа прибытия
    printf("Enter the min2:\n"); //Запрос минут прибытия
    scanf("%d", &t[count].M2); //Ввод минут прибытия
    printf("Enter the cost (in coins):\n"); //Запрос стоимости в копейках
    scanf("%d", &t[count].cost); //Ввод стоимости в копейках
    t[count].ticketsSold = 0; //Обнуление проданных билетов
    printf("Enter the tickets count:\n"); //Запрос кол-ва билетов
    scanf("%d", &t[count].ticketsAvailable); //Ввод кол-ва билетов
    printf("Ticket has been added!\n"); //Вывод сообщения об успешном добавлении билета
}
int delAccount(int p, int count, struct Account *accs) //Удаление аккаунта
{
    for (int i = p; i < count - 1; i++) //Цикл пользователей с удаляемого до конца
    {
        accs[i] = accs[i+1]; //Смещение оставшихся пользователей
    }
}
int delTicket(int p, int count, struct Ticket *t) //Удаление билета
{
    for (int i = p; i < count - 1; i++) //Цикл билетов с удаляемого до конца
    {
        t[i] = t[i+1]; //Смещение оставшихся билетов
    }
}
int editAccount(struct Account *acc) //Редактирование аккаунта
{
    printf("Enter login:\n"); //Запрос логина
    scanf("%s", acc->login); //Ввод логина
    printf("Enter password:\n"); //Запрос пароля
    scanf("%s", acc->password); //Ввод пароля
    int p = 3;
    while (p > 2 || p < 1)
    {
        printf("Enter role: 1-admin, 2-user\n"); //Запрос роли
        scanf("%d", &p); //Ввод роли
        if (p == 1)
            strcpy(acc->role, "admin");
        if (p == 2)
            strcpy(acc->role, "user");
    }
    printf("Account has been edited!\n"); //Вывод сообщения об успешном редактировании аккаунта
}
int editTicket(struct Ticket *t) //Редактирование билета
{
    printf("Enter the number of train:\n"); //Запрос номера поезда
    scanf("%d", &t->trainNumber); //Ввод номера поезда
    printf("Enter the last station:\n"); //Запрос станции
    scanf("%s", t->station); //Ввод станции
    printf("Enter the date:\n"); //Запрос даты
    scanf("%s", t->date); //Ввод даты
    printf("Enter the hour1:\n"); //Запрос часа отбытия
    scanf("%d", &t->H1); //Ввод часа отбытия
    printf("Enter the min1:\n"); //Запрос минут отбытия
    scanf("%d", &t->M1); //Ввод минут отбытия
    printf("Enter the hour2:\n"); //Запрос часа прибытия
    scanf("%d", &t->H2); //Ввод часа прибытия
    printf("Enter the min2:\n"); //Запрос минут прибытия
    scanf("%d", &t->M2); //Ввод минут прибытия
    printf("Enter the cost (in coins):\n"); //Запрос стоимости в копейках
    scanf("%d", &t->cost); //Ввод стоимости в копейках
    printf("Enter the sold tickets count:\n"); //Запрос кол-ва проданных билетов
    scanf("%d", &t->ticketsSold); //Ввод кол-ва проданных билетов
    printf("Enter the tickets count:\n"); //Запрос кол-ва билетов
    scanf("%d", &t->ticketsAvailable); //Ввод кол-ва билетов
    printf("Ticket has been edited!\n"); //Вывод сообщения об успешном редактировании билета
}
int sortTickets(int count, struct Ticket *t) //Сортировка билетов
{
    for (int j = 0; j < count; j++)
        for (int i = 0; i < count - 1; i++)
        {
            if (strcmp(t[i].station, t[i+1].station) > 0) //Сравнение конечных станций
            {
                struct Ticket p; //Временная переменная
                p = t[i]; //Обмен значений
                t[i] = t[i+1]; //Обмен значений
                t[i+1] = p; //Обмен значений
            }
        }
}
int buy(int count, struct Ticket tickets[]) //Покупка билета
{
    printf("Which city do you want to go to?\n"); //Ввод необходимого конечного пункта
    char city[50];
    scanf("%s", &city);
    printf("From what time (hour) do you need a ticket?\n"); //Ввод с какого часа необходим билет
    int hour1;
    scanf("%d", &hour1);
    printf("Until what time (hour) do you need a ticket?\n"); //Ввод до какого часа необходим билет
    int hour2;
    scanf("%d", &hour2);
    for (int i = 0; i < count; i++) //Цикл на все билеты
    {
        if (strcmp(tickets[i].station, city) == 0 &&
            tickets[i].H1 >= hour1 &&
            tickets[i].H2 < hour2) //Проверка билета
        {
            printf("%3d|", i); //Вывод подходящего билета
            printTicket(tickets[i]);
        }
    }
    printf("Which ticket do you want to buy?\n"); //Запрос на покупку билета
    int ticketNumber;
    scanf("%d", &ticketNumber);
    if (ticketNumber < 0 || ticketNumber >= count) //Проверка корректности введённого номера
    {
        printf("Error"); //Вывод ошибки
        exit(1);
    }
    if (tickets[ticketNumber].ticketsSold < tickets[ticketNumber].ticketsAvailable) //Проверка: остались ли билеты
    {
        tickets[ticketNumber].ticketsSold++; //Продажа
        printf("Sold!\n");
    }
    else
    {
        printf("Unfortunately, tickets ran out"); //Вывод ошибки о том, что билеты закончились
    }
}
int main()
{
    struct Account accs[100]; //Массив аккаунтов
    int accCount; //Переменная количества аккаунтов
    accCount = loadAccounts(accs); //Загрузка аккаунтов из файла
    struct Account acc; //Переменная аккаунта
    printf("Enter login:\n"); //Запрос логина
    scanf("%s", acc.login); //Ввод логина
    printf("Enter password:\n"); //Запрос пароля
    scanf("%s", acc.password); //Ввод пароля
    logIn(&acc, accs, accCount); //Попытка входа
    if (strcmp(acc.role, "") == 0) //Проверка корректности входа по роли (при корректном входе роль будет отлична от псутой строки)
    {
        printf("Error. Account not found."); //Вывод ошибки: не найден пользователь
        exit(0); //Завершение работы программы
    }
    struct Ticket tickets[100]; //Массив билетов
    int count; //Переменная количества билетов
    count = loadTickets(tickets); //Загрузка билетов
    int act = 0; //Переменная для меню
    if (strcmp(acc.role, "admin") == 0) //Меню для администратора
    {
        while (1)
        {
            printf("0-exit, 1-users, 2-tickets\n"); //Запрос действия
            scanf("%d", &act); //Ввод действия
            switch (act)
            {
                case 0:
                    {
                        saveTickets(count, tickets); //Сохранение билетов в файл
                        saveAccounts(accCount, accs); //Сохранение аккаунтов в файл
                        exit(0); //Завершение работы программы
                    }
                    break;
                case 1:
                    {
                        int act2 = -1; //Переменная для меню
                        while(act2 != 0)
                        {
                            printf("0-return, 1-print all accounts, 2-add, 3-delete, 4-edit\n"); //Запрос действия
                            scanf("%d", &act2); //Ввод действия
                            switch (act2)
                            {
                                case 1: //Вывод всех пользователей
                                {
                                    for (int i = 0; i < accCount; i++)
                                    {
                                        printf("%3d|", i);
                                        printAcc(accs[i]);
                                    }
                                }
                                break;
                                case 2: //Добавление нового пользователя
                                {
                                    addAccount(accCount, accs); //Добавление нового пользоватея
                                    accCount++; //Увеличение количества пользователей
                                }
                                break;
                                case 3: //Удаление пользователя
                                {
                                    for (int i = 0; i < accCount; i++)
                                    {
                                        printf("%3d|", i);
                                        printAcc(accs[i]);
                                    }
                                    printf("Which user should be deleted?"); //Запрос номера пользователя для удаления
                                    int p = -1;
                                    while (p < 0 || p >= accCount)
                                        scanf("%d", &p); //Ввод номера пользователя
                                    printf("Are you sure want to delete account? 1-yes\n"); //Подтверждение удаления
                                    int q;
                                    scanf("%d", &q);
                                    if (q == 1)
                                    {
                                        delAccount(p, accCount, accs); //Удаление пользователя
                                        accCount--; //Уменьшение кол-ва пользоватеей
                                    }
                                }
                                break;
                                case 4: //Редактирование пользователя
                                {
                                    for (int i = 0; i < accCount; i++)
                                    {
                                        printf("%3d|", i);
                                        printAcc(accs[i]);
                                    }
                                    printf("Which user should be edited? "); //Запрос номера пользователя для редактирования
                                    int p = -1;
                                    while (p < 0 || p >= accCount)
                                        scanf("%d", &p); //Ввод номера пользователя
                                    editAccount(&accs[p]); //Редактирование пользователя
                                }
                                break;
                            }
                        }
                    }
                    break;
                case 2:
                    {
                        int act2 = -1; //Переменная для меню
                        while(act2 != 0)
                        {
                            printf("0-return, 1-print all tickets, 2-add, 3-delete, 4-edit, 5-sort\n"); //Запрос действия
                            scanf("%d", &act2); //Ввод действия
                            switch (act2)
                            {
                                case 1: //Вывод всех билетов
                                {
                                    for (int i = 0; i < count; i++)
                                    {
                                        printf("%3d|", i);
                                        printTicket(tickets[i]);
                                    }
                                }
                                break;
                                case 2: //Добавление нового билета
                                {
                                    addTicket(count, tickets); //Добавление нового билета
                                    count++; //Увеличение количества билетов
                                }
                                break;
                                case 3: //Удаление билета
                                {
                                    for (int i = 0; i < count; i++)
                                    {
                                        printf("%3d|", i);
                                        printTicket(tickets[i]);
                                    }
                                    printf("Which ticket should be deleted?"); //Запрос номера билета для удаления
                                    int p = -1;
                                    while (p < 0 || p >= count)
                                        scanf("%d", &p); //Ввод номера билета
                                    printf("Are you sure want to delete ticket? 1-yes\n"); //Подтверждение удаления
                                    int q;
                                    scanf("%d", &q);
                                    if (q == 1)
                                    {
                                        delTicket(p, count, tickets); //Удаление билета
                                        count--; //Уменьшение кол-ва билетов
                                    }
                                }
                                break;
                                case 4: //Редактирование билета
                                {
                                    for (int i = 0; i < count; i++)
                                    {
                                        printf("%3d|", i);
                                        printTicket(tickets[i]);
                                    }
                                    printf("Which ticket should be edited? "); //Запрос номера билета для редактирования
                                    int p = -1;
                                    while (p < 0 || p >= count)
                                        scanf("%d", &p); //Ввод номера билета
                                    editTicket(&tickets[p]); //Редактирование билета
                                }
                                break;
                                case 5: //Сортировка билетов
                                {
                                    sortTickets(count, tickets); //Сортировка билетов
                                }
                                break;
                            }
                        }
                    }
                    break;
            }
        }
    }
    if (strcmp(acc.role, "user") == 0) //Меню для пользователя
    {
        while (1)
        {
            printf("0-exit, 1-buy, 2-print all tickets\n"); //Запрос действия
            scanf("%d", &act); //Ввод действия
            switch (act)
            {
                case 0: //Выход
                {
                    saveTickets(count, tickets);
                    exit(0);
                }
                break;
                case 1: //Покупка
                {
                    buy(count, tickets);
                }
                break;
                case 2: //Вывод всех билетов
                {
                    for (int i = 0; i < count; i++)
                    {
                        printf("%3d|", i);
                        printTicket(tickets[i]);
                    }
                }
                break;
            }
        }
    }
    return 0;
}
