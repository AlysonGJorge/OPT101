/**
 * Definição das principais configurações do sistema
 */
#ifndef CONFIG_H
#define CONFIG_H

//===----------------------------------------------------------------------===//
// Definições de Tempo
//===----------------------------------------------------------------------===//

/**
 * Tempo limite para verificação de envio. Em micro segundos.
 */
#define TIMEOUT_SEND 6000

/**
 * Tempo limite para verificação de recebimento. Em micro segundos.
 */
#define TIMEOUT_RECV 2000

/**
 * Tempo limite para verificação de recebimento do RTS.
 */
#define TIMEOUT_RTS 6000

/**
 * Tempo limite para verificação de recebimento do CTS.
 */
#define TIMEOUT_CTS 6000

/**
 * Tempo limite para verificação do ACK. Em micro segundos.
 */
#define TIMEOUT_ACK 2000

/**
 * Tempo de delay para preencher o buffer. Em micro segundos.
 */
#define DELAY_SEND 200

/**
 * Tempo de delay para receber um RTS.
 */
#define DELAY_RTS 120

/**
 * Tempo de delay para receber um CTS.
 */
#define DELAY_CTS 120

/**
 * Tempo de delay após enviar uma mensagem. Em micro segundos.
 */
#define DELAY_RECV 70

/**
 * Tempo de espera antes de realizar as operações no loop.
 */
#define WAIT_LOOP 600

//===----------------------------------------------------------------------===//
// Definições de Serial
//===----------------------------------------------------------------------===//

/**
 * Define a velocidade com que os dados são enviados ou recebidos em uma
 * interface serial.
 */
#define BAUD_RATE 115200

//===----------------------------------------------------------------------===//
// Definições da Rede
//===----------------------------------------------------------------------===//

/**
 * Endereço da rede.
 */
#define NETWORK_ADDR 113

/**
 * Endereço curinga. Serve para aceitar pacotes de qualquer um na rede.
 */
#define WILD_ADDR 0

/**
 * Endereço do nó master>
 */
#define MASTER_ADDR 1

/**
 * Endereço do nó worker led.
 */
#define WORKER_LED_ADDR 2

/**
 * Endereço do nó worker sensor.
 */
#define WORKER_SENSOR_ADDR 3

//===----------------------------------------------------------------------===//
// Definições do Sensor
//===----------------------------------------------------------------------===//

/**
 * Define o pino de leitura.
 */
#define SENSOR_PIN A1

#endif // CONFIG_H
