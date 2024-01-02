#include <string>

#define FUNCTIONS_H
#ifdef FUNCTIONS_H

// менюшка
void menu();
void menuHeader();
void menuAuth();

// выход
void exitNow();

// вход 
void authorization();

// создание нового пользователя + личных сообщений (предустановленные)
void createNewUser();
void createTestMessage();

// проверка на пароль ( 3 символа цифры и буквы)
bool checkNewPassword(std::string password);

// очистка консоли
void clearconsole();

// проверка есть ли пользователи зарегистрированные
bool checkExistUsersList();

// выход из авторизованных
void exitCurrentUser();

// создвание тестовых пользователей
void createTestUsers();

// отображение сколько пользователей сейчас зарегистрировано
void showUserList();

// отображение информации о тестовых пользователях
void viewTestUsersInfo();

// отправка сообщения пользователь --> пользователь
void sendMessage(int userIDrecipient);

// отправка сообщения пользователь --> все
void sendMessage();

// проверка сообщений (для текущего пользователя)
void showCountMessageCurrentUser();

// отображение моих сообщений
void showMyMessage();

#endif // FUNCTIONS_H





