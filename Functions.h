#include <string>

#define FUNCTIONS_H
#ifdef FUNCTIONS_H

// �������
void menu();
void menuHeader();
void menuAuth();

// �����
void exitNow();

// ���� 
void authorization();

// �������� ������ ������������ + ������ ��������� (�����������������)
void createNewUser();
void createTestMessage();

// �������� �� ������ ( 3 ������� ����� � �����)
bool checkNewPassword(std::string password);

// ������� �������
void clearconsole();

// �������� ���� �� ������������ ������������������
bool checkExistUsersList();

// ����� �� ��������������
void exitCurrentUser();

// ��������� �������� �������������
void createTestUsers();

// ����������� ������� ������������� ������ ����������������
void showUserList();

// ����������� ���������� � �������� �������������
void viewTestUsersInfo();

// �������� ��������� ������������ --> ������������
void sendMessage(int userIDrecipient);

// �������� ��������� ������������ --> ���
void sendMessage();

// �������� ��������� (��� �������� ������������)
void showCountMessageCurrentUser();

// ����������� ���� ���������
void showMyMessage();

#endif // FUNCTIONS_H





