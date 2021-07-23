# Prüfung: „Einführung in die Softwareentwicklung“
## Instruktionen zum Bauen des Projektes


# Spezifikationen und wie man das Programm ausführt
- Geschrieben mit XCODE / Clang (AppleClang 12.0.5.12050022) / Qt5.12.11
- Prozessor Apple M1 Arm64 -> QT mit Rosetta, Rest nativ

#Wie bekomme ich das Projekt zum laufen:
cmake CMakeLists.txt -B "Hier das Verzeichnes wo es hin soll" -DCMAKE_OSX_ARCHITECTURES=x86_64
--> -DCMAKE_OSX_ARCHITECTURES=x86_64 wird nur beim build auf einer ARM64 Architektur benötigt. Normalerweise kann dieser Befehl weggelassen werden.

make (im besagten Verzeichnis ausführen)

Jetzt muss der Inhalt vom copyme-Ordner auch ins selbe Verzeichnis.

Das Programm kann gestartet werden. Bei mir war dies nur über das Terminal möglich, da ansonsten die Maps aus dem Copyme-Ordner nicht funktioniert haben.


## Notizen an die Korrigierenden

# Steuerung 
#Menü
- Tasten zum Wählen des Levels: 1 - 3
- Taste zum Verlassen des Spiel: e

#Normal
- Steuerung des Characters: Pfeiltasten
- Monster wechseln: Zahlen für ein entsprechendes Monster

#Kampf
- Monster wechseln: p
- Dialog weiter: a
- Angriff: 1
- Heilen: 2
- Flucht: 3
- Special Angriif: s

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


-Zum Zeitpunkt der Abgabe läuft das Programm fehlerfrei auf dem oben beschriebenen System.

-Wenn ein Monster im Spiel besiegt wird, stirbt es und es kann auch nicht Wiederbelebt werden. Dafür wird aber ein neuer Platz
im Monster-Inventar frei und der Spiel kann wieder ein neues Monster fangen.
Um zu beweisen, dass dies eine bewusste Entscheidung war, erkläre ich kurz, wie man dies hätte anders machen können. Anstatt das Monster
aus dem vector zu entfernen, hätte man das Monster dort drinnen lassen können und eine Variable dem Monster hinzufügen können, die
angibt, ob das Monster lebt (bool). So hätte man in der Ausgabe der Monster auch anzeigen können, dass das Monster nicht zu Verfügung steht
und auch den dementsprechenden Knopf deaktivieren können. In der Heil-Methode müsste man alle Monster wieder auf alive setzen.
Ich habe es für sinnvoller gehalten, die Monster in jedem Level neu zu erzeugen, sodass jedes Level ein Neustart ist und dann wäre es nur
unnötig leichter gewesen, dass man diese wiederbeleben kann.

# Extras 
- Es können 5 verschiede Monster auftauchen.

1. Fisch | 1 LP | 1 AP
2. OverPower | 50 LP | 50 AP
3. Tanki | 50 LP | 3 AP
4. SuperStark | 5 LP | 10 AP

--> Derzeit sind alle wahrscheinlichkeiten gleich hoch ... damit das spiel sinn macht müsste es zum beispiel extrem unwarscheinlich sein das Monster
OverPower zu finden. Dies habe ich nicht gemacht damit man alle Monster bekommen kann und sie testen kann.


- Man kann sein Monster im Kampf tranieren. Es werden 5 LP von der Maximalen LPs abgezogen und man bekommt 2 Ap mehr.
--> Begründung: 
Man traniert sein Monster während des Kampfes. Dadurch wird es stärker,
gleichzeitig aber auch abgelenkt, wodurch es einen bleibenden Schaden bekommt.

-Scoresystem:
 
 - Jedes Monster das stirbt: -5 Punkte
 - Jedes Monster welches aufgesammelt wird: +5 Punkte
 - Das Ziel erreichen: +50 Punkte
 - Bonus Punkte: +20 Punkte -> ich habe einen neuen Block eingeführt, welcher auf der advancedmap 3x vorhanden ist.
 - Einen Kampf gewinnen: +20 Punkte
 - Sterben: -50 Punkte:

-Menü:

- Man kann am Anfang eingeben, welches Level man spielen will.
- Man kann das Spiel im Menü beenden.
- Man kann, wenn man auf dem end-screen ist (win oder lose), wieder zurück ins Menü und ein neues level Spielen.
- Ich habe ein neues Level eingeführt, in welchem sich alle Funktionen leicht und schnell testen lassen.
- Es würden sich leicht beliebig viele Maps einbauen lassen.

-Specialattacke:

- SuperTaube kann jetzt aus jedem Kampf fliehen und die erfolgswahrscheinlichkeit liegt bei ihr nicht bei 80 sondern bei 100%
- OverPower kann jetzt den Gegner schwächen und zieht dem Gegner 2 AP ab (Der Gegner kann nicht unter 1 AP fallen)
- SuperStark kann jetzt dem Gegner 2 LP klauen und bekommt Sie selbst -> seine max LP können nicht übertroffen werden und der Gegner kann mit dieser Attacke nicht getötet werden (nicht unter 1 LP)

- nach jeder Special attacke greift immernoch der Gegner an

## Quellen
- https://im-coder.com/zeile-fuer-zeile-lesen-in-c-und-c.html -> damit ich eine ganze zeile lesen kann
- https://unicode-table.com/de/search/?q=stern -> unicode code für den bonus stern
- https://www.cplusplus.com/reference/chrono/ -> Ich habe nachgeschaut wie ich die zeit richtig einbinden kann (Dokumentation)
- https://stackoverflow.com/questions/39288595/why-not-just-use-random-device -> Warum man nicht nur random_device benutzen soll
- https://docs.microsoft.com/de-de/cpp/cpp/program-termination?view=msvc-160 -> wie kann ich ein Programm beenden

-> alle verwendeten Quelle sind Faktenwissen
