#ifndef USER_BOOKS_DIALOG_HPP
#define USER_BOOKS_DIALOG_HPP

#include <QDialog>
#include <QListView>
#include <QStringListModel>
#include "user.hpp"

class UserBooksDialog : public QDialog {
    Q_OBJECT

public:
    explicit UserBooksDialog(const std::shared_ptr<User>& user, QWidget* parent = nullptr);

private:
    std::shared_ptr<User> user;
    void rebuildBooksList();

    QListView* listView;
    QStringListModel* model;
    QStringList books;

private slots:
    void deleteCurrentBook();
};

#endif // USER_BOOKS_DIALOG_HPP
