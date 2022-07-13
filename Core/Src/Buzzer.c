#include "Buzzer.h"

TIM_HandleTypeDef *BUZZER_htim; 
uint32_t BUZZER_TIM_CHANNEL;

void BUZZER_SetTIM(TIM_HandleTypeDef *htim, uint32_t TIM_CHANNEL)
{
	BUZZER_htim = htim;
	BUZZER_TIM_CHANNEL = TIM_CHANNEL;
}

void BUZZER_Play_Doom(void)
{
	// change this to make the song slower or faster
	int tempo = 225;

	// notes of the moledy followed by the duration.
	// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
	// !!negative numbers are used to represent dotted notes,
	// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
	// This code uses PROGMEM to fit the melody to flash as it was to long to fit
	// in SRAM. It may not work on other Arduino arquitectures other than AVR
	const int melody[] = 
	{

		// At Doom's Gate (E1M1)
		// Score available at https://musescore.com/pieridot/doom

		NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8, //1
		NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_B2, 8, NOTE_C3, 8,
		NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8,
		NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, -2,

		NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8, //5
		NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_B2, 8, NOTE_C3, 8,
		NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8,
		NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, -2,

		NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8, //9
		NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_B2, 8, NOTE_C3, 8,
		NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8,
		NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, -2,

		NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8, //13
		NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_B2, 8, NOTE_C3, 8,
		NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8,
		NOTE_FS3, -16, NOTE_D3, -16, NOTE_B2, -16, NOTE_A3, -16, NOTE_FS3, -16, NOTE_B2, -16, NOTE_D3, -16, NOTE_FS3, -16, NOTE_A3, -16, NOTE_FS3, -16, NOTE_D3, -16, NOTE_B2, -16,

		NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8, //17
		NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_B2, 8, NOTE_C3, 8,
		NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8,
		NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, -2,

		NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8, //21
		NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_B2, 8, NOTE_C3, 8,
		NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8,
		NOTE_B3, -16, NOTE_G3, -16, NOTE_E3, -16, NOTE_G3, -16, NOTE_B3, -16, NOTE_E4, -16, NOTE_G3, -16, NOTE_B3, -16, NOTE_E4, -16, NOTE_B3, -16, NOTE_G4, -16, NOTE_B4, -16,

		NOTE_A2, 8, NOTE_A2, 8, NOTE_A3, 8, NOTE_A2, 8, NOTE_A2, 8, NOTE_G3, 8, NOTE_A2, 8, NOTE_A2, 8, //25
		NOTE_F3, 8, NOTE_A2, 8, NOTE_A2, 8, NOTE_DS3, 8, NOTE_A2, 8, NOTE_A2, 8, NOTE_E3, 8, NOTE_F3, 8,
		NOTE_A2, 8, NOTE_A2, 8, NOTE_A3, 8, NOTE_A2, 8, NOTE_A2, 8, NOTE_G3, 8, NOTE_A2, 8, NOTE_A2, 8,
		NOTE_F3, 8, NOTE_A2, 8, NOTE_A2, 8, NOTE_DS3, -2,

		NOTE_A2, 8, NOTE_A2, 8, NOTE_A3, 8, NOTE_A2, 8, NOTE_A2, 8, NOTE_G3, 8, NOTE_A2, 8, NOTE_A2, 8, //29
		NOTE_F3, 8, NOTE_A2, 8, NOTE_A2, 8, NOTE_DS3, 8, NOTE_A2, 8, NOTE_A2, 8, NOTE_E3, 8, NOTE_F3, 8,
		NOTE_A2, 8, NOTE_A2, 8, NOTE_A3, 8, NOTE_A2, 8, NOTE_A2, 8, NOTE_G3, 8, NOTE_A2, 8, NOTE_A2, 8,
		NOTE_A3, -16, NOTE_F3, -16, NOTE_D3, -16, NOTE_A3, -16, NOTE_F3, -16, NOTE_D3, -16, NOTE_C4, -16, NOTE_A3, -16, NOTE_F3, -16, NOTE_A3, -16, NOTE_F3, -16, NOTE_D3, -16,

		NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8, //33
		NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_B2, 8, NOTE_C3, 8,
		NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8,
		NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, -2,

		NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8, //37
		NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_B2, 8, NOTE_C3, 8,
		NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8,
		NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, -2,

		NOTE_CS3, 8, NOTE_CS3, 8, NOTE_CS4, 8, NOTE_CS3, 8, NOTE_CS3, 8, NOTE_B3, 8, NOTE_CS3, 8, NOTE_CS3, 8, //41
		NOTE_A3, 8, NOTE_CS3, 8, NOTE_CS3, 8, NOTE_G3, 8, NOTE_CS3, 8, NOTE_CS3, 8, NOTE_GS3, 8, NOTE_A3, 8,
		NOTE_B2, 8, NOTE_B2, 8, NOTE_B3, 8, NOTE_B2, 8, NOTE_B2, 8, NOTE_A3, 8, NOTE_B2, 8, NOTE_B2, 8,
		NOTE_G3, 8, NOTE_B2, 8, NOTE_B2, 8, NOTE_F3, -2,

		NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8, //45
		NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_B2, 8, NOTE_C3, 8,
		NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8,
		NOTE_B3, -16, NOTE_G3, -16, NOTE_E3, -16, NOTE_G3, -16, NOTE_B3, -16, NOTE_E4, -16, NOTE_G3, -16, NOTE_B3, -16, NOTE_E4, -16, NOTE_B3, -16, NOTE_G4, -16, NOTE_B4, -16,

		NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8, //49
		NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_B2, 8, NOTE_C3, 8,
		NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8,
		NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, -2,

		NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8, //53
		NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_B2, 8, NOTE_C3, 8,
		NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8,
		NOTE_FS3, -16, NOTE_DS3, -16, NOTE_B2, -16, NOTE_FS3, -16, NOTE_DS3, -16, NOTE_B2, -16, NOTE_G3, -16, NOTE_D3, -16, NOTE_B2, -16, NOTE_DS4, -16, NOTE_DS3, -16, NOTE_B2, -16,

	// -/-

		NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8, //57
		NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_B2, 8, NOTE_C3, 8,
		NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8,
		NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, -2,

		NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8, //61
		NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_B2, 8, NOTE_C3, 8,
		NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8,
		NOTE_E4, -16, NOTE_B3, -16, NOTE_G3, -16, NOTE_G4, -16, NOTE_E4, -16, NOTE_G3, -16, NOTE_B3, -16, NOTE_D4, -16, NOTE_E4, -16, NOTE_G4, -16, NOTE_E4, -16, NOTE_G3, -16,  

		NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8, //65
		NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_B2, 8, NOTE_C3, 8,
		NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8,
		NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, -2,

		NOTE_A2, 8, NOTE_A2, 8, NOTE_A3, 8, NOTE_A2, 8, NOTE_A2, 8, NOTE_G3, 8, NOTE_A2, 8, NOTE_A2, 8, //69
		NOTE_F3, 8, NOTE_A2, 8, NOTE_A2, 8, NOTE_DS3, 8, NOTE_A2, 8, NOTE_A2, 8, NOTE_E3, 8, NOTE_F3, 8,
		NOTE_A2, 8, NOTE_A2, 8, NOTE_A3, 8, NOTE_A2, 8, NOTE_A2, 8, NOTE_G3, 8, NOTE_A2, 8, NOTE_A2, 8,
		NOTE_A3, -16, NOTE_F3, -16, NOTE_D3, -16, NOTE_A3, -16, NOTE_F3, -16, NOTE_D3, -16, NOTE_C4, -16, NOTE_A3, -16, NOTE_F3, -16, NOTE_A3, -16, NOTE_F3, -16, NOTE_D3, -16,

		NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8, //73
		NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_B2, 8, NOTE_C3, 8,
		NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8,
		NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, -2,

		NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8, //77
		NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_B2, 8, NOTE_C3, 8,
		NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8,
		NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, -2,

		NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8, //81
		NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_B2, 8, NOTE_C3, 8,
		NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8,
		NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, -2,

		NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8, //73
		NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_B2, 8, NOTE_C3, 8,
		NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8,
		NOTE_B3, -16, NOTE_G3, -16, NOTE_E3, -16, NOTE_B2, -16, NOTE_E3, -16, NOTE_G3, -16, NOTE_C4, -16, NOTE_B3, -16, NOTE_G3, -16, NOTE_B3, -16, NOTE_G3, -16, NOTE_E3, -16,  
	};

	// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
	// there are two values per note (pitch and duration), so for each note there are four bytes
	int notes = sizeof(melody) / sizeof(melody[0]) / 2;

	// this calculates the duration of a whole note in ms
	int wholenote = (60000 * 4) / tempo;

	int divider = 0, noteDuration = 0;

  // iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) 
	{
    // calculates the duration of each note
    divider = pgm_read_word_near(melody+thisNote + 1);
   
		if (divider > 0) 
		{
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } 
		else if (divider < 0) 
		{
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    Tone(pgm_read_word_near(melody+thisNote) , noteDuration * 0.9 );

    // Wait for the specief duration before playing the next note.
    HAL_Delay(noteDuration);

    // stop the waveform generation before the next note.
    NoTone();
  }
}

void BUZZER_Play_HarryPotter(void)
{
	// change this to make the song slower or faster
	int tempo = 144;

	// notes of the moledy followed by the duration.
	// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
	// !!negative numbers are used to represent dotted notes,
	// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
	int melody[] = 
	{

		// Hedwig's theme fromn the Harry Potter Movies
		// Socre from https://musescore.com/user/3811306/scores/4906610
		
		REST, 2, NOTE_D4, 4,
		NOTE_G4, -4, NOTE_AS4, 8, NOTE_A4, 4,
		NOTE_G4, 2, NOTE_D5, 4,
		NOTE_C5, -2, 
		NOTE_A4, -2,
		NOTE_G4, -4, NOTE_AS4, 8, NOTE_A4, 4,
		NOTE_F4, 2, NOTE_GS4, 4,
		NOTE_D4, -1, 
		NOTE_D4, 4,

		NOTE_G4, -4, NOTE_AS4, 8, NOTE_A4, 4, //10
		NOTE_G4, 2, NOTE_D5, 4,
		NOTE_F5, 2, NOTE_E5, 4,
		NOTE_DS5, 2, NOTE_B4, 4,
		NOTE_DS5, -4, NOTE_D5, 8, NOTE_CS5, 4,
		NOTE_CS4, 2, NOTE_B4, 4,
		NOTE_G4, -1,
		NOTE_AS4, 4,
			 
		NOTE_D5, 2, NOTE_AS4, 4,//18
		NOTE_D5, 2, NOTE_AS4, 4,
		NOTE_DS5, 2, NOTE_D5, 4,
		NOTE_CS5, 2, NOTE_A4, 4,
		NOTE_AS4, -4, NOTE_D5, 8, NOTE_CS5, 4,
		NOTE_CS4, 2, NOTE_D4, 4,
		NOTE_D5, -1, 
		REST,4, NOTE_AS4,4,  

		NOTE_D5, 2, NOTE_AS4, 4,//26
		NOTE_D5, 2, NOTE_AS4, 4,
		NOTE_F5, 2, NOTE_E5, 4,
		NOTE_DS5, 2, NOTE_B4, 4,
		NOTE_DS5, -4, NOTE_D5, 8, NOTE_CS5, 4,
		NOTE_CS4, 2, NOTE_AS4, 4,
		NOTE_G4, -1, 
		
	};

	// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
	// there are two values per note (pitch and duration), so for each note there are four bytes
	int notes = sizeof(melody) / sizeof(melody[0]) / 2;

	// this calculates the duration of a whole note in ms (60s/tempo)*4 beats
	int wholenote = (60000 * 4) / tempo;

	int divider = 0, noteDuration = 0;

	// iterate over the notes of the melody. 
	// Remember, the array is twice the number of notes (notes + durations)
	for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) 
	{
		// calculates the duration of each note
		divider = melody[thisNote + 1];
		if (divider > 0) {
			// regular note, just proceed
			noteDuration = (wholenote) / divider;
		} else if (divider < 0) {
			// dotted notes are represented with negative durations!!
			noteDuration = (wholenote) / abs(divider);
			noteDuration *= 1.5; // increases the duration in half for dotted notes
		}

		// we only play the note for 90% of the duration, leaving 10% as a pause
		Tone(melody[thisNote], noteDuration*0.9);

		// Wait for the specief duration before playing the next note.
		HAL_Delay(noteDuration);
		
		// stop the waveform generation before the next note.
		NoTone();
	}
}

void BUZZER_Play_Supermario(void)
{
	// change this to make the song slower or faster
	int tempo = 500;

	// notes of the moledy followed by the duration.
	// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
	// !!negative numbers are used to represent dotted notes,
	// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
	int melody[] = {

		// Super Mario Bros theme
		// Score available at https://musescore.com/user/2123/scores/2145
		// Theme by Koji Kondo
		
		
		NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,8, //1
		NOTE_G5,4, REST,4, NOTE_G4,8, REST,4, 
		NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // 3
		NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
		NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
		REST,8, NOTE_E5,4,NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,
		NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // repeats from 3
		NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
		NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
		REST,8, NOTE_E5,4,NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,

		
		REST,4, NOTE_G5,8, NOTE_FS5,8, NOTE_F5,8, NOTE_DS5,4, NOTE_E5,8,//7
		REST,8, NOTE_GS4,8, NOTE_A4,8, NOTE_C4,8, REST,8, NOTE_A4,8, NOTE_C5,8, NOTE_D5,8,
		REST,4, NOTE_DS5,4, REST,8, NOTE_D5,-4,
		NOTE_C5,2, REST,2,

		REST,4, NOTE_G5,8, NOTE_FS5,8, NOTE_F5,8, NOTE_DS5,4, NOTE_E5,8,//repeats from 7
		REST,8, NOTE_GS4,8, NOTE_A4,8, NOTE_C4,8, REST,8, NOTE_A4,8, NOTE_C5,8, NOTE_D5,8,
		REST,4, NOTE_DS5,4, REST,8, NOTE_D5,-4,
		NOTE_C5,2, REST,2,

		NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4,//11
		NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,

		NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,8, NOTE_E5,8,//13
		REST,1, 
		NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4,
		NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,
		NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,4,
		NOTE_G5,4, REST,4, NOTE_G4,4, REST,4, 
		NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // 19
		
		NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
		NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
		REST,8, NOTE_E5,4, NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,

		NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // repeats from 19
		NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
		NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
		REST,8, NOTE_E5,4, NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,

		NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,//23
		NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
		NOTE_D5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_G5,-8, NOTE_F5,-8,
		
		NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2, //26
		NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
		NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
		NOTE_B4,8, NOTE_F5,4, NOTE_F5,8, NOTE_F5,-8, NOTE_E5,-8, NOTE_D5,-8,
		NOTE_C5,8, NOTE_E4,4, NOTE_E4,8, NOTE_C4,2,

		NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,//repeats from 23
		NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
		NOTE_D5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_G5,-8, NOTE_F5,-8,
		
		NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2, //26
		NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
		NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
		NOTE_B4,8, NOTE_F5,4, NOTE_F5,8, NOTE_F5,-8, NOTE_E5,-8, NOTE_D5,-8,
		NOTE_C5,8, NOTE_E4,4, NOTE_E4,8, NOTE_C4,2,
		NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,8, NOTE_E5,8,
		REST,1,

		NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4, //33
		NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,
		NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,4,
		NOTE_G5,4, REST,4, NOTE_G4,4, REST,4, 
		NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
		NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
		NOTE_D5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_G5,-8, NOTE_F5,-8,
		
		NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2, //40
		NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
		NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
		NOTE_B4,8, NOTE_F5,4, NOTE_F5,8, NOTE_F5,-8, NOTE_E5,-8, NOTE_D5,-8,
		NOTE_C5,8, NOTE_E4,4, NOTE_E4,8, NOTE_C4,2,
		
		//game over sound
		NOTE_C5,-4, NOTE_G4,-4, NOTE_E4,4, //45
		NOTE_A4,-8, NOTE_B4,-8, NOTE_A4,-8, NOTE_GS4,-8, NOTE_AS4,-8, NOTE_GS4,-8,
		NOTE_G4,8, NOTE_D4,8, NOTE_E4,-2,  

	};

	// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
	// there are two values per note (pitch and duration), so for each note there are four bytes
	int notes = sizeof(melody) / sizeof(melody[0]) / 2;

	// this calculates the duration of a whole note in ms
	int wholenote = (60000 * 4) / tempo;

	int divider = 0, noteDuration = 0;

	// iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) 
	{
    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    Tone(melody[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    HAL_Delay(noteDuration);

    // stop the waveform generation before the next note.
    NoTone();
  }
}

void BUZZER_Play_HappyBirthday(void)
{
	// change this to make the song slower or faster
	int tempo = 500;

	// notes of the moledy followed by the duration.
	// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
	// !!negative numbers are used to represent dotted notes,
	// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
	int melody[] = {

		// Happy Birthday
		// Score available at https://musescore.com/user/8221/scores/26906

		NOTE_C4,4, NOTE_C4,8, 
		NOTE_D4,-4, NOTE_C4,-4, NOTE_F4,-4,
		NOTE_E4,-2, NOTE_C4,4, NOTE_C4,8, 
		NOTE_D4,-4, NOTE_C4,-4, NOTE_G4,-4,
		NOTE_F4,-2, NOTE_C4,4, NOTE_C4,8,

		NOTE_C5,-4, NOTE_A4,-4, NOTE_F4,-4, 
		NOTE_E4,-4, NOTE_D4,-4, NOTE_AS4,4, NOTE_AS4,8,
		NOTE_A4,-4, NOTE_F4,-4, NOTE_G4,-4,
		NOTE_F4,-2,
	 
	};

	// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
	// there are two values per note (pitch and duration), so for each note there are four bytes
	int notes = sizeof(melody) / sizeof(melody[0]) / 2;

	// this calculates the duration of a whole note in ms
	int wholenote = (60000 * 4) / tempo;

	int divider = 0, noteDuration = 0;

	// iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) 
	{
    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    Tone(melody[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    HAL_Delay(noteDuration);

    // stop the waveform generation before the next note.
    NoTone();
  }
}

void BUZZER_Play_GameOfThrones(void)
{
	// change this to make the song slower or faster
	int tempo = 200;

	// notes of the moledy followed by the duration.
	// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
	// !!negative numbers are used to represent dotted notes,
	// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
	int melody[] = {

		// Game of Thrones
		// Score available at https://musescore.com/user/8407786/scores/2156716

		NOTE_G4,8, NOTE_C4,8, NOTE_DS4,16, NOTE_F4,16, NOTE_G4,8, NOTE_C4,8, NOTE_DS4,16, NOTE_F4,16, //1
		NOTE_G4,8, NOTE_C4,8, NOTE_DS4,16, NOTE_F4,16, NOTE_G4,8, NOTE_C4,8, NOTE_DS4,16, NOTE_F4,16,
		NOTE_G4,8, NOTE_C4,8, NOTE_E4,16, NOTE_F4,16, NOTE_G4,8, NOTE_C4,8, NOTE_E4,16, NOTE_F4,16,
		NOTE_G4,8, NOTE_C4,8, NOTE_E4,16, NOTE_F4,16, NOTE_G4,8, NOTE_C4,8, NOTE_E4,16, NOTE_F4,16,
		NOTE_G4,-4, NOTE_C4,-4,//5

		NOTE_DS4,16, NOTE_F4,16, NOTE_G4,4, NOTE_C4,4, NOTE_DS4,16, NOTE_F4,16, //6
		NOTE_D4,-1, //7 and 8
		NOTE_F4,-4, NOTE_AS3,-4,
		NOTE_DS4,16, NOTE_D4,16, NOTE_F4,4, NOTE_AS3,-4,
		NOTE_DS4,16, NOTE_D4,16, NOTE_C4,-1, //11 and 12

		//repeats from 5
		NOTE_G4,-4, NOTE_C4,-4,//5

		NOTE_DS4,16, NOTE_F4,16, NOTE_G4,4, NOTE_C4,4, NOTE_DS4,16, NOTE_F4,16, //6
		NOTE_D4,-1, //7 and 8
		NOTE_F4,-4, NOTE_AS3,-4,
		NOTE_DS4,16, NOTE_D4,16, NOTE_F4,4, NOTE_AS3,-4,
		NOTE_DS4,16, NOTE_D4,16, NOTE_C4,-1, //11 and 12
		NOTE_G4,-4, NOTE_C4,-4,
		NOTE_DS4,16, NOTE_F4,16, NOTE_G4,4,  NOTE_C4,4, NOTE_DS4,16, NOTE_F4,16,

		NOTE_D4,-2,//15
		NOTE_F4,-4, NOTE_AS3,-4,
		NOTE_D4,-8, NOTE_DS4,-8, NOTE_D4,-8, NOTE_AS3,-8,
		NOTE_C4,-1,
		NOTE_C5,-2,
		NOTE_AS4,-2,
		NOTE_C4,-2,
		NOTE_G4,-2,
		NOTE_DS4,-2,
		NOTE_DS4,-4, NOTE_F4,-4, 
		NOTE_G4,-1,
		
		NOTE_C5,-2,//28
		NOTE_AS4,-2,
		NOTE_C4,-2,
		NOTE_G4,-2, 
		NOTE_DS4,-2,
		NOTE_DS4,-4, NOTE_D4,-4,
		NOTE_C5,8, NOTE_G4,8, NOTE_GS4,16, NOTE_AS4,16, NOTE_C5,8, NOTE_G4,8, NOTE_GS4,16, NOTE_AS4,16,
		NOTE_C5,8, NOTE_G4,8, NOTE_GS4,16, NOTE_AS4,16, NOTE_C5,8, NOTE_G4,8, NOTE_GS4,16, NOTE_AS4,16,
		
		REST,4, NOTE_GS5,16, NOTE_AS5,16, NOTE_C6,8, NOTE_G5,8, NOTE_GS5,16, NOTE_AS5,16,
		NOTE_C6,8, NOTE_G5,16, NOTE_GS5,16, NOTE_AS5,16, NOTE_C6,8, NOTE_G5,8, NOTE_GS5,16, NOTE_AS5,16,  
	};

	// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
	// there are two values per note (pitch and duration), so for each note there are four bytes
	int notes = sizeof(melody) / sizeof(melody[0]) / 2;

	// this calculates the duration of a whole note in ms
	int wholenote = (60000 * 4) / tempo;

	int divider = 0, noteDuration = 0;

	// iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) 
	{
    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    Tone(melody[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    HAL_Delay(noteDuration);

    // stop the waveform generation before the next note.
    NoTone();
  }
}

void Tone(uint32_t pwmFreq, uint32_t duration)
{
	uint8_t coeff = 1;
	if(HAL_RCC_GetHCLKFreq() != HAL_RCC_GetPCLK1Freq())    // APB1 Prescaler is not equal to 1 thus * 2
		coeff = 2;
	
	// Set frequency
	uint32_t timerFreq = coeff * HAL_RCC_GetPCLK1Freq();
	BUZZER_htim->Instance->PSC = ( (double)timerFreq / (double)pwmFreq )/1000 - 1;
	BUZZER_htim->Instance->ARR = 1000 - 1;
	
	// Set CCR
	__HAL_TIM_SetCompare(BUZZER_htim, BUZZER_TIM_CHANNEL, 499);

	// Tone
	HAL_TIM_PWM_Start(BUZZER_htim,BUZZER_TIM_CHANNEL);
	
	// Wait
	HAL_Delay(duration);
}

void NoTone(void)
{
	HAL_TIM_PWM_Stop(BUZZER_htim,BUZZER_TIM_CHANNEL);
}

void BUZZER_Stop(void)
{
	HAL_TIM_PWM_Stop(BUZZER_htim,BUZZER_TIM_CHANNEL);
}
