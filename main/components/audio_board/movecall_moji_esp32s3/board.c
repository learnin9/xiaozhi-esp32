#include "esp_log.h"
#include "driver/gpio.h"
#include "board.h"
#include "audio_hal.h"
#include "audio_mem.h"
#include "board_pins_config.h"
#include "es8311.h"
#include "periph_button.h"

static const char *TAG = "AUDIO_BOARD";

static audio_board_handle_t board_handle = 0;

audio_board_handle_t audio_board_init(void)
{
    if (board_handle) {
        ESP_LOGW(TAG, "The board has already been initialized!");
        return board_handle;
    }
    board_handle = (audio_board_handle_t) audio_calloc(1, sizeof(struct audio_board_handle));
    AUDIO_MEM_CHECK(TAG, board_handle, return NULL);
    
    board_handle->audio_hal = audio_board_codec_init();
    board_handle->adc_hal = audio_board_adc_init();
    
    return board_handle;
}

audio_hal_handle_t audio_board_codec_init(void)
{
    audio_hal_codec_config_t audio_codec_cfg = AUDIO_CODEC_DEFAULT_CONFIG();
    audio_hal_handle_t codec_hal = audio_hal_init(&audio_codec_cfg, &AUDIO_CODEC_ES8311_DEFAULT_HANDLE);
    AUDIO_NULL_CHECK(TAG, codec_hal, return NULL);
    
    return codec_hal;
}

audio_hal_handle_t audio_board_adc_init(void)
{
    return NULL;
}

display_service_handle_t audio_board_led_init(void)
{
    return NULL;
}

esp_err_t audio_board_key_init(esp_periph_set_handle_t set)
{
    esp_err_t ret = ESP_OK;
    
    if (set) {
        // 初始化 BOOT 按键 (GPIO0)
        periph_button_cfg_t btn_cfg = {
            .gpio_mask = (1ULL << GPIO_NUM_0),  // BOOT_BUTTON_GPIO
        };
        esp_periph_handle_t button_handle = periph_button_init(&btn_cfg);
        AUDIO_NULL_CHECK(TAG, button_handle, return ESP_ERR_ADF_MEMORY_LACK);
        ret = esp_periph_start(set, button_handle);
    }
    
    return ret;
}

esp_err_t audio_board_sdcard_init(esp_periph_set_handle_t set, periph_sdcard_mode_t mode)
{
    return ESP_OK;
}

audio_board_handle_t audio_board_get_handle(void)
{
    return board_handle;
}

esp_err_t audio_board_deinit(audio_board_handle_t audio_board)
{
    esp_err_t ret = ESP_OK;
    if (audio_board) {
        if (audio_board->audio_hal) {
            audio_hal_deinit(audio_board->audio_hal);
            audio_board->audio_hal = NULL;
        }
        if (audio_board->adc_hal) {
            audio_hal_deinit(audio_board->adc_hal);
            audio_board->adc_hal = NULL;
        }
        audio_free(audio_board);
        board_handle = NULL;
    }
    return ret;
} 