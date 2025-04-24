#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QListView>
#include <QMainWindow>
#include <QStringListModel>
#include "add_book_dialog.hpp"
#include "add_user_dialog.hpp"
#include "find_book_dialog.hpp"
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
    void showFindBookDialog();
    void addBookToUser();

private:
    void updateUsersList();
    void updateBooksList();

    Library lib;
    AddUserDialog addUserDialog;
    AddBookDialog addBookDialog;
    FindBookDialog findBookDialog;
    QListView* usersList;
    QListView* booksList;
    QStringListModel* usersListModel;
    QStringListModel* booksListModel;
    int topId = 0;
};

#endif // MAIN_WINDOW_HPP
