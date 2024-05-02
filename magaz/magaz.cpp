#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
#include <stdlib.h>
using namespace std;

class Product
{
public:
    string product_name;
    double product_price;
    Product(string product_name, double product_price)
    {
        this->product_name = product_name;
        this->product_price = product_price;
    }
};

class User
{
private:
    string login;
    string password;
public:
    vector<Product> korzina;

    string getLogin(){ return login; }
    string getPassword(){ return password; }

    User(string login, string password)
    {
        this->login = login;
        this->password = password;
    }
};

class Shop
{
private:
    Product product = Product("Пиво", 100);
    vector<Product> products = {product};

    User admin = User("admin","12345");
    User user = User("user1","123");
    vector<User> users = { admin,user };
public:
    bool passwordCheck(string login, string password)
    {
        size_t max = users.size();
        for (int i = 0; i < max; i++)
        {
            if ((users[i].getLogin() == login) && (users[i].getPassword() == password))
            {
                return true;
            }
        }
        return false;
    }
    


    void registration()
    {
        cin.ignore();
        string newacc_login, newacc_password;
        cout << "Введите логин: ";
        getline(cin, newacc_login);
        cout << "Введите пароль: ";
        getline(cin, newacc_password);

        size_t max = users.size();
        bool err;
        for (int i = 0; i < max; i++)
        {
            if ((users[i].getLogin() == newacc_login) || newacc_login == "admin")
            {
                err = true;
            }
            else
            {
                err = false;
            }
        }
        if (err == true)
        {
            system("cls");
            cout << "Логин уже занят!\n\n";
        }
        else
        {
            user = User(newacc_login,newacc_password);
            users.push_back(user);
            system("cls");
            cout << "Вы успешно зарегестрировались!\n\n";
        }
    }

    void getProducts()
    {
        size_t max = products.size();
        cout << "Каталог\n\n";
        for (int i = 0; i < max; i++)
        {
            cout << (i + 1) << ". " << products[i].product_name << " " << products[i].product_price << "P\n";
        }
        cout << endl;
    }

    void productAdd(string name, double price)
    {
        product = Product(name,price);
        products.push_back(product);

        system("cls");
        getProducts();
    }

    void productRemove(int number)
    {
        number--;

        int max = products.size();
        if (((number+1) > 0) && ((number+1) <= max))
        {
            vector<Product>::iterator iter = products.begin();
            advance(iter, number);
            products.erase(iter);

            system("cls");
            getProducts();
        }
        else
        {
            cout << "\nПродукт под таким номером не существует!\n\n";
        }
        
    }

    void productEdit(int number, string name, double price)
    {
        number--;
        size_t max = products.size();
        if (((number+1) > 0) && ((number+1) <= max))
        {
            products[number].product_name = name;
            products[number].product_price = price;
            cout << "\nТовар успешно изменен\n\n";
        }
        else
        {
            cout << "\nТовар под таким номером не существует!\n\n";
        }

        system("cls");
        getProducts();
    }

    void getAccounts()
    {
        size_t max = users.size();
        for (int i = 0; i < max; i++)
        {
            cout << (i + 1) << ". " << users[i].getLogin() << endl;
        }
        cout << endl;
    }

    void getKorzina()
    {
        size_t max = user.korzina.size();
        for (int i = 0; i < max; i++)
        {
            cout << (i + 1) << ". " << user.korzina[i].product_name << " " << user.korzina[i].product_price << "P. \n";
        }
        cout << endl;
    }

    void insertKorzina()
    {
        int num;
        getProducts();
        cout << "\nВведите номер товара :";
        cin >> num;

        num--;
        size_t max = products.size();
        if (((num+1) <= max) && ((num+1) > 0))
        {
            product = Product(products[num].product_name, products[num].product_price);
            user.korzina.push_back(product);
            cout << "\nТовар добавлен в корзину.\n\n";
        }
        else
        {
            cout << "\nТовар под таким номером не существует!\n\n";
        }
        
    }
    
    void clearKorzina()
    {
        user.korzina.clear();
        cout << "Корзина очищена!\n";
    }

    void buyProducts()
    {
        srand(time(0));
        int check_number = rand();
        int number_card, cvc;
        double sum = 0;
        DATE date;
        cout << "Введите номер карты: ";
        cin >> number_card;
        cout << "Введите код с обратной стороны карты: ";
        cin >> cvc;
        cout << "Введите срок действия карты: ";
        cin >> date;

        system("cls");
        cout << "Чек:\n\n";
        cout << "Номер чека: " << check_number << endl;
        cout << "Товары в чеке:\n";
        getKorzina();
        cout << "Итого к оплате: ";
        size_t max = user.korzina.size();
        for (int i = 0; i < max; i++)
        {
            sum = sum + user.korzina[i].product_price;
        }
        cout << sum << endl << endl;
        user.korzina.clear();
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);

    Shop shop;

    int choice;
    string login, password;
    do
    {
        cout << "Выберите действие:\n1. Авторизация\n2. Регистрация\n3. Выход\n\n";
        cin >> choice;
        switch (choice)
        {
        case 1:
            system("cls");
            cin.ignore();
            cout << "Введите логин: ";
            getline(cin, login);
            cout << "Введите пароль: ";
            getline(cin, password);
            if ((login == "admin") && ((shop.passwordCheck(login, password)) == true))
            {
                system("cls");
                int adm_choice, product_number;
                string product_name;
                double product_price;
                do
                {
                    cout << "Выберите действие:\n1. Посмотреть каталог.\n2. Добавить продукт.\n3. Удалить продукт.\n4. Изменить продукт\n5. Посмотреть все аккаунты\n6. Выйти из аккаунта.\n\n";
                    cin >> adm_choice;
                    switch (adm_choice)
                    {
                    case 1:
                        system("cls");
                        shop.getProducts();
                        cout << endl;
                        break;
                    case 2:
                        system("cls");
                        cin.ignore();
                        cout << "Введите имя: ";
                        getline(cin, product_name);
                        cout << "Введите цену: ";
                        cin >> product_price;
                        shop.productAdd(product_name, product_price);
                        break;
                    case 3:
                        system("cls");
                        shop.getProducts();
                        cout << "Введите номер продукта: ";
                        cin >> product_number;
                        shop.productRemove(product_number);
                        break;
                    case 4:
                        system("cls");
                        shop.getProducts();
                        cout << "Введите номер продукта: ";
                        cin >> product_number;
                        cin.ignore();
                        cout << "Введите имя: ";
                        getline(cin, product_name);
                        cout << "Введите цену: ";
                        cin >> product_price;
                        shop.productEdit(product_number, product_name, product_price);
                        break;
                    case 5:
                        system("cls");
                        shop.getAccounts();
                        break;
                    case 6:
                        system("cls");
                        break;
                    default:
                        break;
                    }
                } while (adm_choice != 6);
            }
            else if ((shop.passwordCheck(login, password)) == true)
            {
                system("cls");
                int user_choice;
                do
                {
                    cout << "Выберите действие:\n1. Посмотреть каталог.\n2. Посмотреть корзину\n3. Добавить товары в корзину\n4. Очистить корзину.\n5. Купить продукты.\n6. Выйти из аккаунта.\n\n";
                    cin >> user_choice;
                    switch (user_choice)
                    {
                    case 1:
                        system("cls");
                        shop.getProducts();
                        cout << endl; 
                        break;
                    case 2:
                        system("cls");
                        cout << "Корзина\n\n";
                        shop.getKorzina();
                        break;
                    case 3:
                        system("cls");
                        shop.insertKorzina();
                        break;
                    case 4:
                        system("cls");
                        shop.clearKorzina();
                        break;
                    case 5:
                        system("cls");
                        shop.buyProducts();
                        break;
                    case 6:
                        system("cls");
                        break;
                    default:
                        system("cls");
                        cout << "Неверное действие!\n\n";
                        break;
                    }
                } while (user_choice != 6);
            }
            else
            {
                system("cls");
                cout << "Неверный логин или пароль!\n\n";
            }
            break;
        case 2:
            system("cls");
            shop.registration();
            break;
        case 3:
            system("cls");
            cout << "Выход...";
            break;
        default:
            system("cls");
            cout << "\nНеверное действие\n";
            break;
        }
    } while (choice != 3);

    return 0;
}