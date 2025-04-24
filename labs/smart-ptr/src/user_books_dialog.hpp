#ifndef USER_BOOKS_DIALOG_HPP
#define USER_BOOKS_DIALOG_HPP

#include <QDialog>
#include "user.hpp"

class UserBooksDialog : public QDialog {
    Q_OBJECT

public:
    explicit UserBooksDialog(const std::shared_ptr<User>& user, QWidget* parent = nullptr);

private:
    std::shared_ptr<User> user;
};

#endif // USER_BOOKS_DIALOG_HPP
