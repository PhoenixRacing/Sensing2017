EESchema Schematic File Version 4
EELAYER 26 0
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
Text Notes 950  2050 0    50   ~ 0
Backdash includes: \nBuck\nNano x3\nRTD \nTach input\nCVT input\nWheel speed input\nIR sensor input
$Comp
L Connector:Conn_01x03_Female J1
U 1 1 5BEB8D2E
P 3250 1400
F 0 "J1" H 3277 1426 50  0000 L CNN
F 1 "Conn_01x03_Female" H 3277 1335 50  0000 L CNN
F 2 "" H 3250 1400 50  0001 C CNN
F 3 "~" H 3250 1400 50  0001 C CNN
	1    3250 1400
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x03_Female J2
U 1 1 5BEB8D7A
P 5050 1400
F 0 "J2" H 5077 1426 50  0000 L CNN
F 1 "Conn_01x03_Female" H 5077 1335 50  0000 L CNN
F 2 "" H 5050 1400 50  0001 C CNN
F 3 "~" H 5050 1400 50  0001 C CNN
	1    5050 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2750 1300 3050 1300
Wire Wire Line
	2750 1500 3050 1500
Text Label 2600 1400 0    50   ~ 0
tach_output
$Comp
L power:GND #PWR?
U 1 1 5BEB8E11
P 2750 1500
F 0 "#PWR?" H 2750 1250 50  0001 C CNN
F 1 "GND" V 2755 1372 50  0000 R CNN
F 2 "" H 2750 1500 50  0001 C CNN
F 3 "" H 2750 1500 50  0001 C CNN
	1    2750 1500
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 5BEB8E50
P 2750 1300
F 0 "#PWR?" H 2750 1150 50  0001 C CNN
F 1 "+5V" V 2765 1428 50  0000 L CNN
F 2 "" H 2750 1300 50  0001 C CNN
F 3 "" H 2750 1300 50  0001 C CNN
	1    2750 1300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2600 1400 3050 1400
Text Notes 2850 1150 0    50   ~ 0
OUTPUT FROM TACH
Wire Notes Line
	4150 1050 4150 1650
Wire Notes Line
	4150 1650 2350 1650
Wire Notes Line
	2350 1650 2350 1050
Wire Notes Line
	2350 1050 4150 1050
$Comp
L power:+5V #PWR?
U 1 1 5BEB8FB5
P 4850 1300
F 0 "#PWR?" H 4850 1150 50  0001 C CNN
F 1 "+5V" V 4865 1428 50  0000 L CNN
F 2 "" H 4850 1300 50  0001 C CNN
F 3 "" H 4850 1300 50  0001 C CNN
	1    4850 1300
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5BEB8FC4
P 4850 1500
F 0 "#PWR?" H 4850 1250 50  0001 C CNN
F 1 "GND" V 4855 1372 50  0000 R CNN
F 2 "" H 4850 1500 50  0001 C CNN
F 3 "" H 4850 1500 50  0001 C CNN
	1    4850 1500
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x04_Female J3
U 1 1 5BEB903B
P 3250 2100
F 0 "J3" H 3277 2076 50  0000 L CNN
F 1 "Conn_01x04_Female" H 3277 1985 50  0000 L CNN
F 2 "" H 3250 2100 50  0001 C CNN
F 3 "~" H 3250 2100 50  0001 C CNN
	1    3250 2100
	1    0    0    -1  
$EndComp
Text Label 4350 1400 0    50   ~ 0
wheelspeed
Wire Wire Line
	4350 1400 4850 1400
Wire Notes Line
	4200 1650 4200 1050
Wire Notes Line
	4200 1050 5950 1050
Wire Notes Line
	5950 1050 5950 1650
Wire Notes Line
	5950 1650 4200 1650
Text Notes 4500 1150 0    50   ~ 0
OUTPUT FROM WHEEL SPEED 
$Comp
L power:+5V #PWR?
U 1 1 5BEB91D2
P 3050 2000
F 0 "#PWR?" H 3050 1850 50  0001 C CNN
F 1 "+5V" V 3065 2128 50  0000 L CNN
F 2 "" H 3050 2000 50  0001 C CNN
F 3 "" H 3050 2000 50  0001 C CNN
	1    3050 2000
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5BEB91E3
P 3100 2300
F 0 "#PWR?" H 3100 2050 50  0001 C CNN
F 1 "GND" V 3105 2172 50  0000 R CNN
F 2 "" H 3100 2300 50  0001 C CNN
F 3 "" H 3100 2300 50  0001 C CNN
	1    3100 2300
	0    1    1    0   
$EndComp
Wire Wire Line
	3050 2100 2600 2100
Wire Wire Line
	2600 2200 3050 2200
Text Label 2600 2100 0    50   ~ 0
A4
Text Label 2600 2200 0    50   ~ 0
A5
Wire Notes Line
	2350 1800 4150 1800
Wire Notes Line
	4150 1800 4150 2450
Wire Notes Line
	4150 2450 2350 2450
Wire Notes Line
	2350 2450 2350 1800
Text Notes 2700 1900 0    50   ~ 0
OUTPUT FROM CVT TEMP
$EndSCHEMATC
