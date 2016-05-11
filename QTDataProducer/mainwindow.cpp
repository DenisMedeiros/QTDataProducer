#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QRegExp>
#include <QStringList>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    QString ipRange, portRange;
    QRegExp ipPortaRegex;

    ui->setupUi(this);

    /* Expressão regular para garantir um endereço IP. */
    ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";

    portRange = "([0-9]{1,4}|[1-5][0-9]{4}|6[0-4][0-9]{3}|"
                          "65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5])";

    ipPortaRegex = QRegExp("^" + ipRange
                     + "\\." + ipRange
                     + "\\." + ipRange
                     + "\\." + ipRange + "\\:" + portRange + "$");



    /* Cria um validator para IP. */
    ipPortaValidator = new QRegExpValidator(ipPortaRegex, this);
    ui->lineEditIPPorta->setValidator(ipPortaValidator);

    /* Cria um validator para números reais. */
    faixaValidator = new QIntValidator();

    ui->lineEditFaixaInicio->setValidator(faixaValidator);
    ui->lineEditFaixaFim->setValidator(faixaValidator);

    /* Altere a mensagem padrão na barra de status. */
    ui->statusBar->showMessage("Desconectado");


    /* Preparando a lista de dados enviados. */
    model = new QStringListModel(this);


    /* Adicione o modelo na lista e torne-a não editável. */
    ui->listViewRegistros->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listViewRegistros->setModel(model);

    /* Crie a conexão. */
    conexao = new Conexao();

    connect(conexao, SIGNAL(dadoEnviado(QString)), this, SLOT(inserirDadoLista(QString)));

}

MainWindow::~MainWindow()
{
    delete ipPortaValidator;
    delete faixaValidator;
    delete conexao;
    delete ui;
}

void MainWindow::conectarServidor(bool ativado)
{
    QString ip;
    QStringList ipPorta;
    unsigned int porta;
    int faixaInicio, faixaFim, intervalo;

    if (ativado)
    {
        ipPorta = ui->lineEditIPPorta->text().split(":");

        ip = ipPorta.at(0);
        porta = ipPorta.at(1).toUInt();

        /* Tente criar a conexão. */
        try
        {
            conexao->abrir(ip, porta);
            ui->pushButtonConectar->setText("Desonectar");
            ui->statusBar->clearMessage();
            ui->statusBar->showMessage("Conectado com sucesso ao servidor "
                    + ip + " na porta " + QString::number(porta) + ".");


            /* Inicie o envio de dados. */

            faixaInicio = ui->lineEditFaixaInicio->text().toInt();
            faixaFim = ui->lineEditFaixaFim->text().toInt();
            intervalo = ui->horizontalSliderIntervalo->value();

            conexao->enviarDados(faixaInicio, faixaFim, intervalo);
        }
        catch(ConexaoNaoEstabelecida &erro)
        {
            ui->pushButtonConectar->setChecked(false);
            ui->statusBar->clearMessage();
            ui->statusBar->showMessage(QString(erro.getMensagem()));
        }
    }
    else
    {
        ui->pushButtonConectar->setText("Conectar");
        ui->statusBar->clearMessage();
        ui->statusBar->showMessage("Desconectado.");
        conexao->pararEnvio();
        conexao->fechar();
    }
}

void MainWindow::inserirDadoLista(QString dado)
{
    model->insertRows(0, 1);
    model->setData(model->index(0), dado);
}
