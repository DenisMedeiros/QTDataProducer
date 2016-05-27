#include "conexaosender.h"
#include <QDateTime>

ConexaoSender::ConexaoSender() : Conexao()
{

}

ConexaoSender::~ConexaoSender()
{

}

void ConexaoSender::enviar(const QString &dado)
{
    QString comando;

    if (this->isAtiva())
    {
        comando = "set "+ dado + "\r\n";

        socket->write(comando.toStdString().c_str());
        if(!socket->waitForBytesWritten(3000))
        {
            throw ErroConexao("Erro na conexão: O servidor parou de responder.");
        }
    } else {
        throw ErroConexao("Erro na conexão: O servidor parou de responder.");
    }

}
