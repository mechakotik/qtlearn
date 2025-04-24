#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QListView>
#include <QMainWindow>
#include <QStringListModel>
#include "add_book_dialog.hpp"
#include "add_user_dialog.hpp"
#include "library.hpp"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);

private slots:
    void showAddUserDialog();
    void deleteUser();
    void showUserBooks();
    void showAddBookDialog();
    void deleteBook();
    void addBookToUser();

private:
    void updateUsersList();
    void updateBooksList();

    Library lib;
    AddUserDialog addUserDialog;
    AddBookDialog addBookDialog;
    QListView* usersList;
    QListView* booksList;
    QStringListModel* usersListModel;
    QStringListModel* booksListModel;
};

#endif // MAIN_WINDOW_HPP
