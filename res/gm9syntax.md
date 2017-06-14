#godmode 9 syntax
with the newest release of godmode 9 you can write scripts and execute them
the syntax is quite simple

#this is a comment
say "this is a sentence"
ask "this is a question?"
set MSGOK "this message will appear with a successful command"
set MSGFAIL "this message will appear when something goes wrong"
mkdir 0:/testdir #this will create the directory "testdir" on the sd card
reboot #self explanatory
poweroff #self explanatory
mount S:/ctrnand_full.bin #mount image
unmount #unmount mounted image
set VARIABLE #if you set a variable that does not exist it will create itself

________________________________

if a command is unknown it will abort and head back to the gm9 menu
