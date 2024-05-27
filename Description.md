Osnovna funkcija uređaja je da izbacuje tabletu u određeno vrijeme koje korisnik unese.
Moguće je unositi vremena za 2 različite tablete. Unos vremena se vrši pomoću 2 tastera i smješta se u strukturu inputs koja se sastoji od rednog broja tablete, sati, minuta i bool varijable koja nam daje informaciju da li je tableta već izbačena. 
Prvi taster (pin 50) služi za povećavanje broja sati ili minuta prilikom unosa, a pritiskom drugog tastera (pin 52) prelazi se na sljedeći unos.
Korisnik prvo unosi vrijeme za prvu tabletu prilikom čega je na displayu koji se nalazi na prednjoj strani uređaja ispisano “Unos 1. tablete” i vrijednost trenutnog unosa.
Korisnik pomoću prvog tastera unese broj sati, zatim pritiskom na drugi taster prelazi na broj minuta, nakon čega putem prvog tastera unosi broj minuta. 
Ponovnim pritiskom na drugi taster unos se završava. Korisniku se opet nudi unos vremena za prvu tabletu ukoliko je potrebno istu tabletu uzimati 2 ili više puta tokom istog dana.
Kada korisnik želi preći na unos druge tablete to će učiniti pritiskom drugog tastera. Postupak je isti za unos vremena za drugu tabletu.
Nakon unosa na displayu će biti ispisano vrijeme i broj tableta koji se nalazi u spremniku. Spremnik za tablete sadrži 6 slotova.
Da bi uređaj izbacio tablete korišteni su stepper motori koji su na Arduino spojeni pomoću Motor Shielda. Za stepper motore je u programu koristena biblioteka <AFMotor>
Na uređaju se nalazi crvena led dioda koja služi za signalizaciju kao i zvučnik koji se nalazi unutar uređaja.
Nakon što uređaj izbaci tabletu u određeno vrijeme, led dioda će da svijetli i zvučnik će se oglašavati, te će na displayu biti ispisano: “Preuzmite tabletu”.
Uređaj neće izbacivati sljedeću tabletu ukoliko osoba nije preuzela već izbačenu.
Tableta se izbacuje u ladicu koja je prislonjena uz taster(pin 48) koji ima zadatak dati informaciju da li je tableta preuzeta kako bi program mogao da nastavi sa radom.
Punjenje spremnika se vrši tako što se pritisne prvi ili drugi taster, u zavisnosti koji spremnik korisnik želi da napuni, time će motor vratiti u početnu poziciju. 
Ukoliko se spremnik isprazni, led dioda će blinkati i zvučnik će se oglašavati dok spremnik ne bude napunjen.
Kako bi uređaj znao tačno vrijeme koristi se Real Time Clock modul, za cije upravljanje se koriste biblioteke <ThreeWire.h> i <RtcDS1302.h>. 
Na Arduino je preko stabilizatora dovedeno 9V za napajanje.
