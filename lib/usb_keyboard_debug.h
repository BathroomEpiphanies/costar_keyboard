#ifndef usb_serial_h__
#define usb_serial_h__

#include <stdint.h>
#include <util/delay.h>

void usb_init(void);            // initialize everything
uint8_t usb_configured(void);   // is the USB port configured

int8_t usb_keyboard_press(uint8_t key, uint8_t modifier);
int8_t usb_keyboard_send(void);
void jump_bootloader(void);
extern uint8_t keyboard_modifier_keys;
extern uint8_t keyboard_keys[6];
extern volatile uint8_t keyboard_leds;

int8_t usb_debug_putchar(uint8_t c);  // transmit a character
void usb_debug_flush_output(void);    // immediately transmit any buffered output
#define USB_DEBUG_HID

// Everything below this point is only intended for usb_serial.c
//#ifdef USB_SERIAL_PRIVATE_INCLUDE
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

#define EP_TYPE_CONTROL           0x00
#define EP_TYPE_BULK_IN           0x81
#define EP_TYPE_BULK_OUT          0x80
#define EP_TYPE_INTERRUPT_IN      0xC1
#define EP_TYPE_INTERRUPT_OUT     0xC0
#define EP_TYPE_ISOCHRONOUS_IN    0x41
#define EP_TYPE_ISOCHRONOUS_OUT   0x40
#define EP_SINGLE_BUFFER          0x02
#define EP_DOUBLE_BUFFER          0x06

#define EP_SIZE(s)  ((s) == 64 ? 0x30 : \
      ((s) == 32 ? 0x20 : \
      ((s) == 16 ? 0x10 : \
                   0x00)))

#define MAX_ENDPOINT    4

#define LSB(n) (n & 255)
#define MSB(n) ((n >> 8) & 255)

// ATmega32u2
#if defined(__AVR_ATmega32U2__)
#define HW_CONFIG()  (REGCR = 0x00)
#define PLL_CONFIG() (PLLCSR = 0x06)      //controls USB interface clock 0x06 for 16MHz clock source 0x02 for 8MHz clock source
#define USB_CONFIG() (USBCON = (1<<USBE)) //no OPGPADE for the ATmega32u2
#define USB_FREEZE() (USBCON = ((1<<USBE)|(1<<FRZCLK)))
// ATmega32u4, Teensy 2.0 
#elif defined(__AVR_ATmega32U4__)
#define HW_CONFIG() (UHWCON = 0x01)
#define PLL_CONFIG() (PLLCSR = 0x12)
#define USB_CONFIG() (USBCON = ((1<<USBE)|(1<<OTGPADE)))
#define USB_FREEZE() (USBCON = ((1<<USBE)|(1<<FRZCLK)))
// AT90USB162, Teensy 1.0
#elif defined(__AVR_AT90USB162__)
#define HW_CONFIG()
#define PLL_CONFIG() (PLLCSR = ((1<<PLLE)|(1<<PLLP0)))
#define USB_CONFIG() (USBCON = (1<<USBE))
#define USB_FREEZE() (USBCON = ((1<<USBE)|(1<<FRZCLK)))
// AT90USB646, Teensy++ 1.0
#elif defined(__AVR_AT90USB646__)
#define HW_CONFIG() (UHWCON = 0x81)
#define PLL_CONFIG() (PLLCSR = 0x1A)
#define USB_CONFIG() (USBCON = ((1<<USBE)|(1<<OTGPADE)))
#define USB_FREEZE() (USBCON = ((1<<USBE)|(1<<FRZCLK)))
// AT90USB1286, Teensy++ 2.0 
#elif defined(__AVR_AT90USB1286__)
#define HW_CONFIG() (UHWCON = 0x81)
#define PLL_CONFIG() (PLLCSR = 0x16)
#define USB_CONFIG() (USBCON = ((1<<USBE)|(1<<OTGPADE)))
#define USB_FREEZE() (USBCON = ((1<<USBE)|(1<<FRZCLK)))
#endif

// standard control endpoint request types
#define GET_STATUS                     0
#define CLEAR_FEATURE                  1
#define SET_FEATURE                    3
#define SET_ADDRESS                    5
#define GET_DESCRIPTOR                 6
#define GET_CONFIGURATION              8
#define SET_CONFIGURATION              9
#define GET_INTERFACE                 10
#define SET_INTERFACE                 11
// HID (human interface device)
#define HID_GET_REPORT                 1
#define HID_GET_IDLE                   2
#define HID_GET_PROTOCOL               3
#define HID_SET_REPORT                 9
#define HID_SET_IDLE                  10
#define HID_SET_PROTOCOL              11
// CDC (communication class device)
#define CDC_SET_LINE_CODING         0x20
#define CDC_GET_LINE_CODING         0x21
#define CDC_SET_CONTROL_LINE_STATE  0x22
#endif
//#endif
