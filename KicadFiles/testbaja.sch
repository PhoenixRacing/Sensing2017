EESchema Schematic File Version 4
EELAYER 28 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector:Conn_01x05_Male J1
U 1 1 5BA4425B
P 2700 2550
F 0 "J1" H 2806 2928 50  0000 C CNN
F 1 "Conn_01x05_Male" H 2806 2837 50  0000 C CNN
F 2 "TestBaja:Buck_module" H 2700 2550 50  0001 C CNN
F 3 "~" H 2700 2550 50  0001 C CNN
	1    2700 2550
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x08_Female J2
U 1 1 5BAD48CA
P 4500 2650
F 0 "J2" H 4527 2626 50  0000 L CNN
F 1 "Conn_01x08_Female" H 4527 2535 50  0000 L CNN
F 2 "TestBaja:microSD_module" H 4500 2650 50  0001 C CNN
F 3 "~" H 4500 2650 50  0001 C CNN
	1    4500 2650
	1    0    0    -1  
$EndComp
Text Notes 4250 2250 0    50   ~ 0
microSD
Wire Wire Line
	4000 2350 4150 2350
Text Label 4000 2350 0    50   ~ 0
CD
Wire Wire Line
	4300 2450 4000 2450
Wire Wire Line
	4300 2550 4000 2550
Wire Wire Line
	4300 2650 4000 2650
Wire Wire Line
	4300 2750 4000 2750
Wire Wire Line
	4300 2850 4000 2850
Wire Wire Line
	4300 2950 4000 2950
Wire Wire Line
	4300 3050 4000 3050
Text Label 4000 2450 0    50   ~ 0
d4
Text Label 4000 2550 0    50   ~ 0
d11
Text Label 4000 2650 0    50   ~ 0
d12
Text Label 4000 2750 0    50   ~ 0
SCK
Text Label 4000 2850 0    50   ~ 0
GND
Text Label 4000 2950 0    50   ~ 0
3V3
Text Label 4000 3050 0    50   ~ 0
5V
Text Notes 2500 2100 0    50   ~ 0
BUCK
Wire Wire Line
	2900 2550 3200 2550
Wire Wire Line
	2900 2650 3200 2650
Wire Wire Line
	2900 2350 3200 2350
Text Label 3200 2350 0    50   ~ 0
PG
Text Label 3200 2550 0    50   ~ 0
IN
Text Label 3200 2650 0    50   ~ 0
GND
Text Label 3200 2750 0    50   ~ 0
5V
$Comp
L Connector:Conn_01x04_Female J3
U 1 1 5BADD25C
P 3150 3500
F 0 "J3" H 3177 3476 50  0000 L CNN
F 1 "Conn_01x04_Female" H 3177 3385 50  0000 L CNN
F 2 "TestBaja:RealTimeClock" H 3150 3500 50  0001 C CNN
F 3 "~" H 3150 3500 50  0001 C CNN
	1    3150 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2950 3400 2650 3400
Wire Wire Line
	2950 3500 2650 3500
Wire Wire Line
	2950 3600 2650 3600
Wire Wire Line
	2950 3700 2650 3700
Text Label 2650 3400 0    50   ~ 0
SCL
Text Label 2650 3500 0    50   ~ 0
SDA
Text Label 2650 3600 0    50   ~ 0
5V
Text Label 2650 3700 0    50   ~ 0
GND
Text Notes 2650 3250 0    50   ~ 0
RTC
$Comp
L Connector:Conn_01x04_Female J4
U 1 1 5BADDC61
P 5200 3450
F 0 "J4" H 5227 3426 50  0000 L CNN
F 1 "Conn_01x04_Female" H 5227 3335 50  0000 L CNN
F 2 "TestBaja:7_segment_display" H 5200 3450 50  0001 C CNN
F 3 "~" H 5200 3450 50  0001 C CNN
	1    5200 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 3350 4650 3350
Wire Wire Line
	5000 3450 4650 3450
Wire Wire Line
	5000 3550 4650 3550
Wire Wire Line
	5000 3650 4650 3650
Text Label 4650 3350 0    50   ~ 0
5V
Text Label 4650 3450 0    50   ~ 0
GND
Text Label 4650 3550 0    50   ~ 0
SDA
Text Label 4650 3650 0    50   ~ 0
SCL
$Comp
L Connector:Conn_01x16_Female J5
U 1 1 5BADEA94
P 6300 2150
F 0 "J5" H 6327 2126 50  0000 L CNN
F 1 "Conn_01x16_Female" H 6327 2035 50  0000 L CNN
F 2 "TestBaja:CAN_Module" H 6300 2150 50  0001 C CNN
F 3 "~" H 6300 2150 50  0001 C CNN
	1    6300 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 1450 5800 1450
Wire Wire Line
	6100 1550 5800 1550
Wire Wire Line
	6100 1650 5800 1650
Wire Wire Line
	6100 1750 5800 1750
Wire Wire Line
	6100 1850 5800 1850
Wire Wire Line
	6100 1950 5800 1950
Wire Wire Line
	6100 2050 5800 2050
Wire Wire Line
	6100 2150 6050 2150
Wire Wire Line
	6100 2350 5800 2350
Wire Wire Line
	6100 2850 5800 2850
Wire Wire Line
	6100 2950 5800 2950
Text Label 5800 1450 0    50   ~ 0
GND
Text Label 5800 1550 0    50   ~ 0
3V3
Text Label 5800 1650 0    50   ~ 0
d11
Text Label 5800 1750 0    50   ~ 0
d12
Text Label 5800 1850 0    50   ~ 0
SCK
Text Label 5800 1950 0    50   ~ 0
d10
Text Label 5800 2050 0    50   ~ 0
RST
Text Label 5800 2150 0    50   ~ 0
NC
Text Label 5800 2350 0    50   ~ 0
INT
Text Label 5800 2850 0    50   ~ 0
5V
Text Label 5800 2950 0    50   ~ 0
GND
Text Notes 5650 3400 0    50   ~ 0
7-seg
Text Notes 6100 1300 0    50   ~ 0
CAN
$Comp
L Connector:Conn_01x04_Female J8
U 1 1 5BAE551C
P 5200 4000
F 0 "J8" H 5227 3976 50  0000 L CNN
F 1 "Conn_01x04_Female" H 5227 3885 50  0000 L CNN
F 2 "TestBaja:7_segment_display" H 5200 4000 50  0001 C CNN
F 3 "~" H 5200 4000 50  0001 C CNN
	1    5200 4000
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Female J6
U 1 1 5BAE5558
P 6750 3350
F 0 "J6" H 6777 3326 50  0000 L CNN
F 1 "Conn_01x04_Female" H 6777 3235 50  0000 L CNN
F 2 "TestBaja:7_segment_display" H 6750 3350 50  0001 C CNN
F 3 "~" H 6750 3350 50  0001 C CNN
	1    6750 3350
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Female J7
U 1 1 5BAE55AF
P 6750 4000
F 0 "J7" H 6777 3976 50  0000 L CNN
F 1 "Conn_01x04_Female" H 6777 3885 50  0000 L CNN
F 2 "TestBaja:7_segment_display" H 6750 4000 50  0001 C CNN
F 3 "~" H 6750 4000 50  0001 C CNN
	1    6750 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 3900 4700 3900
Wire Wire Line
	4700 4000 5000 4000
Wire Wire Line
	5000 4100 4700 4100
Wire Wire Line
	4700 4200 5000 4200
Wire Wire Line
	6550 4200 6250 4200
Wire Wire Line
	6250 4100 6550 4100
Wire Wire Line
	6550 4000 6250 4000
Wire Wire Line
	6250 3900 6550 3900
Wire Wire Line
	6550 3550 6250 3550
Wire Wire Line
	6550 3450 6250 3450
Wire Wire Line
	6250 3350 6550 3350
Wire Wire Line
	6550 3250 6250 3250
Text Label 4700 3900 0    50   ~ 0
5V
Text Label 6250 3900 0    50   ~ 0
5V
Text Label 6250 3250 0    50   ~ 0
5V
Text Label 6250 3350 0    50   ~ 0
GND
Text Label 6250 4000 0    50   ~ 0
GND
Text Label 4700 4000 0    50   ~ 0
GND
Text Label 4700 4100 0    50   ~ 0
SDA
Text Label 6250 4100 0    50   ~ 0
SDA
Text Label 6250 3450 0    50   ~ 0
SDA
Text Label 6250 3550 0    50   ~ 0
SCL
Text Label 6250 4200 0    50   ~ 0
SCL
Text Label 4700 4200 0    50   ~ 0
SCL
$Comp
L Connector:Conn_01x30_Female J9
U 1 1 5BB4261D
P 9450 2700
F 0 "J9" H 9477 2676 50  0000 L CNN
F 1 "Conn_01x30_Female" H 9477 2585 50  0000 L CNN
F 2 "TestBaja:arduino_nano" H 9450 2700 50  0001 C CNN
F 3 "~" H 9450 2700 50  0001 C CNN
	1    9450 2700
	1    0    0    -1  
$EndComp
Text Notes 9200 1200 0    50   ~ 0
Arduino nano
Wire Wire Line
	9250 1300 8950 1300
Wire Wire Line
	8950 1400 9250 1400
Wire Wire Line
	9250 1500 8950 1500
Wire Wire Line
	8950 1600 9250 1600
Wire Wire Line
	9250 1700 8950 1700
Wire Wire Line
	8950 1800 9250 1800
Wire Wire Line
	9250 1900 8950 1900
Wire Wire Line
	8950 2000 9250 2000
Wire Wire Line
	9250 2100 8950 2100
Wire Wire Line
	8950 2200 9250 2200
Wire Wire Line
	9250 2300 8950 2300
Wire Wire Line
	8950 2400 9250 2400
Wire Wire Line
	8950 2500 9250 2500
Wire Wire Line
	9250 2600 8950 2600
Wire Wire Line
	8950 2700 9250 2700
Wire Wire Line
	9250 2800 8950 2800
Wire Wire Line
	8950 2900 9250 2900
Wire Wire Line
	9250 3000 8950 3000
Wire Wire Line
	8950 3100 9250 3100
Wire Wire Line
	9250 3200 8950 3200
Wire Wire Line
	8950 3300 9250 3300
Wire Wire Line
	9250 3400 8950 3400
Wire Wire Line
	8950 3500 9250 3500
Wire Wire Line
	9250 3600 8950 3600
Wire Wire Line
	8950 3700 9250 3700
Wire Wire Line
	9250 3800 8950 3800
Wire Wire Line
	8950 3900 9250 3900
Wire Wire Line
	8950 4000 9250 4000
Wire Wire Line
	9250 4100 8950 4100
Wire Wire Line
	8950 4200 9250 4200
Text Label 8950 1300 0    50   ~ 0
tx1
Text Label 8950 1400 0    50   ~ 0
rx0
Text Label 8950 1500 0    50   ~ 0
rst
Text Label 8950 1600 0    50   ~ 0
GND
Text Label 8950 1700 0    50   ~ 0
d2
Text Label 8950 1800 0    50   ~ 0
d3
Text Label 8950 1900 0    50   ~ 0
d4
Text Label 8950 2000 0    50   ~ 0
d5
Text Label 8950 2100 0    50   ~ 0
d6
Text Label 8950 2200 0    50   ~ 0
d7
Text Label 8950 2300 0    50   ~ 0
d8
Text Label 8950 2400 0    50   ~ 0
d9
Text Label 8950 2500 0    50   ~ 0
d10
Text Label 8950 2600 0    50   ~ 0
d11
Text Label 8950 2700 0    50   ~ 0
d12
Text Label 8950 2800 0    50   ~ 0
SCK
Text Label 8950 2900 0    50   ~ 0
3V3
Text Label 8950 3000 0    50   ~ 0
ref
Text Label 8950 3100 0    50   ~ 0
a0
Text Label 8950 3200 0    50   ~ 0
a1
Text Label 8950 3300 0    50   ~ 0
a2
Text Label 8950 3400 0    50   ~ 0
a3
Text Label 8950 3500 0    50   ~ 0
SDA
Text Label 8950 3600 0    50   ~ 0
SCL
Text Label 8950 3700 0    50   ~ 0
a6
Text Label 8950 3800 0    50   ~ 0
a7
Text Label 8950 3900 0    50   ~ 0
5V
Text Label 8950 4000 0    50   ~ 0
rst
Text Label 8950 4100 0    50   ~ 0
GND
Text Label 8950 4200 0    50   ~ 0
vin
Text Notes 4600 2450 0    50   ~ 0
cs
Text Notes 9500 1900 0    50   ~ 0
cs for microsd
Text Notes 9550 2650 0    50   ~ 0
miso for microsd
Text Notes 9550 2600 0    50   ~ 0
mosi
Text Notes 4550 2550 0    50   ~ 0
sdi
Text Notes 4550 2650 0    50   ~ 0
sdo
Text Notes 6350 1750 0    50   ~ 0
sdo
Text Notes 6350 1650 0    50   ~ 0
sdi
Text Label 2600 1400 0    50   ~ 0
IN_UNFUSED
Text Label 2600 1300 0    50   ~ 0
GND
Wire Wire Line
	2900 2450 3200 2450
Wire Wire Line
	6100 2250 6050 2250
Wire Wire Line
	6050 2250 6050 2150
Connection ~ 6050 2150
Wire Wire Line
	6050 2150 5800 2150
Wire Wire Line
	6050 2250 5700 2250
Wire Wire Line
	5700 2250 5700 2450
Wire Wire Line
	5700 2450 6100 2450
Connection ~ 6050 2250
Wire Wire Line
	6100 2750 6100 2650
Wire Wire Line
	6100 2550 6100 2450
Connection ~ 6100 2450
Wire Wire Line
	6100 2650 6100 2550
Connection ~ 6100 2650
Connection ~ 6100 2550
$Comp
L Device:R R1
U 1 1 5BB970D7
P 4150 2200
F 0 "R1" H 4220 2246 50  0000 L CNN
F 1 "R" H 4220 2155 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 4080 2200 50  0001 C CNN
F 3 "~" H 4150 2200 50  0001 C CNN
	1    4150 2200
	1    0    0    -1  
$EndComp
Connection ~ 4150 2350
Wire Wire Line
	4150 2350 4300 2350
Wire Wire Line
	4150 2050 4150 1850
Text Label 4150 1850 0    50   ~ 0
5V
$Comp
L Device:Fuse F1
U 1 1 5BBD7D5C
P 2050 1400
F 0 "F1" H 2110 1446 50  0000 L CNN
F 1 "Fuse" H 2110 1355 50  0000 L CNN
F 2 "TestBaja:Fuse_0ZCFSeries" V 1980 1400 50  0001 C CNN
F 3 "~" H 2050 1400 50  0001 C CNN
	1    2050 1400
	0    -1   -1   0   
$EndComp
Text Label 1800 1400 0    50   ~ 0
IN
$Comp
L Connector:Conn_01x04_Female J10
U 1 1 5BBFF9EB
P 3300 1300
F 0 "J10" H 3327 1276 50  0000 L CNN
F 1 "Conn_01x04_Female" H 3327 1185 50  0000 L CNN
F 2 "TestBaja:DC_Connector" H 3300 1300 50  0001 C CNN
F 3 "~" H 3300 1300 50  0001 C CNN
	1    3300 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 1300 2600 1300
Wire Wire Line
	2200 1400 3100 1400
Wire Wire Line
	3100 1500 2600 1500
Wire Wire Line
	2600 1200 3100 1200
Text Label 2600 1200 0    50   ~ 0
GND
Text Label 2600 1500 0    50   ~ 0
GND
$Comp
L LED:CQY99 D1
U 1 1 5BC89853
P 1650 1550
F 0 "D1" V 1646 1472 50  0000 R CNN
F 1 "RED" V 1555 1472 50  0000 R CNN
F 2 "LED_THT:LED_D5.0mm_FlatTop" H 1650 1725 50  0001 C CNN
F 3 "https://www.prtice.info/IMG/pdf/CQY99.pdf" H 1600 1550 50  0001 C CNN
	1    1650 1550
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R2
U 1 1 5BC8CD5C
P 1650 1900
F 0 "R2" H 1720 1946 50  0000 L CNN
F 1 "220" H 1720 1855 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 1580 1900 50  0001 C CNN
F 3 "~" H 1650 1900 50  0001 C CNN
	1    1650 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 2050 1650 2100
Wire Wire Line
	1650 2100 1950 2100
Text Label 1950 2100 0    50   ~ 0
GND
Wire Wire Line
	1650 1400 1650 1450
Wire Wire Line
	1650 1400 1900 1400
Wire Wire Line
	3200 2550 3200 2450
Wire Wire Line
	2900 2750 3200 2750
$EndSCHEMATC
