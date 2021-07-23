# Prüfung: „Einführung in die Softwareentwicklung“
## Instruktionen zum Bauen des Projektes


# Spezifikationen und wie man das Programm ausführt
- Geschrieben mit XCODE / Clang (AppleClang 12.0.5.12050022) / Qt5.12.11
- Prozessor Apple M1 Arm64 -> QT mit Rosetta, Rest nativ

#Wie bekomme ich das Projekt zum laufen:
cmake CMakeLists.txt -B "Hier das Verzeichnes wo es hin soll" -DCMAKE_OSX_ARCHITECTURES=x86_64
--> -DCMAKE_OSX_ARCHITECTURES=x86_64 kann im Normalfall weggelassen werden, ich habe es aber gebraucht, da ich einen Apple M1 ARM64 Prozessor nutze

make (im besagten verzeichnis ausführen)

Jetzt muss der Inhalt vom copyme ordner auch ins selbe verzeichnis

Das Programm kann gestartet werden, aber bei mir war dies nur über das terminal möglich, da ansonsten die maps aus dem Copyme-Ordner nicht funktioniert haben


## Notizen an die Korrigierenden

# Steuerung 
#Menü
- Tasten zum Wählen des Levels: 1 - 3
- Taste zum verlassen des Spiel: e

#Normal
- Steuerung des Characters: Pfeiltasten
- Monster wechseln: Zahlen für einstprechendes Monster

#Kampf
- Monster wechseln: p
- Dialog weiter: a
- Angriff: 1
- Heilen: 2
- Flucht: 3

#Monsterfangen
- Fangen: 1
- Flucht: 2

#End Screen
- zurück zum Menü: a

# Unicodes 
(Aus der Musterlösung)

- Protagonist*in: QString::fromUtf8("\xF0\x9F\x98\x83")
- Wald/Wildes-Monsterfeld: QString::fromUtf8("\xF0\x9F\x8C\xB2")
- Gegener*in: QString::fromUtf8("\xF0\x9F\x98\x92")
- MonsterCenter/Heilen: QString::fromUtf8("\xF0\x9F\xA4\x8E")
- MonsterGym/Muskelsymbol: QString::fromUtf8("\xF0\x9F\x92\xAA")
- Wand: QString("\u2591")
- Ausgang: QString("\u27A5")

- Bonus(von mir selbst): QString("\u2B50")


# Zusatzinformationen


-Zum Zeitpunkt der Abgabe läuft das Programm fehlerfrei auf dem oben beschriebenen System

-In meinem Spiel greifen sich die Monster immer gegenseitig an, dass hat zur Folge das auch wenn man das gegnerische Monster
getötet hat man trd. noch den Schaden bekommt und man verlieren kann obwohl das gegnerische Monster tot ist.
Dies ist von meiner Seite aus gewollt, da ich es so für sinnvoller halte.
Um zu zeigen dass ich dies absichtlich gemacht habe beschreibe ich kurz wie ich dies so ändere dass die Monster nach einander
angreifen. Hier für müsste ich einfach zuerst dem Gegner den Schaden hinzufügen und nur wenn dieser nicht auf 0 gefallen ist auch
dem Monster des Spielers den Schaden hinzufügen. Dies müsste man in der attack-Methode in dem game-Objekt ändern

# Extras 
- Es können 5 verschiede monster auftauchen
- Man kann sein Monster im Kampf tranieren, dann werden 5 LP von der Maximalen LPs abgezogen und man bekommt 2 Ap mehr
--> Begründung: 
Man traniert sein Monster während dem Kampf und dadurch wird es stärker,
aber da es sehr abgelenkt wird bekommt es einen bleibend schaden

-Scoresystem:
 
 - Jedes Monster das stirbt: -5 Punkte
 - Jedes Monster welches aufgesammelt wird: +5 Punkte
 - Das Ziel erreichen: +50 Punkte
 - Bonus Punkte: +20 Punkte -> ich habe einen neuen Block eingeführt welcher auf der advancedmap 3x vorhanden ist
 - Einen Kampf gewinnen: +20 Punkte
 - Sterben: -50 Punkte:

-Menü:

- Man kann am Anfang eingeben welches Level man spielen will
- Man kann das Spiel im Menue beenden;
- Man kann wenn man auf dem end-screen ist (win oder lose) wieder zurück ins Menü und ein neues level Spielen
- Ich habe ein neues Level eingeführt in welchem sich alle Funktionen leich und schnell testen lassen
- Es würde sich leicht beliebig viele Maps einbauen lassen

## Quellen
- https://luna.informatik.uni-mainz.de/eis21/lehreinheiten.md -> ich habe die Aufgabenstellung der Übungsblätter überflogen um auf ideen zu kommen
- https://im-coder.com/zeile-fuer-zeile-lesen-in-c-und-c.html -> damit ich eine ganze zeile lesen kann
- https://unicode-table.com/de/search/?q=stern -> unicode code für den bonus stern
- https://www.cplusplus.com/reference/chrono/ -> Ich habe nachgeschaut wie ich die zeit richtig einbinden kann (Dokumentation)
- https://stackoverflow.com/questions/39288595/why-not-just-use-random-device -> Warum man nicht nur random_device benutzen soll
- https://docs.microsoft.com/de-de/cpp/cpp/program-termination?view=msvc-160 -> wie kann ich ein Programm beenden
