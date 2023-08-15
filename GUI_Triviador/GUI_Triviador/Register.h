#pragma once

#include <QDialog>
#include "ui_Register.h"
#include <QMessageBox>
#include <string>
#include <cpr/cpr.h>
#include <crow.h>
QT_BEGIN_NAMESPACE
namespace Ui { class RegisterUi; }
QT_END_NAMESPACE
class Register : public QDialog
{
	Q_OBJECT

public:
	Register(QWidget *parent = nullptr);
	~Register();
private slots:
	void on_RegisterButton_clicked();
	void on_CancelButton_clicked();
	void on_LoginButton_clicked();
private:
	Ui::RegisterUi* ui;
};
