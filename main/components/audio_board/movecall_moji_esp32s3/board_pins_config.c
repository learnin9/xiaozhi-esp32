#include "esp_log.h"
#include "driver/gpio.h"
#include "driver/i2c.h"
#include "driver/i2s.h"
#include "driver/spi_master.h"
#include <string.h>
#include "board.h"
#include "board_def.h"
#include "board_pins_config.h"
#include "audio_error.h"
#include "audio_mem.h"
#include "soc/soc_caps.h"

static const char *TAG = "MOVECALL_MOJI_ESP32S3";

esp_err_t get_i2c_pins(i2c_port_t port, i2c_config_t *i2c_config)
{
    AUDIO_NULL_CHECK(TAG, i2c_config, return ESP_FAIL);
    if (port == I2C_NUM_0 || port == I2C_NUM_1) {
        i2c_config->sda_io_num = GPIO_NUM_5;   // AUDIO_CODEC_I2C_SDA_PIN
        i2c_config->scl_io_num = GPIO_NUM_4;   // AUDIO_CODEC_I2C_SCL_PIN
    } else {
        i2c_config->sda_io_num = -1;
        i2c_config->scl_io_num = -1;
        ESP_LOGE(TAG, "i2c port %d is not supported", port);
        return ESP_FAIL;
    }
    return ESP_OK;
}

esp_err_t get_i2s_pins(int port, board_i2s_pin_t *i2s_config)
{
    AUDIO_NULL_CHECK(TAG, i2s_config, return ESP_FAIL);
    if (port == 0) {
        i2s_config->bck_io_num = GPIO_NUM_14;   // AUDIO_I2S_GPIO_BCLK
        i2s_config->ws_io_num = GPIO_NUM_12;    // AUDIO_I2S_GPIO_WS
        i2s_config->data_out_num = GPIO_NUM_11; // AUDIO_I2S_GPIO_DOUT
        i2s_config->data_in_num = GPIO_NUM_13;  // AUDIO_I2S_GPIO_DIN
        i2s_config->mck_io_num = GPIO_NUM_6;    // AUDIO_I2S_GPIO_MCLK
    } else if (port == 1) {
        i2s_config->bck_io_num = -1;
        i2s_config->ws_io_num = -1;
        i2s_config->data_out_num = -1;
        i2s_config->data_in_num = -1;
        i2s_config->mck_io_num = -1;
    } else {
        memset(i2s_config, -1, sizeof(board_i2s_pin_t));
        ESP_LOGE(TAG, "i2s port %d is not supported", port);
        return ESP_FAIL;
    }

    return ESP_OK;
}

esp_err_t get_spi_pins(spi_bus_config_t *spi_config, spi_device_interface_config_t *spi_device_interface_config)
{
    AUDIO_NULL_CHECK(TAG, spi_config, return ESP_FAIL);
    AUDIO_NULL_CHECK(TAG, spi_device_interface_config, return ESP_FAIL);

    // LCD SPI 配置
    spi_config->mosi_io_num = GPIO_NUM_17;      // DISPLAY_SPI_MOSI_PIN
    spi_config->miso_io_num = -1;               // 不需要 MISO
    spi_config->sclk_io_num = GPIO_NUM_16;      // DISPLAY_SPI_SCLK_PIN
    spi_config->quadwp_io_num = -1;
    spi_config->quadhd_io_num = -1;

    spi_device_interface_config->spics_io_num = GPIO_NUM_15;  // DISPLAY_SPI_CS_PIN

    return ESP_OK;
}

// sdcard - Movecall Moji 没有 SD 卡
int8_t get_sdcard_intr_gpio(void)
{
    return -1;
}

int8_t get_sdcard_open_file_num_max(void)
{
    return 0;
}

int8_t get_sdcard_power_ctrl_gpio(void)
{
    return -1;
}

// input-output pins
int8_t get_headphone_detect_gpio(void)
{
    return -1;
}

int8_t get_pa_enable_gpio(void)
{
    return GPIO_NUM_9;  // AUDIO_CODEC_PA_PIN
}

// button id
int8_t get_input_rec_id(void)
{
    return BUTTON_REC_ID;
}

int8_t get_input_mode_id(void)
{
    return -1;
}

int8_t get_input_set_id(void)
{
    return BUTTON_SET_ID;
}

int8_t get_input_play_id(void)
{
    return -1;
}

int8_t get_input_volup_id(void)
{
    return -1;
}

int8_t get_input_voldown_id(void)
{
    return -1;
}

// led pins
int8_t get_green_led_gpio(void)
{
    return GREEN_LED_GPIO;  // GPIO_NUM_21
}

int8_t get_blue_led_gpio(void)
{
    return -1;
}

int8_t get_es8311_mclk_src(void)
{
    return ES8311_MCLK_SOURCE;  // 0
} 