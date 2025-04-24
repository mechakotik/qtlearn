#ifndef ADD_USER_DIALOG_HPP
#define ADD_USER_DIALOG_HPP

#include <QDialog>
#include <QLineEdit>

class AddUserDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddUserDialog(QWidget* parent = nullptr);
    QString getUserName() const;

    void showEvent(QShowEvent *event) override {
        lineEdit->setText("");
        QDialog::showEvent(event);
    }

private:
    QLineEdit* lineEdit;
};

#endif // ADD_USER_DIALOG_HPP
