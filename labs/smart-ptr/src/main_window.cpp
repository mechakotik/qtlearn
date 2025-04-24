#include "main_window.hpp"
#include <QVBoxLayout>
#include <QListView>
#include <QStringListModel>
#include <QPushButton>
#include <QLabel>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle("Библиотека");
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    QLabel* usersListTitle = new QLabel("Пользователи", this);
    QListView* usersList = new QListView(this);
    QStringListModel* usersListModel = new QStringListModel();
    usersList->setModel(usersListModel);

    QHBoxLayout* usersButtonsLayout = new QHBoxLayout(this);

    QPushButton* userAddButton = new QPushButton("Новый", this);
    connect(userAddButton, &QPushButton::clicked, [&]() {
        addUserDialog.exec();
    });

    usersButtonsLayout->addWidget(userAddButton);
    usersButtonsLayout->addWidget(new QPushButton("Удалить"));
    usersButtonsLayout->addWidget(new QPushButton("Книги пользователя"));

    QLabel* booksListTitle = new QLabel("Книги", this);
    QListView* booksList = new QListView(this);
    QStringListModel* booksListModel = new QStringListModel();
    booksList->setModel(booksListModel);

    QHBoxLayout* booksButtonsLayout = new QHBoxLayout(this);
    booksButtonsLayout->addWidget(new QPushButton("Новая"));
    booksButtonsLayout->addWidget(new QPushButton("Удалить"));
    booksButtonsLayout->addWidget(new QPushButton("Добавить пользователю"));

    mainLayout->addWidget(usersListTitle);
    mainLayout->addWidget(usersList);
    mainLayout->addLayout(usersButtonsLayout);
    mainLayout->addWidget(booksListTitle);
    mainLayout->addWidget(booksList);
    mainLayout->addLayout(booksButtonsLayout);
}
