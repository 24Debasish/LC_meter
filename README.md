
# LC Meter – Inductance and Capacitance Measurement

**A low-cost, portable electronic measurement device designed using an ATmega328P microcontroller to measure inductance and capacitance with an LCD interface.**

---

## 1. Project Overview

The LC Meter is an electronic measurement device developed to measure the values of inductors and capacitors using a low-cost hardware implementation.

Traditional low-cost digital multimeters generally do not provide inductance and capacitance measurement capabilities, while dedicated LC meters available in the market can be relatively expensive.

This project addresses these limitations by implementing an affordable, portable, and efficient LC measurement system using an ATmega328P microcontroller, an LM393 comparator, and a 16×2 LCD display.

The device supports two measurement modes:
- Inductance measurement using LC resonant frequency.
- Capacitance measurement using the RC charging time constant.

## 2. Project Objectives

- Design and implement a low-cost LC measurement device.
- Measure inductance using the resonant frequency of an LC tank circuit.
- Determine capacitance using the RC charging time constant.
- Integrate an LCD interface for displaying measurement results.
- Develop a portable and user-friendly measurement solution.
- Achieve satisfactory measurement accuracy using commonly available electronic components.

## 3. Architecture and Design Components

The system consists of a microcontroller-based measurement architecture with dedicated circuits for inductance and capacitance measurement.

### Major Hardware Components

| Component | Description |
|---|---|
| ATmega328P | Main microcontroller for measurement and control |
| LM393 | Comparator IC for oscillation signal detection |
| LM7805 | 5V voltage regulator |
| 16×2 LCD | Measurement output display |
| 2.2 µF Capacitor | Reference capacitor for LC measurement |
| 1N4007 Diode | Signal path component in the inductance circuit |
| Resistors | Charging, discharging and circuit biasing |

### Functional Architecture

The measurement system operates through the following functional blocks:

1. Inductance measurement circuit.
2. Capacitance measurement circuit.
3. Signal conditioning and comparator interface.
4. ATmega328P-based processing and control.
5. LCD-based measurement output.

## 4. Inductance Measurement Architecture

Inductance is measured using the resonant frequency of an LC tank circuit.

### Working Principle

1. The Arduino generates a rectangular pulse.
2. The pulse passes through resistor R4 and a 1N4007 diode.
3. During the high-level pulse, the capacitor charges.
4. The inductor connected in parallel with the capacitor forms an LC tank circuit.
5. The LC tank circuit generates damped oscillations.
6. The LM393 comparator detects the oscillating signal and generates a corresponding rectangular pulse.
7. The output pulse is fed back to the Arduino.
8. The Arduino measures the pulse duration using the `pulseIn()` function.
9. The measured frequency is used to determine the inductance.

## 5. Capacitance Measurement Architecture

Capacitance is measured using the RC charging time constant.

### Working Principle

1. Initially, the capacitor is discharged through a 470 Ω resistor (R3).
2. The capacitor voltage decreases close to 0V.
3. Pin 18 is configured as a high-impedance input to minimize circuit interference.
4. Pin 23 is configured HIGH (5V), allowing the capacitor to charge through R2 (2.2 kΩ).
5. Pin 24 monitors the capacitor voltage and measures the charging time.
6. The timer stops when the capacitor reaches approximately 3.465V, corresponding to 69.3% of the 5V supply.
7. The measured charging time represents the RC time constant.
8. The capacitance is determined using the known resistance and measured time constant.

## 6. Circuital Implementation

The hardware implementation integrates the inductance and capacitance measurement circuits with the microcontroller and LCD interface.

### Inductance Measurement Circuit

The LC tank circuit generates damped oscillations based on the connected inductor and reference capacitor. The LM393 comparator converts the oscillating signal into a rectangular pulse suitable for microcontroller processing.

### Capacitance Measurement Circuit

The capacitance measurement circuit uses controlled charging and discharging paths. The microcontroller measures the time required for the capacitor voltage to reach the specified threshold.

### Display Interface

A 16×2 LCD displays the calculated inductance and capacitance values. A mode-switching feature enables transition between the two measurement functions.

## 7. Results and Testing

The prototype was tested using known inductance and capacitance values to evaluate its measurement performance.

### Inductance Measurement

| Parameter | Value |
|---|---:|
| Known inductance | 120 µH |
| Calculated inductance | 59.69 µH |
| Additional inductance | 22 µH |
| Combined inductance | 81.69 µH |

### Capacitance Measurement

The capacitance measurement circuit was tested using:

- 10 µF capacitor.
- 1000 µF capacitor.

The measurement results were displayed through the LCD interface.

## 8. Future Scope

- Integrate an advanced microcontroller such as STM32 or ESP32 for improved performance and measurement accuracy.
- Incorporate a rechargeable battery for improved portability.
- Introduce additional capacitor charging paths to improve measurement precision.
- Optimize the measurement circuitry for better reliability and accuracy.

## 9. Conclusion

The LC Meter project successfully demonstrates a low-cost electronic solution for measuring inductance and capacitance. By integrating an ATmega328P microcontroller, LM393 comparator, and LCD interface, the system provides two measurement modes using LC resonance and RC time-constant methodologies.

The prototype demonstrates the practical application of analog electronics, microcontroller programming, signal conditioning, and electronic measurement techniques.

---

## 10. Author Information

**Project Contributors:**

- Tanmoy Haldar
- Surya Chatterjee
- Dipak Paswan
- Debashis Ghosh

**Project Author:** Debashis Ghosh

**Guided By:** Prof. Dr. Sukla Basu
