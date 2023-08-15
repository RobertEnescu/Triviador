#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GUI_Triviador.h"
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMessageBox>
#include <QMainWindow>
#include <QCloseEvent>
#include <string>
#include "Register.h"
#include "ui_Register.h"
#include "ui_lobby.h"
#include "game.h"
#include "lobby.h"
#include <cpr/cpr.h>
#include <crow.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class GUI_Triviador : public QMainWindow
{
    Q_OBJECT

public:
    GUI_Triviador(QWidget* parent = nullptr);
    ~GUI_Triviador();

private slots:
    void on_LoginButton_clicked();
    void on_CancelButton_clicked();
    void on_RegisterButton_clicked();
    void on_registerFinished();
    //void closeEvent(QCloseEvent* event);

private:
    Ui::MainWindow* ui;
    Register* m_pRegister;
    Lobby* m_Lobby;
};
#endif // MAINWINDOW_H

