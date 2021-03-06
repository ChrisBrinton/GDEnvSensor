//------------------------------------------------------------------------------
// GENERAL
//------------------------------------------------------------------------------

#define SERIAL_BAUDRATE         115200
#define LED_PIN                 0

//------------------------------------------------------------------------------
// RADIO
//------------------------------------------------------------------------------

#define NODEID                  1
#define GATEWAYID               1
#define NETWORKID               100
#define PROMISCUOUS             0
#define FREQUENCY               RF69_915MHZ
#define ENCRYPTKEY              "sampleEncryptKey"
#define SPI_CS                  2
#define IRQ_PIN                 15
#define RFM69_RST               16
#define IS_RFM69HW              0

// -----------------------------------------------------------------------------
// WIFI
// -----------------------------------------------------------------------------

#define WIFI_RECONNECT_INTERVAL 300000
#define WIFI_MAX_NETWORKS       3
#define ADMIN_PASS              "fibonacci"
#define HTTP_USERNAME           "admin"
#define WS_BUFFER_SIZE          5
#define WS_TIMEOUT              1800000

// -----------------------------------------------------------------------------
// OTA
// -----------------------------------------------------------------------------

#define OTA_PORT                8266

// -----------------------------------------------------------------------------
// MQTT
// -----------------------------------------------------------------------------

#define MQTT_SERVER             "74.208.159.205"
#define MQTT_PORT               1883
#define MQTT_RETAIN             true
#define MQTT_QOS                0
#define MQTT_KEEPALIVE          30
#define MQTT_RECONNECT_DELAY    20000
#define MQTT_TRY_INTERVAL       60000
#define MQTT_MAX_TRIES          20
#define MQTT_USER               "sampleuser"
#define MQTT_PASS               "sampleuserkey"
#define MQTT_IP_TOPIC           "/{hostname}/{nodeid}/ip"
#define MQTT_HEARTBEAT_TOPIC    "/{hostname}/{nodeid}/ping"
#define MQTT_DEFAULT_TOPIC      "/{hostname}/{nodeid}/{key}"

// -----------------------------------------------------------------------------
// NTP
// -----------------------------------------------------------------------------

#define NTP_SERVER              "pool.ntp.org"
#define NTP_TIME_OFFSET         -5
#define NTP_DAY_LIGHT           true
#define NTP_UPDATE_INTERVAL     1800
#define TIMEID                  0

// -----------------------------------------------------------------------------
// Onboard BME280 Sensor
// -----------------------------------------------------------------------------

#define BME280_RUNMODE          3
#define BME280_OVERSAMPLE       1
#define BME280_FILTER           0
#define BME280_STANDBY          0
#define SENSORID                1

// -----------------------------------------------------------------------------
// DEFAULTS
// -----------------------------------------------------------------------------

#define HEARTBEAT_INTERVAL      60000
#define HOSTNAME                APP_NAME
#define DEVICE                  APP_NAME
