#include <stdio.h>
#include <string.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "sdkconfig.h"
#include <esp_log.h>
#include <driver/uart.h>

#define DELAY_MS 1000
#define BAUDRATE 115200
#define CHECK_CRITICAL(x) ESP_ERROR_CHECK(x)
#define CHECK_WEAK(x) {ESP_ERROR_CHECK_WITHOUT_ABORT(x)
// #define BAUDRATE 115200
#define MSG "Msg from ESP-IDF"



void app_main()
{
    // static const char *TAG = "MAIN";
    const uart_port_t uart_num = UART_NUM_2;
    const int uart_buffer_size = 1024;

    uart_config_t uart_config = {
        .baud_rate = BAUDRATE,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };

    //Install UART driver, and get the queue.
    ESP_ERROR_CHECK( uart_driver_install(uart_num, uart_buffer_size*2, 0, 0, NULL, 0) );
    
    // Configure UART parameters
    CHECK_CRITICAL(uart_param_config(uart_num, &uart_config));

    // Set UART pins(TX: IO4, RX: IO5, RTS: IO18, CTS: IO19)
    ESP_ERROR_CHECK(uart_set_pin(uart_num, 17, 16, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));

    uint8_t *data = (uint8_t *)malloc(uart_buffer_size);
    printf("TEST");
    while(1) {
        
        // Receive & Print
        size_t read_len = uart_read_bytes(uart_num, data, uart_buffer_size, DELAY_MS / portTICK_PERIOD_MS);
        if (read_len > 0) {
            char buf[read_len];
            memcpy(buf, data, read_len);
            printf(buf);
            printf("\n");
        }

        printf("read: %u bytes.\n", read_len);
        
        // Send
        uart_write_bytes(uart_num, MSG, strlen(MSG));

        vTaskDelay(DELAY_MS / portTICK_PERIOD_MS);
    }
}
