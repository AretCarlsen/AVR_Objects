#pragma once

#include <avr/io.h>
#include <avr/pgmspace.h>

#define OutputPin_F_internals(PRT, PIN) \
  static inline void set_output_high(void){ PORT##PRT |= _BV(PIN); } \
  static inline void set_output_low(void){ PORT##PRT &= ~_BV(PIN); } \
  static inline void set_output(const bool new_value){ if(new_value) set_output_high(); else set_output_low(); } \
  static inline bool get_output(void){ return (PORT##PRT & _BV(PIN)); } \
  static inline bool output_is_high(void){ return get_output(); } \
  static inline bool output_is_low(void){ return (!get_output()); } \
  static inline void toggle_output(void){ set_output(! get_output()); }
#define OutputPin_F_named(CLASSNAME, PRT, PIN) class CLASSNAME { public: \
  CLASSNAME(){ DDR##PRT |= _BV(PIN); } \
  OutputPin_F_internals(PRT, PIN) \
}
#define OutputPin_F(PRT, PIN) OutputPin_F_named(OutPin_##PRT##_##PIN, PRT, PIN)

#define InputPin_F_internals(PRT, PIN) \
  static inline bool get_input(void){ return (P##IN##PRT & _BV(PIN)); } \
  static inline bool input_is_high(void){ return get_input(); } \
  static inline bool input_is_low(void){ return (! get_input()); } \
  static inline void enable_pullup(void){ PORT##PRT |= _BV(PIN); } \
  static inline void disable_pullup(void){ PORT##PRT &= ~_BV(PIN); } \
  static inline void set_pullup(const bool new_value){ if(new_value) enable_pullup(); else disable_pullup(); }
#define InputPin_F_named(CLASSNAME, PRT, PIN) class CLASSNAME { public: \
  CLASSNAME(){ DDR##PRT &= ~_BV(PIN); } \
  InputPin_F_internals(PRT, PIN) \
}
#define InputPin_F(PRT, PIN) InputPin_F_named(InPin_##PRT##_##PIN, PRT, PIN)

#define BidirPin_F_named(CLASSNAME, PRT, PIN) class CLASSNAME { public: \
  CLASSNAME(){ set_direction_input(); } \
  OutputPin_F_internals(PRT, PIN) \
  InputPin_F_internals(PRT, PIN) \
  static inline void set_direction_output(void){ DDR##PRT |= _BV(PIN); } \
  static inline void set_direction_input(void){ DDR##PRT &= ~_BV(PIN); } \
  static inline void set_direction_output(const bool new_value){ if(new_value) set_direction_output(); else set_direction_input(); } \
  static inline bool get_direction(void){ return (DDR##PRT & _BV(PIN)); } \
  static inline bool is_output(void){ return get_direction(); } \
  static inline bool is_input(void){ return (! get_direction()); } \
}
#define BidirPin_F(PRT, PIN) BidirPin_F_named(BidirPin_##PRT##_##PIN, PRT, PIN)

#define AVRPin_F(PRT, PIN) OutputPin_F(PRT, PIN); InputPin_F(PRT, PIN); BidirPin_F(PRT, PIN);

/* PORT A */
#ifdef PA0
AVRPin_F(A, 0);
#endif
#ifdef PA1
AVRPin_F(A, 1);
#endif
#ifdef PA2
AVRPin_F(A, 2);
#endif
#ifdef PA3
AVRPin_F(A, 3);
#endif
#ifdef PA4
AVRPin_F(A, 4);
#endif
#ifdef PA5
AVRPin_F(A, 5);
#endif
#ifdef PA6
AVRPin_F(A, 6);
#endif
#ifdef PA7
AVRPin_F(A, 7);
#endif

/* PORT B */
#ifdef PB0
AVRPin_F(B, 0);
#endif
#ifdef PB1
AVRPin_F(B, 1);
#endif
#ifdef PB2
AVRPin_F(B, 2);
#endif
#ifdef PB3
AVRPin_F(B, 3);
#endif
#ifdef PB4
AVRPin_F(B, 4);
#endif
#ifdef PB5
AVRPin_F(B, 5);
#endif
#ifdef PB6
AVRPin_F(B, 6);
#endif
#ifdef PB7
AVRPin_F(B, 7);
#endif

/* PORT C */
#ifdef PC0
AVRPin_F(C, 0);
#endif
#ifdef PC1
AVRPin_F(C, 1);
#endif
#ifdef PC2
AVRPin_F(C, 2);
#endif
#ifdef PC3
AVRPin_F(C, 3);
#endif
#ifdef PC4
AVRPin_F(C, 4);
#endif
#ifdef PC5
AVRPin_F(C, 5);
#endif
#ifdef PC6
AVRPin_F(C, 6);
#endif
#ifdef PC7
AVRPin_F(C, 7);
#endif

/* PORT D */
#ifdef PD0
AVRPin_F(D, 0);
#endif
#ifdef PD1
AVRPin_F(D, 1);
#endif
#ifdef PD2
AVRPin_F(D, 2);
#endif
#ifdef PD3
AVRPin_F(D, 3);
#endif
#ifdef PD4
AVRPin_F(D, 4);
#endif
#ifdef PD5
AVRPin_F(D, 5);
#endif
#ifdef PD6
AVRPin_F(D, 6);
#endif
#ifdef PD7
AVRPin_F(D, 7);
#endif

/* PORT E */
#ifdef PE0
AVRPin_F(E, 0);
#endif
#ifdef PE1
AVRPin_F(E, 1);
#endif
#ifdef PE2
AVRPin_F(E, 2);
#endif
#ifdef PE3
AVRPin_F(E, 3);
#endif
#ifdef PE4
AVRPin_F(E, 4);
#endif
#ifdef PE5
AVRPin_F(E, 5);
#endif
#ifdef PE6
AVRPin_F(E, 6);
#endif
#ifdef PE7
AVRPin_F(E, 7);
#endif

/* PORT F */
#ifdef PF0
AVRPin_F(F, 0);
#endif
#ifdef PF1
AVRPin_F(F, 1);
#endif
#ifdef PF2
AVRPin_F(F, 2);
#endif
#ifdef PF3
AVRPin_F(F, 3);
#endif
#ifdef PF4
AVRPin_F(F, 4);
#endif
#ifdef PF5
AVRPin_F(F, 5);
#endif
#ifdef PF6
AVRPin_F(F, 6);
#endif
#ifdef PF7
AVRPin_F(F, 7);
#endif

/* PORT G */
#ifdef PG0
AVRPin_F(G, 0);
#endif
#ifdef PG1
AVRPin_F(G, 1);
#endif
#ifdef PG2
AVRPin_F(G, 2);
#endif
#ifdef PG3
AVRPin_F(G, 3);
#endif
#ifdef PG4
AVRPin_F(G, 4);
#endif
#ifdef PG5
AVRPin_F(G, 5);
#endif
#ifdef PG6
AVRPin_F(G, 6);
#endif
#ifdef PG7
AVRPin_F(G, 7);
#endif

/* PORT H */
#ifdef PH0
AVRPin_F(H, 0);
#endif
#ifdef PH1
AVRPin_F(H, 1);
#endif
#ifdef PH2
AVRPin_F(H, 2);
#endif
#ifdef PH3
AVRPin_F(H, 3);
#endif
#ifdef PH4
AVRPin_F(H, 4);
#endif
#ifdef PH5
AVRPin_F(H, 5);
#endif
#ifdef PH6
AVRPin_F(H, 6);
#endif
#ifdef PH7
AVRPin_F(H, 7);
#endif
