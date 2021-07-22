###################
# Spezifikationen #
###################
- Geschrieben mit XCODE/Clang/Qt5.12.11
- Prozessor Apple M1 Arm64 -> mit Rosetta

#############
# Steuerung #
#############
Steuerung des Characters: Pfeiltasten
Monster wechseln: Zahlen für einstprechendes Monster

Monster wechseln im Kapf: p
Dialog weiter: a

############
# Unicodes #
############
(Aus der Musterlösung)
Protagonist*in: QString::fromUtf8("\xF0\x9F\x98\x83")
Wald/Wildes-Monsterfeld: QString::fromUtf8("\xF0\x9F\x8C\xB2")
Gegener*in: QString::fromUtf8("\xF0\x9F\x98\x92")
MonsterCenter/Heilen: QString::fromUtf8("\xF0\x9F\xA4\x8E")
MonsterGym/Muskelsymbol: QString::fromUtf8("\xF0\x9F\x92\xAA")
Wand: QString("\u2591")
Ausgang: QString("\u27A5")

###########
# Quellen #
###########
- https://luna.informatik.uni-mainz.de/eis21/aufgaben/blatt10/threads-anlage.md
- http://www.cplusplus.com/forum/general/3082/
- https://im-coder.com/zeile-fuer-zeile-lesen-in-c-und-c.html

##########
# Extras #
##########
-Es können 5 verschiede monster auftauchen
-Man kann sein Monster im Kampf tranieren, dann werden 5 LP von der Maximalen LPs abgezogen und man bekommt 2 Ap mehr
--> Begründung: Man traniert sein Monster während dem Kampf und dadurch wird es stärker,
                aber da es sehr abgelenkt wird bekommt es einen bleibend schaden
