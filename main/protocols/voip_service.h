#ifndef _VOIP_SERVICE_H_
#define _VOIP_SERVICE_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Reads VoIP configuration from NVS and starts the SIP service.
 */
void voip_service_start(void);

/**
 * @brief Stops the SIP service.
 */
void voip_service_stop(void);

#ifdef __cplusplus
}
#endif

#endif // _VOIP_SERVICE_H_ 