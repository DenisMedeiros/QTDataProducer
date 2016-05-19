/**
 * @file conexaonaoestabelecida.h
 * @author Denis Ricardo da Silva Medeiros
 * @date 10 May 2016
 * @brief Exceção que é gerada quando este programa 
 * não consegue conectar ao servidor.
 */

#ifndef CONEXAONAOESTABELECIDA_H
#define CONEXAONAOESTABELECIDA_H

#include <iostream>
#include <QString>

/**
 * @brief Esta é exceção que é gerada quando este programa 
 * não consegue conectar ao servidor via socket.
 */
class ConexaoNaoEstabelecida
{

private:

 /** @brief Mensagem de erro informada pelo usuário. */
  QString mensagem;

public:

  /**
   * @brief Este é o construtor padrão desta classe.
   *
   * Ele deve pode receber uma mensagem de erro como parâmetro.
   * @param _mensagem A mensagem de erro informada pelo usuário.
   */
  ConexaoNaoEstabelecida(QString _mensagem = "Não foi possível se conectar ao servidor.") {
      mensagem = _mensagem;
  }

  /**
   * @brief Este método retorna a mensagem de erro.
   *
   * @return mensagem A mensagem de erro informada pelo usuário.
   */
  QString getMensagem(void) const {
      return mensagem;
  }

};

#endif // CONEXAONAOESTABELECIDA_H