#include "main_window.hpp"
#include <QInputDialog>
#include <QLabel>
#include <QListView>
#include <QMessageBox>
#include <QPushButton>
#include <QStringListModel>
#include <QVBoxLayout>
#include "add_book_dialog.hpp"
#include "user_books_dialog.hpp"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), addUserDialog(this), addBookDialog(this) {
    setWindowTitle("Библиотека");
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    QLabel* usersListTitle = new QLabel("Пользователи", this);
    usersListModel = new QStringListModel(this);
    usersList = new QListView(this);
    usersList->setModel(usersListModel);

    QHBoxLayout* usersButtonsLayout = new QHBoxLayout();
    QPushButton* userAddButton = new QPushButton("Новый", this);
    QPushButton* userDeleteButton = new QPushButton("Удалить", this);
    QPushButton* userBooksButton = new QPushButton("Книги пользователя", this);
    usersButtonsLayout->addWidget(userAddButton);
    usersButtonsLayout->addWidget(userDeleteButton);
    usersButtonsLayout->addWidget(userBooksButton);

    QLabel* booksListTitle = new QLabel("Книги", this);
    booksListModel = new QStringListModel(this);
    booksList = new QListView(this);
    booksList->setModel(booksListModel);

    QHBoxLayout* booksButtonsLayout = new QHBoxLayout();
    QPushButton* bookAddButton = new QPushButton("Новая", this);
    QPushButton* bookDeleteButton = new QPushButton("Удалить", this);
    QPushButton* addBookToUserButton = new QPushButton("Добавить пользователю", this);
    booksButtonsLayout->addWidget(bookAddButton);
    booksButtonsLayout->addWidget(bookDeleteButton);
    booksButtonsLayout->addWidget(addBookToUserButton);

    mainLayout->addWidget(usersListTitle);
    mainLayout->addWidget(usersList);
    mainLayout->addLayout(usersButtonsLayout);
    mainLayout->addWidget(booksListTitle);
    mainLayout->addWidget(booksList);
    mainLayout->addLayout(booksButtonsLayout);

    connect(userAddButton, &QPushButton::clicked, this, &MainWindow::showAddUserDialog);
    connect(userDeleteButton, &QPushButton::clicked, this, &MainWindow::deleteUser);
    connect(userBooksButton, &QPushButton::clicked, this, &MainWindow::showUserBooks);
    connect(bookAddButton, &QPushButton::clicked, this, &MainWindow::showAddBookDialog);
    connect(bookDeleteButton, &QPushButton::clicked, this, &MainWindow::deleteBook);
    connect(addBookToUserButton, &QPushButton::clicked, this, &MainWindow::addBookToUser);
    updateUsersList();
    updateBooksList();
}

void MainWindow::updateUsersList() {
    QStringList userList;
    for(const auto& user : lib.getUsers()) {
        userList << QString::number(user->getId()) + " " + user->getName();
    }
    usersListModel->setStringList(userList);
}

void MainWindow::updateBooksList() {
    QStringList bookList;
    for(const auto& book : lib.getBooks()) {
        bookList << book->getTitle() + " (" + book->getAuthor() + ", " + QString::number(book->getYear()) + ")";
    }
    booksListModel->setStringList(bookList);
}

void MainWindow::showAddUserDialog() {
    if(addUserDialog.exec() == QDialog::Accepted) {
        QString name = addUserDialog.getUserName();
        if(!name.isEmpty()) {
            lib.addUser(makeUser(name, topId));
            updateUsersList();
            topId++;
        }
    }
}

void MainWindow::deleteUser() {
    QModelIndex index = usersList->currentIndex();
    if(index.isValid()) {
        lib.removeUser(lib.getUser(index.row()));
        updateUsersList();
    }
}

void MainWindow::showUserBooks() {
    QModelIndex index = usersList->currentIndex();
    if(index.isValid()) {
        UserBooksDialog dialog(lib.getUser(index.row()), this);
        dialog.exec();
        updateBooksList();
    }
}

void MainWindow::showAddBookDialog() {
    if(addBookDialog.exec() == QDialog::Accepted) {
        QString title = addBookDialog.getTitle();
        QString author = addBookDialog.getAuthor();
        int year = addBookDialog.getYear();
        if(!title.isEmpty() && !author.isEmpty() && year > 0) {
            lib.addBook(std::make_shared<Book>(title, author, year));
            updateBooksList();
        }
    }
}

void MainWindow::deleteBook() {
    QModelIndex index = booksList->currentIndex();
    if(index.isValid()) {
        lib.removeBook(lib.getBook(index.row()));
        updateBooksList();
    }
}

void MainWindow::addBookToUser() {
    QModelIndex userIndex = usersList->currentIndex();
    QModelIndex bookIndex = booksList->currentIndex();
    if(userIndex.isValid() && bookIndex.isValid()) {
        auto user = lib.getUser(userIndex.row());
        auto book = lib.getBook(bookIndex.row());
        user->addBook(book);
    }
}
