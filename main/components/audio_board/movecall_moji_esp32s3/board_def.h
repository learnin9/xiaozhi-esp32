#ifndef _AUDIO_BOARD_DEFINITION_H_
#define _AUDIO_BOARD_DEFINITION_H_

#include "driver/gpio.h"
#include "driver/i2s.h"
#include "audio_hal.h"

/**
 * @brief LED Function Definition
 */
#define GREEN_LED_GPIO              GPIO_NUM_21  // BUILTIN_LED_GPIO
#define BLUE_LED_GPIO               -1
#define RED_LED_GPIO                -1

/**
 * @brief LCD SCREEN Function Definition
 */
#define FUNC_LCD_SCREEN_EN          (1)
#define LCD_CTRL_GPIO               -1
#define LCD_RST_GPIO                GPIO_NUM_18  // DISPLAY_SPI_RESET_PIN
#define LCD_CS_GPIO                 GPIO_NUM_15  // DISPLAY_SPI_CS_PIN
// LCD SPI Pins
#define LCD_DC_GPIO                 GPIO_NUM_7   // DISPLAY_SPI_DC_PIN
#define LCD_CLK_GPIO                GPIO_NUM_16  // DISPLAY_SPI_SCLK_PIN
#define LCD_MOSI_GPIO               GPIO_NUM_17  // DISPLAY_SPI_MOSI_PIN
// The LCD pixel number in horizontal and vertical
#define LCD_H_RES                   240          // DISPLAY_WIDTH
#define LCD_V_RES                   240          // DISPLAY_HEIGHT
#define LCD_SWAP_XY                 (false)      // DISPLAY_SWAP_XY
#define LCD_MIRROR_X                (true)       // DISPLAY_MIRROR_X
#define LCD_MIRROR_Y                (false)      // DISPLAY_MIRROR_Y
#define LCD_COLOR_INV               (false)

/**
 * @brief SDCARD Function Definition
 */
#define FUNC_SDCARD_EN             (0)  // Movecall Moji 没有 SD 卡
#define SDCARD_OPEN_FILE_NUM_MAX    5
#define SDCARD_INTR_GPIO            -1
#define SDCARD_PWR_CTRL             -1

#define ESP_SD_PIN_CLK              -1
#define ESP_SD_PIN_CMD              -1
#define ESP_SD_PIN_D0               -1
#define ESP_SD_PIN_D1               -1
#define ESP_SD_PIN_D2               -1
#define ESP_SD_PIN_D3               -1
#define ESP_SD_PIN_D4               -1
#define ESP_SD_PIN_D5               -1
#define ESP_SD_PIN_D6               -1
#define ESP_SD_PIN_D7               -1
#define ESP_SD_PIN_CD               -1
#define ESP_SD_PIN_WP               -1

/**
 * @brief Camera Function Definition
 */
#define FUNC_CAMERA_EN              (0)  // Movecall Moji 没有摄像头
#define CAM_PIN_PWDN                -1
#define CAM_PIN_RESET               -1
#define CAM_PIN_XCLK                -1
#define CAM_PIN_SIOD                -1
#define CAM_PIN_SIOC                -1

#define CAM_PIN_D7                  -1
#define CAM_PIN_D6                  -1
#define CAM_PIN_D5                  -1
#define CAM_PIN_D4                  -1
#define CAM_PIN_D3                  -1
#define CAM_PIN_D2                  -1
#define CAM_PIN_D1                  -1
#define CAM_PIN_D0                  -1
#define CAM_PIN_VSYNC               -1
#define CAM_PIN_HREF                -1
#define CAM_PIN_PCLK                -1

/**
 * @brief LCD TOUCH PANEL Function Definition
 */
#define FUNC_LCD_TOUCH_EN          (0)  // Movecall Moji 没有触摸屏
#define TOUCH_PANEL_SWAP_XY        (0)
#define TOUCH_PANEL_INVERSE_X      (0)
#define TOUCH_PANEL_INVERSE_Y      (0)

/**
 * @brief  Audio Codec Chip Function Definition
 */
#define FUNC_AUDIO_CODEC_EN       (1)
#define CODEC_ADC_I2S_PORT        ((i2s_port_t)0)
#define CODEC_ADC_BITS_PER_SAMPLE ((i2s_data_bit_width_t)32)  /* 32bit */
#define CODEC_ADC_SAMPLE_RATE     (24000)       // AUDIO_INPUT_SAMPLE_RATE
#define RECORD_HARDWARE_AEC       (false)
#define BOARD_PA_GAIN             (6)           /* Power amplifier gain defined by board (dB) */
#define HEADPHONE_DETECT          (-1)
#define PA_ENABLE_GPIO            GPIO_NUM_9    // AUDIO_CODEC_PA_PIN
#define ES8311_MCLK_SOURCE        (0)           /* 0 From MCLK of esp32   1 From BCLK */

/**
 * @brief ADC input data format
 */
#define AUDIO_ADC_INPUT_CH_FORMAT "RMNM"

extern audio_hal_func_t AUDIO_CODEC_ES8311_DEFAULT_HANDLE;

#define AUDIO_CODEC_DEFAULT_CONFIG(){                   \
        .adc_input  = AUDIO_HAL_ADC_INPUT_LINE1,        \
        .dac_output = AUDIO_HAL_DAC_OUTPUT_ALL,         \
        .codec_mode = AUDIO_HAL_CODEC_MODE_BOTH,        \
        .i2s_iface = {                                  \
            .mode = AUDIO_HAL_MODE_SLAVE,               \
            .fmt = AUDIO_HAL_I2S_NORMAL,                \
            .samples = AUDIO_HAL_24K_SAMPLES,           \
            .bits = AUDIO_HAL_BIT_LENGTH_16BITS,        \
        },                                              \
};

/**
 * @brief Button Function Definition
 */
#define FUNC_BUTTON_EN              (1)
#define INPUT_KEY_NUM               1
#define BUTTON_VOLUP_ID             -1
#define BUTTON_VOLDOWN_ID           -1
#define BUTTON_SET_ID               GPIO_NUM_0   // BOOT_BUTTON_GPIO
#define BUTTON_PLAY_ID              -1
#define BUTTON_MODE_ID              -1
#define BUTTON_REC_ID               GPIO_NUM_0   // BOOT_BUTTON_GPIO

#define INPUT_KEY_DEFAULT_INFO() {                      \
     {                                                  \
        .type = PERIPH_ID_BUTTON,                       \
        .user_id = INPUT_KEY_USER_ID_REC,               \
        .act_id = BUTTON_REC_ID,                        \
    },                                                  \
}

#endif 