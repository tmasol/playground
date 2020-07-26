/*
Example of using the library MenuBackend to handle multi-level menus:
by wojtekizk ... (wk@warcaby.lh.pl) prepared for the forum majasterkowo.pl
// ------------------------------------------------ ----------------------------------
Description:
Generally create menus based on MenuBackend library is very simple,
If you remember a few rules:
1) The most important is the configuration menu menuSetup function ()
2) Navigating through the menus should be consistent with the diagram menu, ie if
    something submenu, you are looking for the key "to the right" and equivalent "bottom - up"
3) It is for the user to print the map at the keypad.
4) Support for all options to dispose menuUseEvent void function (MenuUseEvent used)
    There plunging while loops or for a while and read in the state's keypad.
    In this loop, modifies the behavior of the utility depending on what press.
    If you press OK it come out of the while loop and actually go back to loop-a.
All the more important issues is indicated quite readable commentary.
*/
// ============= MenuBackend tutorial ================================= ==============
#include "MenuBackend.h" // attach the library
#include <LiquidCrystal.h> // handle the LCD display
// --- Define their own characters for the LCD arrow: down, left, right, the top-down and back ---
uint8_t arrowUpDown[8] = {0x4,0xe,0x15,0x4,0x15,0xe,0x4};
uint8_t arrowDown[8]  = {0x4,0x4,0x4,04,0x15,0xe,0x4};
uint8_t arrowRight[8] = {0x0,0x4,0x2,0x1f,0x2,0x4,0x0};
uint8_t arrowLeft[8] = {0x0,0x4,0x8,0x1f,0x8,0x4,0x0};
uint8_t arrowBack[8] = {0x1,0x1,0x5,0x9,0x1f,0x8,0x4};

LiquidCrystal lcd(8,9,4,5,6,7);    // definicja pinów dla LCD (sprawdź piny w swoim LCD)
volatile int zm =-1;               // to dla kontroli zmiany stanu klawiatury
volatile int x=-1;                 // zmienna pomocnicza
volatile int stan_Analog;          // wartość na wejściu Analogowym dla klawiaturki analogowej
char *Line_1;                      // pierwsza linia wyświetlanego tekstu na LCD
char *Line_2;                      // druga linia wyświetlanego tekstu na LCD


//LiquidCrystal lcd(8,9,4,5,6,7); // Define the pins for the LCD (check the pins in your LCD)
//volatile int zm = -1; // This for a change in the keyboard control
//volatile int x = -1; // Variable secondary
//volatile int stan_Analog; // Analog input value for an analog keypad
//char *Line_1; // First line of the text displayed on the LCD
//char *Line_2; // Second line of text displayed on the LCD
/* Sample menu (similar to the Arduino IDE): --------------------------------------- -----
// We have 5 main options FILE, EDIT, SKETCH, TOOLS, HELP
// DRAFT option and we TOOLS extensive options for level 2 and 3 Menu
// ------------------------------------------------ --------------------------------------------
       FILE
          new
          Open
          Sketchbook
          Examples
          Save
          Save as
          Load
          Exit
       EDIT
          Cut
          Copy
          paste
          Mark
          Find
       SKETCH
          Verify
          Compile
          Import
              EEPROM
              GSM
              SD
              MenuBackend
       TOOLS
           plate
              Arduino Uno
              Leonardo
              Decimila
              Nano
              LilyPad
           reading
              temperature
              COM 2
              COM 15
           Programmer
              USBasp
              AVR ISP
              AVR ISP MKII
       HELP
           How to start
           Environment
           documentation
           About Arduino
--- The following definition of menu options: ------------------------------------------
de facto definition of the constructor for the class object MenuBackend named menu.
Here we define each item. We can do this in 2 ways:
- No use of so-called. shortkey, eg P1 = MenuItem MenuItem ("FILE");
- Or szortkey, ie P1 = MenuItem MenuItem ("FILE", 1);
We have an additional parameter, and thanks to him we will be able to decide what is to be
display on the display. In this example, the parameter identifies shortkey
We nesting level menu. Then, in a fairly simple way by using the arrow
help you in your selection.
*/

void menuUseEvent(MenuUseEvent used)      // funkcja klasy MenuBackend - reAction na wciśnięcie OK
                                          // tutaj właśnie oddajemy menu na rzecz akcji obsługi klawisza OK
{
   Serial.print("wybrano:  "); Serial.println(used.item.getName()); // do testów, potem niepotrzebne
   // --- ponizej kilka przykładów obsługi  opcji -----------
   // przykładowa reAction na wcisnięcie klawisza OK w opcji Otworz :
   if (used.item.getName() == "    Otworz")   // Uwaga - dokładnie taki sam ciąg "    Otworz" jak w menu !!!
                                              // bo przecież getName() pobiera nazwę
      {
        lcd.setCursor(1,0);lcd.print("Otwieram drzwi"); // info 
        digitalWrite(0,HIGH);delay(2000);digitalWrite(0,LOW); // na 2 sekundy pin 0 otrzymał stan wysoki
                                                              // czyli np. otworzyły się drzwi
        lcd.setCursor(1,0);lcd.print("              ");lcd.setCursor(1,0);lcd.print(Line_1); //poprzedni stan LCD
      }
    // A teraz coś ambitniejszego :-), bo przekazujemy sterowanie klawiaturką do innej procedury,
    // w tym przykładzie programik czeka aż ustawisz jakąś temperaturę i po wciśnięciu OK wraca do pętli głównej
      if (used.item.getName() == " Temperatura")   // dokładnie taki sam ciąg " Temperatura"
      {
        int temp=21;                         // przykładowo 21 st. C
        lcd.setCursor(0,0);lcd.write(7);     // wyswietlamy nasz symbol strzałki góra-dół
        lcd.print("              ");lcd.setCursor(1,0);lcd.print("Ust.temp. = "); // tekst dla użytkownika
        lcd.setCursor(13,0);lcd.print(temp); // wyświetlamy akt. temperaturę
        int  Action=-1;delay(1000);         // zmienna pomocnicza, sterująca dla petli while
                                           // jesli nie puścisz klawisza OK w ciągu 1 sek. to powrót do menu    
        while(Action!=4)                   // ta pętla trwa tak długo aż wciśniesz klawisz OK  
         {
           zm=-1; 
           Action=Read_1(0);//delay(300);   // odczyt stanu klawiatury - funkcja Read_1 lub Read_2 lub Read_3
                                            // opis poniżej przy 3 różnych definicjach funkcji Read
           if(zm!=Action)                    // ruszamy do pracy tylko wtedy gdy zmienił sie stan klawiatury
             {
             if (Action==1) {temp++;if(temp>99)temp=99;lcd.setCursor(13,0);lcd.print(temp);delay(300);}
               // jesli Action=1 (czyli wciśnieto klawisz w górę to zwiększono temperaturę
               // ustawiono max próg i wyświetlono obecną temperaturę
             if(Action==2)  {temp--;if(temp<10)temp=10;lcd.setCursor(13,0);lcd.print(temp);delay(300);}
               // jesli Action=2 (czyli wciśnieto klawisz w dół to mniejszono temperaturę
               // ustawiono min próg i wyświetlono obecną temperaturę
             if(Action==4) // jeśli wciśnieto OK 
               {
                 lcd.setCursor(0,0);lcd.print("*Temperatura OK");delay(2000); // pokazujemy OK przez 2 sek.
                 lcd.setCursor(1,0);lcd.print("              "); // czyścimy linię
                 lcd.setCursor(1,0);lcd.print(Line_1);           // odtwarzamy poprzedni stan na LCD
               }
             } 
         } zm=Action;  // aktualizacja zmiennej zm, po to aby reagować tylko na zmiany stanu klawiatury
         // tu WAŻNY MOMENT - kończy się pętla while i zwracamy sterowanie do głównej pętli loop()
      }
// a tutaj obsługa pozostałych opcji :-)  
// ...
// ...
}

// --- Response to pressing ----------------------------------------- ------------------------
void menuChangeEvent (MenuChangeEvent changed) // function class MenuBackend
{
   /* So really it is only here that shortkey useful and is used primarily to enrich the menu
      of arrow symbols, whichever is selected. Everything here is going on is displayed on the LCD.
   */
   int c = changed.to.getShortkey (); // Fetch shortkey (1,2,3, LUB4)
   lcd.clear (); // No comment
   lcd.setCursor (0,0);
   if (c == 1) // if the menu Main contacts (shortkey = 1) are:
     {
     lcd.write (3); // Left arrow
     strcpy (Line_1, changed.to.getName ()); // Create a string in the first line
     lcd.print (Line_1); // Display it
     lcd.setCursor (15,0); lcd.write (4); // Right arrow
     lcd.setCursor (0,1); lcd.write (5); // Down arrow
     lcd.setCursor (15,1); lcd.write (5); // Down arrow
     }
     if (c == 2) // if the submenu for the child - (shortkey = 2) are:
     {
     lcd.print ("*"); // Draw a star
     strcpy (Line_2, changed.to.getName ()); // Create a string in the first line
     lcd.print (Line_1); // Display it
     lcd.setCursor (15,0); lcd.print ("*"); // Star
     lcd.setCursor (0,1); lcd.write (6); // Second line and arrow return (arrowBack)
     lcd.print (changed.to.getName ()); // Display name of "child"
     lcd.setCursor (15,1); lcd.write (7); // Arrow up and down
     }
     if (c == 3) // if the child has a child - (shortkey = 3) are:
     {
     lcd.print ("*"); // Star
     strcpy (Line_2, changed.to.getName ()); // Copy the files. the name of the menu options to the variable line 2
     lcd.print (Line_1); // And display the first line of
     lcd.setCursor (15,0); lcd.print ("*"); // Star
     lcd.setCursor (0,1); lcd.write (6); // Second line and arrow arrowBack
     lcd.print (changed.to.getName ()); // Display the grandson of the second line
     lcd.setCursor (15,1); lcd.write (4); // Right arrow as they are the grandchildren
     }
    
     if (c == 4) // if this grandson (shortkey = 4) are:
     {
     lcd.print ("*"); // Gwaizdka
     lcd.print (Line_2); // Display the first line of the child (or parent grandchild)
     lcd.setCursor (15,0); lcd.print ("*"); // Gwaizdka
     lcd.setCursor (0,1); lcd.write (6); // Second line and arrow arrowBack
     lcd.print (changed.to.getName ()); // Display grandson
     lcd.setCursor (15,1); lcd.write (7); // Arrow up and down
     }
}


// --- Create all menu options: ---------------------------------------
// Create a de facto class MenuItem objects that inherit from the class MenuBackend
MenuBackend menu = MenuBackend(menuUseEvent,menuChangeEvent); // konstruktor 
   //                        ("                ")
   MenuItem P1 =  MenuItem("     PLIK",1);
      MenuItem P11 = MenuItem("     Nowy",2);
      MenuItem P12 = MenuItem("    Otworz",2);
      MenuItem P13 = MenuItem("  Szkicownik",2);
      MenuItem P14 = MenuItem("  Przyklady",2);
      MenuItem P15 = MenuItem("    Zapisz",2);
      MenuItem P16 = MenuItem(" Zapisz jako..",2);
      MenuItem P17 = MenuItem("   Zaladuj",2);
      MenuItem P18 = MenuItem("     Exit",2);
      
   MenuItem P2 = MenuItem("    EDYCJA",1);
      MenuItem P21 = MenuItem("    Wytnij",2);
      MenuItem P22 = MenuItem("    Kopiuj",2);
      MenuItem P23 = MenuItem("     Wklej",2);
      MenuItem P24 = MenuItem("    Zaznacz",2);
      MenuItem P25 = MenuItem("    Znajdz",2);
   
   MenuItem P3 = MenuItem("     SZKIC",1);
      MenuItem P31 = MenuItem("   Weryfikuj",2);
      MenuItem P32 = MenuItem("   Kompiluj",2);
      MenuItem P33 = MenuItem("   Importuj",3);
          MenuItem P331 = MenuItem(" Menu Backend",4);
          MenuItem P332 = MenuItem("    EEPROM",4);
          MenuItem P333 = MenuItem("   KeyBoard",4);
          MenuItem P334 = MenuItem("      GSM",4);
   
   MenuItem P4 = MenuItem("  NARZEDZIA",1);
      MenuItem P41 = MenuItem("    Plytka",3);
          MenuItem P411 = MenuItem("  Arduino Uno",4);
          MenuItem P412 = MenuItem("   Leonardo",4);
          MenuItem P413 = MenuItem("   Decimila",4);
          MenuItem P414 = MenuItem("   LilyPad",4);
          MenuItem P415 = MenuItem("     Nano",4);
      MenuItem P42 = MenuItem("    Odczyt",3);  
          MenuItem P421 = MenuItem(" Temperatura",4);
          MenuItem P422 = MenuItem("     COM 2",4);
          MenuItem P423 = MenuItem("    COM 13",4);
      MenuItem P43 = MenuItem("  Programator",3);  
          MenuItem P431 = MenuItem("    USBasp",4);
          MenuItem P432 = MenuItem("    AVR ISP",4);
          MenuItem P433 = MenuItem(" AVR ISP MK II",4);    
      
      MenuItem P5 = MenuItem("     POMOC",1);
          MenuItem P51 = MenuItem("  Jak zaczac",2);
          MenuItem P52 = MenuItem("  Srodowisko",2);
          MenuItem P53 = MenuItem(" Dokumentacja",2);
          MenuItem P54 = MenuItem("  O Arduino",2);
/* --- Now position the menu (according to the setting specified above) ------------
add - adds vertical addRight - adds a level to the right, to the left adds addLeft
*/
void menuSetup() // function class MenuBackend
{
       menu.getRoot().add(P1); // Set the root menu, which is the first option
       P1.add(P11); // FILE parent has a child new so adds them vertically
         P11.add(P12); P11.addLeft(P1); // Below is a New Open so also in the vertical
                                        // A addLeft (P1) will allow us to return the key to the left to FILE
         P12.add (P13); P12.addLeft (P1); // Analogously we do with all podopcjami for FILE
         P13.add (P14); P13.addLeft (P1);
         P14.add (P15); P14.addLeft (P1);
         P15.add (P16); P15.addLeft (P1);
         P16.add (P17); P16.addLeft (P1);
         P17.add (P18); P17.addLeft (P1);
         P18.addLeft (P1); P18.add (P11); // Here we close the loop and back to the first suboption
                                        // Thanks to this we do not need to go back to the top of the cumbersome
                                        // Clicking the button Up
                                  
       P1.addRight (P2); // Right for the EDIT FILE
       P2.add (P21); // EDIT parent has a child Cut
         P21.add (P22); P21.addLeft (P2); // Below is Cut Copy
         P22.add (P23); P22.addLeft (P2); // Similarly for all the suboptions
         P23.add (P24); P23.addLeft (P2);
         P24.add (P25); P24.addLeft (P2);
         P25.addLeft (P2); P25.add (P21); // And loop closure, and possibly back to the first option
       P2.addRight (P3); // To the right of the SKETCH EDITION
       P3.add (P31); // Parent has a child Verify SKETCH
         P31.add (P32); P31.addLeft (P3); // Verify below is Compile
         P32.add (P33); P32.addLeft (P3); // Below is compile Import
         P33.addRight (P331); // And here the child Import no longer own child MenuBackend
                                        // Add the right, because if they gave less than it would have done
                                        // Another child for SKETCH, and the project is otherwise
           P331.add (P332); P331.addLeft (P33); // Below is MenuBackend EEPROM
           P332.add (P333); P332.addLeft (P33); // We deal similarly
           P333.add (P334); P333.addLeft (P33);
           P334.addLeft (P33); P334.add (P331);
         P33.addLeft (P3); P33.add (P31); // Close the loop and possibly back to the first option
       P3.addRight (P4); // On the same ....
       P4.add (P41);
         P41.addRight (P411); // Another child who has a child :-)
           P411.add (P412); P411.addLeft (P41);
           P412.add (P413); P412.addLeft (P41);
           P413.add (P414); P413.addLeft (P41);
           P414.add (P415); P414.addLeft (P41);
           P415.addLeft (P41); P415.add (P411); // Close the loop, etc. ..
         P41.addLeft (P4);
         P41.add (P42);
         P42.addRight (P421);
           P421.add (P422); P421.addLeft (P42);
           P422.add (P423); P422.addLeft (P42);
           P423.addLeft (P42); P423.add (P421); // Loop closure, etc. ..
         P42.addLeft (P4);
         P42.add (P43);
         P43.addRight (P431);
           P431.add (P432); P431.addLeft (P43);
           P432.add (P433); P432.addLeft (P43);
           P433.addLeft (P43); P433.add (P431); // Loop closure, etc. ..
         P43.addLeft (P4); P43.add (P41);
         P4.addRight (P5);
       P5.add(P51);
         P51.add(P52); P51.addLeft(P5);
         P52.add(P53); P52.addLeft(P5);
         P53.add(P54); P53.addLeft(P5);
         P54.addLeft(P5); P54.add(P51); // Loop closure
       P5.addRight(P1); // Main loop closure, ie, the horizontal - the AID is FILE
}
// ----------- Phew ... finally :-) ----------------------------- ------------------------------------------
// ----------- uff... nareszcie :-) -----------------------------------------------------------------------

/* --- Hereinbelow feature that senses the state of the keyboard ---------------------------------------- ---
I prepared three different versions:
1) for analog keypad with shield LCDanalogKey company DFRobot
2) for the joystick (2 analog inputs and 1 digital pin)
    Note for this version option, you must add the function setup configuration for the pin, like this:
    pinMode (1, INPUT); digitalWrite (1, HIGH);
3) for the 5-five individual buttons (need 5 digital pins)
    Note for this version option, you must add the function setup configuration for the pins, like this:
    pinMode (1, INPUT); digitalWrite (1, HIGH);
    pinMode (2, INPUT); digitalWrite (2, HIGH);
    pinMode (3, INPUT); digitalWrite (3, HIGH);
    pinMode (11, INPUT); digitalWrite (11, HIGH);
    pinMode (12, INPUT); digitalWrite (12, HIGH);
*/
// --- Version for keyboard 5-button mouse DFRobot ------------------------------------- -
volatile int Read_1(int analog)
{
    int stan_Analog = analogRead (analog); delay (30) ;// Serial.println (stan_Analog);
    if (stan_Analog> 1000) return -1; // For values ​​outside the range
    if (stan_Analog <50) return 0; // Right
    if (stan_Analog <150) return 1; // To the top
    if (stan_Analog <300) return 2; // Down
    if (stan_Analog <500) return 3; // Left
    if (stan_Analog <700) return 4; // OK
    return -1; // Do not pressed
}
// --- Version joystick (2 + pin input analog digital -------------------------------
int Read_2(int poziom, int pion, int pinD)
{
// Level - no analog input is connected to the shift lever joystick for movement left-right
// Vertical - no analog input is connected to the shift lever joystick for movement up and down
// Pind - no digital pin that is connected to the OK button on the joystick
int stan1= analogRead(pion); {delay(60);if(stan1>0)stan1=(stan1+50)/1024+1;}  
   int stan2= analogRead(poziom); {delay(60);if(stan2>0)stan2=(stan2+50)/1024+1;} 
   int stanD=digitalRead(pinD);
   if(stanD==LOW) return 4;           // OK 
   if(stan1==0) return 2;             // w dĂłĹ‚
   if(stan1==2) return 1;             // do gĂłry
   if(stan2==0) return 3;             // w lewo
   if(stan2==2) return 0;             // w prawo
   return -1;                         // nic nie wcisnieto
}
// --- Version for 5 five number keys -------------------------------------- ------------
// For example if you are using pins: 1,2,3,11 and 12 are calling: Read_2 (1,2,3,11,12)
int Read_3(int up, int left, int ok, int right,int down)
// up - no digital pin that is connected to the up
// Left - no digital pin that is connected to the left buttons
// Ok - no digital pin that is connected to the OK
// Right - no digital pin that is connected to the right buttons
// Lower - no digital pin that is connected to the buttons down
{
if (digitalRead (up) == LOW) return 1;
if (digitalRead (left) == LOW) return 3;
if (digitalRead (ok) == LOW) return 4;
if (digitalRead (right) == LOW) return 0;
if (digitalRead (down) == LOW) return 2;
return -1;
}
// ================================================ ============================================
//
void setup ()
{
   Line_1 = new char [16]; // Initialize a pointer to a dynamic text
   Line_2 = new char [16]; // Is VERY IMPORTANT because dynamic indicator must indicate
                         // Pre-defined location in memory. If we did not do
                         // This sooner or later applet could jump in indefinite
                         // Close the memory area, which can result in irreversible consequences
                         // Including switching Fuse Bits!
                         // Please be careful at all dynamic indicators, SUCH GOOD ADVICE :-)
   Serial.begin (9600); // Initialize serial, mainly for test
   lcd.begin (16, 2); // Initialize the LCD
   lcd.createChar (3, arrowLeft); // Create a memory of your LCD 5 characters for arrows
   lcd.createChar (4, arrowRight);
   lcd.createChar (5, arrowDown);
   lcd.createChar (6, arrowBack);
   lcd.createChar (7, arrowUpDown);
   /* Here exemplary digital pins for the 3 versions feature Read_3 (1,2,3,11,12)
    pinMode (1, INPUT); digitalWrite (1, HIGH);
    pinMode (2, INPUT); digitalWrite (2, HIGH);
    pinMode (3, INPUT); digitalWrite (3, HIGH);
    pinMode (11, INPUT); digitalWrite (11, HIGH);
    pinMode (12, INPUT); digitalWrite (12, HIGH);
   */
   pinMode (0, OUTPUT); digitalWrite (0, LOW); // For testing
   menuSetup (); // Function MenuBackend class - there really are creating our menu
   menu.moveDown (); // Go to the first option - FILE, moveDown because originally we were at the root
                         // It's like in the Avatar tree roots grow up :-)
}
// --- And it's time for neverending story :-) ------------------------------------ --------
void loop ()
{
   x=Read_1(0);delay(30);   // Read the state of the keyboard:
   /*
   I use Read_1 function () because I just Keyboard plugged into A0
   If you have a different keypads that use the Read_2 or Read_3 - see description
   In addition, you must remember that in the functions obsługo OK button - menuUseEvent (MenuUseEvent used)
   Also you need to use the appropriate version of the function read!
   */
   if(zm!=x)   // if it was the change in the state are:
     {
       switch(x) // check to see what was pressed
       {
       case 0: menu.moveRight(); break; // If pressed, move it in the right menu to the right
       case 1: menu.moveUp(); break; // Menu to top
       case 2: menu.moveDown(); break; // Menu Down
       case 3: menu.moveLeft(); break; // Menu to the left
       case 4: menu.use(); break; // Pressed OK, so jump to the function menuUseEvent (MenuUseEvend used)
                                           // This function is just serve our menu, check here
                                           // Which option is selected, and here we create code to handle the event.
       }
     } zm = x; // Assign the value of x variable amended so that the long pressing the
                                           // Same key did not result in the re-generation event.
                                           // Program responds to a change in the keyboard.
}
// === END ============================================ ===============
