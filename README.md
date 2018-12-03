---
# IoT Project with Sub 1-Ghz sensor nodes and Bluetooth Low Energy Gateway
---
## CC3220SF-RT-SensorReading-and-MultimeterDisplayResult
---

## Project Summary

This repository is part of a bigger "Mobile and IoT project", composed of an Android Things module working as a Gateway for Bluetooth Low Energy sensors that uploads telemetry values to the Cloud, an Android Application that shows the sensor values in real time and this module, that creates a Sub 1-Ghz MASH network where additional sensors subscribe and publish their readings to the same Google IoT core.

The firmware found in this repository has been written in C for the CC3220 Microcontroller and creates two threads, one to make the readings of the ADC and the other to set the values to the DAC using a Pulse Width Modulation.

The different repositories have been developed by [Marc Farssac](https://github.com/marcfarssac) and can be found under his [Github](https://github.com/marcfarssac) account. 

## Background

The software developed for the CC3220 Microcontroller runs on the Texas Instruments Real Time Operating System. This embedded software or firmware uses the realtime features of the OS.

The characteristic of this MCU platform allows to build networks of distributed sensors making use of the different MESH networks, including Sub 1-Ghz, Wi-Fi, Bluetooth, Thread and Zigbee thanks to the chip build in features and SDKs.

## Current status

Currently the firmware allows to make the measurement of one thermistor and displays its value. Since the 16x2 LCD displays I had at hand are not supported by the drivers of the SDKs I have substituted it by the LCD of a multimeter. In order to display the temperature reading on the multimeter I have set an analog output with the reading of the analog input.

### ADC Conversion of the analog temperature sensor voltage

Using the SDKs primitives and after seting the GPIO pin to an analog input one of the threads reads the voltage on it. In order to simulate different temperatures I have used a potentiometer with output voltage spaning from 0v to Vcc (+3.3v)

### DAC Conversion of the digital measured temperature to an analog value

In the same way I have set up one of the pins as an analog output. A second thread is used to convert the digital values to analog using a Pulse Width Modulation. After adjusting the periode to produce the desired outputs it has been observed that the output voltage had an offset and different slope than the voltage in. Arbitrarily as a starting point a dutty cycle equivalent to the ADC reading has been used.

In order to correct this, the ADC needed to be calibrated.

### ADC Calibration

The calibration has been done setting different resistors values at the input, checking the converted ADC and observing the value at the output. The following graph shows all the measures made and can be found in this [Google Sheets document](https://docs.google.com/spreadsheets/d/1w78oADKGyZ6T9LdS9Efq9nlCd5ekKN-49e6IdjmsagY/edit?usp=sharing). All maths calaulations are found in this [Matcha file](https://www.mathcha.io/editor/xp89hYWivrhkosYB)

![calibration-values1](https://user-images.githubusercontent.com/18221570/49331802-25f3a900-f5a3-11e8-88de-f1f7db8116bd.PNG)

![adc in](https://user-images.githubusercontent.com/18221570/49338608-a5c15800-f623-11e8-9a2f-d6b8ea7f7a65.PNG) 

In the following graph we can see the ADC value read by the firmware for all given Voltage in values. In the X-Axis we have the voltage in that we have given and in the Y-Axis, the ADC. This can be represented by a linear function of order 1.

ADC = a Vin + b Using the values in the table we can isolate and find the values of a and b.

![calibration-values2](https://user-images.githubusercontent.com/18221570/49331804-28560300-f5a3-11e8-8163-507851b9b7b6.PNG)

![pwmout](https://user-images.githubusercontent.com/18221570/49338617-c2f62680-f623-11e8-839f-aa49e3bae87d.PNG)

In a different way, the Voltage out is a function of a given PWM dutty. Since we took a PWM equal to the ADC we have on the X-Axis the ADC reading and in the Y-Axis the Vout. 

The following graph shows how the Vout differs from the Vin. This expains again why the conversion has to be calibrated.

![calibration-values3](https://user-images.githubusercontent.com/18221570/49331805-2a1fc680-f5a3-11e8-81f7-b917a774e522.PNG)

![vbin vout](https://user-images.githubusercontent.com/18221570/49338622-e02af500-f623-11e8-8a7d-4944a2cdbe93.PNG)

Finally we can see how after isolating the ADC out as a function of the ADC in the Vout equals the Vin. This can also be seen in the Youtube video.

![calibration-values4](https://user-images.githubusercontent.com/18221570/49331806-2be98a00-f5a3-11e8-85fe-031b29821da1.PNG)

![calibration](https://user-images.githubusercontent.com/18221570/49338627-f33dc500-f623-11e8-936e-37df5459daf1.PNG)

## Resources

- [Data Analysis Google Sheets document](https://docs.google.com/spreadsheets/d/1w78oADKGyZ6T9LdS9Efq9nlCd5ekKN-49e6IdjmsagY/edit?usp=sharing)
- [Calculations Matcha file](https://www.mathcha.io/editor/xp89hYWivrhkosYB)

<a href="https://www.codecogs.com/eqnedit.php?latex=\begin{table}[!h]&space;\centering&space;\begin{tabular}{|p{0.90809\textwidth}|}&space;\hline&space;ADC$\displaystyle&space;_{in\&space;}&space;=\&space;m_{in}&space;\&space;\times&space;\&space;V_{in}&space;\&space;&plus;\&space;b_{1}$\\&space;\hline&space;\end{tabular}&space;\end{table}&space;\begin{gather*}&space;where\&space;m_{in}&space;\&space;=\frac{\Delta&space;ADC_{in}}{\Delta&space;V_{in}}&space;\&space;=\&space;\frac{(&space;3870\&space;-\&space;324)&space;\&space;}{(&space;3,26\&space;-\&space;3)}&space;\&space;=\&space;1182\&space;\\&space;\\&space;and\&space;b_{1}&space;\&space;=\&space;ADC_{in}&space;\&space;-\&space;1182\&space;\times&space;\&space;V_{in}\\&space;\\&space;b_{ADC_{in}&space;\&space;=\&space;324\&space;}&space;\&space;=\&space;324\&space;-\&space;1182\&space;\times&space;\&space;0,26\&space;=\&space;16,\&space;68\\&space;\end{gather*}&space;\begin{table}[!h]&space;\centering&space;\begin{tabular}{|p{0.90602\textwidth}|}&space;\hline&space;ADC$\displaystyle&space;_{in\&space;}&space;=\&space;1182\&space;\times&space;V_{in}&space;\&space;&plus;\&space;16,68$\\&space;\hline&space;\end{tabular}&space;\end{table}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\begin{table}[!h]&space;\centering&space;\begin{tabular}{|p{0.90809\textwidth}|}&space;\hline&space;ADC$\displaystyle&space;_{in\&space;}&space;=\&space;m_{in}&space;\&space;\times&space;\&space;V_{in}&space;\&space;&plus;\&space;b_{1}$\\&space;\hline&space;\end{tabular}&space;\end{table}&space;\begin{gather*}&space;where\&space;m_{in}&space;\&space;=\frac{\Delta&space;ADC_{in}}{\Delta&space;V_{in}}&space;\&space;=\&space;\frac{(&space;3870\&space;-\&space;324)&space;\&space;}{(&space;3,26\&space;-\&space;3)}&space;\&space;=\&space;1182\&space;\\&space;\\&space;and\&space;b_{1}&space;\&space;=\&space;ADC_{in}&space;\&space;-\&space;1182\&space;\times&space;\&space;V_{in}\\&space;\\&space;b_{ADC_{in}&space;\&space;=\&space;324\&space;}&space;\&space;=\&space;324\&space;-\&space;1182\&space;\times&space;\&space;0,26\&space;=\&space;16,\&space;68\\&space;\end{gather*}&space;\begin{table}[!h]&space;\centering&space;\begin{tabular}{|p{0.90602\textwidth}|}&space;\hline&space;ADC$\displaystyle&space;_{in\&space;}&space;=\&space;1182\&space;\times&space;V_{in}&space;\&space;&plus;\&space;16,68$\\&space;\hline&space;\end{tabular}&space;\end{table}" title="\begin{table}[!h] \centering \begin{tabular}{|p{0.90809\textwidth}|} \hline ADC$\displaystyle _{in\ } =\ m_{in} \ \times \ V_{in} \ +\ b_{1}$\\ \hline \end{tabular} \end{table} \begin{gather*} where\ m_{in} \ =\frac{\Delta ADC_{in}}{\Delta V_{in}} \ =\ \frac{( 3870\ -\ 324) \ }{( 3,26\ -\ 3)} \ =\ 1182\ \\ \\ and\ b_{1} \ =\ ADC_{in} \ -\ 1182\ \times \ V_{in}\\ \\ b_{ADC_{in} \ =\ 324\ } \ =\ 324\ -\ 1182\ \times \ 0,26\ =\ 16,\ 68\\ \end{gather*} \begin{table}[!h] \centering \begin{tabular}{|p{0.90602\textwidth}|} \hline ADC$\displaystyle _{in\ } =\ 1182\ \times V_{in} \ +\ 16,68$\\ \hline \end{tabular} \end{table}" /></a>
