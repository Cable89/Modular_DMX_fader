#include Midi.ahk

midi := new Midi()
midi.OpenMidiIn( 5 )

Return

MidiNoteOn60:
	MsgBox You played note 60!
	Return

MidiNoteOn61:
	MsgBox You played note 61!
	Return

MidiNoteOn62:
	MsgBox You played note 62!
	Return

MidiControlChange7:
	cc := midi.MidiIn()
	ccValue := cc.value
	MsgBox You set the mod wheel to %ccValue%
	Return