# EMF-Detector
Simple Arduino ElectroMagnetic Fields Detector

### Squematic
![alt text](https://github.com/ibuioli/emf-detector/blob/master/squematic.png "EMF Detector Squematic")

### Calibration
Use switch for select mode. If ON, Arduino will calibrate after 2 seconds (just one time); If OFF the calibration is disable and the sensor will capture the raw signal. On calibration, the signal has to be stable and not wanted. For re-calibrate, you have to presse the button. The calibration works like a "cleanner" for EMF not wanted.

### Save Data
Sketch save_data.pde is a simple script for connect Arduino and save the data output into txt file. It start to save when start, and stop when any key is pressed. The data is saved into data/data.csv.
