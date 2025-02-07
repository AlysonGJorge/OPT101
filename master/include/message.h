#ifndef MESSAGE_H
#define MESSAGE_H

#include <Arduino.h>

//===----------------------------------------------------------------------===//
// Definições das flags dos protocolos
//===----------------------------------------------------------------------===//

/**
 * Acknowledge.
 *
 * Usado para reconhecer que a mensagem chegou até o destino
 */
#define ACK 1

/**
 * Clear to Send.
 *
 * Diz aos nós da rede que está livre para receber mensagens.
 */
#define CTS 2

/**
 * Request to Send.
 *
 * Diz aos nós da rede que deseja enviar uma mensagem.
 */
#define RTS 3

/**
 * Data.
 *
 * Diz ao nó que o pacote atual tem dados que podem ser interpretados..
 */
#define DTA 4

//===----------------------------------------------------------------------===//
// Funções públicas
//===----------------------------------------------------------------------===//

/**
 * @brief Envia uma mensagem
 *
 * Inicializa um pacote com cabeçalho e demais metadados e então envia o mesmo
 * na rede.
 * Pacotes do tipo DTA precisam de um recebimento ACK. Demais pacotes só são
 * enviados.
 *
 * @param destiny Endereço de destino da mensagem
 * @param flag Definição do tipo de pacote
 * @param body Dados do pacote
 *
 * @return true se a mensagem foi enviada, false caso contrário
 */
bool send_msg(uint8_t destiny, uint8_t flag, uint8_t body);

/**
 * @brief Recebe uma mensagem
 *
 * Escuta a rede esperando receber um pacote.
 * Pacotes do tipo DTA ao serem recebidos geram o envio de um ACK. Demais
 * pacotes só são recebidos.
 *
 * @param source Endereço de origem esperado
 * @param flag Tipo de pacote esperado
 * @param body Dados do pacote. Somente o pacote DTA usa este campo
 *
 * @return true se a mensagem foi recebida, false caso contrário.
 */
bool receive_msg(uint8_t source, uint8_t flag, uint8_t &body);

#endif // MESSAGE_H