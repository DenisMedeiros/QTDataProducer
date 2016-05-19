#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRegExpValidator>
#include <QStringListModel>
#include "conexao.h"
#include "conexaonaoestabelecida.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    /** Validator para validar a string no formato IP:porta. */
    QRegExpValidator *ipPortaValidator;

    /** Modelo usado para desenhar na lista de IPs. */
    QStringListModel *model;

    /** Conexão utilizada para se comunicar com o servidor. */
    Conexao *conexao;

public slots:
    void conectar(bool);
    void plot(void);
};

#endif // MAINWINDOW_H