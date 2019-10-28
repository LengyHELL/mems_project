Ez egy projekt a Miktroelektromechanikai rendszerek órára.
A projektet Hingyi Martin (CGH096) és Lengyel Márk (LNXQYO) készítette.
A projekt magába foglal egy raspberry pi alapú játékkonzolt, amelyen egy saját készítésű tetris játék játszható.

Fájlmagyarázat:
  * /tetris_pi - a tetris játék kódja és fordítási parancsai
  * /boot - raspberry pi rendszerfájlok
  * /.bashrc - módosított raspberry redszerfájl, amely lehetővé teszi a 'mainscript' fájl futtatását bootolás után
  * /mainscript - egy script amely lefut közvetlenül indítás után

A játék az SDL2 fejlesztői könyvtárat használja, amely az alábbi forrás alapján került telepítésre és beállításra:
  * https://gist.github.com/Lokathor/e6fec720b722b8a6f78e399698cae6e4

A képernyő működéséhez szükséges fájlok telepítéséhez:
  * https://learn.adafruit.com/adafruit-pitft-28-inch-resistive-touchscreen-display-raspberry-pi/easy-install-2
