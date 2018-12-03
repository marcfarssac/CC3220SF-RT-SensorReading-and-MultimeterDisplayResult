---
# IoT Project with Sub 1-Ghz sensor nodes and Bluetooth Low Energy Gateway
---
## CC3220SF-RT-SensorReading-and-MultimeterDisplayResult
---

## Project Summary

This repository is part of a bigger "Mobile and IoT project", composed of an Android Things module working as a Gateway for Bluetooth Low Energy sensors that uploads telemetry values to the Cloud, an Android Application that shows the sensor values in real time and this module, that creates a Sub 1-Ghz MASH network where additional sensors subscribe and publish their readings to the same Google IoT core.

I have written the firmware found in this repository in C for the CC3220 Microcontroller and creates two threads, one to make the readings of the ADC and the other to set the values to the DAC using a Pulse Width Modulation.

The different repositories have been developed by [Marc Farssac](https://github.com/marcfarssac) and can be found under his [Github](https://github.com/marcfarssac) account. 

### Youtube Video (Project summary)

[![Watch the video](https://user-images.githubusercontent.com/18221570/49393651-28383d80-f732-11e8-8756-1fcd79d88fa2.PNG)](https://youtu.be/QPvVPHSGuN0?list=PLk7A4gvo5SIdjq2N2y8oxlR_yW7zcPpmn)

[Summary YouTube video link](https://youtu.be/QPvVPHSGuN0?list=PLk7A4gvo5SIdjq2N2y8oxlR_yW7zcPpmn):[https://youtu.be/QPvVPHSGuN0?list=PLk7A4gvo5SIdjq2N2y8oxlR_yW7zcPpmn](https://youtu.be/QPvVPHSGuN0?list=PLk7A4gvo5SIdjq2N2y8oxlR_yW7zcPpmn)

### Youtube Video (Extended explanations)

[![Watch the video](https://user-images.githubusercontent.com/18221570/49393650-28383d80-f732-11e8-98a8-a041cd77c540.PNG)](https://youtu.be/oZzbYkJpgOQ?list=PLk7A4gvo5SIdjq2N2y8oxlR_yW7zcPpmn)

[Extended YouTube video link](https://youtu.be/oZzbYkJpgOQ?list=PLk7A4gvo5SIdjq2N2y8oxlR_yW7zcPpmn) : [https://youtu.be/oZzbYkJpgOQ?list=PLk7A4gvo5SIdjq2N2y8oxlR_yW7zcPpmn](https://youtu.be/oZzbYkJpgOQ?list=PLk7A4gvo5SIdjq2N2y8oxlR_yW7zcPpmn)

### Screenshoots

|ADC Calibration setup|Whole IoT Sensor Readings project       |
|-----------|-----------|
|<img src="https://user-images.githubusercontent.com/18221570/49393839-a4cb1c00-f732-11e8-92e8-a1d7477e12b4.jpg" width=500></img> | <img src="https://user-images.githubusercontent.com/18221570/49393842-a563b280-f732-11e8-9693-cbcf68faf682.jpg" width=500></img>|

## Background

The software developed for the CC3220 Microcontroller runs on the Texas Instruments Real Time Operating System. This embedded software or firmware uses the realtime features of the OS.

The characteristic of this MCU platform allows to build networks of distributed sensors making use of the different MESH networks, including Sub 1-Ghz, Wi-Fi, Bluetooth, Thread and Zigbee thanks to the chip build in features and SDKs.

## Current status

Currently the firmware allows to make the measurement of one thermistor and displays its value. Since the 16x2 LCD displays I had at hand are not supported by the drivers of the SDKs I have substituted it by the LCD of a multimeter. In order to display the temperature reading on the multimeter I have set an analog output with the reading of the analog input.

### Data Analysis

|ADC and PWM Measurements |Mathematical analysis       |
|-----------|-----------|
|<img src="https://user-images.githubusercontent.com/18221570/49394144-6da93a80-f733-11e8-8945-6aff1a637f43.PNG" width=400 height="200"></img><br/>[Watch the measurements](https://docs.google.com/spreadsheets/d/1w78oADKGyZ6T9LdS9Efq9nlCd5ekKN-49e6IdjmsagY/edit?usp=sharing)| <img src="https://user-images.githubusercontent.com/18221570/49394142-6d10a400-f733-11e8-9587-d2ac038cc48b.PNG" width=400 height="200"></img><br/>[Review the Mathematical Analysis](https://www.mathcha.io/editor/xp89hYWivrhkosYB)|

### ADC Conversion of the analog temperature sensor voltage

Using the SDKs primitives and after seting the GPIO pin to an analog input one of the threads reads the voltage on it. In order to simulate different temperatures I have used a potentiometer with output voltage spaning from 0v to Vcc (+3.3v)

### DAC Conversion of the digital measured temperature to an analog value

In the same way I have set up one of the pins as an analog output. A second thread is used to convert the digital values to analog using a Pulse Width Modulation. After adjusting the periode to produce the desired outputs it has been observed that the output voltage had an offset and different slope than the voltage in. Arbitrarily as a starting point a dutty cycle equivalent to the ADC reading has been used.

In order to correct this, the ADC needed to be calibrated.

### ADC Calibration

The calibration has been done setting different resistors values at the input, checking the converted ADC and observing the value at the output. The following graph shows all the measures made and can be found in this [Google Sheets document](https://docs.google.com/spreadsheets/d/1w78oADKGyZ6T9LdS9Efq9nlCd5ekKN-49e6IdjmsagY/edit?usp=sharing). All maths calaulations are found in this [Matcha file](https://www.mathcha.io/editor/xp89hYWivrhkosYB)

![calibration-values1](https://user-images.githubusercontent.com/18221570/49371079-8e06d400-f6f6-11e8-95c6-2c513bdbf6a4.PNG)
![adc in](https://user-images.githubusercontent.com/18221570/49338608-a5c15800-f623-11e8-9a2f-d6b8ea7f7a65.PNG) 

In the following graph we can see the ADC value read by the firmware for all given Voltage in values. In the X-Axis we have the voltage in that we have given and in the Y-Axis, the ADC. This can be represented by a linear function of order 1.

ADC = a Vin + b Using the values in the table we can isolate and find the values of a and b.

![calibration-values2](https://user-images.githubusercontent.com/18221570/49371078-8e06d400-f6f6-11e8-82a2-2195fef8817b.PNG)

![pwmout](https://user-images.githubusercontent.com/18221570/49338617-c2f62680-f623-11e8-839f-aa49e3bae87d.PNG)

In a different way, the Voltage out is a function of a given PWM dutty. Since we took a PWM equal to the ADC we have on the X-Axis the ADC reading and in the Y-Axis the Vout. 

The following graph shows how the Vout differs from the Vin. This expains again why the conversion has to be calibrated.

![calibration-values3](https://user-images.githubusercontent.com/18221570/49371076-8d6e3d80-f6f6-11e8-83af-51fbd0c0919c.PNG)

![vbin vout](https://user-images.githubusercontent.com/18221570/49338622-e02af500-f623-11e8-8a7d-4944a2cdbe93.PNG)

Finally we can see how after isolating the ADC out as a function of the ADC in the Vout equals the Vin. This can also be seen in the Youtube video.

![calibration-values4](https://user-images.githubusercontent.com/18221570/49371075-8d6e3d80-f6f6-11e8-94c1-de06bc3b0213.PNG)

![calibration](https://user-images.githubusercontent.com/18221570/49338627-f33dc500-f623-11e8-936e-37df5459daf1.PNG)

However there is one thing that is surprising. The Vin and Vout are linear and also the ADC reading. So why is the calibration not linear? 

### Non linearity of the calibration factor

There are a few things that need to be taken into account. 

At the Voltage in:
- Inaccuracy of the reference voltage, which can easily introduce an error of twenty counts with only a 60mv variation using a 10-bit ADC. Twenty counts represent almost 5% error in the ADC value provided at low voltages.
- Measurement errors of the Vin at low voltages. These errors are introduced by the human reading of the values shown in the multimeter, which lack accuracy at the milivolt level.
- Measurement errors introduce by the multimeter lacking calibration.

At the voltage out:
- Not using a True-RMS multimeter provides an approximate reading. The DV value read at the output is the result of sampling a PWM signal, which introduces some errors too.

## Resources

- [Data Analysis Google Sheets document](https://docs.google.com/spreadsheets/d/1w78oADKGyZ6T9LdS9Efq9nlCd5ekKN-49e6IdjmsagY/edit?usp=sharing)
- [Calculations Matcha file](https://www.mathcha.io/editor/xp89hYWivrhkosYB)

## License
Copyright 2018 Marc Farssac

Licensed to the Apache Software Foundation (ASF) under one or more contributor license agreements. See the NOTICE file distributed with this work for additional information regarding copyright ownership. The ASF licenses this file to you under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.

