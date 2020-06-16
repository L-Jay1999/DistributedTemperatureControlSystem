#ifndef MANAGER_H
#define MANAGER_H
#include <QString>

class Manager
{
public:
    Manager() = delete;
    Manager(const QString &Account, const QString &Password) : _Account(Account), _Password(Password) {}
    QString getAccount() const;
private:
    QString _Account;
    QString _Password;
};

#endif // MANAGER_H
