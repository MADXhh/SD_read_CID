/*
  This software based on a Arduino SD.h Library example.
  Show: https://www.arduino.cc/reference/en/libraries/sd/
  The example shows how use the utility libraries on which the
  SD library is based in order to get info about your SD card.
  Very useful for testing a card when you're not sure whether its working or not.
  Pin numbers reflect the default SPI pins for Uno and Nano models.
  The circuit:
    SD card attached to SPI bus as follows:
 ** SDO - pin 11 on Arduino Uno/Duemilanove/Diecimila
 ** SDI - pin 12 on Arduino Uno/Duemilanove/Diecimila
 ** CLK - pin 13 on Arduino Uno/Duemilanove/Diecimila
 ** CS - depends on your SD card shield or module.
     Pin 10 used here for consistency with other Arduino examples
  original created  28 Mar 2011
  by Limor Fried
  modified 24 July 2020
  by Tom Igoe

  + changes from me :-)
*/


// include the SD library:
#include "SPI.h"
#include "SD.h"
//#include "./SD/src/SD.h"

// set up variables using the SD utility library functions:
Sd2Card card;
SdVolume volume;
SdFile root;

cid_t cid;  // *****at the top with the other globals (for get cid)

void PrintCID(cid_t cidValue);

// change this to match your SD shield or module;
// Default SPI on Uno and Nano: pin 10
// Arduino Ethernet shield: pin 4
// Adafruit SD shields and modules: pin 10
// Sparkfun SD shield: pin 8
// MKR Zero SD: SDCARD_SS_PIN
const int chipSelect = 10;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect.
  }

  Serial.println("\nInitializing SD card...");

  // we'll use the initialization code from the utility libraries
  // since we're just testing if the card is working!
  if (!card.init(SPI_HALF_SPEED, chipSelect)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("* is a card inserted?");
    Serial.println("* is your wiring correct?");
    Serial.println("* did you change the chipSelect pin to match your shield or module?");
    Serial.println("Note: press reset button on the board and reopen this Serial Monitor after fixing your issue!");
    while (1);
  } else {
    Serial.println("Wiring is correct and a card is present.");
  }

  // print the type of card
  Serial.println();
  Serial.print("Card type:                    ");
  switch (card.type()) {
    case SD_CARD_TYPE_SD1:
      Serial.println("SD1");
      break;
    case SD_CARD_TYPE_SD2:
      Serial.println("SD2");
      break;
    case SD_CARD_TYPE_SDHC:
      Serial.println("SDHC");
      break;
    default:
      Serial.println("Unknown");
  }
  Serial.println("");

  Serial.println("Read CID register...");
  Serial.println("");
  card.readCID(&cid);
  
  PrintCID(cid);
  
  Serial.println("");
  Serial.println("");
  
  /*
  // Try to open the 'volume'/'partition' - it should be FAT16 or FAT32
  if (!volume.init(card)) {
    Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
    while (1);
  }
  
  Serial.print("Clusters:          ");
  Serial.println(volume.clusterCount());
  Serial.print("Blocks x Cluster:  ");
  Serial.println(volume.blocksPerCluster());

  Serial.print("Total Blocks:      ");
  Serial.println(volume.blocksPerCluster() * volume.clusterCount());
  Serial.println();

  // print the type and size of the first FAT-type volume
  uint32_t volumesize;
  Serial.print("Volume type is:    FAT");
  Serial.println(volume.fatType(), DEC);

  volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
  volumesize *= volume.clusterCount();       // we'll have a lot of clusters
  volumesize /= 2;                           // SD card blocks are always 512 bytes (2 blocks are 1 KB)
  Serial.print("Volume size (KB):  ");
  Serial.println(volumesize);
  Serial.print("Volume size (MB):  ");
  volumesize /= 1024;
  Serial.println(volumesize);
  Serial.print("Volume size (GB):  ");
  Serial.println((float)volumesize / 1024.0);

  Serial.println("\nFiles found on the card (name, date and size in bytes): ");
  root.openRoot(volume);

  // list all files in the card with date and size
  root.ls(LS_R | LS_DATE | LS_SIZE);
  root.close();
  */
}

void loop(void) {
}


void PrintCID(cid_t cidValue)
{
  Serial.println("SD Card Info (CID register):");
  Serial.print("Manufacturer ID:              "); Serial.print("0x"); Serial.print(((uint8_t)cidValue.mid), HEX ); Serial.print(" (dec:"); Serial.print(cidValue.mid); Serial.println(")");
  Serial.print("OEM/Application ID:           "); Serial.print(cidValue.oid[0]); Serial.println(cidValue.oid[1]);
  Serial.print("Product name:                 "); Serial.print(cidValue.pnm[0]); Serial.print(cidValue.pnm[1]); Serial.print(cidValue.pnm[2]); Serial.print(cidValue.pnm[3]); Serial.println(cidValue.pnm[4]); 
  Serial.print("Product revision n.m:         "); Serial.print(cidValue.prv_n); Serial.print("."); Serial.println(cidValue.prv_m);
  Serial.print("Product serial number:        "); Serial.println(cidValue.psn);
  Serial.print("Manufacturing date YY/MM:     "); Serial.print(cidValue.mdt_year_high); Serial.print(cidValue.mdt_year_low); Serial.print("/"); Serial.println(cidValue.mdt_month);

  Serial.println(); 
  Serial.println("Raw Hex dump of CID register:");
  
  uint8_t *p = (uint8_t *)&cid;
  Serial.print("0x");
  for (int i = 0; i < sizeof(cid); i++) {
    Serial.print(p[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
}
