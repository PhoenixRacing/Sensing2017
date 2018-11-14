EESchema Schematic File Version 4
LIBS:backdash-cache
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
Text Label 1550 2900 2    50   ~ 0
A0
Text Label 1550 3000 2    50   ~ 0
A1
Text Label 1550 3100 2    50   ~ 0
A2
Text Label 1550 3200 2    50   ~ 0
A3
Text Label 1550 3300 2    50   ~ 0
A4
Text Label 1550 3400 2    50   ~ 0
A5
Text Label 1550 3500 2    50   ~ 0
A6
Text Label 1550 3600 2    50   ~ 0
A7
Text Label 1550 3700 2    50   ~ 0
VCC
Text Label 1550 3800 2    50   ~ 0
RST
Text Label 1550 3900 2    50   ~ 0
GND
Text Label 1550 4000 2    50   ~ 0
VIN
Text Label 1550 2500 2    50   ~ 0
D12
Text Label 1550 2400 2    50   ~ 0
D11
Text Label 1550 2300 2    50   ~ 0
D10
Text Label 1550 2200 2    50   ~ 0
D9
Text Label 1550 2100 2    50   ~ 0
D8
Text Label 1550 2000 2    50   ~ 0
D7
Text Label 1550 1900 2    50   ~ 0
D6
Text Label 1550 1800 2    50   ~ 0
D5
Text Label 1550 1700 2    50   ~ 0
D4
Text Label 1550 1600 2    50   ~ 0
D3
Text Label 1550 1500 2    50   ~ 0
D2
Text Label 1550 1400 2    50   ~ 0
GND
Text Label 1550 1300 2    50   ~ 0
RST
Text Label 1550 1200 2    50   ~ 0
RX0
$Comp
L Connector:Conn_01x30_Female NANO1
U 1 1 5BD90424
P 1750 2500
F 0 "NANO1" H 1777 2476 50  0000 L CNN
F 1 "Conn_01x30_Female" H 1777 2385 50  0000 L CNN
F 2 "TestBaja:arduino_nano" H 1750 2500 50  0001 C CNN
F 3 "~" H 1750 2500 50  0001 C CNN
	1    1750 2500
	1    0    0    -1  
$EndComp
Text Label 1550 2600 2    50   ~ 0
D13
Text Label 1550 2700 2    50   ~ 0
3.3V
Text Label 1550 2800 2    50   ~ 0
REF
Text Label 1550 1100 2    50   ~ 0
TX1
$Comp
L Connector:Conn_01x08_Female RTD1
U 1 1 5BD9076A
P 2850 1550
F 0 "RTD1" H 2877 1526 50  0000 L CNN
F 1 "Conn_01x08_Female" H 2877 1435 50  0000 L CNN
F 2 "TestBaja:RTD" H 2850 1550 50  0001 C CNN
F 3 "~" H 2850 1550 50  0001 C CNN
	1    2850 1550
	1    0    0    -1  
$EndComp
Text Label 2650 1250 2    50   ~ 0
VIN
Text Label 2650 1350 2    50   ~ 0
GND
Text Label 2650 1450 2    50   ~ 0
3V3
Text Label 2650 1550 2    50   ~ 0
CLK
Text Label 2650 1650 2    50   ~ 0
SDO
Text Label 2650 1750 2    50   ~ 0
SDI
Text Label 2650 1850 2    50   ~ 0
CS
Text Label 2650 1950 2    50   ~ 0
RDY
$Comp
L Connector:Conn_01x16_Female CAN1
U 1 1 5BD90B2E
P 3450 2950
F 0 "CAN1" H 3477 2926 50  0000 L CNN
F 1 "Conn_01x16_Female" H 3477 2835 50  0000 L CNN
F 2 "TestBaja:CAN_Module" H 3450 2950 50  0001 C CNN
F 3 "~" H 3450 2950 50  0001 C CNN
	1    3450 2950
	1    0    0    -1  
$EndComp
Text Label 3250 2250 2    50   ~ 0
GND
Text Label 3250 2350 2    50   ~ 0
3.3V
Text Label 3250 2450 2    50   ~ 0
SDI
Text Label 3250 2550 2    50   ~ 0
SDO
Text Label 3250 2650 2    50   ~ 0
SCK
Text Label 3250 2750 2    50   ~ 0
CS
Text Label 3250 2850 2    50   ~ 0
RST
Text Label 3250 2950 2    50   ~ 0
NC
Text Label 3250 3050 2    50   ~ 0
NC
Text Label 3250 3150 2    50   ~ 0
INT
Text Label 3250 3250 2    50   ~ 0
NC
Text Label 3250 3350 2    50   ~ 0
NC
Text Label 3250 3450 2    50   ~ 0
NC
Text Label 3250 3550 2    50   ~ 0
NC
Text Label 3250 3650 2    50   ~ 0
VCC
Text Label 3250 3750 2    50   ~ 0
GND
$Comp
L Connector:Conn_01x05_Female BUCK1
U 1 1 5BDBB2FB
P 4350 1900
F 0 "BUCK1" H 4378 1926 50  0000 L CNN
F 1 "Conn_01x05_Female" H 4378 1835 50  0000 L CNN
F 2 "TestBaja:Buck_module" H 4350 1900 50  0001 C CNN
F 3 "~" H 4350 1900 50  0001 C CNN
	1    4350 1900
	1    0    0    -1  
$EndComp
Text Notes 4000 2100 0    50   ~ 0
OUT\n
Text Label 1500 6150 2    50   ~ 0
A0
Text Label 1500 6250 2    50   ~ 0
A1
Text Label 1500 6350 2    50   ~ 0
A2
Text Label 1500 6450 2    50   ~ 0
A3
Text Label 1500 6550 2    50   ~ 0
A4
Text Label 1500 6650 2    50   ~ 0
A5
Text Label 1500 6750 2    50   ~ 0
A6
Text Label 1500 6850 2    50   ~ 0
A7
Text Label 1500 6950 2    50   ~ 0
VCC
Text Label 1500 7050 2    50   ~ 0
RST
Text Label 1500 7150 2    50   ~ 0
GND
Text Label 1500 7250 2    50   ~ 0
VIN
Text Label 1500 5750 2    50   ~ 0
D12
Text Label 1500 5650 2    50   ~ 0
D11
Text Label 1500 5550 2    50   ~ 0
D10
Text Label 1500 5450 2    50   ~ 0
D9
Text Label 1500 5350 2    50   ~ 0
D8
Text Label 1500 5250 2    50   ~ 0
D7
Text Label 1500 5150 2    50   ~ 0
D6
Text Label 1500 5050 2    50   ~ 0
D5
Text Label 1500 4950 2    50   ~ 0
D4
Text Label 1500 4850 2    50   ~ 0
D3
Text Label 1500 4750 2    50   ~ 0
D2
Text Label 1500 4650 2    50   ~ 0
GND
Text Label 1500 4550 2    50   ~ 0
RST
Text Label 1500 4450 2    50   ~ 0
RX0
$Comp
L Connector:Conn_01x30_Female NANO2
U 1 1 5BDBAFDD
P 1700 5750
F 0 "NANO2" H 1727 5726 50  0000 L CNN
F 1 "Conn_01x30_Female" H 1727 5635 50  0000 L CNN
F 2 "TestBaja:arduino_nano" H 1700 5750 50  0001 C CNN
F 3 "~" H 1700 5750 50  0001 C CNN
	1    1700 5750
	1    0    0    -1  
$EndComp
Text Label 1500 5850 2    50   ~ 0
D13
Text Label 1500 5950 2    50   ~ 0
3.3V
Text Label 1500 6050 2    50   ~ 0
REF
Text Label 1500 4350 2    50   ~ 0
TX1
Text Label 3250 6250 2    50   ~ 0
A0
Text Label 3250 6350 2    50   ~ 0
A1
Text Label 3250 6450 2    50   ~ 0
A2
Text Label 3250 6550 2    50   ~ 0
A3
Text Label 3250 6650 2    50   ~ 0
A4
Text Label 3250 6750 2    50   ~ 0
A5
Text Label 3250 6850 2    50   ~ 0
A6
Text Label 3250 6950 2    50   ~ 0
A7
Text Label 3250 7050 2    50   ~ 0
VCC
Text Label 3250 7150 2    50   ~ 0
RST
Text Label 3250 7250 2    50   ~ 0
GND
Text Label 3250 7350 2    50   ~ 0
VIN
Text Label 3250 5850 2    50   ~ 0
D12
Text Label 3250 5750 2    50   ~ 0
D11
Text Label 3250 5650 2    50   ~ 0
D10
Text Label 3250 5550 2    50   ~ 0
D9
Text Label 3250 5450 2    50   ~ 0
D8
Text Label 3250 5350 2    50   ~ 0
D7
Text Label 3250 5250 2    50   ~ 0
D6
Text Label 3250 5150 2    50   ~ 0
D5
Text Label 3250 5050 2    50   ~ 0
D4
Text Label 3250 4950 2    50   ~ 0
D3
Text Label 3250 4850 2    50   ~ 0
D2
Text Label 3250 4750 2    50   ~ 0
GND
Text Label 3250 4650 2    50   ~ 0
RST
Text Label 3250 4550 2    50   ~ 0
RX0
$Comp
L Connector:Conn_01x30_Female NANO3
U 1 1 5BDBB034
P 3450 5850
F 0 "NANO3" H 3477 5826 50  0000 L CNN
F 1 "Conn_01x30_Female" H 3477 5735 50  0000 L CNN
F 2 "TestBaja:arduino_nano" H 3450 5850 50  0001 C CNN
F 3 "~" H 3450 5850 50  0001 C CNN
	1    3450 5850
	1    0    0    -1  
$EndComp
Text Label 3250 5950 2    50   ~ 0
D13
Text Label 3250 6050 2    50   ~ 0
3.3V
Text Label 3250 6150 2    50   ~ 0
REF
Text Label 3250 4450 2    50   ~ 0
TX1
NoConn ~ 1700 1100
NoConn ~ 1700 1200
NoConn ~ 1700 1300
NoConn ~ 1550 1300
NoConn ~ 1550 1200
NoConn ~ 1550 1100
NoConn ~ 1750 1400
NoConn ~ 1750 1500
$EndSCHEMATC
