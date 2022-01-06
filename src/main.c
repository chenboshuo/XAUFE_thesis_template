#include <msp430.h>

#include "lib/IR_sensor.h"
#include "lib/alias.h"
#include "lib/interrupt.h"
#include "lib/led.h"
#include "lib/motor.h"
#include "lib/switch.h"
#include "lib/system_mode.h"
#include "lib/timer.h"

void main(void) {
  stop_watchdog();  // Stop WDT

  init_green_led();

  // initial motor
  init_motor();
  normal_speed_go_ahead();

  set_listener_of_switch();
  // set_listener_of_IR_sensor();

  detect_rising_edge_of_switch();
  // detect_descending_edge_of_IR_sensor();

  // enable_IR_sensor_interrupt();
  enable_switch_interrupt();

  enable_interrupt();
  while (RUNNING) {
    if (is_blocked()) {
      __delay_cycles(100);
      if (is_blocked()) {
        open_green_led();
        stop_ahead_signal();
        right_wheel_inverse_rotation();
        while (is_blocked()) {
          ;
        }
        restore_ahead_signal();
        close_green_led();
      }
    }
  }
}

#pragma vector = PORT1_VECTOR
__interrupt void stop() {
  switch (get_P1_interrupt_events()) {
    case SWITCH_BIT:
      stop_ahead_signal();
      break;
  }
}

// #pragma vector = PORT2_VECTOR
// __interrupt void get_IR_sensor_outcome() {
//   switch (get_P2_interrupt_events()) {
//     case IR_SENSOR_BIT:
//       // alternate_green_led();
//       open_green_led();
//       // __delay_cycles(10000);
//       stop_motor();
//       right_wheel_inverse_rotation();
//       while (is_blocked()) {
//         ;  // keep until eased
//       }
//       restore_normal_go_ahead();
//       close_green_led();
//       close_IR_sensor_interrupt();
//       break;
//   }
// }
