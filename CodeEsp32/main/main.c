#include <stdio.h>
#include <stdlib.h>

#include "string.h"
#include "nvs_flash.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"


#include "dht11.h"
#include "mqtt_connect.h"
#include "wifi_connect.h"

extern char temp_value[10];
extern char humidity_value[10];
extern int err;

// esp_mqtt_client_config_t mqtt_cfg = {
//         .broker.address = {
//             .uri = MQTT_ADDRESS,
//             .port = MQTT_PORT
//         },
//         .credentials = {
//             .username = "WSVFxw7Lhodp2v6zSqYQiNHIAwvodbTXTEseYpN5ERjuafTStFyBg47HqtVruCeb",
//             .client_id = "phuc",
//             .authentication.password = ""
//         },
//         .session = {
//             .keepalive = KEEPALIVE,
//             .lastwill.topic = DISCONNECT_PUB,
//             .lastwill.msg = "Esp32",
//             .lastwill.msg_len = strlen("Esp32"),
//             .lastwill.qos = 1,
//             .lastwill.retain = 0
//         }
//     };
    
esp_mqtt_client_config_t mqtt_cfg = {
            .host = MQTT_ADDRESS,
            .port = MQTT_PORT,
            .username = "WSVFxw7Lhodp2v6zSqYQiNHIAwvodbTXTEseYpN5ERjuafTStFyBg47HqtVruCeb",
            .client_id = "phuc",
            .password = "",
            .keepalive = KEEPALIVE,
            .lwt_topic = DISCONNECT_PUB,
            .lwt_msg = "Esp32",
            .lwt_msg_len = strlen("Esp32"),
            .lwt_qos = 1,
            .lwt_retain = 0
};
    
MQTT_Handler_Struct mqtt_h =
{
    .mqtt_cfg = &mqtt_cfg,
};

void app_main()
{
    esp_err_t ret;

    /* Initialize NVS. */
    ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );

    ESP_ERROR_CHECK(esp_netif_init());

    ESP_ERROR_CHECK(esp_event_loop_create_default());

    esp_netif_create_default_wifi_sta();


    DHT11_init(DHT_GPIO);
    wifi_init_start();
    mqtt_init_start(&mqtt_h);

}