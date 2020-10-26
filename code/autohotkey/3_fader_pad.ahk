#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
; #Warn  ; Enable warnings to assist with detecting common errors.

SendMode Input 
SetWorkingDir %A_ScriptDir% 

OnExit, sub_exit 
if (midi_in_Open(0)) 
   ExitApp 

;--------------------  Midi "hotkey" mappings  ----------------------- 

listenNote(60, "note60")
listenNote(61, "playPause")
listenNote(62, "note62")

listenCC(7, "do_cc_1", 1)
listenCC(7, "media_volume", 2)
listenCC(7, "master_volume", 3)

return 
;----------------------End of auto execute section-------------------- 

sub_exit: 
   midi_in_Close() 
ExitApp 

;-------------------------Miscellaneous hotkeys----------------------- 
Esc::ExitApp 

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