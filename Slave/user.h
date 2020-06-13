#ifndef USER_H
#define USER_H
#include <QString>

class User
{
public:
    User() = delete;
    User(const QString &RoomID, const QString &UserID) : _RoomID(RoomID), _UserID(UserID) {}
    QString getRoomID() const;
    QString getUserID() const;
    double getUsage() const;
    double getCost() const;
    void setUsage(double usage);
    void setCost(double cost);

private:
    QString _RoomID;
    QString _UserID;
    double _usage{};
    double _cost{};
};

#endif // USER_H
