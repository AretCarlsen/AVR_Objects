
#pragma once

#define SPI_DIRECTION_BUS    DDRB
#define MISO_PIN             PB4
#define MOSI_PIN             PB3
#define SCK_PIN              PB5
#define SS_PIN               PB2

#define DUMMY_BYTE 0

class SPI {
public:
  // This could be defined as an enum of the possible values.
  // However, enums tend to be unnecessarily large on 8-bit cores.
  typedef uint8_t ClockRate_t;

// Bits are SPI2X, SPR1, SPR0
  static const ClockRate_t   FOSC_DIV_2 = 0b100;
  static const ClockRate_t   FOSC_DIV_4 = 0b000;
  static const ClockRate_t   FOSC_DIV_8 = 0b101;
  static const ClockRate_t  FOSC_DIV_16 = 0b001;
  static const ClockRate_t  FOSC_DIV_32 = 0b110;
  // There are two possible implementations of DIV64.
  static const ClockRate_t  FOSC_DIV_64 = 0b010;
  static const ClockRate_t FOSC_DIV_128 = 0b011;

  // Default clock rate
  static const ClockRate_t DefaultClockrate = FOSC_DIV_8;

//  void set_clockRate(ClockRate_t new_clockRate);
//  void init(ClockRate_t initial_clockRate = DefaultClockrate);

static inline void set_clockRate(const ClockRate_t new_clockRate){
  // SPI2X (double clock)
  if(new_clockRate & 0b100) sbi(SPSR, SPI2X);
  else cbi(SPSR, SPI2X);

  // SPR1
  if(new_clockRate & 0b010) sbi(SPCR, SPR1);
  else cbi(SPCR, SPR1);

  // SPR0
  if(new_clockRate & 0b001) sbi(SPCR, SPR0);
  else cbi(SPCR, SPR0);
}

static inline void init(const ClockRate_t initial_clockRate = DefaultClockrate, bool enable_SS = true){
// Set pin directions.
  sbi(SPI_DIRECTION_BUS, SCK_PIN);
  sbi(SPI_DIRECTION_BUS, MOSI_PIN);
// MISO is not always utilized, but set to input anyway.
  cbi(SPI_DIRECTION_BUS, MISO_PIN);
// SS is usually set as output. If not, many AVR SPI buses will behave differently.
  sbi(SPI_DIRECTION_BUS, SS_PIN);

  SPCR = 0;
  SPSR = 0;

  // Master mode
  sbi(SPCR, MSTR);

  // Disable interrupt
  //cbi(SPCR, SPIE);

  // MSb transmitted first
  //cbi(SPCR, DORD);
  // Polarity: Leading rising, trailing falling
  //cbi(SPCR, CPOL);
  // Phase: Leading sample, trailing setup
  //cbi(SPCR, CPHA);

// Set clockrate
  set_clockRate(initial_clockRate);

  // Enable SPI bus.
  sbi(SPCR, SPE);
}

// Wait for an SPI transmission to complete.
static inline void wait_for_SPI_complete(){
  DEBUGprint("wfSc1;");
  while((SPSR & (1<<SPIF))==0);
  DEBUGprint("wfSc2;");
}

// Send and receive one byte.
static inline uint8_t transceive(const uint8_t data){
  SPDR = data;
  wait_for_SPI_complete();
  return SPDR;
}
// Send and receive a buffer of bytes.
static inline void transceive(const uint8_t* outBuf, uint8_t* inBuf, uint8_t len){
  for(; len > 0; len--){
    *inBuf = transceive(*outBuf);
    inBuf++;
    outBuf++;
  }
}

// Transmit a byte.
static inline void transmit(const uint8_t data){
  transceive(data);
}
// Transmit a buffer of bytes.
static inline void transmit(const uint8_t* outBuf, uint8_t len){
  // Still need to be reading SPDR to reset SPIF flag.
  for(; len > 0; len--){
    transceive(*outBuf);
    outBuf++;
  }
}

// Receive a byte, transmitting a dummy byte.
static inline uint8_t receive(){
  return transceive(DUMMY_BYTE);
}
// Receive a buffer of bytes, transmitting dummy bytes.
static inline void receive(uint8_t* inBuf, uint8_t len){
  for(; len > 0; len--){
  // Send a dummy byte
    *inBuf = transceive(DUMMY_BYTE);
    inBuf++;
  }
}

// End namespace: SPI
};

