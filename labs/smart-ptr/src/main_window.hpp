#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QMainWindow>
#include "library.hpp"
#include "add_user_dialog.hpp"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    Library lib;
    AddUserDialog addUserDialog;
};

#endif // MAIN_WINDOW_HPP
