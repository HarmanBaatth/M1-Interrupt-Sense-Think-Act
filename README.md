# Interrupt Based Sense–Think–Act System

## About This Project
This project is an interrupt-based embedded system using Arduino.

It uses:
- Pin Change Interrupt (PCI)
- External Interrupt
- Timer Interrupt (Timer1)

The system can handle sensor events and timer events at the same time.

## Hardware Used
- PIR Sensor (Pin 8)
- Tilt Sensor (Pin 9)
- Slide Switch (Pin 2)
- LED (Pin 13 – Event LED)
- LED (Pin 12 – Timer LED)

## How It Works
- PIR and Tilt sensors are monitored using Pin Change Interrupt.
- Slide switch is monitored using attachInterrupt().
- Timer1 creates a 1-second interrupt.
- Interrupt functions only set flags.
- The main loop checks flags and controls LEDs.

## Output
- If PIR and Tilt are active → Event LED turns ON.
- Slide switch change → message printed in Serial Monitor.
- Every 1 second → Timer LED toggles.

This project shows how interrupts help in real-time embedded systems.

tinker cad link :https://www.tinkercad.com/things/3ImwTp4Qm6A/editel?returnTo=%2Fdashboard

