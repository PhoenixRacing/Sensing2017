# Olin College of Engineering Baja Electrical Subteam Repository

## Backbox

Contains the back-end files (.ino) for the various Arduinos responsible for communication and various tasks relating to reading in sensor data and passing it to the dashboard and SD card.

## Dashboard

Contains the files (.ino) necessary for communicating between the dashboard Arduino and the backbox, as well as for displaying information to the driver as well as logging the information the SD card.

## Dependencies

Contains the libraries necessary to making the code compile on the Arduinos.

## Examples

Contains example code for the various components of the electrical subsystem (refer to system architecture diagram); utilize this for reference for skeleton code.

## LogFiles

Contains (or will contain) the log files saved on the SD card from the car. Will either be in .csv or.xlsx format.

## Outdated Code

Contains archival code from past years that has been ommitted for various reasons (didn't work, redone, unnecessary).

## i2cSlaveTest

Will be absorbed underneath Examples directory eventually. Contains example code for a test for communication between two Arduinos over i2c.
