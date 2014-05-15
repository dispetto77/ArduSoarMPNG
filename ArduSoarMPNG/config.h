// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-
//
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
//
//  DO NOT EDIT this file to adjust your configuration.  Create your own
//  APM_Config.h and use APM_Config.h.example as a reference.
//
// WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
///
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// Default and automatic configuration details.
//
// Notes for maintainers:
//
// - Try to keep this file organised in the same order as APM_Config.h.example
//

#include "defines.h"

///
/// DO NOT EDIT THIS INCLUDE - if you want to make a local change, make that
/// change in your local copy of APM_Config.h.
///
#ifdef USE_CMAKE_APM_CONFIG
 #include "APM_Config_cmake.h" // <== Prefer cmake config if it exists
#else
 #include "APM_Config.h" // <== THIS INCLUDE, DO NOT EDIT IT. EVER.
#endif
///
/// DO NOT EDIT THIS INCLUDE - if you want to make a local change, make that
/// change in your local copy of APM_Config.h.
///

// Just so that it's completely clear...
#define ENABLED                 1
#define DISABLED                0

// this avoids a very common config error
#define ENABLE ENABLED
#define DISABLE DISABLED

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// HARDWARE CONFIGURATION AND CONNECTIONS
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#ifdef CONFIG_APM_HARDWARE
#error CONFIG_APM_HARDWARE option is depreated! use CONFIG_HAL_BOARD instead.
#endif

//////////////////////////////////////////////////////////////////////////////
// APM HARDWARE
//

#if defined( __AVR_ATmega1280__ )
 // default choices for a 1280. We can't fit everything in, so we 
 // make some popular choices by default
 #define LOGGING_ENABLED DISABLED
 #ifndef GEOFENCE_ENABLED
 # define GEOFENCE_ENABLED DISABLED
 #endif
 #ifndef CLI_ENABLED
 # define CLI_ENABLED DISABLED
 #endif
 #ifndef MOUNT2
 # define MOUNT2 DISABLED
 #endif
 #ifndef MOUNT
 # define MOUNT DISABLED
 #endif
 #ifndef CAMERA
 # define CAMERA DISABLED
 #endif
#endif

// use this to enable telemetry on UART2. This is used
// when you have setup the solder bridge on an APM2 to enable UART2
#ifndef TELEMETRY_UART2
 # define TELEMETRY_UART2 DISABLED
#endif

//////////////////////////////////////////////////////////////////////////////
// main board differences
//
#if CONFIG_HAL_BOARD == HAL_BOARD_APM1
 # define A_LED_PIN        37
 # define B_LED_PIN        36
 # define C_LED_PIN        35
 # define LED_ON           HIGH
 # define LED_OFF          LOW
 # define USB_MUX_PIN      -1
 # define BATTERY_VOLT_PIN      0      // Battery voltage on A0
 # define BATTERY_CURR_PIN      1      // Battery current on A1
 # define CONFIG_INS_TYPE CONFIG_INS_OILPAN
 # define CONFIG_BARO     AP_BARO_BMP085
 # define CONFIG_COMPASS  AP_COMPASS_HMC5843
#elif CONFIG_HAL_BOARD == HAL_BOARD_APM2
 # define A_LED_PIN        27
 # define B_LED_PIN        26
 # define C_LED_PIN        25
 # define LED_ON           LOW
 # define LED_OFF          HIGH
 #if TELEMETRY_UART2 == ENABLED
  # define USB_MUX_PIN -1
 #else
  # define USB_MUX_PIN 23
 #endif
 # define BATTERY_VOLT_PIN      1      // Battery voltage on A1
 # define BATTERY_CURR_PIN      2      // Battery current on A2
 # define CONFIG_INS_TYPE CONFIG_INS_MPU6000
 # ifdef APM2_BETA_HARDWARE
 #  define CONFIG_BARO     AP_BARO_BMP085
 # else // APM2 Production Hardware (default)
 #  define CONFIG_BARO          AP_BARO_MS5611
 #  define CONFIG_MS5611_SERIAL AP_BARO_MS5611_SPI
 # endif
 # define CONFIG_COMPASS  AP_COMPASS_HMC5843
#elif CONFIG_HAL_BOARD == HAL_BOARD_MPNG
 #ifndef MPNG_BOARD_TYPE
  #define MPNG_BOARD_TYPE RCTIMER_CRIUS_V2
 #endif

 #if MPNG_BOARD_TYPE != RCTIMER_CRIUS_V2
 	#define LOGGING_ENABLED DISABLED
 #endif

 # define PIEZO_PIN AN3
 
 #if MPNG_BOARD_TYPE == HK_RED_MULTIWII_PRO || MPNG_BOARD_TYPE == BLACK_VORTEX
	 # define CONFIG_INS_TYPE   CONFIG_INS_ITG3200
	 # define CONFIG_BARO       AP_BARO_BMP085_MPNG
 #elif MPNG_BOARD_TYPE == PARIS_V5_OSD
	 # define CONFIG_INS_TYPE   CONFIG_INS_ITG3200
	 # define CONFIG_BARO       AP_BARO_MS5611
	 # define CONFIG_MS5611_SERIAL AP_BARO_MS5611_I2C 
 #else
	 # define CONFIG_INS_TYPE   CONFIG_INS_MPU6000_I2C
	 # define CONFIG_BARO       AP_BARO_MS5611
	 # define CONFIG_MS5611_SERIAL AP_BARO_MS5611_I2C
 #endif 
 
 # define A_LED_PIN        13
 # define B_LED_PIN        31
 # define C_LED_PIN        30
 # define LED_ON           HIGH
 # define LED_OFF          LOW
 # define USB_MUX_PIN -1
 # define BATTERY_VOLT_PIN      1      // Battery voltage on A0
 # define BATTERY_CURR_PIN      2      // Battery current on A1
 # define CONFIG_SONAR_SOURCE SONAR_SOURCE_ANALOG_PIN
 # define MAGNETOMETER ENABLED
 # define CONFIG_COMPASS  AP_COMPASS_HMC5843
#elif CONFIG_HAL_BOARD == HAL_BOARD_AVR_SITL
 # define A_LED_PIN        27
 # define B_LED_PIN        26
 # define C_LED_PIN        25
 # define LED_ON           LOW
 # define LED_OFF          HIGH
 # define BATTERY_VOLT_PIN      1      // Battery voltage on A1
 # define BATTERY_CURR_PIN      2      // Battery current on A2
 # define CONFIG_INS_TYPE CONFIG_INS_STUB
 # define CONFIG_BARO     AP_BARO_HIL
 # define CONFIG_COMPASS  AP_COMPASS_HIL
#elif CONFIG_HAL_BOARD == HAL_BOARD_PX4
 # define A_LED_PIN        27
 # define B_LED_PIN        26
 # define C_LED_PIN        25
 # define LED_ON           LOW
 # define LED_OFF          HIGH
 # define USB_MUX_PIN -1
 # define BATTERY_VOLT_PIN      -1
 # define BATTERY_CURR_PIN      -1
 # define CONFIG_INS_TYPE CONFIG_INS_PX4
 # define CONFIG_BARO AP_BARO_PX4
 # define CONFIG_COMPASS  AP_COMPASS_PX4
 # define SERIAL0_BAUD 115200
#endif

//////////////////////////////////////////////////////////////////////////////
// GPS Port speed
#ifndef SERIAL2_BAUD
	#define SERIAL2_BAUD 38400
#endif 


#ifndef CONFIG_BARO
 # error "CONFIG_BARO not set"
#endif

#ifndef CONFIG_COMPASS
 # error "CONFIG_COMPASS not set"
#endif

//////////////////////////////////////////////////////////////////////////////
// HIL_MODE                                 OPTIONAL

#ifndef HIL_MODE
 #define HIL_MODE        HIL_MODE_DISABLED
#endif

#if HIL_MODE != HIL_MODE_DISABLED       // we are in HIL mode
 #undef GPS_PROTOCOL
 #define GPS_PROTOCOL GPS_PROTOCOL_HIL
 #undef CONFIG_BARO
 #define CONFIG_BARO AP_BARO_HIL
 #undef CONFIG_INS_TYPE
 #define CONFIG_INS_TYPE CONFIG_INS_STUB
 #undef  CONFIG_COMPASS
 #define CONFIG_COMPASS  AP_COMPASS_HIL
#endif

//////////////////////////////////////////////////////////////////////////////
// GPS_PROTOCOL
//
// Note that this test must follow the HIL_PROTOCOL block as the HIL
// setup may override the GPS configuration.
//
#ifndef GPS_PROTOCOL
 # define GPS_PROTOCOL GPS_PROTOCOL_AUTO
#endif

#ifndef MAV_SYSTEM_ID
 # define MAV_SYSTEM_ID          1
#endif

//////////////////////////////////////////////////////////////////////////////
// Serial port speeds.
//
#ifndef SERIAL0_BAUD
 # define SERIAL0_BAUD                   115200
#endif
#ifndef SERIAL3_BAUD
 # define SERIAL3_BAUD                    57600
#endif


//////////////////////////////////////////////////////////////////////////////
// Battery monitoring
//
#ifndef VOLT_DIV_RATIO
 # define VOLT_DIV_RATIO                 3.56   // This is the proper value for an on-board APM1 voltage divider with a 3.9kOhm resistor
//# define VOLT_DIV_RATIO		15.70	// This is the proper value for the AttoPilot 50V/90A sensor
//# define VOLT_DIV_RATIO		4.127	// This is the proper value for the AttoPilot 13.6V/45A sensor

#endif

#ifndef CURR_AMP_PER_VOLT
 # define CURR_AMP_PER_VOLT              27.32  // This is the proper value for the AttoPilot 50V/90A sensor
//# define CURR_AMP_PER_VOLT	13.66	// This is the proper value for the AttoPilot 13.6V/45A sensor
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// RADIO CONFIGURATION
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
// Radio channel limits
//
// Note that these are not called out in APM_Config.h.reference.
//
#ifndef CH5_MIN
 # define CH5_MIN        1000
#endif
#ifndef CH5_MAX
 # define CH5_MAX        2000
#endif
#ifndef CH6_MIN
 # define CH6_MIN        1000
#endif
#ifndef CH6_MAX
 # define CH6_MAX        2000
#endif
#ifndef CH7_MIN
 # define CH7_MIN        1000
#endif
#ifndef CH7_MAX
 # define CH7_MAX        2000
#endif
#ifndef CH8_MIN
 # define CH8_MIN        1000
#endif
#ifndef CH8_MAX
 # define CH8_MAX        2000
#endif


#ifndef FLAP_1_PERCENT
 # define FLAP_1_PERCENT 0
#endif
#ifndef FLAP_1_SPEED
 # define FLAP_1_SPEED 0
#endif
#ifndef FLAP_2_PERCENT
 # define FLAP_2_PERCENT 0
#endif
#ifndef FLAP_2_SPEED
 # define FLAP_2_SPEED 0
#endif
//////////////////////////////////////////////////////////////////////////////
// FLIGHT_MODE
// FLIGHT_MODE_CHANNEL
//
#ifndef FLIGHT_MODE_CHANNEL
 # define FLIGHT_MODE_CHANNEL    8
#endif
#if (FLIGHT_MODE_CHANNEL != 5) && (FLIGHT_MODE_CHANNEL != 6) && (FLIGHT_MODE_CHANNEL != 7) && (FLIGHT_MODE_CHANNEL != 8)
 # error XXX
 # error XXX You must set FLIGHT_MODE_CHANNEL to 5, 6, 7 or 8
 # error XXX
#endif

#if !defined(FLIGHT_MODE_1)
 # define FLIGHT_MODE_1                  RTL
#endif
#if !defined(FLIGHT_MODE_2)
 # define FLIGHT_MODE_2                  RTL
#endif
#if !defined(FLIGHT_MODE_3)
 # define FLIGHT_MODE_3                  STABILIZE
#endif
#if !defined(FLIGHT_MODE_4)
 # define FLIGHT_MODE_4                  STABILIZE
#endif
#if !defined(FLIGHT_MODE_5)
 # define FLIGHT_MODE_5                  MANUAL
#endif
#if !defined(FLIGHT_MODE_6)
 # define FLIGHT_MODE_6                  MANUAL
#endif


//////////////////////////////////////////////////////////////////////////////
// THROTTLE_FAILSAFE
// THROTTLE_FS_VALUE
// SHORT_FAILSAFE_ACTION
// LONG_FAILSAFE_ACTION
// GCS_HEARTBEAT_FAILSAFE
//
#ifndef THROTTLE_FAILSAFE
 # define THROTTLE_FAILSAFE              ENABLED
#endif
#ifndef THROTTLE_FS_VALUE
 # define THROTTLE_FS_VALUE              950
#endif
#ifndef SHORT_FAILSAFE_ACTION
 # define SHORT_FAILSAFE_ACTION          0
#endif
#ifndef LONG_FAILSAFE_ACTION
 # define LONG_FAILSAFE_ACTION           0
#endif
#ifndef GCS_HEARTBEAT_FAILSAFE
 # define GCS_HEARTBEAT_FAILSAFE         DISABLED
#endif


//////////////////////////////////////////////////////////////////////////////
// AUTO_TRIM
//
#ifndef AUTO_TRIM
 # define AUTO_TRIM                              DISABLED
#endif


//////////////////////////////////////////////////////////////////////////////
// THROTTLE_OUT
//
#ifndef THROTTE_OUT
 # define THROTTLE_OUT                   ENABLED
#endif


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// STARTUP BEHAVIOUR
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
// GROUND_START_DELAY
//
#ifndef GROUND_START_DELAY
 # define GROUND_START_DELAY             0
#endif

//////////////////////////////////////////////////////////////////////////////
// ENABLE_AIR_START
//
#ifndef ENABLE_AIR_START
 # define ENABLE_AIR_START               DISABLED
#endif

//////////////////////////////////////////////////////////////////////////////
// ENABLE ELEVON_MIXING
//
#ifndef ELEVON_MIXING
 # define ELEVON_MIXING          DISABLED
#endif
#ifndef ELEVON_REVERSE
 # define ELEVON_REVERSE     DISABLED
#endif
#ifndef ELEVON_CH1_REVERSE
 # define ELEVON_CH1_REVERSE     DISABLED
#endif
#ifndef ELEVON_CH2_REVERSE
 # define ELEVON_CH2_REVERSE     DISABLED
#endif

//////////////////////////////////////////////////////////////////////////////
// CAMERA TRIGGER AND CONTROL
//
// uses 1182 bytes of memory
#ifndef CAMERA
 # define CAMERA         ENABLED
#endif

//////////////////////////////////////////////////////////////////////////////
// MOUNT (ANTENNA OR CAMERA)
//
// uses 4174 bytes of memory on 1280 chips (MNT_JSTICK_SPD_OPTION, MNT_RETRACT_OPTION, MNT_STABILIZE_OPTION and MNT_MOUNT2_OPTION disabled)
// uses 7726 bytes of memory on 2560 chips (all options are enabled)
#ifndef MOUNT
 # define MOUNT          ENABLED
#endif

// second mount, can for example be used to keep an antenna pointed at the home position
#ifndef MOUNT2
 # define MOUNT2         DISABLED
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// FLIGHT AND NAVIGATION CONTROL
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// Altitude measurement and control.
//
#ifndef ALT_EST_GAIN
 # define ALT_EST_GAIN                   0.01
#endif
#ifndef ALTITUDE_MIX
 # define ALTITUDE_MIX                   1
#endif


//////////////////////////////////////////////////////////////////////////////
// AIRSPEED_CRUISE
//
#ifndef AIRSPEED_CRUISE
 # define AIRSPEED_CRUISE                12 // 12 m/s
#endif
#define AIRSPEED_CRUISE_CM AIRSPEED_CRUISE*100


//////////////////////////////////////////////////////////////////////////////
// MIN_GNDSPEED
//
#ifndef MIN_GNDSPEED
 # define MIN_GNDSPEED                   0 // m/s (0 disables)
#endif
#define MIN_GNDSPEED_CM MIN_GNDSPEED*100


//////////////////////////////////////////////////////////////////////////////
// FLY_BY_WIRE_B airspeed control
//
#ifndef AIRSPEED_FBW_MIN
 # define AIRSPEED_FBW_MIN               6
#endif
#ifndef AIRSPEED_FBW_MAX
 # define AIRSPEED_FBW_MAX               22
#endif

#ifndef ALT_HOLD_FBW
 # define ALT_HOLD_FBW 0
#endif
#define ALT_HOLD_FBW_CM ALT_HOLD_FBW*100



/*  The following parameters have no corresponding control implementation
 * #ifndef THROTTLE_ALT_P
 # define THROTTLE_ALT_P         0.32
 ##endif
 ##ifndef THROTTLE_ALT_I
 # define THROTTLE_ALT_I         0.0
 ##endif
 ##ifndef THROTTLE_ALT_D
 # define THROTTLE_ALT_D         0.0
 ##endif
 ##ifndef THROTTLE_ALT_INT_MAX
 # define THROTTLE_ALT_INT_MAX   20
 ##endif
 ##define THROTTLE_ALT_INT_MAX_CM THROTTLE_ALT_INT_MAX*100
 */


//////////////////////////////////////////////////////////////////////////////
// Servo Mapping
//
#ifndef THROTTLE_MIN
 # define THROTTLE_MIN                   0 // percent
#endif
#ifndef THROTTLE_CRUISE
 # define THROTTLE_CRUISE                45
#endif
#ifndef THROTTLE_MAX
 # define THROTTLE_MAX                   75
#endif

//////////////////////////////////////////////////////////////////////////////
// Autopilot control limits
//
#ifndef HEAD_MAX
 # define HEAD_MAX                               45
#endif
#ifndef PITCH_MAX
 # define PITCH_MAX                              15
#endif
#ifndef PITCH_MIN
 # define PITCH_MIN                              -25
#endif
#define HEAD_MAX_CENTIDEGREE HEAD_MAX * 100
#define PITCH_MAX_CENTIDEGREE PITCH_MAX * 100
#define PITCH_MIN_CENTIDEGREE PITCH_MIN * 100

//////////////////////////////////////////////////////////////////////////////
// Attitude control gains
//
#ifndef SERVO_ROLL_P
 # define SERVO_ROLL_P         0.4
#endif
#ifndef SERVO_ROLL_I
 # define SERVO_ROLL_I         0.0
#endif
#ifndef SERVO_ROLL_D
 # define SERVO_ROLL_D         0.0
#endif
#ifndef SERVO_ROLL_INT_MAX
 # define SERVO_ROLL_INT_MAX   5
#endif
#define SERVO_ROLL_INT_MAX_CENTIDEGREE SERVO_ROLL_INT_MAX*100
#ifndef ROLL_SLEW_LIMIT
 # define ROLL_SLEW_LIMIT      0
#endif
#ifndef SERVO_PITCH_P
 # define SERVO_PITCH_P        0.6
#endif
#ifndef SERVO_PITCH_I
 # define SERVO_PITCH_I        0.0
#endif
#ifndef SERVO_PITCH_D
 # define SERVO_PITCH_D        0.0
#endif
#ifndef SERVO_PITCH_INT_MAX
 # define SERVO_PITCH_INT_MAX  5
#endif
#define SERVO_PITCH_INT_MAX_CENTIDEGREE SERVO_PITCH_INT_MAX*100
#ifndef PITCH_COMP
 # define PITCH_COMP           0.2
#endif
#ifndef SERVO_YAW_P
 # define SERVO_YAW_P          0.0
#endif
#ifndef SERVO_YAW_I
 # define SERVO_YAW_I          0.0
#endif
#ifndef SERVO_YAW_D
 # define SERVO_YAW_D          0.0
#endif
#ifndef SERVO_YAW_INT_MAX
 # define SERVO_YAW_INT_MAX    0
#endif
#ifndef RUDDER_MIX
 # define RUDDER_MIX           0.5
#endif


//////////////////////////////////////////////////////////////////////////////
// Navigation control gains
//
#ifndef NAV_ROLL_P
 # define NAV_ROLL_P           0.7
#endif
#ifndef NAV_ROLL_I
 # define NAV_ROLL_I           0.02
#endif
#ifndef NAV_ROLL_D
 # define NAV_ROLL_D           0.1
#endif
#ifndef NAV_ROLL_INT_MAX
 # define NAV_ROLL_INT_MAX     5
#endif
#define NAV_ROLL_INT_MAX_CENTIDEGREE NAV_ROLL_INT_MAX*100
#ifndef NAV_PITCH_ASP_P
 # define NAV_PITCH_ASP_P      0.65
#endif
#ifndef NAV_PITCH_ASP_I
 # define NAV_PITCH_ASP_I      0.1
#endif
#ifndef NAV_PITCH_ASP_D
 # define NAV_PITCH_ASP_D      0.0
#endif
#ifndef NAV_PITCH_ASP_INT_MAX
 # define NAV_PITCH_ASP_INT_MAX 5
#endif
#define NAV_PITCH_ASP_INT_MAX_CMSEC NAV_PITCH_ASP_INT_MAX*100
#ifndef NAV_PITCH_ALT_P
 # define NAV_PITCH_ALT_P      0.65
#endif
#ifndef NAV_PITCH_ALT_I
 # define NAV_PITCH_ALT_I      0.1
#endif
#ifndef NAV_PITCH_ALT_D
 # define NAV_PITCH_ALT_D      0.0
#endif
#ifndef NAV_PITCH_ALT_INT_MAX
 # define NAV_PITCH_ALT_INT_MAX 5
#endif
#define NAV_PITCH_ALT_INT_MAX_CM NAV_PITCH_ALT_INT_MAX*100


//////////////////////////////////////////////////////////////////////////////
// Energy/Altitude control gains
//
#ifndef THROTTLE_TE_P
 # define THROTTLE_TE_P        0.50
#endif
#ifndef THROTTLE_TE_I
 # define THROTTLE_TE_I        0.0
#endif
#ifndef THROTTLE_TE_D
 # define THROTTLE_TE_D        0.0
#endif
#ifndef THROTTLE_TE_INT_MAX
 # define THROTTLE_TE_INT_MAX  20
#endif
#ifndef THROTTLE_SLEW_LIMIT
 # define THROTTLE_SLEW_LIMIT  0
#endif
#ifndef PITCH_TARGET
 # define PITCH_TARGET         0
#endif

//////////////////////////////////////////////////////////////////////////////
// Crosstrack compensation
//
#ifndef XTRACK_GAIN
 # define XTRACK_GAIN          1 // deg/m
#endif
#ifndef XTRACK_ENTRY_ANGLE
 # define XTRACK_ENTRY_ANGLE   30 // deg
#endif
# define XTRACK_GAIN_SCALED XTRACK_GAIN*100
# define XTRACK_ENTRY_ANGLE_CENTIDEGREE XTRACK_ENTRY_ANGLE*100

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// DEBUGGING
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// Dataflash logging control
//

#ifndef LOGGING_ENABLED
 # define LOGGING_ENABLED                ENABLED
#endif

#define DEFAULT_LOG_BITMASK     \
    MASK_LOG_ATTITUDE_MED | \
    MASK_LOG_GPS | \
    MASK_LOG_PM | \
    MASK_LOG_NTUN | \
    MASK_LOG_MODE | \
    MASK_LOG_CMD | \
    MASK_LOG_COMPASS | \
    MASK_LOG_CURRENT



//////////////////////////////////////////////////////////////////////////////
// Navigation defaults
//
#ifndef WP_RADIUS_DEFAULT
 # define WP_RADIUS_DEFAULT              30
#endif

#ifndef LOITER_RADIUS_DEFAULT
 # define LOITER_RADIUS_DEFAULT 60
#endif

#ifndef ALT_HOLD_HOME
 # define ALT_HOLD_HOME 100
#endif
#define ALT_HOLD_HOME_CM ALT_HOLD_HOME*100

#ifndef USE_CURRENT_ALT
 # define USE_CURRENT_ALT FALSE
#endif

#ifndef INVERTED_FLIGHT_PWM
 # define INVERTED_FLIGHT_PWM 1750
#endif

//////////////////////////////////////////////////////////////////////////////
// Developer Items
//

#ifndef SCALING_SPEED
 # define SCALING_SPEED          15.0
#endif

// use this to completely disable the CLI
#ifndef CLI_ENABLED
 # define CLI_ENABLED ENABLED
#endif

// use this to disable geo-fencing
#ifndef GEOFENCE_ENABLED
 # define GEOFENCE_ENABLED ENABLED
#endif

// pwm value on FENCE_CHANNEL to use to enable fenced mode
#ifndef FENCE_ENABLE_PWM
 # define FENCE_ENABLE_PWM 1750
#endif

// a digital pin to set high when the geo-fence triggers. Defaults
// to -1, which means don't activate a pin
#ifndef FENCE_TRIGGERED_PIN
 # define FENCE_TRIGGERED_PIN -1
#endif

// if RESET_SWITCH_CH is not zero, then this is the PWM value on
// that channel where we reset the control mode to the current switch
// position (to for example return to switched mode after failsafe or
// fence breach)
#ifndef RESET_SWITCH_CHAN_PWM
 # define RESET_SWITCH_CHAN_PWM 1750
#endif

// OBC Failsafe enable
#ifndef OBC_FAILSAFE
 # define OBC_FAILSAFE DISABLED
#endif

#ifndef SERIAL_BUFSIZE
 # define SERIAL_BUFSIZE 256
#endif

