#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
; #Warn  ; Enable warnings to assist with detecting common errors.

#include Midi.ahk

midi := new Midi()
midi.OpenMidiIn( 5 )

Return

MidiNoteOn60:
	note60(60, 100)
	Return

MidiNoteOff60:
	note60(60, 0)
	Return

MidiNoteOn61:
	playPause(61, 100)
	Return

MidiNoteOff61:
	playPause(61, 0)
	Return

MidiNoteOn62:
	note62(62, 100)
	Return

MidiNoteOff62:
	note62(62, 0)
	Return

MidiControlChange7:
	cc := midi.MidiIn()
	ccValue := cc.value
	master_volume(7, ccValue)
	Return

;-------------------------Midi "hotkey" functions--------------------- 

playPause(note, vel) 
{ 
   if (vel)
   Send, {Media_Play_Pause down}
   else
   Send, {Media_Play_Pause up}
   return
} 
note60(note, vel) 
{ 
   if (vel)
   Send {Media_Next down}
   else
   Send {Media_Next up}
} 
note62(note, vel) 
{ 
   if (vel)
   Send {Media_Prev down}
   else
   Send {Media_Prev up}
} 

master_volume(ccnumber, ccvel)
{
   if (ccvel) 
    SoundSet, ccvel/1.27
}

media_volume(ccnumber, ccvel)
{
 if (ccvel)
   SoundSet, ccvel/1.27, Microphone
}

do_cc_1(ccnumber, ccvel)
{
 if (ccvel)
   SoundSet, ccvel/1.27
}

;-------------------------  Midi input library  ---------------------- 
#include midi_in_lib.ahk