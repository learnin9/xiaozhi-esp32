#include "esp_log.h"
#include "string.h"

#include "application.h"
#include "settings.h"
#include "sip_service.h"
#include "voip_service.h"

static const char *TAG = "VOIP_SERVICE";

#define VOIP_SETTINGS_NAMESPACE "voip_config"
#define VOIP_SETTINGS_KEY "voip_settings"

static esp_rtc_handle_t sip_handle = NULL;

void voip_service_start(void)
{
    char uri[256];
    VoipSettings settings;

    if (sip_handle) {
        ESP_LOGI(TAG, "VoIP service is already running.");
        return;
    }

    if (settings_read(VOIP_SETTINGS_NAMESPACE, VOIP_SETTINGS_KEY, &settings, sizeof(settings)) == ESP_OK) {
        if (strlen(settings.user) > 0 && strlen(settings.server) > 0) {
            snprintf(uri, sizeof(uri), "sip:%s@%s:%d;transport=%s",
                     settings.user,
                     settings.server,
                     settings.port,
                     settings.transport);
            
            ESP_LOGI(TAG, "Starting SIP service with uri: %s", uri);
            sip_handle = sip_service_start(get_av_stream(), uri);
            if (!sip_handle) {
                ESP_LOGE(TAG, "Failed to start SIP service.");
            }
        } else {
            ESP_LOGI(TAG, "VoIP settings not fully configured, skipping SIP start.");
        }
    } else {
        ESP_LOGI(TAG, "No VoIP settings found in NVS.");
    }
}

void voip_service_stop(void)
{
    if (sip_handle) {
        ESP_LOGI(TAG, "Stopping SIP service.");
        sip_service_stop(sip_handle);
        sip_handle = NULL;
    } else {
        ESP_LOGI(TAG, "SIP service not running, no need to stop.");
    }
} 